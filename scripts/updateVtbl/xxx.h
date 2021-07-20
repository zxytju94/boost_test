#include <fstream>
#include <stdint.h>
#include <cstddef>
#include <vector>
#include <assert.h>
#include "common/common_utility.h"
#include "sp_SIwaveSimEngine/Pin.h"
#include "sp_Common/Common.h"

namespace nimbus {

class SiwaveDatabase;
class SIwaveGarbageCollector;
class PinGroup;
class Point;
class Net;
class Layer;

//=============== class Part ===============
class Part { //0xC8
 public:
  //Part_vtable* Part_vtable_ptr0_0x0;
  SiwaveDatabase* SiwaveDatabase_ptr0_0x8;
  std::vector<Pin*> vector_pin_0x10;
  char char8_0x28;
  int64_t* int64_t_ptr2_0x30;
  int64_t* int64_t_ptr3_0x38;
  int64_t* int64_t_ptr4_0x40; //std::map<> map_0x40;
  int64_t* int64_t_ptr5_0x48;
  int64_t* int64_t_ptr6_0x50;
  std::vector<PinGroup*> vector_pin_groups_0x58;
  int32_t int32_t1_0x70;
  int32_t int32_t2_0x74;
  int32_t int32_t4_0x78;
  int32_t int32_t5_0x7c;
  std::string std_string0_0x80;
  std::string std_string1_0x88;
  char char17_0x90;
  char char18_0x91;
  double double_0x98;
  char char19_0xa0;
  char char20_0xa1;
  int64_t* int64_t_ptr8_0xa8;
  int64_t* int64_t_ptr9_0xb0;
  int64_t* int64_t_ptr10_0xb8;
  AString std_string1_0xc0;

 public:
  Part();
  bool HasPinGroupContainingPin(Pin*) const;
  bool HasSamePinInMoreThanOneGroup() const;
  PinGroup* GetPinGroup(const AString&) const;
  bool PinGroupsExists() const;
  void SavePinGroups(FILE*) const;
  void WritePinGroupsToComponentFile(_IO_FILE*) const;
  Pin* GetPinByPosition(const Point&) const;
  void RemovePinReference(Pin*);
  void SetDisplayListId(unsigned int, int);
  void GetGreatestPinNumber();
  bool IsIgnored() const;
  bool IsSelected() const;
  bool IsVisible() const;
  bool IsActive() const;
  bool IsDistributed() const;
  bool IsJumper() const;
  bool IsPinGroupJumper() const;
  bool IsMarkedForDeletion() const;
  bool IsSIwizardGenerated() const;
  void ComputeSensitivity() const;
  void IncludeInPiOptimization() const;
  void ExposeInCpaNetlist() const;
  bool IsCapacitorPort() const;
  bool IsX2YCap() const;
  bool IsCpmGenerated() const;
  void SkipValidation() const;
  void SetVisible(bool);
  void SetDistributedFlag(bool);
  void SetIgnoreFlag(bool);
  void SetJumperFlag(bool);
  void SetPinGroupJumperFlag(bool);
  void MarkForDeletion(bool);
  void SetSIwizardGeneratedFlag(bool);
  void SetActive(bool);
  void SetComputeSensitivity(bool);
  void SetIncludeInPiOptimization(bool);
  void SetExposeInCpaNetlist(bool);
  void SetCapacitorPort(bool);
  void SetX2YCap(bool);
  void SetCpmGenerated(bool);
  void SetSkipValidation(bool);
  void RevertToBackupFlags();
  void UpdateParentNameInPins();
  void GetPinByNumber(char const*) const;
  void GetAllPinGroups(std::vector<PinGroup*> &) const;
  void GetPinsOnNet(Net const*, std::vector<Pin*> &) const;
  void CreatePinGroupByNet(Net const*);
  void RemovePinsOnNetFromGroups(Net const*);
  void AddPinGroup(PinGroup*);
  bool HasPinsOnDifferentLayers(bool, bool, std::map<Layer*,std::vector<Pin*>> *) const;
  void GetNextGroupName(std::string);
  void RemovePinGroup(PinGroup*);
  void DeletePinGroup(const AString&);
  void DeleteAllPinGroups();
  void ReadPinGroups(_IO_FILE*);
  void AddPin(Pin*);
  void GetAllPins(std::vector<Pin*> &, bool) const;

 public:
  virtual void dword_0() ;
  //virtual void dword_0() ;
  virtual void DeleteDisplayLists() ;
  virtual bool Clone() ;
  virtual void GetTypeString() const;
  virtual void SetSelected(bool) ;
  virtual void __cxa_pure_virtual() ;
  //virtual void __cxa_pure_virtual() ;
  //virtual void __cxa_pure_virtual() ;
  //virtual void __cxa_pure_virtual() ;
};

} // namespace nimbus

