#!/home/xnli/tools/python3.6/bin/python3.6
"""
This script is used to generate header file named myclass.h and source file named myclass.cc.
You can only provide the classList and module name that you want.
Please ask xiaoyu if you have any question.
"""

import os
import sys
import re
import copy
import logging

LOG_FORMAT = "%(asctime)s - %(levelname)s - %(message)s"
logging.basicConfig(format = LOG_FORMAT, level = logging.DEBUG)

def writeHfileHeader(output_h_file):
  output_h_file.write("/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil  -*- */\n")
  output_h_file.write("/* vim: set tabstop=2 softtabstop=2 shiftwidth=2 expandtab: */\n")
  output_h_file.write("\n")
  output_h_file.write("//============================================================================\n")
  output_h_file.write("// Copyright (c) 2017, All Right Reserved, XXXX\n")
  output_h_file.write("//\n")
  output_h_file.write("// file:      XXXXX.h\n")
  output_h_file.write("// author:    XXXXXX\n")
  output_h_file.write("// purpose:   XXXXX\n")
  output_h_file.write("// revision history:\n")
  output_h_file.write("// 2021/XX/XX initial version\n")
  output_h_file.write("//============================================================================\n")
  output_h_file.write("\n")
  output_h_file.write("#ifndef XXXXXXXXXXXXXXXXXXXXXX\n")
  output_h_file.write("#define XXXXXXXXXXXXXXXXXXXXXX\n")
  output_h_file.write("\n")
  output_h_file.write("#include <fstream>\n")
  output_h_file.write("#include <stdint.h>\n")
  output_h_file.write("#include <cstddef>\n")
  output_h_file.write("#include <vector>\n")
  output_h_file.write("#include <assert.h>\n")
  output_h_file.write("#include \"common/common_utility.h\"\n")
  output_h_file.write("\n")
  output_h_file.write("namespace nimbus {\n")
  output_h_file.write("\n")

def writeHfileTail(output_h_file):
  output_h_file.write("\n")
  output_h_file.write("\n")
  output_h_file.write("} // namespace nimbus\n")
  output_h_file.write("\n")
  output_h_file.write("#endif\n")

def writeCfileHeader(output_cc_file):
  output_cc_file.write("/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil  -*- */\n")
  output_cc_file.write("/* vim: set tabstop=2 softtabstop=2 shiftwidth=2 expandtab: */\n")
  output_cc_file.write("\n")
  output_cc_file.write("//============================================================================\n")
  output_cc_file.write("// Copyright (c) 2017, All Right Reserved, XXX\n")
  output_cc_file.write("//\n")
  output_cc_file.write("// file:      XXXXX.h\n")
  output_cc_file.write("// author:    XXXXXXX\n")
  output_cc_file.write("// purpose:   XXXXXXX\n")
  output_cc_file.write("// revision history:\n")
  output_cc_file.write("// 2021/XX/XX initial version\n")
  output_cc_file.write("//============================================================================\n")
  output_cc_file.write("\n")
  output_cc_file.write("#include \"XXXXXXX.h\"\n")
  output_cc_file.write("\n")
  output_cc_file.write("namespace nimbus {\n")
  output_cc_file.write("\n")

def writeCfileTail(output_cc_file):
  output_cc_file.write("\n")
  output_cc_file.write("\n")
  output_cc_file.write("} // namespace nimbus\n")
  output_cc_file.write("\n")

