#!/home/xnli/tools/python3.6/bin/python3.6
import copy
import re
import sys

ignore_class = ["HDTree", "HSTVector", "STLIter", "HSTMap", "HSTSet", "UTF8", "STLConstIter", "CSL",\
                "HSTHashMap", "HST2DVector", "HSTSList", "HSTPtrHashMap", "Data"]
class depen:
  def __init__(self, vtablePath):
    self.vtablePath = vtablePath
    self.depenMap = {}
    self.depensGraph = {}

  def loadRelation(self):
    title_pattern = re.compile(r'^typeinfo\s+\w+\s+([\w:]+)\s+{')
    #  typeinfo 0xe15ad88 HDDLRouteFileInfo {
    title_without_typeinfo_pattern = re.compile(r'^typeinfo\s+([\w:]+) with NoTypeInfoDef')
    #  typeinfo HDVAttribMcvirtexuplusHBM_clk_test_buf_veamAtomLogicData_Impl with NoTypeInfoDef {
    base_pattern = re.compile(r'\s+typedef:.*\'typeinfo for\'([\w:]+)')
    functn_pattern = re.compile(r'\s+function:\s+\w+\s+(\w+)::(.*)\((.*)\)(\w*)')
    className = ""
    inClass = False

    with open(self.vtablePath, 'r') as f:
      lines = f.readlines()
      for line in lines:
        if inClass:
          if line == "}\n": 
            inClass = False
            className = ""
            continue
          # process its father
          assert(len(className))
          base_match = base_pattern.findall(line)

          if len(base_match) > 0:
            baseName = base_match[0]
            self.depenMap[className].add(baseName)

          parameters = ""
          func_match = functn_pattern.findall(line)
          if len(func_match) > 0:
            parameters = func_match[0][2]
          fiter = re.finditer(r'\s*[\w:]+', parameters)
          for ite in fiter:
            name = ite.group().strip()
            idx = name.find(':')
            if idx != -1:
              name = name[0:idx]
            if name not in ignore_class and name != className and len(name) > 0 and\
              name.find('_') == -1 and (name[0] >= 'A' and name[0] <= 'Z'):
              self.depenMap[className].add(name)
              # print(name)
            
        else:
          title_match = title_pattern.findall(line)
          title_no_typeinfo_match = title_without_typeinfo_pattern.findall(line)
          if len(title_match) > 0:
            className = title_match[0]
            inClass = True
            self.depenMap[className] = set()
          elif len(title_no_typeinfo_match) > 0:
            className = title_no_typeinfo_match[0]
            inClass = True
            self.depenMap[className] = set()
    
    self.depensGraph = self.depenMap

  def TopoSort(self):
    lev = 1
    degree = 0
    while True:
      removed = []
      if len(self.depensGraph) == 0: break
      for k, v in self.depensGraph.items():
        if len(v) == degree:
          removed.append(k)

      if len(removed) == 0:
        degree = degree + 1
      else:
        print("\nClass level %d:" % lev)
        lev = lev + 1
        for cls in removed:
          print(cls)
          del self.depensGraph[cls]
        for k in self.depensGraph:
          for cls in removed:
            if cls in self.depensGraph[k]:
              self.depensGraph[k].remove(cls)
        degree = 0

  def run(self):
    self.loadRelation()
    self.TopoSort()


if __name__ == "__main__":
  if len(sys.argv) < 2:
    print("This script can automatically sort class according to their dependency.\n")
    print("usage: ./dispDepenClass.py $lib_path\n")
    print("$lib_path: the path of vtable file\n")
    print("e.g. ./dispDepenClass.py ./script/vvd_lib/librdi_device_vtable.h")
    sys.exit()

  vtable_file = sys.argv[1]

  vtable_class = depen(vtable_file)
  vtable_class.run()
