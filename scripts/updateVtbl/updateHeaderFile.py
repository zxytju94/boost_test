#!/home/xnli/tools/python3.6/bin/python3.6

import os
import sys
import re
import copy
import math

skipped_class = []


class patterns():
  def __init__(self):
    self.variable_pattern = re.compile(r'\s+(const |mutable )?([\w:]*)(\<.*\>\w*)?\s*([*]*)\s([^=:\}]*?)_0x([0-9a-fA-F]*?)(\[[0-9a-fA-Fx]+\])?;')
    # disp: [0][0]const/mutable flag  [0][1]var type  [0][2]tmplate class type  [0][3]ptr  [0][4]var name  [0][5]var offset [0][6]var size
    # e.g.  line = "  const std::vector<std::string>* names_0x28[58]"
    # [0][0]=const  [0][1]=std::vector  [0][2]=std::string  [0][3]=*  [0][4]=names [0][5]=28  [0][6]=[58]
    self.unsigned_vars_pattern = re.compile(r'\s+(const|mutable )?(unsigned \w+)\s*([*]*)\s([^=:\}]*?)_0x([0-9a-fA-F]*?)(\[[0-9a-fA-Fx]+\])?;')
    self.class_pattern = re.compile(r'^\s*class\s+([\w:]+)\s*{\s*$')
    self.struct_vtable_pattern = re.compile(r'^struct\s+([\w:]+)')
    self.inheritclass_pattern = re.compile(r'^\s*class (.*?)\s*:\s*(public[\s\w,]+)\s*{\s*$')
    self.enum_struct_pattern = re.compile(r'\s*(enum|struct|template)\s+.+\s*{')
    self.union_pattern = re.compile(r'\s*union\s+(\w+)\s+{')
    self.union_end = re.compile(r'}\s*(\w+)_0x([0-9a-fA-F]*?);')
    self.endblock_pattern = re.compile(r'^\s*}\s*;')
    self.comment_line = re.compile(r'(\/\/.*)')
    self.comment_block_single_line = re.compile(r'(/\*(?:(?!\*/).)*\*/)')
    self.comment_block_multiline_beg = re.compile(r'(/\*(?:(?!\*/).)*$)')
    self.comment_block_multiline_end = re.compile(r'(^(?:(?!\*/).)*\*/)')
    self.vfunc_pattern = re.compile(r'virtual.*\(.*\)\s*;}?')
    self.func_pattern = re.compile(r'\((.*)\)\s*(const)?\s*(.*)?;\s*}?')
    self.func_block_pattern = re.compile(r'\((.*)\)\s*(const)?\s*{\s*')
    self.type_pattern = re.compile(r'(\w+::(\w*T[yY][pP][eE]|[_A-Z]+))$')
    self.preclass_pattern = re.compile(r'^class ([\w:]+);')
    self.vtable = re.compile(r'(vtable|vfunc_table|vfun_table)')
    self.classMemberPatter = re.compile(r'(.*) (.*);(.*)')
    self.typedef = re.compile(r'typedef uint32_t ([\w:]+);')