def replaceUselessPart(funcParts):
    list_pattern = re.compile(r'.*(std::__cxx11::list<(.*), std::allocator<(.*)>>).*')  # e.g std::__cxx11::list<int, std::allocator<int>>  transform to std::list<int>
    hstvec_pattern = re.compile(r'.*(HSTVector<([^\>]+), std::allocator<([^\>]+)>>).*')  # e.g HSTVector<HDDCPort *, std::allocator<HDDCPort *>>  transform to std::vector<HDDCPort *>
    hstset_pattern = re.compile(r'.*(HSTSet<([\w:\s\*\<\>]+), ([\w:\s\*\<\>]+), std::allocator<([\w:\s\*\<\>]+)>>).*')
    hstmap_pattern = re.compile(r'.*(HSTMap<([\w:\s\*\<\>]+), ([\w:\s\*\<\>]+), std::less<([\w:\s\*\<\>]+)>, std::allocator<([\w:\s\*\<\>]+)>>).*')
    """  
    args :
    # funcParts[0] is className or scope. In virtual function, we only care the case scope == className
    # funcParts[1] is function name, it need to delete abi::cxx11
    # funcParts[2] is variable, it need to delete the cxx11 ect. (std::string, and std::list)
    # funcParts[3] is const flag
    # funcParts[4] is common info
    """
    funcParts.append("") # add common info
    funcParts[1] = funcParts[1].replace("[abi:cxx11]", "")
    funcParts[2] = funcParts[2].replace("void", "")
    funcParts[2] = funcParts[2].replace("64u", "uint64_t")
    funcParts[3] = " " + funcParts[3] if funcParts[3] == "const" else ""
    list_match = list_pattern.findall(funcParts[2])
    hstvec_match = hstvec_pattern.findall(funcParts[2])
    if len(list_match) > 0:
      funcParts[2] = funcParts[2].replace(list_match[0][0], list_match[0][1])
    if len(hstvec_match) > 0:
      funcParts[2] = funcParts[2].replace(hstvec_match[0][0], "std::vector<%s>" % hstvec_match[0][1])
    funcParts[2] = funcParts[2].replace("HSTVector&<std::string, std::allocator<std::allocator<char>>>", "std::vector<std::string>")
    hstset_match = hstset_pattern.findall(funcParts[2])
    hstmap_match = hstmap_pattern.findall(funcParts[2])
    if len(hstset_match) > 0:
      funcParts[2] = funcParts[2].replace(hstset_match[0][0], "std::set<%s>" % hstset_match[0][1])
    if len(hstmap_match) > 0:
      funcParts[2] = funcParts[2].replace(hstmap_match[0][0], "std::map<%s, %s>" % (hstmap_match[0][1], hstmap_match[0][2]))
    return funcParts


def addValueInMap(key, val, mymap):
  mymap.setdefault(key, [])
  mymap[key].append(val)
  return mymap


class patterns:
  def __init__(self):
    self.vtable_pattern = re.compile(r'^vtable\s+\w+\s+([\w:]+)\s+{')  # vtable 0x38e6b0 HEXError {
    self.vfunctn_pattern = re.compile(r'\s+vfunctn:\s+\w+\s+->\s+\w+\s+([\w:]+)::([^:]*)\((.*)\)(\w*)')  #  vfunctn: 0x38e6d0 -> 0x3985c0 HEXAll::what(void)const
    self.vspecial_func_pattern = re.compile(r'\s+vfunctn:\s+\w+\s+->\s+\w+\s+(\w+)')  # e.g. sub_xxxx

    self.title_pattern1 = re.compile(r'^typeinfo\s+\w+\s+([\w:]+)\s+{')
    self.title_pattern2 = re.compile(r'^typeinfo\s+([\w:]+)\s+with\s+NoTypeInfoDef\s+{')
    self.base_pattern = re.compile(r'\s+typedef:.*\`typeinfo for\'([\w:]+)')  #  typedef: 0x38e298 -> 0x398b30 `typeinfo for'HEXAll ----- class HEXError : public HEXALL
    self.functn_pattern = re.compile(r'\s+function:\s+\w+\s+([\w:]+)::([^:]*)\((.*)\)(\w*)')

    self.class_pattern = re.compile(r'^\s*class\s+([\w:]+)\s*{')
    self.comment_pattern = re.compile(r'^\s*\/\/(.*)')
    self.variable_pattern = re.compile(r'\s+(const )?([\w:]*)(\<.*\>\w*)?\s*([*]*)\s([^=:\}]*?)_0x([0-9a-fA-F]*?)(\[[0-9a-fA-Fx]+\])?;')


