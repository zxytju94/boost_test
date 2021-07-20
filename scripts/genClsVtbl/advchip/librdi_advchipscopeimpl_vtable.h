vtable 0x38f3f0 HACSECoreMgr {
  typedef: 0x38f3f8 -> 0x38f148 `typeinfo for'HACSECoreMgr
  vfunctn: 0x38f400 -> 0x397b48 HANEObserver::lhPreModifyCallback(HANECVRequest const&)
  vfunctn: 0x38f408 -> 0x398d00 HANEObserver::lhPostModifyCallback(HANEPPSummary const&)
  vfunctn: 0x38f410 -> 0x398bd0 HANEObserver::lhPortsCallback(HANEPortSummary const&)
  vfunctn: 0x38f418 -> 0x8f870 HACSECoreMgr::lhPreIncrChgCallback(HANELHChgTxn *)
  vfunctn: 0x38f420 -> 0x8dda0 HACSECoreMgr::lhPostIncrChgCallback(HANELHChgTxn *)
  vfunctn: 0x38f428 -> 0x985c0 HACSECoreMgr::~HACSECoreMgr()
  vfunctn: 0x38f430 -> 0x988d0 HACSECoreMgr::~HACSECoreMgr()
  vfunctn: 0x38f438 -> 0x398400 HANEObserver::lhPRMsCallback_(HANEPRMSummary const&)
}

typeinfo 0x38f148 HACSECoreMgr {
  typedef: 0x38f150 -> 0x1550d8 `typeinfo name for'HACSECoreMgr
  typedef: 0x38f158 -> 0x398bd8 `typeinfo for'HANEObserver
  function: 0x832b0 HACSECoreMgr::getConfig(void)const
  function: 0x832c0 HACSECoreMgr::getEveChangeNL(void)const
  function: 0x832d0 HACSECoreMgr::getNetlist(void)const
  function: 0x832e0 HACSECoreMgr::getFloorplan(void)const
  function: 0x832f0 HACSECoreMgr::getTargetPart(void)const
  function: 0x83300 HACSECoreMgr::getHDManager(void)const
  function: 0x83320 HACSECoreMgr::isChipscopePRFlowEnabled(void)const
  function: 0x83330 HACSECoreMgr::isChipscopeXVCFlowEnabled(void)const
  function: 0x83340 HACSECoreMgr::isChipscopeSwitchEnabled(void)const
  function: 0x83350 HACSECoreMgr::getTopRPInstance(HDLHInstance const*)const
  function: 0x833a0 HACSECoreMgr::getTopRPInstanceName[abi:cxx11](HDLHInstance const*)
  function: 0x83430 HACSECoreMgr::getInserter(HDDCCoreSpec const*)const
  function: 0x83480 HACSECoreMgr::markProbePinNetsDontTouch(HDDCCoreInst *)
  function: 0x83690 HACSECoreMgr::getInsertableCore[abi:cxx11](void)const
  function: 0x836c0 HACSECoreMgr::getCoreSpec(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&)const
  function: 0x83960 HACSECoreMgr::forceToBlackBox(HDDCCoreInst *)
  function: 0x839d0 HACSECoreMgr::createPortAndInstTerm(HDDCPortSpec const*, HDDCCoreInst *, bool)
  function: 0x83a50 HACSECoreMgr::rmPortAndInstTerm(HDDCCoreInst *, HDDCPort *)
  function: 0x83ac0 HACSECoreMgr::getDebugCoreForInstance(HDLHInstance const*)const
  function: 0x83bc0 HACSECoreMgr::createDebugCoreSpecIter(void)const
  function: 0x83c20 HACSECoreMgr::findNeededSpec(HACSEConfig::CoreType)
  function: 0x83d60 HACSECoreMgr::markNeedsSave(void)
  function: 0x83e20 HACSECoreMgr::detectNets(void)
  function: 0x83e70 HACSECoreMgr::createDebugCoreIter(void)const
  function: 0x83ed0 HACSECoreMgr::setUnimplemented(HDDCCoreInst *)
  function: 0x83f00 HACSECoreMgr::setDebugPortWidth(HDDCPort *, int)
  function: 0x83fc0 HACSECoreMgr::updateDataModel(void)
  function: 0x84000 HACSECoreMgr::createMarkedDebugNetIter(void)
  function: 0x84020 HACSECoreMgr::unMarkDebugNets(HSTVector<HDLHNet *, std::allocator<HDLHNet *>> const&)
  function: 0x841c0 HACSECoreMgr::isMarkDebugNet(HDLHNet const*)const
  function: 0x84380 HACSECoreMgr::isNetOrBusConnected(HDLHElement *)
  function: 0x844c0 HACSECoreMgr::isMarkDebugNetOrBus(HDLHElement *)
  function: 0x84600 HACSECoreMgr::isPRShellDesign(void)const
  function: 0x84610 HACSECoreMgr::isDebuggableDesign(HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>> &, bool)
  function: 0x84620 HACSECoreMgr::isRPDesign(void)
  function: 0x84670 HACSECoreMgr::findDontModCVName(HDLHNet *, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> &)const
  function: 0x846a0 HACSECoreMgr::findProhibitCVName(HDLHNet *, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> &)const
  function: 0x84770 HACSECoreMgr::exportDebugProbes(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, bool, bool, HPFIHwDesign *)
  function: 0x84870 HACSECoreMgr::getUniqName(void)const
  function: 0x84880 HACSECoreMgr::getDebugCoreType(void)const
  function: 0x84890 HACSECoreMgr::getCoreClockNet(HDDCCoreInst const*)const
  function: 0x84a20 HACSECoreMgr::configureDebugCore(HDDCCoreInst *, HATOptGroup *, bool)
  function: 0x84ab0 HACSECoreMgr::getClocksForNetOrBusNet(HDLHNet const*, HSTVector<HDLHNet*, std::allocator<HDLHNet*>> &)
  function: 0x84fe0 HACSECoreMgr::getBlockramCount(HDDCCoreInst *)const
  function: 0x85030 HACSECoreMgr::netContainedInProbeProhibit(HDLHNet *, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> &)const
  function: 0x85460 HACSECoreMgr::hasChipscopeProhibitAttr(HDLHInstance const*)const
  function: 0x854b0 HACSECoreMgr::connectsToTopTerm(HDLHNet *, HANUFlatNetTraversal &)const
  function: 0x85670 HACSECoreMgr::connectsToGT(HDLHNet *, HANUFlatNetTraversal &)const
  function: 0x85950 HACSECoreMgr::netConnectedBetweenSynchronizer(HDLHNet *)const
  function: 0x85b40 HACSECoreMgr::netConnectedBetweenCascadeURAMCells(HDLHNet *, HANUFlatNetTraversal &)const
  function: 0x85e30 HACSECoreMgr::netConnectedBetweenGTandBUFGTCells(HDLHNet *, HANUFlatNetTraversal &)const
  function: 0x86250 HACSECoreMgr::exportDebugNetsToDefaultFile(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&)
  function: 0x86500 HACSECoreMgr::detectCores(bool)
  function: 0x86600 HACSECoreMgr::initCoreMgr(HFLFloorplan *, HACSTypes::HDDesignContext, bool)
  function: 0x86950 HACSECoreMgr::restoreAfterUpdNetlist(void)
  function: 0x86ca0 HACSECoreMgr::netContainedInChipscopeProhibit(HDLHNet *, HANUFlatNetTraversal &)const
  function: 0x86fa0 HACSECoreMgr::isDebuggableITerm(HDLHInstTerm *)const
  function: 0x87ac0 HACSECoreMgr::isImplementDebugCoresRequired(HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>> &)
  function: 0x87c50 HACSECoreMgr::isImplementDebugCoresRequired(void)
  function: 0x87ce0 HACSECoreMgr::canRemoveDebugPort(HDDCPort const*, HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>> &)const
  function: 0x87e90 HACSECoreMgr::generateDebugCoresReport(std::ostream &, bool, bool)
  function: 0x88320 HACSECoreMgr::createDebugPort(HDDCPortSpec const*, HDDCCoreInst *, HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>> &)
  function: 0x884b0 HACSECoreMgr::createDebugCore(HDDCCoreSpec const*, HDLHInstance *, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, bool, HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>> &)
  function: 0x88600 HACSECoreMgr::isDebuggableNet(HDLHNet *, HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const*, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const*>> *)const
  function: 0x89d80 HACSECoreMgr::markDebugNets(HSTVector<HDLHNet *, std::allocator<HDLHNet *>> const&)
  function: 0x89f20 HACSECoreMgr::disconnectDebugPort(HDDCCoreInst *, HDDCPort *, int)
  function: 0x8a3f0 HACSECoreMgr::removeDebugPorts(HSTVector<HDDCPort *, std::allocator<HDDCPort *>> const&, HSTVector&<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::allocator<char>>>)
  function: 0x8a5e0 HACSECoreMgr::addSourceNets(HSTVector<HDLHNet *, std::allocator<HDLHNet *>> const&)
  function: 0x8a8a0 HACSECoreMgr::clearAndSaveForUpdNetlist(void)
  function: 0x8add0 HACSECoreMgr::connectDebugPort(HDDCCoreInst *, HDDCPort *, int, HSTVector<HDLHNet *, std::allocator<HDLHNet *>> &, HSTVector&<HDLHInstTerm *, std::allocator<HDLHInstTerm>>)
  function: 0x8c4a0 HACSECoreMgr::addToUnconnectedSlave(HDLHInstance *)
  function: 0x8c540 HACSECoreMgr::removeFromUnconnectedSlave(HDLHInstance *)
  function: 0x8c6e0 HACSECoreMgr::connectDebugSlavesToMaster(HDLHInstance *, HSTVector<HDLHInstance *, std::allocator<HDLHInstance *>> &)
  function: 0x8d270 HACSECoreMgr::registerEveInserter(HDDCCoreSpec *, std::unique_ptr<HACSEBaseInserter> &)
  function: 0x8d3d0 HACSECoreMgr::init(void)
  function: 0x8d900 HACSECoreMgr::lhPostIncrChgCallback_(HANELHChgTxn *)
  function: 0x8dda0 HACSECoreMgr::lhPostIncrChgCallback(HANELHChgTxn *)
  function: 0x8e2f0 HACSECoreMgr::lhPreIncrChgCallback_(HANELHChgTxn *)
  function: 0x8f870 HACSECoreMgr::lhPreIncrChgCallback(HANELHChgTxn *)
  function: 0x91a50 HACSECoreMgr::getUniqueCoreName(int, HSTVector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>> const&)const
  function: 0x92490 HACSECoreMgr::rmCoreAndInst(HDDCCoreInst *)
  function: 0x92710 HACSECoreMgr::removeDebugCores(HSTVector<HDDCCoreInst *, std::allocator<HDDCCoreInst *>> const&)
  function: 0x92c30 HACSECoreMgr::mapInstanceToDebugCore(HDLHInstance *, HDDCCoreInst *)
  function: 0x93080 HACSECoreMgr::createCoreAndBlackBoxInst(HDDCCoreSpec const*, HDLHInstance *, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&)
  function: 0x93110 HACSECoreMgr::createEveHub(HDDCCoreSpec *, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &)
  function: 0x934e0 HACSECoreMgr::createEvePS(HDDCCoreSpec *, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &)
  function: 0x93800 HACSECoreMgr::createEveSMC(HDDCCoreSpec *, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &)
  function: 0x93b20 HACSECoreMgr::createEveNoc(HDDCCoreSpec *, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &)
  function: 0x93e60 HACSECoreMgr::connectHubToPs(HDDCCoreInst *, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &)
  function: 0x940d0 HACSECoreMgr::identifyDebugCore(HDDCCoreSpec *, HDLHInstance *, HDDCCoreInst *)
  function: 0x94420 HACSECoreMgr::createInstantiatedAXIEnabledSlaveCore(HDDCCoreSpec *, HDLHInstance *, std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &, HDDCCoreInst *)
  function: 0x949f0 HACSECoreMgr::getUnconnectedMarkDebugNets(HSTVector<HDLHNet *, std::allocator<HDLHNet *>> &)
  function: 0x95bc0 HACSECoreMgr::createCoreSpec(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, bool, bool)
  function: 0x95e20 HACSECoreMgr::filterNonDebuggableNets(HSTVector<HDLHNet *, std::allocator<HDLHNet *>> &, HSTVector&<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::allocator<char>>>, HSTVector&<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::allocator<std::allocator<char>>>)const
  function: 0x98210 HACSECoreMgr::HACSECoreMgr(HANENetlist *, HFLFloorplan *, HACGIPMgr *)
  function: 0x985c0 HACSECoreMgr::~HACSECoreMgr()
  function: 0x988d0 HACSECoreMgr::~HACSECoreMgr()
  function: 0x988f0 HACSECoreMgr::replaceBlackBoxWithActualCore(HDGUIStatus &, HSTVector<ComMsgMgrInstance, std::allocator<ComMsgMgrInstance>> &, HDDCCoreInst *)
  function: 0x98fb0 HACSECoreMgr::applyConstraintsToDebugCores(HFLFloorplan *, HSTVector<HDDCCoreInst *, std::allocator<HDDCCoreInst *>> &, HDGUIStatus &)
  function: 0x99b50 HACSECoreMgr::implementDebugCoreParallel(HFLFloorplan *, HSTVector<HDDCCoreInst *, std::allocator<HDDCCoreInst *>> &, HDGUIStatus &, HSTVector&<ComMsgMgrInstance, std::allocator<HSTVector&>>, bool)
  function: 0x9c310 HACSECoreMgr::implementDebugCoresTrigger(HFLFloorplan *, HDGUIStatus &, HDPLTask *)
  function: 0x9c940 HACSECoreMgr::reportDebugCores(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>> const&, bool, bool, bool, bool)
}