class vtable():
  def __init__(self, patternCfg, lib_root, allClassFile, allEmptyClassFile, prociseFile):
    self.pattern = patternCfg
    self.lib_root = lib_root
    self.allClassFile = allClassFile
    self.allEmptyClassFile = allEmptyClassFile
    self.prociseFile = prociseFile
    self.prociseClassParts = {}
    self.classBaseMap = {}  # inherit relation
    self.classExternMap = {}
    self.finalClassVtableMap = {}
    self.structVtableMap = {}
    self.allClassVtableMap = {}
    self.allClassSet = set()
    self.allEnumType = set()
    self.debug = False # print before write

    # fun_utils
    self.cache_lines = []
    self.cur_class = ""
    self.cur_struct = ""
    self.inClass = False
    self.base_class = ""
    self.offset_dict = {"std::vector": 0x18, "std::string": 0x20, "std::vector_bool": 0x28,
                "std::map": 0x30, "std::set": 0x30, "std::multimap": 0x30, 
                "std::unordered_map": 0x38, "std::unordered_set": 0x38, "std::shared_ptr": 0x10,
                "std::unordered_multimap": 0x38, "void": 0x8, "float": 0x4, "double": 0x8,
                "uint8_t": 0x1, "uint16_t": 0x2, "uint32_t": 0x4, "uint64_t": 0x8,
                "int8_t": 0x1, "int16_t": 0x2, "int32_t": 0x4, "int64_t": 0x8, "int": 0x4, 
                "short": 0x2, "long": 0x4, "long long": 0x8, "bool": 0x1, "char": 0x1, 
                "unsigned int": 0x4, "unsigned short": 0x2, "unsigned int": 0x4, "unsigned long": 0x4,
                "unsigned long long": 0x8, "pthread_mutex_t": 0x28,
                "unsigned": 1e3, "pthread_t": 1e3, "struct": 1e3, " ": 1e3,
                "AString": 0x8}


  def loadAllClass(self, libfilelist):
    for libfile in libfilelist:
      with open(os.path.join(self.lib_root, libfile), 'r') as f:
        inStruct = False
        for line in f:
          class_match = self.pattern.class_pattern.findall(line)
          struct_vtable_match = self.pattern.struct_vtable_pattern.findall(line)
          if len(class_match) > 0:
            self.cur_class = class_match[0]
            self.inClass = True
            continue
          if self.inClass:
            if len(self.pattern.endblock_pattern.findall(line)) > 0:
              self.inClass = False
              self.allClassVtableMap[self.cur_class] = copy.copy(self.cache_lines)
              self.cache_lines = []
            else:
              self.cache_lines.append(line)


  def loadVVD(self):
    '''
    load all defined class as allClassSet and load allVtable to finalClassVtableMap
    finalClassVtableMap [className] = lines in this class
    '''
    with open(self.allEmptyClassFile, 'r') as emptyFile:
      for line in emptyFile:
        class_match = self.pattern.class_pattern.findall(line)
        if len(class_match) > 0: self.allClassSet.add(class_match[0])
        type_match = self.pattern.typedef.findall(line)
        if len(type_match) > 0: self.allEnumType.add(type_match[0])

    with open(self.allClassFile, 'r') as allClass:
      inStruct = False
      for line in allClass:
        class_match = self.pattern.class_pattern.findall(line)
        struct_vtable_match = self.pattern.struct_vtable_pattern.findall(line)
        if len(class_match) > 0:
          self.cur_class = class_match[0]
          self.inClass = True
          continue
        elif len(struct_vtable_match) > 0:
          self.cur_struct = struct_vtable_match[0]
          inStruct = True
          self.cache_lines.append(line)
          continue
        if self.inClass:
          if len(self.pattern.endblock_pattern.findall(line)) > 0:
            self.inClass = False
            self.finalClassVtableMap[self.cur_class] = copy.copy(self.cache_lines)
            self.cache_lines = []
          else:
            self.cache_lines.append(line)
        elif inStruct:
          if len(self.pattern.endblock_pattern.findall(line)) > 0:
            inStruct = False
            self.structVtableMap[self.cur_struct] = copy.copy(self.cache_lines)
            self.cache_lines = []
          else:
            self.cache_lines.append(line)

    print("1. Empty class and Vivado class load finished")


  def formatProciseFile(self):
    """
    1. load prociseFile to prociseClassParts
    In this map, value (lines) will be fomat as a standerd format.
    tips: standerd format:
    (var_type) ptr (var_name)_0x(var_offset);
    
    2. find the inherit relationship and record it as classBaseMap for class lines merge
    """
    skipped_flag = False
    block_flag = False
    union_flag = False
    func_block_level = 0
    isEnclosing = False
    inComment = False
    multi_line_merge = ""
    self.cur_class = ""
    self.base_class = ""
    self.cache_lines = []
    self.inClass = False
    classStack = []
    unwEnclosingParts = {}
    cache_parts = []
    union_size = 0
    with open(self.prociseFile, 'r') as prociseFile:
      for i, line in enumerate(prociseFile):
        #print(line)
        line = re.sub(self.pattern.comment_block_single_line, "", line)
        line = re.sub(self.pattern.comment_line, "", line)
        
        if inComment:
          if (len(self.pattern.comment_block_multiline_end.findall(line)) > 0):
            multi_line_merge += re.sub(self.pattern.comment_block_multiline_end, "", line)
            line = multi_line_merge
            inComment = False
            multi_line_merge = ""
          continue

        if (len(self.pattern.comment_block_multiline_beg.findall(line)) > 0):
          multi_line_meger = re.sub(self.pattern.comment_block_multiline_beg, "", line)
          inComment = True
          continue

        if line == "" or line == "\n": continue

        ##skip useless block until end_pattern
        if skipped_flag:
          if len(self.pattern.endblock_pattern.findall(line)) > 0: skipped_flag = False
          continue

        if block_flag:
          if len(self.pattern.endblock_pattern.findall(line)) > 0: block_flag = False
          continue

        if (func_block_level != 0):
          if (line.find('}') != -1) and (line.find('{') < line.find('}')):
            func_block_level -= 1
          elif len(self.pattern.func_block_pattern.findall(line)) > 0 and line.find('}') == -1:
            func_block_level += 1
          continue

        if union_flag:
          end_union = self.pattern.union_end.findall(line)
          var_union = self.pattern.variable_pattern.findall(line)
          if len(end_union) > 0:
            if union_size == 0:
              print("skipped union %s_0x%s" % (end_union[0][0], end_union[0][1]))
              union_flag = False
              continue
            vtable_part = [('', union_type, '', union_ptr, end_union[0][0], hex(int(end_union[0][1]) + union_size)[2:], '')]
            union_flag = False
          elif len(var_union) > 0:
            cur_size = 0x8
            if var_union[0][3] == '':
              cur_size = self.offset_dict[var_union[0][1]]
            if (cur_size > union_size):
              union_size = cur_size
              union_type = var_union[0][1]
              union_ptr = var_union[0][3]
          continue
          
        ## if has "(" and ")", the line is function, skip
        if len(self.pattern.func_pattern.findall(line)) > 0: 
          if len(self.pattern.vfunc_pattern.findall(line)) > 0 and self.inClass and \
                (self.cur_class + '_vtable' not in self.allClassSet):
            self.allClassSet.add(self.cur_class + '_vtable')
          continue
        ## if has "(", ")" and "{", the line is function block begin
        if len(self.pattern.func_block_pattern.findall(line)) > 0 and line.find('}') == -1:
          func_block_level += 1
          continue
        ## skip predefine class
        if len(self.pattern.preclass_pattern.findall(line)) > 0: continue

        class_match = self.pattern.class_pattern.findall(line)
        inherclass_match = self.pattern.inheritclass_pattern.findall(line)

        if len(class_match) > 0:
          # class HDDMSiteType {
          tmp_cur_class = self.cur_class
          self.cur_class = class_match[0]
          if self.cur_class in skipped_class:
            skipped_flag = True
            continue
          if not self.inClass:
            classStack.append(self.cur_class)
            unwEnclosingParts[self.cur_class] = []
            self.base_class = ""
            self.inClass = True
          else:  # inClass -- nested class
            if len(self.pattern.endblock_pattern.findall(line)) > 0: continue
            self.base_class = tmp_cur_class
            self.cur_class = class_match[0]
            classStack.append(self.cur_class)
            self.cur_class = ("::").join(classStack)
            unwEnclosingParts[self.base_class] = copy.copy(cache_parts)
            cache_parts = []
          continue
        elif len(inherclass_match) > 0:
          # e.g. class NetCount public: class HDPLConnTag  self.base_class = HDPLConnTag className = NetCount
          baselist = inherclass_match[0][1].strip().split(',')
          newBaselist = [x[x.strip().find(' ') + 1:].strip() for x in baselist]
          self.cur_class = inherclass_match[0][0]
          if self.cur_class in skipped_class:
            skipped_flag = 1
            continue
          self.base_class = newBaselist[0]
          classStack.append(self.cur_class)
          unwEnclosingParts[self.cur_class] = []
          self.classBaseMap[self.cur_class] = newBaselist 
          self.inClass = True
          continue
      
        if len(self.pattern.enum_struct_pattern.findall(line)) > 0:
          if line.find("};") == -1:
            block_flag = True
          continue

        if len(self.pattern.union_pattern.findall(line)) > 0:
          if line.find("};") == -1:
            union_flag = True
          continue

        if self.inClass:
          if len(self.pattern.endblock_pattern.findall(line)) > 0:
            # a block end, to load in unWrite cache
            # to process the nested class
            if self.cur_class in unwEnclosingParts and len(classStack) > 1:
              unwEnclosingParts[self.cur_class] += copy.copy(cache_parts)
              cache_parts = []
            if not isEnclosing:
              self.prociseClassParts[self.cur_class] = copy.copy(cache_parts)
              cache_parts = []
            classStack.pop()
            if classStack == []:
              self.inClass = False
              isEnclosing = False
              if len(unwEnclosingParts[self.cur_class]) > 0:
                self.prociseClassParts[self.cur_class] = copy.copy(unwEnclosingParts[self.cur_class])
              unwEnclosingParts = {}
            else:
              if self.cur_class in unwEnclosingParts:
                self.prociseClassParts[self.cur_class] = copy.copy(unwEnclosingParts[self.cur_class])
                del unwEnclosingParts[self.cur_class]
              self.cur_class = self.base_class
              if len(classStack) == 1:
                isEnclosing = False
                self.base_class = ""
              elif len(classStack) == 2:
                isEnclosing = False
                self.base_class = classStack[-2]
              else:
                isEnclosing = True
                self.base_name = ("::").join(classStack[:-1])
          elif len(self.pattern.vtable.findall(line)) > 0:
            vtable_name = self.cur_class + '_vtable'
            vtable_part = [('', vtable_name, '', '*', vtable_name, '0', '')]
            cache_parts.append(vtable_part)
            if (vtable_name not in self.allClassSet):
              print("add %s in AllEmptyClass" % vtable_name)
              self.allClassSet.add(vtable_name)
          elif len(self.pattern.variable_pattern.findall(line)) > 0: # format the line
            var_match = self.pattern.variable_pattern.findall(line)
            if (var_match[0][1] == "std::vector" and var_match[0][2] == "<bool>" and var_match[0][3] != "*"):
              var_match = [("", "std::vector_bool", "", "", var_match[0][4], var_match[0][5], var_match[0][6])]
            if (len(self.pattern.type_pattern.findall(var_match[0][1])) > 0 and var_match[0][3] == ""):
              if var_match[0][1] not in self.allEnumType:
                self.allEnumType.add(var_match[0][1])
              var_match = [('', 'uint32_t', var_match[0][2], var_match[0][3], var_match[0][4], var_match[0][5], var_match[0][6])]
            # formated_line = "  %s%s %s_0x%s; //%s\n" % (var_match[0][1], var_match[0][3], \
            #            var_match[0][4], var_match[0][5], var_match[0][2])
            # cache_parts.append("  " + formated_line.strip(" "))
            if var_match[0][1] == "unsigned":
              unsigned_var_match = self.pattern.unsigned_vars_pattern.findall(line)
              var_match = [('', unsigned_var_match[0][1], '', unsigned_var_match[0][2], unsigned_var_match[0][3], unsigned_var_match[0][4], unsigned_var_match[0][5])]
            cache_parts.append(var_match)
            if var_match[0][1] not in self.offset_dict and var_match[0][1] not in self.allClassSet:
              print("add %s in AllEmptyClass" % var_match[0][1])
              self.allClassSet.add(var_match[0][1])
            #if var_match[0][1] == "": assert(0)
            assert(len(var_match[0]) == 7)
          else: continue

    
    ## compute class size and add to offset_dict
    for class_key, vals in self.prociseClassParts.items():
      if len(vals) > 0:
        _, class_size = self.calculateNextOffset(int(vals[-1][0][5], 16), vals[-1])
        #print("the size of class %s is 0x%x" % (class_key, class_size))
        if (class_size != -1):
          self.offset_dict[class_key] = class_size
      else:
        self.offset_dict[class_key] = 0

    print("2. Procise file has been formated completed")


  def calculateNextOffset(self, offset, part):
    if part[0][3] == "*":
      var_size = 0x8
    elif part[0][1] == "std::vector" and part[0][2][1:-1] == "bool":  # replace the std::vector<bool> by std::vector_bool
      var_size = 0x28
      part = [("", "std::vector_bool", "", "", part[0][4], part[0][5], part[0][6])]
    elif part[0][1] in self.offset_dict:
      var_size = self.offset_dict[part[0][1]]
    else:
      return part, -1

    if part[0][6] == "":
      offset += var_size
    else:
      offset += var_size * int(part[0][6][1:-1], 16)
    return part, offset


  def addbaseParts(self, base, class_key, baseParts, Parts_new):
    if len(baseParts) == 0:
      lastOffset = 0
    else:
      lastPart = baseParts[-1]
      lastOffset = int(lastPart[0][5], 16)
      _, lastOffset = self.calculateNextOffset(lastOffset, lastPart)
      if (lastOffset == -1):
        print("Wrong! Please ask xiaoyu check.")
        assert(0)
      lastOffset = math.ceil(lastOffset/8) * 8

    offset = -1
    for part in Parts_new:
      offset = int(part[0][5], 16) + lastOffset
      new_part = [(part[0][0], part[0][1], part[0][2], part[0][3], \
                  part[0][4].replace(base, class_key), hex(offset)[2:], part[0][6])]
      baseParts.append(new_part)

    if len(baseParts) == 0:
      offset = -1
    elif baseParts[0][0][1].find('vtable') != -1:
      baseParts[0] = [('', class_key + '_vtable', '', '*', class_key + '_vtable', '0', '')]
    return baseParts, offset


  def formated2line(self, class_key, parts):
    """
    remove the instance
    """
    lines = []
    cur_offset = -8 # avoid to name vtable confilt
    for i, part in enumerate(parts):
      if i == 0 and int(part[0][5], 16) > 0:
        print("Warning: please check class %s whether has 0x0 or not" % class_key)  
      if part[0][1][-7:] == "_vtable":
        line = "  %s%s %s_%s%s; //%s\n" % (part[0][1], part[0][3], part[0][4], hex(cur_offset + 0x8), part[0][6], part[0][2])
      else:
        line = "  %s%s %s_0x%s%s; //%s\n" % (part[0][1], part[0][3], part[0][4], part[0][5], part[0][6], part[0][2])
      lines.append(line)
      cur_offset = int(part[0][5], 16)
    return lines


  def getPartsFromAllVtable(self, className):
    parts = []
    if className not in self.allClassVtableMap: return parts
    baseLines = self.allClassVtableMap[className]
    for line in baseLines:
      line = line.replace(className + "_", "")
      parts.append(self.pattern.variable_pattern.findall(line))
    return parts


  def addTmpVar(self, prociseParts):
    prociseParts_new = prociseParts
    pos_offset = 1
    for i in range(len(prociseParts) - 1):
      lastOffset = int(prociseParts[i][0][5], 16)
      _, lastOffset = self.calculateNextOffset(lastOffset, prociseParts[i])
      if lastOffset == -1: continue

      interpolation_num = math.floor((int(prociseParts[i+1][0][5], 16) - lastOffset)/ 8)
      for j in range(interpolation_num):
        prociseParts.insert(pos_offset + j + i, [('', 'uint64_t', '', '', 'qword', hex(lastOffset + j * 8)[2:], '')])
        print("add var by interpolating")
      pos_offset += interpolation_num

    return prociseParts_new


  def mergeLines(self):
    """
    cover the vtable class variables with prociseClassParts and add the base class from base offset
    """
    unMerged = list(self.prociseClassParts.keys())
    mergedSet = set()
    while True:
      if len(unMerged) == 0:
        break
      class_key = unMerged.pop()
      if (class_key in skipped_class) or (class_key[-7:] == '_vtable'): 
        continue
      if (class_key not in self.finalClassVtableMap):
        continue

      can_merge = True
      if class_key in self.classBaseMap:
        baseClasses = self.classBaseMap[class_key]
        for base in baseClasses:
          if base not in self.prociseClassParts or len(self.prociseClassParts[base]) == 0:
            continue
          if base not in mergedSet:
            can_merge = False
            break
      if not can_merge: 
        unMerged.insert(0, class_key)
        continue
      mergedSet.add(class_key)
      prociseParts = self.prociseClassParts[class_key]
      vtableName = class_key + "_vtable"
      hasVtable = False
      if vtableName in self.allClassSet:
        hasVtable = True

      if class_key in self.classBaseMap:  #has base
        baseParts = []
        baseClasses = self.classBaseMap[class_key]
        for base in baseClasses:
          baseParts_tmp = []
          if base in self.prociseClassParts:
            baseParts_tmp = copy.copy(self.prociseClassParts[base])
          else:
            baseParts_tmp = self.getPartsFromAllVtable(base) + baseParts_tmp
          baseParts, lastOffset = self.addbaseParts(base, class_key, baseParts, baseParts_tmp)

        for part in prociseParts:
          if (int(part[0][5], 16) > lastOffset):
            baseParts.append(part)
        if hasVtable and len(baseParts) > 0:
          if int(baseParts[0][0][5], 16) >= 8 or baseParts[0][0][1].find("table") == -1:
            baseParts.insert(0, [('', vtableName, '', '*', vtableName, '0', '')])
          else:
            assert(baseParts[0][0][1].find("table") != -1)
        elif len(self.finalClassVtableMap[class_key]) > 0:
          if hasVtable and self.finalClassVtableMap[class_key][0].find("_vtable") != -1:
            if len(baseParts) > 0:
              baseParts[0] = [('', vtableName, '', '*', vtableName, '0', '')]
            else:
              baseParts = [[('', vtableName, '', '*', vtableName, '0', '')]]
        self.prociseClassParts[class_key] = baseParts
        self.finalClassVtableMap[class_key] = self.formated2line(class_key, baseParts)
      else:  # no base class
        if hasVtable and len(prociseParts) > 0:
          if int(prociseParts[0][0][5], 16) >= 8:
            prociseParts.insert(0, [('', vtableName, '', '*', vtableName, '0', '')])
          else:
            if (prociseParts[0][0][1].find("table") == -1):
              prociseParts[0] = [('', vtableName, '', '*', vtableName, '0', '')]
            assert(prociseParts[0][0][1].find("table") != -1)
          prociseParts = self.addTmpVar(prociseParts)
        elif len(self.finalClassVtableMap[class_key]) > 0:
          if self.finalClassVtableMap[class_key][0].find("_vtable") != -1:
            vtableName = class_key + '_vtable'
            if prociseParts == []:
              prociseParts.append([('', vtableName, '', '*', vtableName, '0', '')])
            else:
              prociseParts[0] = [('', vtableName, '', '*', vtableName, '0', '')]
            if (vtableName not in self.allClassSet):
              print("add %s in AllEmptyClass" % vtableName)
              self.allClassSet.add(vtableName)
        self.finalClassVtableMap[class_key] = copy.copy(self.formated2line(class_key, prociseParts))

    print("3. Procise class has processed finished")


  def writeFile(self):
    vtableFile = open(self.allClassFile, mode="w+")
    vtableFile.write("#include \"../%s\"\n" % (allEmptyClassFile))
    vtableFile.write("#include \"../common_class.h\"\n")
    for class_key, classMember_lines in self.finalClassVtableMap.items():
      vtableFile.write("class %s {\n" % class_key)
      for line in classMember_lines:
        match = self.pattern.classMemberPatter.findall(line);
        if len(match) > 0 :
          className = class_key
          if (match[0][1].find(className.replace("::", "")) == -1 and 
              match[0][1].find(className.replace("::", "_")) == -1 and
              match[0][1].find(className) == -1):
            line = match[0][0] + " " + className.replace("::", "_") + "_" + match[0][1] + ";"
            if len(match[0]) > 2 :
              line = line + match[0][2]
            line = line + "\n";
        vtableFile.write(line)
      vtableFile.write("}; // end of class %s\n" % class_key)
    for struct_key, vtablelines in self.structVtableMap.items():
      for line in vtablelines:
        vtableFile.write(line)
      vtableFile.write("};\n\n")
    vtableFile.close()

    emptyFile = open(self.allEmptyClassFile, mode="w+")
    emptyFile.write("//This file predefines the classes in all structure.h and vfunction.h\n")
    emptyList = list(self.allClassSet)
    emptyList.sort()
    for empty_key in emptyList:
      if empty_key.strip() == "" : continue
      emptyFile.write("class %s {\n" % empty_key)
      emptyFile.write("};\n")
    enumTypeList = list(self.allEnumType)
    enumTypeList.sort()
    for EType in enumTypeList:
      emptyFile.write("typedef uint32_t %s;\n" % EType)
    emptyFile.close()

    print("4. Empty classes and all classes have been updated")


  def process(self):
    print("Processing: %s" % self.prociseFile)    
    # 1. Load pre defined class
    self.loadVVD();

    # 2. Load prociseFile to cache
    self.formatProciseFile();

    # 3. Merge and Write
    self.mergeLines();
    self.writeFile();
    

if __name__ == "__main__":
  # open files and load to lines array
  if len(sys.argv) < 2:
    print("This script can extract IDA class header files from a well-defined C++ header file.\n")
    print("The member variables must contains byte offset: _0x..\n")
    print("Suggest you use it in the directory: procise/scripts/")
    print("usage: ./updateIdaClassHeader.py ${classVtable.h} ${procise_hfileName.h}")
    print("e.g. ./updateIdaClassHeader.py libs/librdi_constraints_classVtable.h constraintsH.h")
    sys.exit()
  
  vtableClassFileName = sys.argv[1]
  allEmptyClassFile = re.sub("_classVtable.h", "_empty_class.h", vtableClassFileName)
  prociseClassFileName = sys.argv[2]

  mypattern = patterns()
  # you can choose the lib file which base of any class contained
  lib_root = 'libs'
  filelist = ['libsp_SIwaveSimEngine_classVtable.h']
  newVtable = vtable(mypattern, lib_root, vtableClassFileName, allEmptyClassFile, prociseClassFileName)
  newVtable.loadAllClass(filelist)
  newVtable.process()