class genClass:
  def __init__(self, patternCfg, moduleDir, module):
    self.pattern = patternCfg
    self.rootpath = moduleDir
    self.struct_file = "%s_structures.h" % module  # librdi_advchipscopeimpl_structures
    self.allfuns = "%s_vtable.h" % module # librdi_advchipscopeimpl_vtable
    self.heritMap = {}  # the structure is a tree, so key is baseClass, value is heritClass
    self.myFatherMap = {}  # <key, value> is <thisClass, list(fatherClasses)> 
    self.varsMap = {}
    self.commFunsMap = {}
    self.vFunsMap = {}
    self.funIdNotInCfile = {}
    self.relatedClass = set()

    # utils
    self.offset_dict = {"std::vector": 0x18, "std::string": 0x20, "std::vector_bool": 0x28,
                  "std::map": 0x30, "std::set": 0x30, "std::multimap": 0x30, 
                  "std::unordered_map": 0x38, "std::unordered_set": 0x38, "std::shared_ptr": 0x10,
                  "std::unordered_multimap": 0x38, "void": 0x8, "float": 0x4, "double": 0x8,
                  "uint8_t": 0x1, "uint16_t": 0x2, "uint32_t": 0x4, "uint64_t": 0x8,
                  "int8_t": 0x1, "int16_t": 0x2, "int32_t": 0x4, "int64_t": 0x8, "int": 0x4, 
                  "short": 0x2, "long": 0x4, "long long": 0x8, "bool": 0x1, "char": 0x1,
                  "unsigned": 1e3, "pthread_t": 1e3, "struct": 1e3, " ": 1e3, "UHashSet": 0x38}


  def loadOriginalFuns(self, classList):
    inVClass, inClass = False, False
    curClass = ""
    v_func_arr = []
    v_spec_func = []
    func_arr = []

    with open(os.path.join(self.rootpath, self.allfuns)) as funs_file:
      for i, line in enumerate(funs_file):
        line = line.replace("std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>", "std::string")
        if inVClass :
          assert(curClass != "")
          if line == "}\n": 
            self.vFunsMap[curClass] = copy.copy(v_func_arr)
            inVClass, curClass, v_func_arr = False, "", []
            continue
          line = line.replace("[abi:cxx11]", "")
          vfunc_match = self.pattern.vfunctn_pattern.findall(line)
          vspecial_match = self.pattern.vspecial_func_pattern.findall(line)
          if len(vfunc_match) > 0:
            vfunc = list(vfunc_match[0])
            v_func_arr.append(replaceUselessPart(vfunc))
          elif len(vspecial_match) > 0:
            spec_fun_part = [curClass, vspecial_match[0], "", "", ""]
            v_func_arr.append(spec_fun_part)
        elif inClass :
          assert(curClass != "")
          if line == "}\n":
            self.commFunsMap[curClass] = copy.copy(func_arr)
            inClass, curClass, func_arr = False, "", []
            continue
          base_match = self.pattern.base_pattern.findall(line)
          func_match = self.pattern.functn_pattern.findall(line)
          if len(base_match) > 0:
            self.heritMap = addValueInMap(base_match[0], curClass, self.heritMap)
            self.myFatherMap = addValueInMap(curClass, base_match[0], self.myFatherMap)
          elif len(func_match) > 0:
            func = list(func_match[0])
            func_arr.append(replaceUselessPart(func))
            
        # entrance of func block
        vclass_match = self.pattern.vtable_pattern.findall(line)
        if len(vclass_match) > 0:
          inVClass, curClass = True, vclass_match[0]
          if curClass in classList:
            self.relatedClass.add(curClass)
          continue
        class_match1 = self.pattern.title_pattern1.findall(line)
        if len(class_match1) > 0:
          inClass, curClass = True, class_match1[0]
          if curClass in classList:
            self.relatedClass.add(curClass)
          continue
        class_match2 = self.pattern.title_pattern2.findall(line)
        if len(class_match2) > 0:
          inClass, curClass = True, class_match2[0]
          if curClass in classList:
            self.relatedClass.add(curClass)
          continue

    def addbase2related(class_key, relatedMap):
      if class_key in self.myFatherMap:
        bases = self.myFatherMap[class_key]
        for base in bases:
          relatedMap.add(base)
          relatedMap = addbase2related(base, relatedMap)
      return relatedMap

    for class_key in classList:
      self.relatedClass = addbase2related(class_key, self.relatedClass)
      if class_key in self.myFatherMap:
        bases = self.myFatherMap[class_key]
        for base in bases:
          for cousin in self.heritMap[base]:
            self.relatedClass.add(cousin)

    for class_key in list(self.commFunsMap.keys()):
      if class_key not in self.relatedClass:
        del self.commFunsMap[class_key]

    for class_key in list(self.vFunsMap.keys()):
      if class_key not in self.relatedClass:
        del self.vFunsMap[class_key]

  
  def formatLine(self, className, line):
    var_match = self.pattern.variable_pattern.findall(line)
    try:
      assert(len(var_match) > 0)
    except:
      logging.debug("variable can not matched", end = "")
      logging.debug(line)
    var_match = list(var_match[0])
    className = className.replace("::", "_")
    var_match[4] = var_match[4][len(className)+1:]
    var_match[1] = var_match[1].replace("HSTVector", "std::vector")
    return var_match

  def loadStructVars(self):
    varscache = []
    inClass = False
    curClass = ""
    with open(os.path.join(self.rootpath, self.struct_file), 'r') as file_vars:
      for line in file_vars:
        if len(self.pattern.comment_pattern.findall(line)) > 0: continue
        if inClass:
          assert(curClass != "")
          if line[:2] == "};":   # end of class
            self.varsMap[curClass] = copy.copy(varscache)
            inClass, varscache, curClass = False, [], ""
          else:                 # format lines
            varscache.append(self.formatLine(curClass, line))
        else:
          class_match = self.pattern.class_pattern.findall(line)
          if len(class_match) > 0:
            curClass = class_match[0]
            if curClass in self.relatedClass:
              inClass = True

  def coverBaseVars(self, classList):
    for class_key, vars_cache in self.varsMap.items():
      if class_key in self.myFatherMap:
        new_vars_cache = []
        lastOffset = 0
        for base in self.myFatherMap[class_key]:
          if base not in self.varsMap:
            if class_key in classList:
              logging.debug("The base class of class %s is not in $module_structure.h, please check this class members manually." % class_key)
            continue
          base_vars = self.varsMap[base]
          if len(base_vars) == 0:
            continue
          if base_vars[-1][3] == "*":
            lastOffset += int(base_vars[-1][5], 16) + 0x8
          else:
            lastOffset += int(base_vars[-1][5], 16) + self.offset_dict[base_vars[-1][1]]
        if lastOffset == 0: continue
        for var in vars_cache:
          curOffset = int(var[5], 16)
          if curOffset >= lastOffset:
            new_vars_cache.append(var)
        self.varsMap[class_key] = new_vars_cache
  
  def funNameNotSpecial(self, part):
    if (part[1][:4] == "sub_" or part[1] == "dword_0" or part[1][:8] == "nullsub_"):
      return False
    else:
      return True

  def searchAndReplace(self, className, idx, child_class, base_class):
    found_part = []
    base_has_replaced = False
    for base in base_class:
      cousin_class = self.heritMap[base]
      for cousin in cousin_class:
        if cousin == className: continue
        try:
          func_part = self.vFunsMap[cousin][idx]
          if (self.funNameNotSpecial(func_part)):
            self.vFunsMap[className][idx][4] = " // %s TODO" % self.vFunsMap[className][idx][1]
            if self.vFunsMap[className][idx][1].find("nullsub") != -1:
              self.vFunsMap[className][idx][4] += " maybe empty function"
            self.vFunsMap[className][idx][1:3] = func_part[1:3]
            base_has_replaced = True
            break
        except LookupError:
          logging.error("cousin class not exist or idx is oevrflow")
          pass
    if not base_has_replaced:
      for child in child_class:
        try:
          func_part = self.vFunsMap[child][idx]
          if func_part[1][0] == "~":
            self.vFunsMap[className][idx][1] = "~%s" % className
            break
          elif (self.funNameNotSpecial(func_part)):
            self.vFunsMap[className][idx][4] = " // %s TODO" % self.vFunsMap[className][idx][1]
            if self.vFunsMap[className][idx][1].find("nullsub") != -1:
              self.vFunsMap[className][idx][4] += " maybe empty function"
            self.vFunsMap[className][idx][1:3] = func_part[1:3]
            break
        except LookupError:
          logging.error("child class %s can not find %s's corresponding function" % (child, className))


  def replaceSpecFuns(self, classList):
    # replace the some special functions such as sub_xxx, dword_0, nullsub_xxx, __cxa_pure_virtual and so on as well as we can.
    for class_key, fun_parts in self.vFunsMap.items():
      if class_key not in classList: continue
      children_classes, father_classes = [], []  
      if class_key in self.heritMap:
        children_classes = self.heritMap[class_key]
      if class_key in self.myFatherMap:
        father_classes = self.myFatherMap[class_key]
      for i, fun_part in enumerate(fun_parts):
        if (not self.funNameNotSpecial(fun_part)):
          self.searchAndReplace(class_key, i, children_classes, father_classes)
          
        elif fun_part[1] == "__cxa_pure_virtual":
          self.funIdNotInCfile = addValueInMap(class_key, i, self.funIdNotInCfile)
          for ch_class in children_classes:
            try:
              func_part = self.vFunsMap[ch_class][i]
              if (self.funNameNotSpecial(func_part)):
                fun_parts[i][1:3] = func_part[1:3]
                fun_parts[i][3] += "= 0" 
                fun_parts[i][4] = " // __pure_virtual"
                break
            except LookupError:
              logging.error("Can not replace the pure virtual function!")


  def writeVarsFuncs(self, className, h_stream, cc_stream):
    h_stream.write("\n\n//=============== class %s ===============\n" % className)
    cc_stream.write("\n//=========== member functions for class %s ===========\n" % className)
    if className not in self.myFatherMap:
      h_stream.write("class %s {\n" % className)
    else:
      h_stream.write("class %s : public %s {\n" % (className, (", ").join(self.myFatherMap[className])))
    if className in self.varsMap and len(self.varsMap[className]) > 0:
      h_stream.write(" public:\n")
      var_parts = self.varsMap[className]
      for var in var_parts:
        var_line = "  %s%s%s %s_0x%s%s;\n" % (var[1], var[2], var[3], var[4], var[5], var[6])
        h_stream.write(var_line)
    has_deconstru = False
    if className in self.commFunsMap and len(self.commFunsMap[className]) > 0:
      h_stream.write("\n public:\n")
      commfun_parts = self.commFunsMap[className]
      for fun in commfun_parts:
        if fun[1] == className.split("::")[-1]:
          h_fun_line = "  %s(%s)%s;\n" % (fun[1], fun[2], fun[3])
          cc_fun_line = "%s::%s(%s)%s {\n}\n\n" % (className, fun[1], fun[2], fun[3])
        elif fun[1][0] == "~":
          if className in self.vFunsMap or has_deconstru: continue  
          h_fun_line = "  %s(%s)%s;\n" % (fun[1], fun[2], fun[3])
          cc_fun_line = "%s::%s(%s)%s {\n}\n\n" % (className, fun[1], fun[2], fun[3])
          has_deconstru = True
        else:
          h_fun_line = "  void %s(%s)%s;\n" % (fun[1], fun[2], fun[3])
          cc_fun_line = "void %s::%s(%s)%s {\n}\n\n" % (className, fun[1], fun[2], fun[3])
        if className not in self.vFunsMap or fun not in self.vFunsMap[className]:
          h_stream.write(h_fun_line)
          cc_stream.write(cc_fun_line)
    if className in self.vFunsMap and len(self.vFunsMap[className]) > 0:
      h_stream.write("\n public:\n")
      vfun_parts = self.vFunsMap[className]
      for i, vfun in enumerate(vfun_parts):
        if vfun[1][0] == "~":
          if has_deconstru: continue
          h_vfun_line = "  virtual %s(%s) %s;%s\n" % (vfun[1], vfun[2], vfun[3], vfun[4])
          cc_vfun_line = "%s::%s(%s) %s {\n}\n\n" % (className, vfun[1], vfun[2], vfun[3])
          has_deconstru = True
        else:
          h_vfun_line = "  virtual void %s(%s) %s;%s\n" % (vfun[1], vfun[2], vfun[3], vfun[4])
          cc_vfun_line = "void %s::%s(%s) %s {\n}\n\n" % (className, vfun[1], vfun[2], vfun[3])
        h_stream.write(h_vfun_line)
        if className not in self.funIdNotInCfile or i not in self.funIdNotInCfile[className]:
          cc_stream.write(cc_vfun_line)
    h_stream.write("}")


