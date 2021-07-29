#!/home/xnli/tools/python3.6/bin/python3.6
"""
This file can generate ($module)_classVtable.py by parse the ($module)_structures.h ($module)_vtable_functions.h.
Please ask xiaoyu if you have any question.
"""

import os
import sys
import re
import copy
import logging

LOG_FORMAT = "%(asctime)s - %(levelname)s - %(message)s"
logging.basicConfig(format = LOG_FORMAT, level = logging.DEBUG)

class patterns():
  def __init__(self):
    self.variable_pattern = re.compile(r'\s+(const )?([\w:]*)(\<.*\>\w*)?\s*([*]*)\s([^=:\}]*?)_0x([0-9a-fA-F]*?)(\[[0-9a-fA-Fx]+\])?;')
    # disp: [0][0]const flag  [0][1]var type  [0][2]tmplate class type  [0][3]ptr  [0][4]var name  [0][5]var offset [0][6]var size
    # e.g.  line = "  const std::vector<std::string>* names_0x28[58]"
    # [0][0]=const  [0][1]=std::vector  [0][2]=std::string  [0][3]=*  [0][4]=names [0][5]=28  [0][6]=[58]

    self.class_pattern = re.compile(r'^\s*class\s+([\w:]+)\s*{')
    self.typedef = re.compile(r'typedef uint32_t ([\w:]+);')
    self.comment_pattern = re.compile(r'^\s*\/\/(.*)')


class Trans2Vtable:
  def __init__(self, patternCfg, root_path, module):
    self.pattern = patternCfg
    self.root = root_path
    self.struct_file = "%s_structures.h" % module  # librdi_advchipscopeimpl_structures
    self.vfuns = "%s_vtable_functions.h" % module  # librdi_advchipscopeimpl_vtable_functions
    self.allfuns = "%s_vtable.h" % module # librdi_advchipscopeimpl_vtable
    self.allEmptyClassFile = "allEmptyClass.h"

    self.allClassSet = set()
    self.allEnumType = set()
    self.finalClassVtableMap = {}
    self.lines = []

    self.offset_dict = {"std::vector": 0x18, "std::string": 0x20, "std::vector_bool": 0x28,
            "std::map": 0x30, "std::set": 0x30, "std::multimap": 0x30, 
            "std::unordered_map": 0x38, "std::unordered_set": 0x38, "std::shared_ptr": 0x10,
            "std::unordered_multimap": 0x38, "void": 0x8, "float": 0x4, "double": 0x8,
            "uint8_t": 0x1, "uint16_t": 0x2, "uint32_t": 0x4, "uint64_t": 0x8,
            "int8_t": 0x1, "int16_t": 0x2, "int32_t": 0x4, "int64_t": 0x8, "int": 0x4, 
            "short": 0x2, "long": 0x4, "long long": 0x8, "bool": 0x1, "char": 0x1, "unsigned": 1e3,
            "pthread_t": 1e3, "struct": 1e3, " ": 1e3}


  def loadEmptyFile(self):
    with open(self.allEmptyClassFile, 'r') as emptyFile:
      for line in emptyFile:
        class_match = self.pattern.class_pattern.findall(line)
        if len(class_match) > 0: self.allClassSet.add(class_match[0])
        type_match = self.pattern.typedef.findall(line)
        if len(type_match) > 0: self.allEnumType.add(type_match[0])


  def formatLine(self, line):
    var_match = self.pattern.variable_pattern.findall(line)
    try:
      assert(len(var_match) > 0)
    except:
      logging.debug("variable can not matched", end = "")
      logging.debug(line)
    #else:
    #  print(var_match)
    if var_match[0][1] not in self.offset_dict:
      self.allClassSet.add(var_match[0][1])
    return var_match
  

  def tmp2line(self, tmpparts, linecache):
    # rewrite func_line
    offset_minus = -1
    offset = 0
    linecache.append("class %s {\n" %self.className)
    for i, parts in enumerate(tmpparts):
      vline = "  %s%s %s_0x%s%s; //%s\n" % (parts[0][1], parts[0][3], parts[0][4], parts[0][5], parts[0][6], parts[0][2])
      linecache.append(vline)
      if (i == 0):
        offset = int(parts[0][5], 16)
      elif (i > 0):
        offset_minus = offset
        offset = int(parts[0][5], 16)
      if (offset == offset_minus):
        logging.debug("src file variable:\n%s has overlaped" %vline)
        if i + 1 < len(tmpparts):
          res_offset = int(tmpparts[i+1][0][5], 16) - offset
          
          if (parts[0][3] == ""):
            if (parts[0][1] in self.offset_dict):
              res = self.offset_dict[parts[0][1]]
            else:
              logging.warning("variable type is error!!")
              res = 0x8
          else:
            res = 0x8
          if (res == res_offset):
            del(linecache[-1])
          else:
            del(linecache[-2])

    linecache.append("}; // end of class %s\n" %self.className)
    return linecache


  def loadLines(self):
    linecache = []
    templines = []  # store the split part of line then load
    inClass = 0
    with open(os.path.join(self.root, self.struct_file), 'r') as f:
      for line in f:
        if len(self.pattern.comment_pattern.findall(line)) > 0: continue
        if inClass:
          if line[:2] == "};":   # end of class
            linecache = self.tmp2line(templines, linecache)
            templines = []
            inClass = 0
          else:                 # format lines
            templines.append(self.formatLine(line))
        else:
          class_match = self.pattern.class_pattern.findall(line)
          if len(class_match) > 0:
            inClass = 1
            self.className = class_match[0]
            if self.className not in self.allClassSet:
              self.allClassSet.add(self.className)
    self.lines = linecache


  def writefile(self):
    output_vtable_file = module + "_classVtable.h"
    with open(output_vtable_file, 'w+') as f:
      f.write("#include \"allEmptyClass.h\"\n")
      f.write("#include \"common_class.h\"\n")
      for line in self.lines:
        f.write(line)

      with open(os.path.join(self.root, self.vfuns), 'r') as vf:
        for vline in vf:
          f.write(vline)

    emptyFile = open(self.allEmptyClassFile, mode="w+")
    emptyFile.write("//This file predefines the classes in all structure.h and vfunction.h\n")
    emptyList = list(self.allClassSet)
    emptyList.sort()
    for empty_key in emptyList:
      emptyFile.write("class %s {\n" % empty_key)
      emptyFile.write("};\n")
    enumTypeList = list(self.allEnumType)
    enumTypeList.sort()
    for EType in enumTypeList:
      emptyFile.write("typedef uint32_t %s;\n" % EType)

  def run(self):
    self.loadEmptyFile()
    self.loadLines()
    self.writefile()

if __name__ == "__main__":
  # set path and transform the struct file to classVtable.h
  if len(sys.argv) < 2:
    print("This script can load the first argv para as a path, and load second argv para as $module_Vtable.h.")
    print("The classVtable include EmptyClass.h, common_class.h, vtable and vfuns.")
    print("usage: ./generateModuleVtable.py $dir_path $module_name")
    print("e.g. ./generateModuleVtable.py advchip librdi_advchipscopeimpl")
    print("The generate will be at the current path default.")

  root_path = sys.argv[1]
  module = sys.argv[2]

  mypattern = patterns()
  transFile = Trans2Vtable(mypattern, root_path, module)
  transFile.run()
