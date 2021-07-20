vtable 0x2bbbde0 HARTDFCnfError {
  typedef: 0x2bbbde8 -> 0x2bbbd98 `typeinfo for'HARTDFCnfError
  vfunctn: 0x2bbbdf0 -> 0xa61170 sub_A61170
  vfunctn: 0x2bbbdf8 -> 0xa61210 sub_A61210
  vfunctn: 0x2bbbe00 -> 0xa519c0 HARTDFCnfError::what(void)const
}

vtable 0x2bbbe08 HARTDFCnf {
  typedef: 0x2bbbe10 -> 0x2bbbdb0 `typeinfo for'HARTDFCnf
  vfunctn: 0x2bbbe18 -> 0xa60210 HARTDFCnf::addClauseToDb(std::vector<int> &)
}

typeinfo 0x2bbbd98 HARTDFCnfError {
  typedef: 0x2bbbda0 -> 0x22ea540 `typeinfo name for'HARTDFCnfError
  typedef: 0x2bbbda8 -> 0x2e81c98 `typeinfo for'std::exception
  function: 0xa519c0 HARTDFCnfError::what(void)const
}

typeinfo 0x2bbbdb0 HARTDFCnf {
  typedef: 0x2bbbdb8 -> 0x22ea558 `typeinfo name for'HARTDFCnf
  typedef: 0x2bbbdc0 -> 0x2bc7df8 `typeinfo for'HARTCnf
  function: 0xa52300 HARTDFCnf::_error(int)
  function: 0xa52490 HARTDFCnf::_assert(bool, int)
  function: 0xa524b0 HARTDFCnf::truncateLitVec(std::vector<int> &, int)
  function: 0xa52530 HARTDFCnf::findDFVar(DFPin *)
  function: 0xa525b0 HARTDFCnf::printPinVar(DFPin *, std::shared_ptr<HARTDFCnf::DFVarC>)
  function: 0xa52710 HARTDFCnf::printMap(std::map<DFPin *,DFPin *> const&)
  function: 0xa52e40 HARTDFCnf::buildFA(int, int, int, int &, int &)
  function: 0xa52ef0 HARTDFCnf::isInPinSigned(DFPin *)
  function: 0xa52f30 HARTDFCnf::buildImply(std::shared_ptr<HARTDFCnf::DFVarC>, std::shared_ptr<HARTDFCnf::DFVarC>)
  function: 0xa53040 HARTDFCnf::checkGraph(DFGraph *)
  function: 0xa530d0 HARTDFCnf::printResult(int)
  function: 0xa53150 HARTDFCnf::isValidCasePartitionR(DFGraph *)
  function: 0xa53270 HARTDFCnf::isValidCasePartition(NRealMod)
  function: 0xa532a0 HARTDFCnf::isValidBselPartitionR(DFGraph *)
  function: 0xa53330 HARTDFCnf::setDontCaresForPrimitiveNode(DFNode *)
  function: 0xa533e0 HARTDFCnf::setDontCaresRecur(DFGraph *)
  function: 0xa53480 HARTDFCnf::setDontCares(NRealMod)
  function: 0xa53500 HARTDFCnf::reset(void)
  function: 0xa53670 HARTDFCnf::printMap(std::map<DFPin *,std::shared_ptr<HARTDFCnf::DFVarC>> const&)
  function: 0xa53870 HARTDFCnf::extendLitVec(std::vector<int> &, int, bool)
  function: 0xa539a0 HARTDFCnf::buildEq(std::shared_ptr<HARTDFCnf::DFVarC>, std::shared_ptr<HARTDFCnf::DFVarC>)
  function: 0xa53b70 HARTDFCnf::buildNotEq(std::shared_ptr<HARTDFCnf::DFVarC>, std::shared_ptr<HARTDFCnf::DFVarC>)
  function: 0xa53d40 HARTDFCnf::buildMiter_(void)
  function: 0xa53eb0 HARTDFCnf::buildRippleCarryAdder(std::vector<int>, bool, std::vector<int>, bool, int, std::vector<int>&, unsigned int, int &)
  function: 0xa54080 HARTDFCnf::buildLShift(std::vector<int>, unsigned int, std::vector<int>&, unsigned int)
  function: 0xa54180 HARTDFCnf::buildBmerge(std::vector<int> &, std::vector<int> &, std::vector<int> &, bool, int, bool, int, unsigned int, unsigned int)
  function: 0xa545a0 HARTDFCnf::buildUminus(std::vector<int>, unsigned int, bool, std::vector<int>&, unsigned int)
  function: 0xa546c0 HARTDFCnf::buildSubtractor(std::vector<int>, bool, std::vector<int>, bool, std::vector<int>&, unsigned int, int &)
  function: 0xa54860 HARTDFCnf::selectLitVec(std::vector<int>, std::vector<int>&, int, unsigned int)
  function: 0xa54930 HARTDFCnf::buildMult(std::vector<int>, bool, std::vector<int>, bool, std::vector<int>&, unsigned int)
  function: 0xa55110 HARTDFCnf::buildConstMult(std::vector<int>, bool, UConst, std::vector<int>&, unsigned int)
  function: 0xa557b0 HARTDFCnf::buildConstEq(std::vector<int> const&, int, UConst)
  function: 0xa55930 HARTDFCnf::buildDecode(std::vector<int> &, std::vector<int> &, unsigned int, bool)
  function: 0xa55b20 HARTDFCnf::buildMux(std::vector<int>, std::vector<std::vector<int>>, std::vector<int>&, unsigned int)
  function: 0xa560f0 HARTDFCnf::buildMiter(void)
  function: 0xa56710 HARTDFCnf::addToMap(DFPin *, std::shared_ptr<HARTDFCnf::DFVarC>)
  function: 0xa568f0 HARTDFCnf::addDFVar(DFPin *, std::vector<int> &)
  function: 0xa569b0 HARTDFCnf::addDFVar(DFPin *, int)
  function: 0xa56a70 HARTDFCnf::addDFVar(DFPin *)
  function: 0xa56ba0 HARTDFCnf::getDFVar(DFPin *)
  function: 0xa57030 HARTDFCnf::buildSubtractor(DFNode *)
  function: 0xa57370 HARTDFCnf::buildRShift(DFNode *)
  function: 0xa57770 HARTDFCnf::buildLShift(DFNode *)
  function: 0xa57a70 HARTDFCnf::buildUminus(DFNode *)
  function: 0xa57c30 HARTDFCnf::buildLogicalOp(DFNode *)
  function: 0xa57e60 HARTDFCnf::buildReductionOp(DFNode *)
  function: 0xa580b0 HARTDFCnf::buildNotEq(DFNode *)
  function: 0xa58250 HARTDFCnf::buildEq(DFNode *)
  function: 0xa583f0 HARTDFCnf::markInputs(DFGraph *)
  function: 0xa58460 HARTDFCnf::markOutputs(DFGraph *)
  function: 0xa58500 HARTDFCnf::buildReg(DFNode *)
  function: 0xa585c0 HARTDFCnf::buildUnaryOp(DFNode *)
  function: 0xa58970 HARTDFCnf::buildDecode(DFNode *)
  function: 0xa58c30 HARTDFCnf::buildWire(DFNode *)
  function: 0xa58ff0 HARTDFCnf::buildRelationalOp(DFNode *)
  function: 0xa598a0 HARTDFCnf::buildBconc(DFNode *)
  function: 0xa59ac0 HARTDFCnf::buildConstructPriority(DFNode *)
  function: 0xa5a8b0 HARTDFCnf::buildAdder(DFNode *)
  function: 0xa5afd0 HARTDFCnf::buildConstructParallel(DFNode *)
  function: 0xa5bbc0 HARTDFCnf::buildConstruct(DFNode *)
  function: 0xa5bc70 HARTDFCnf::buildMerge(DFNode *)
  function: 0xa5c750 HARTDFCnf::buildMult(DFNode *)
  function: 0xa5cd60 HARTDFCnf::buildBitwiseOp(DFNode *)
  function: 0xa5d2a0 HARTDFCnf::buildBsel(DFNode *)
  function: 0xa5d830 HARTDFCnf::buildBmerge(DFNode *)
  function: 0xa5df50 HARTDFCnf::buildNode(DFNode *)
  function: 0xa5e390 HARTDFCnf::buildGraph(DFGraph *)
  function: 0xa5e4b0 HARTDFCnf::buildExtWire(DFPin *, int)
  function: 0xa5e800 HARTDFCnf::markEqPins(DFPin *, DFPin *)
  function: 0xa5ea50 HARTDFCnf::markEqPins(DFGraph *, DFGraph *)
  function: 0xa5ed20 HARTDFCnf::markEqRegs(DFGraph *, DFGraph *)
  function: 0xa5f2f0 HARTDFCnf::checkEquivalence(DFGraph *, DFGraph *)
  function: 0xa5f480 HARTDFCnf::markEqVars(int, int, bool)
  function: 0xa5f630 HARTDFCnf::markEqPins(DFGraph *, NRealMod, HARTNlCnf &)
  function: 0xa5fc70 HARTDFCnf::getCaseModulesRecur(NRealMod, UList<NRealModC *, UListNode<NRealModC *>, NRealModC *, UEValue<NRealModC *, UListNode<NRealModC *>>> &, bool)
  function: 0xa5ffe0 HARTDFCnf::getBselModulesRecur(NRealMod, UList<NRealModC *, UListNode<NRealModC *>, NRealModC *, UEValue<NRealModC *, UListNode<NRealModC *>>> &)
  function: 0xa60210 HARTDFCnf::addClauseToDb(std::vector<int> &)
  function: 0xa60220 HARTDFCnf::importNetlistCnf(HARTNlCnf &)
  function: 0xa602a0 HARTDFCnf::checkEquivalence(NRealMod)
  function: 0xa604b0 HARTDFCnf::checkCaseEquivalences(NRealMod)
  function: 0xa608c0 HARTDFCnf::checkBselEquivalences(NRealMod)
  function: 0xa60cd0 HARTDFCnf::checkEquivalenceTop(NRealMod)
}