def writeToFile(classList, mymodule):
  h_file_name = "myclass.h"
  cc_file_name = "myclass.cc"
  output_h_file = open(h_file_name, mode="w")
  output_cc_file = open(cc_file_name, mode="w")
  
  # write header for h and cc file
  writeHfileHeader(output_h_file)
  writeCfileHeader(output_cc_file)

  # find the class herit sence and fill the original funs
  mymodule.loadOriginalFuns(classList)
  mymodule.loadStructVars()

  # process the herit relationship
  mymodule.coverBaseVars(classList)
  mymodule.replaceSpecFuns(classList)

  for className in classList:
    mymodule.writeVarsFuncs(className, output_h_file, output_cc_file)

  writeHfileTail(output_h_file)
  writeCfileTail(output_cc_file)

  output_h_file.close()
  output_cc_file.close()

def catch_classList(nameListFile):
  classList = []
  with open(nameListFile, 'r') as targetClassList:
    for line in targetClassList:
      className = line.strip()
      if className != "":
        classList.append(line.strip())
  return classList

if __name__ == "__main__":
  # 1. open files and load to lines array
  if len(sys.argv) < 4:
    print("This script can automatically generate C++ h and cc file framework for all class listed in $classNameList\n")
    print("usage: ./generateClassForProcise.py  $classNameList  $moduleDir  $module\n")
    print("e.g. ./newGenerateClassForProcise.py target_procise_classes hfiles librdi_chipscopeimpl")
    print("$classNameList: the file contain the list of class you want to generate. Remember: one classname one line!\n")
    print("$moduleDir: ($module)_structures.h and ($module)_vtable.h must be in this direction\n")
    print("$module: named like libdir_xxx and classes in $classNameList are in this module.\n")
    sys.exit()

  moduleDir = sys.argv[2]
  module = sys.argv[3]
  
  classNameList = catch_classList(sys.argv[1])
  mypattern = patterns()
  mymodule = genClass(mypattern, moduleDir, module)
  writeToFile(classNameList, mymodule)

