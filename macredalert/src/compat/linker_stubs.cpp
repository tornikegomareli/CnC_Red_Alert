/*
 * linker_stubs.cpp — Stub definitions for all undefined symbols
 * Signatures match FUNCTION.H / WIN32LIB declarations exactly.
 * Purpose: get the linker to succeed on macOS.  Runtime correctness
 * is NOT a goal of this file.
 */

#include "FUNCTION.H"
#include "DDE.H"
#include "FIELD.H"
#include "TCPIP.H"
#include <string.h>
#include <stdlib.h>

/* ================================================================== */
/*  Audio                                                              */
/* ================================================================== */
void Sound_Effect(VocType voc, COORDINATE coord, int variation, HousesType house) {
    (void)voc; (void)coord; (void)variation; (void)house;
}
int Sound_Effect(VocType voc, fixed volume, int variation, signed short panvalue, HousesType house) {
    (void)voc; (void)volume; (void)variation; (void)panvalue; (void)house;
    return 0;
}
void Speak(VoxType voice) { (void)voice; }
void Speak_AI(void) {}
void Stop_Speaking(void) {}
bool Is_Speaking(void) { return false; }
void VQA_PauseAudio(void) {}
void Check_VQ_Palette_Set(void) {}
VocType Voc_From_Name(char const * name) { (void)name; return VOC_NONE; }
char const * Voc_Name(VocType voc) { (void)voc; return ""; }

/* ================================================================== */
/*  Platform (Phase 3)                                                 */
/* ================================================================== */
void Create_Main_Window(HANDLE inst, int show, int w, int h) { (void)inst; (void)show; (void)w; (void)h; }
void Prog_End(const char *msg, bool fatal) { (void)msg; (void)fatal; }
void Check_For_Focus_Loss(void) {}
void Memory_Error_Handler(void) {}
void Reset_Theater_Shapes(void) {}

/* ================================================================== */
/*  Mouse                                                              */
/* ================================================================== */
void Block_Mouse(GraphicBufferClass *buf) { (void)buf; }
void Unblock_Mouse(GraphicBufferClass *buf) { (void)buf; }

/* ================================================================== */
/*  Network                                                            */
/* ================================================================== */
bool Init_Network(void) { return false; }
void Shutdown_Network(void) {}
bool Remote_Connect(void) { return false; }
void Modem_Signoff(void) {}
void Shutdown_Modem(void) {}
int Reconnect_Modem(void) { return 0; }
unsigned long Compute_Name_CRC(char *name) { (void)name; return 0; }
void Destroy_Connection(int id, int error) { (void)id; (void)error; }
bool Process_Global_Packet(GlobalPacketType *pkt, IPXAddressClass *addr) { (void)pkt; (void)addr; return false; }
void Net_Reconnect_Dialog(int a, int b, int c, unsigned long d) { (void)a; (void)b; (void)c; (void)d; }
void WWDebugString(char *s) { (void)s; }
void Destroy_Null_Connection(int id, int error) { (void)id; (void)error; }
void Check_From_WChat(char *wchat_name) { (void)wchat_name; }
bool Client_Remote_Connect(void) { return false; }
bool Server_Remote_Connect(void) { return false; }
bool Spawn_WChat(bool can_launch) { (void)can_launch; return false; }
int Com_Show_Scenario_Dialog(void) { return 0; }

/* ================================================================== */
/*  Dialogs                                                            */
/* ================================================================== */
char const * Map_Selection(void) { return NULL; }
int Surrender_Dialog(int text) { (void)text; return 0; }
int Surrender_Dialog(const char *text) { (void)text; return 0; }
int Com_Scenario_Dialog(bool skirmish) { (void)skirmish; return 0; }
GameType Select_MPlayer_Game(void) { return GAME_NORMAL; }
GameType Select_Serial_Dialog(void) { return GAME_NORMAL; }

/* ================================================================== */
/*  Score                                                              */
/* ================================================================== */
void Register_Game_End_Time(void) {}
void Register_Game_Start_Time(void) {}
void Send_Statistics_Packet(void) {}
void Multi_Score_Presentation(void) {}

void ScoreClass::Init(void) {}
void ScoreClass::Presentation(void) {}

/* ================================================================== */
/*  Misc                                                               */
/* ================================================================== */
unsigned long Get_CPU_Clock(unsigned long &high) { high = 0; return 1000000; }
int First_False_Bit(const void *data) { (void)data; return 0; }
int Get_Bit(const void *data, int bit) { (void)data; (void)bit; return 0; }
void Set_Bit(void *data, int bit, int val) { (void)data; (void)bit; (void)val; }
int Bound(int val, int lo, int hi) { if (val < lo) return lo; if (val > hi) return hi; return val; }
int calcx(short a, short b) { (void)a; (void)b; return 0; }
int calcy(short a, short b) { (void)a; (void)b; return 0; }
void output(short a, short b) { (void)a; (void)b; }
void outrgb(unsigned char r, unsigned char g, unsigned char b) { (void)r; (void)g; (void)b; }
void outportb(int port, unsigned char val) { (void)port; (void)val; }

int ABS(int v) { return v < 0 ? -v : v; }
int MAX(int a, int b) { return a > b ? a : b; }
int MIN(int a, int b) { return a < b ? a : b; }
long MIN(long a, long b) { return a < b ? a : b; }
unsigned int Fixed_To_Cardinal(unsigned int base, unsigned int fixed) {
    (void)base; (void)fixed; return 0;
}

/* ================================================================== */
/*  Crypto                                                             */
/* ================================================================== */
Int<MAX_UNIT_PRECISION> Generate_Prime(Straw &rng, int bits, Int<MAX_UNIT_PRECISION> const *test) {
    (void)rng; (void)bits; (void)test;
    Int<MAX_UNIT_PRECISION> result;
    return result;
}

/* XMP functions (multi-precision math) */
unsigned XMP_Count_Bits(const unsigned long * r, int precision) { (void)r; (void)precision; return 0; }
void XMP_DER_Decode(unsigned long * result, unsigned char const * input, int precision) { (void)result; (void)input; (void)precision; }
int XMP_DER_Encode(unsigned long const * from, unsigned char * output, int precision) { (void)from; (void)output; (void)precision; return 0; }
int xmp_exponent_mod(unsigned long * expout, unsigned long const * expin, unsigned long const * exponent_ptr, unsigned long const * modulus, int precision) {
    (void)expout; (void)expin; (void)exponent_ptr; (void)modulus; (void)precision; return 0;
}
void XMP_Init(unsigned long * r, unsigned long value, int precision) { (void)r; (void)value; (void)precision; }
void XMP_Inverse_A_Mod_B(unsigned long * result, unsigned long const * number, unsigned long const * modulus, int precision) {
    (void)result; (void)number; (void)modulus; (void)precision;
}
int XMP_Signed_Mult(unsigned long * prod, unsigned long const * multiplicand, unsigned long const * multiplier, int precision) {
    (void)prod; (void)multiplicand; (void)multiplier; (void)precision; return 0;
}
bool XMP_Sub_Int(unsigned long * result, unsigned long const * r1, unsigned short r2, bool borrow, int precision) {
    (void)result; (void)r1; (void)r2; (void)borrow; (void)precision; return false;
}

/* ================================================================== */
/*  Enum bitwise operators                                             */
/*  These are declared 'inline' in headers but never defined.  We     */
/*  need __attribute__((used)) to force emission despite the inline    */
/*  linkage inherited from the forward declaration.                    */
/* ================================================================== */
#define FORCE_EMIT __attribute__((used, noinline))

FORCE_EMIT ThreatType operator&(ThreatType a, ThreatType b) { return (ThreatType)((int)a & (int)b); }
FORCE_EMIT ThreatType operator|(ThreatType a, ThreatType b) { return (ThreatType)((int)a | (int)b); }
FORCE_EMIT ThreatType operator~(ThreatType a) { return (ThreatType)(~(int)a); }

FORCE_EMIT TextPrintType operator&(TextPrintType a, TextPrintType b) { return (TextPrintType)((int)a & (int)b); }
FORCE_EMIT TextPrintType operator|(TextPrintType a, TextPrintType b) { return (TextPrintType)((int)a | (int)b); }
FORCE_EMIT TextPrintType operator~(TextPrintType a) { return (TextPrintType)(~(int)a); }

FORCE_EMIT GadgetClass::FlagEnum operator|(GadgetClass::FlagEnum a, GadgetClass::FlagEnum b) { return (GadgetClass::FlagEnum)((int)a | (int)b); }
FORCE_EMIT GadgetClass::FlagEnum operator~(GadgetClass::FlagEnum a) { return (GadgetClass::FlagEnum)(~(int)a); }

FORCE_EMIT DriveClass::TrackControlType operator&(DriveClass::TrackControlType a, DriveClass::TrackControlType b) { return (DriveClass::TrackControlType)((int)a & (int)b); }
FORCE_EMIT DriveClass::TrackControlType operator|(DriveClass::TrackControlType a, DriveClass::TrackControlType b) { return (DriveClass::TrackControlType)((int)a | (int)b); }

FORCE_EMIT EditClass::EditStyle operator&(EditClass::EditStyle a, EditClass::EditStyle b) { return (EditClass::EditStyle)((int)a & (int)b); }

FORCE_EMIT ShapeFlags_Type operator&(ShapeFlags_Type a, ShapeFlags_Type b) { return (ShapeFlags_Type)((int)a & (int)b); }
FORCE_EMIT ShapeFlags_Type operator|(ShapeFlags_Type a, ShapeFlags_Type b) { return (ShapeFlags_Type)((int)a | (int)b); }
FORCE_EMIT ShapeFlags_Type operator~(ShapeFlags_Type a) { return (ShapeFlags_Type)(~(int)a); }

/* ================================================================== */
/*  Enum increment operators                                           */
/* ================================================================== */
#define ENUM_INC(T) FORCE_EMIT T operator++(T &v, int) { T old = v; v = (T)((int)v + 1); return old; }
ENUM_INC(BulletType)
ENUM_INC(FacingType)
ENUM_INC(HousesType)
ENUM_INC(SmudgeType)
ENUM_INC(StructType)
ENUM_INC(VesselType)
ENUM_INC(OverlayType)
ENUM_INC(TerrainType)
ENUM_INC(TheaterType)
ENUM_INC(AircraftType)
ENUM_INC(InfantryType)
ENUM_INC(TemplateType)
ENUM_INC(AnimType)
ENUM_INC(UnitType)
ENUM_INC(LayerType)
ENUM_INC(ThemeType)
FORCE_EMIT ScenarioVarEnum operator++(ScenarioVarEnum &v, int) { ScenarioVarEnum old = v; v = (ScenarioVarEnum)((int)v + 1); return old; }

/* ================================================================== */
/*  CCPtr template instantiations                                      */
/* ================================================================== */
/* CCPtr<T>::CCPtr(T*) — the template body is in CCPTR.CPP but with
   delayed template parsing it is not visible here.  Redefine the body
   and force-instantiate. */
template<class T>
CCPtr<T>::CCPtr(T * ptr) : ID(-1) { if (ptr) ID = ptr->ID; }

template<class T>
bool CCPtr<T>::operator > (CCPtr<T> const & rvalue) const {
    return (stricmp((*this)->Name(), rvalue->Name()) > 0);
}

template class CCPtr<AircraftTypeClass>;
template class CCPtr<AnimTypeClass>;
template class CCPtr<BuildingTypeClass>;
template class CCPtr<BulletTypeClass>;
template class CCPtr<FactoryClass>;
template class CCPtr<HouseClass>;
template class CCPtr<HouseTypeClass>;
template class CCPtr<InfantryTypeClass>;
template class CCPtr<OverlayTypeClass>;
template class CCPtr<SmudgeTypeClass>;
template class CCPtr<TeamClass>;
template class CCPtr<TeamTypeClass>;
template class CCPtr<TemplateTypeClass>;
template class CCPtr<TerrainTypeClass>;
template class CCPtr<TriggerClass>;
template class CCPtr<TriggerTypeClass>;
template class CCPtr<UnitTypeClass>;
template class CCPtr<VesselTypeClass>;

/* ================================================================== */
/*  DynamicVectorClass template instantiations                         */
/* ================================================================== */
/* VECTOR.CPP has these but with -fdelayed-template-parsing the method */
/* bodies (defined in VECTOR.H) may not get instantiated.  We provide */
/* the method bodies and explicit instantiations here.                 */

/* Provide the template method bodies that are defined in VECTOR.H    */
/* but may not be parsed due to delayed template parsing.              */

template<class T>
VectorClass<T>::VectorClass(unsigned size, T const * array) :
    Vector(0), VectorMax(size), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new((void*)new char[sizeof(T)*size]) T[size];
            IsAllocated = true;
            for (unsigned i = 0; i < size; i++) Vector[i] = array[i];
        } else {
            Vector = new((void*)new char[sizeof(T)*size]) T[size];
            IsAllocated = true;
        }
    }
}

template<class T>
VectorClass<T>::~VectorClass() {
    Clear();
}

template<class T>
void VectorClass<T>::Clear() {
    if (Vector && IsAllocated) {
        delete[] (char*)Vector;
        Vector = 0;
    }
    IsAllocated = false;
    VectorMax = 0;
}

template<class T>
int VectorClass<T>::Resize(unsigned newsize, T const * array) {
    if (newsize) {
        T * newptr = new((void*)new char[sizeof(T)*newsize]) T[newsize];
        if (!newptr) return false;
        if (this->Vector) {
            unsigned copycount = (newsize < VectorMax) ? newsize : VectorMax;
            for (unsigned i = 0; i < copycount; i++) newptr[i] = this->Vector[i];
            if (IsAllocated) delete[] (char*)this->Vector;
        }
        this->Vector = newptr;
        this->IsAllocated = true;
        this->VectorMax = newsize;
    } else {
        Clear();
    }
    return true;
}

template<class T>
int VectorClass<T>::ID(T const * ptr) {
    if (ptr && Vector) return (int)(((char*)ptr - (char*)Vector) / sizeof(T));
    return 0;
}

template<class T>
int VectorClass<T>::ID(T const & object) {
    for (unsigned i = 0; i < VectorMax; i++) {
        if (Vector[i] == object) return (int)i;
    }
    return -1;
}

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const * array)
    : VectorClass<T>(size, array), ActiveCount(0), GrowthStep(10) {}

template<class T>
int DynamicVectorClass<T>::Resize(unsigned newsize, T const * array) {
    if (VectorClass<T>::Resize(newsize, array)) {
        if (this->VectorMax < (unsigned)ActiveCount) ActiveCount = this->VectorMax;
        return true;
    }
    return false;
}

template<class T>
int DynamicVectorClass<T>::Add(T const & object) {
    if ((unsigned)ActiveCount >= this->VectorMax) {
        if ((GrowthStep == 0) || !Resize(this->VectorMax + GrowthStep)) return false;
    }
    this->Vector[ActiveCount++] = object;
    return true;
}

template<class T>
int DynamicVectorClass<T>::Add_Head(T const & object) {
    if ((unsigned)ActiveCount >= this->VectorMax) {
        if ((GrowthStep == 0) || !Resize(this->VectorMax + GrowthStep)) return false;
    }
    if (ActiveCount) {
        for (int i = ActiveCount-1; i >= 0; i--) this->Vector[i+1] = this->Vector[i];
    }
    this->Vector[0] = object;
    ActiveCount++;
    return true;
}

template<class T>
int DynamicVectorClass<T>::Delete(T const & object) {
    int idx = ID(object);
    if (idx != -1) return Delete(idx);
    return false;
}

template<class T>
int DynamicVectorClass<T>::Delete(int index) {
    if ((unsigned)index < (unsigned)ActiveCount) {
        ActiveCount--;
        for (int i = index; i < ActiveCount; i++) this->Vector[i] = this->Vector[i+1];
        return true;
    }
    return false;
}

template<class T>
int DynamicVectorClass<T>::ID(T const & object) {
    for (int i = 0; i < ActiveCount; i++) {
        if (this->Vector[i] == object) return i;
    }
    return -1;
}

/* Now instantiate all needed types */
template class DynamicVectorClass<void *>;
template class DynamicVectorClass<ObjectClass *>;
template class DynamicVectorClass<TriggerClass *>;
template class DynamicVectorClass<char const *>;
template class DynamicVectorClass<char *>;
template class DynamicVectorClass<BaseNodeClass>;
template class DynamicVectorClass<RemapControlType *>;
template class DynamicVectorClass<PhoneEntryClass *>;
template class DynamicVectorClass<FileEntryClass *>;
template class DynamicVectorClass<MultiMission *>;
template class DynamicVectorClass<NodeNameTag *>;
/* EgoClass* needs explicit instantiation of the methods that EGOS.CPP
   doesn't trigger (Add, Delete, ctor with args). */
template DynamicVectorClass<EgoClass*>::DynamicVectorClass(unsigned, EgoClass* const*);
template int DynamicVectorClass<EgoClass*>::Add(EgoClass* const&);
template int DynamicVectorClass<EgoClass*>::Delete(int);

/* ================================================================== */
/*  TFixedIHeapClass template instantiations                           */
/* ================================================================== */
#define INST_TFIXED(T) \
    template<> int TFixedIHeapClass<T>::Save(Pipe & file) const { (void)file; return 0; } \
    template<> int TFixedIHeapClass<T>::Load(Straw & file) { (void)file; return 0; } \
    template<> void TFixedIHeapClass<T>::Code_Pointers(void) {} \
    template<> void TFixedIHeapClass<T>::Decode_Pointers(void) {}

INST_TFIXED(AircraftClass)
INST_TFIXED(AircraftTypeClass)
INST_TFIXED(AnimClass)
INST_TFIXED(AnimTypeClass)
INST_TFIXED(BuildingClass)
INST_TFIXED(BuildingTypeClass)
INST_TFIXED(BulletClass)
INST_TFIXED(BulletTypeClass)
INST_TFIXED(FactoryClass)
INST_TFIXED(HouseClass)
INST_TFIXED(HouseTypeClass)
INST_TFIXED(InfantryClass)
INST_TFIXED(InfantryTypeClass)
INST_TFIXED(OverlayClass)
INST_TFIXED(OverlayTypeClass)
INST_TFIXED(SmudgeClass)
INST_TFIXED(SmudgeTypeClass)
INST_TFIXED(TeamClass)
INST_TFIXED(TeamTypeClass)
INST_TFIXED(TemplateClass)
INST_TFIXED(TemplateTypeClass)
INST_TFIXED(TerrainClass)
INST_TFIXED(TerrainTypeClass)
INST_TFIXED(TriggerClass)
INST_TFIXED(TriggerTypeClass)
INST_TFIXED(UnitClass)
INST_TFIXED(UnitTypeClass)
INST_TFIXED(VesselClass)
INST_TFIXED(VesselTypeClass)
INST_TFIXED(WarheadTypeClass)
INST_TFIXED(WeaponTypeClass)

/* ================================================================== */
/*  MixFileClass<CCFileClass>                                          */
/* ================================================================== */
#include "MIXFILE.H"

template<> List<MixFileClass<CCFileClass>> MixFileClass<CCFileClass>::List;

template<> MixFileClass<CCFileClass>::MixFileClass(char const *filename, PKey const * key) :
    Filename(filename), IsDigest(false), IsEncrypted(false), IsAllocated(false),
    Count(0), DataSize(0), DataStart(0), HeaderBuffer(nullptr), Data(nullptr) {
    (void)key;
}
template<> MixFileClass<CCFileClass>::~MixFileClass() {}
template<> bool MixFileClass<CCFileClass>::Cache(Buffer const * buffer) { (void)buffer; return false; }
template<> bool MixFileClass<CCFileClass>::Cache(char const *filename, Buffer const * buffer) { (void)filename; (void)buffer; return false; }
template<> bool MixFileClass<CCFileClass>::Offset(char const *filename, void ** realptr, MixFileClass<CCFileClass> ** mixfile, long * offset, long * size) {
    (void)filename; (void)realptr; (void)mixfile; (void)offset; (void)size; return false;
}
template<> void const * MixFileClass<CCFileClass>::Retrieve(char const *filename) { (void)filename; return nullptr; }

/* ================================================================== */
/*  Timer classes (WIN32LIB)                                           */
/* ================================================================== */
TimerClass::TimerClass(BaseTimerEnum timer, BOOL start) : Started(0), Accumulated(0), TickType(timer) {
    (void)start;
}
long TimerClass::Time(void) { return 0; }
long TimerClass::Set(long value, BOOL start) { (void)value; (void)start; Accumulated = 0; return 0; }
long TimerClass::Stop(void) { return 0; }
long TimerClass::Start(void) { return 0; }
long TimerClass::Get_Ticks(void) { return 0; }

CountDownTimerClass::CountDownTimerClass(BaseTimerEnum timer, long set, int on) : TimerClass(timer, on), DelayTime(set) { (void)on; }
CountDownTimerClass::CountDownTimerClass(BaseTimerEnum timer, int on) : TimerClass(timer, on), DelayTime(0) { (void)on; }
long CountDownTimerClass::Set(long set, BOOL start) { (void)start; DelayTime = set; return set; }
long CountDownTimerClass::Time(void) { return 0; }

WinTimerClass::WinTimerClass(unsigned int freq, BOOL partial) : TimerHandle(0), Frequency(freq), TrueRate(0), SysTicks(0), UserTicks(0), UserRate(0) {
    (void)partial;
}
WinTimerClass::~WinTimerClass() {}
unsigned WinTimerClass::Get_System_Tick_Count(void) { return 0; }

/* ================================================================== */
/*  IPXAddressClass                                                    */
/* ================================================================== */
IPXAddressClass::IPXAddressClass() { memset(this, 0, sizeof(*this)); }
IPXAddressClass::IPXAddressClass(unsigned char *net, unsigned char *node) { (void)net; (void)node; memset(this, 0, sizeof(*this)); }
int IPXAddressClass::Is_Broadcast() { return 0; }
int IPXAddressClass::operator==(IPXAddressClass &other) { (void)other; return 0; }

/* ================================================================== */
/*  IPXManagerClass                                                    */
/* ================================================================== */
IPXManagerClass::IPXManagerClass(int glb_maxlen, int pvt_maxlen, int glb_num_packets,
    int pvt_num_packets, unsigned short socket, unsigned short product_id) :
    IPXStatus(0), Listening(0), RealMemAllocd(0),
    Glb_MaxPacketLen(glb_maxlen), Glb_NumPackets(glb_num_packets),
    Pvt_MaxPacketLen(pvt_maxlen), Pvt_NumPackets(pvt_num_packets),
    ProductID(product_id), Socket(socket), ConnectionNum(0),
    NumConnections(0), GlobalChannel(nullptr), CurConnection(0),
    RetryDelta(0), MaxRetries(0), Timeout(0),
    NumBufs(0), PacketLen(0), FullPacketLen(0),
    Selector(0), Segment(0), RealMemSize(0), RealModeData(nullptr),
    Handler(0), ListenECB(nullptr),
    FirstHeaderBuf(nullptr), FirstDataBuf(nullptr),
    CurIndex(0), CurHeaderBuf(nullptr), CurDataBuf(nullptr),
    SendECB(nullptr), SendHeader(nullptr), SendBuf(nullptr), BufferFlags(nullptr),
    SendOverflows(0), ReceiveOverflows(0), BadConnection(0) {
    memset(Connection, 0, sizeof(Connection));
}
IPXManagerClass::~IPXManagerClass() {}
int IPXManagerClass::Num_Connections(void) { return 0; }
int IPXManagerClass::Connection_ID(int index) { (void)index; return 0; }
char * IPXManagerClass::Connection_Name(int id) { (void)id; return (char*)""; }
IPXAddressClass * IPXManagerClass::Connection_Address(int id) { (void)id; return nullptr; }
int IPXManagerClass::Create_Connection(int id, char *name, IPXAddressClass *address) { (void)id; (void)name; (void)address; return 0; }
int IPXManagerClass::Delete_Connection(int id) { (void)id; return 0; }
int IPXManagerClass::Get_Global_Message(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id) {
    (void)buf; (void)buflen; (void)address; (void)product_id; return 0;
}
int IPXManagerClass::Send_Global_Message(void *buf, int buflen, int ack_req, IPXAddressClass *address) {
    (void)buf; (void)buflen; (void)ack_req; (void)address; return 0;
}
int IPXManagerClass::Service(void) { return 0; }
void IPXManagerClass::Set_Socket(unsigned short socket) { (void)socket; }
void IPXManagerClass::Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout) {
    (void)retrydelta; (void)maxretries; (void)timeout;
}
unsigned long IPXManagerClass::Response_Time(void) { return 0; }
void IPXManagerClass::Reset_Response_Time(void) {}
int IPXManagerClass::Send_Private_Message(void *buf, int buflen, int ack_req, int conn_id) {
    (void)buf; (void)buflen; (void)ack_req; (void)conn_id; return 0;
}
int IPXManagerClass::Get_Private_Message(void *buf, int *buflen, int *conn_id) {
    (void)buf; (void)buflen; (void)conn_id; return 0;
}
int IPXManagerClass::Global_Num_Send(void) { return 0; }
int IPXManagerClass::Global_Num_Receive(void) { return 0; }
int IPXManagerClass::Private_Num_Send(int id) { (void)id; return 0; }
int IPXManagerClass::Private_Num_Receive(int id) { (void)id; return 0; }
int IPXManagerClass::Connection_Index(int id) { (void)id; return 0; }
void IPXManagerClass::Configure_Debug(int index, int type_offset, int type_size, char **names, int namestart, int namecount) {
    (void)index; (void)type_offset; (void)type_size; (void)names; (void)namestart; (void)namecount;
}
void IPXManagerClass::Mono_Debug_Print(int index, int refresh) { (void)index; (void)refresh; }

/* ================================================================== */
/*  NullModemClass                                                     */
/* ================================================================== */
NullModemClass::NullModemClass(int numsend, int numreceive, int maxlen, unsigned short magicnum) :
    BuildBuf(nullptr), MaxLen(maxlen), EchoBuf(nullptr), EchoSize(0), EchoCount(0),
    OldIRQPri(0), ModemVerboseOn(0), ModemEchoOn(0), ModemWaitCarrier(0),
    ModemCarrierDetect(0), ModemCarrierLoss(0), ModemHangupDelay(0),
    ModemGuardTime(0), ModemEscapeCode('+'),
    Connection(nullptr), NumConnections(0),
    PortHandle(nullptr),
    NumSend(numsend), NumReceive(numreceive), MagicNum(magicnum),
    RXBuf(nullptr), RXSize(0), RXCount(0),
    RetryDelta(0), MaxRetries(0), Timeout(0),
    SendOverflows(0), ReceiveOverflows(0), CRCErrors(0) {
}
NullModemClass::~NullModemClass() {}
int NullModemClass::Num_Connections(void) { return 0; }
int NullModemClass::Init_Send_Queue(void) { return 0; }
int NullModemClass::Send_Message(void *buf, int buflen, int ack_req) { (void)buf; (void)buflen; (void)ack_req; return 0; }
int NullModemClass::Service(void) { return 0; }
void NullModemClass::Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout) {
    (void)retrydelta; (void)maxretries; (void)timeout;
}
unsigned long NullModemClass::Response_Time(void) { return 0; }
void NullModemClass::Reset_Response_Time(void) {}
int NullModemClass::Get_Message(void *buf, int *buflen) { (void)buf; (void)buflen; return 0; }
int NullModemClass::Num_Send(void) { return 0; }
int NullModemClass::Num_Receive(void) { return 0; }
void NullModemClass::Configure_Debug(int index, int type_offset, int type_size, char **names, int namestart, int namecount) {
    (void)index; (void)type_offset; (void)type_size; (void)names; (void)namestart; (void)namecount;
}

/* Static members */
void (*NullModemClass::OrigAbortModemFunc)(int) = nullptr;
KeyNumType NullModemClass::Input = KN_NONE;
GadgetClass *NullModemClass::Commands = nullptr;

/* ================================================================== */
/*  TcpipManagerClass                                                  */
/* ================================================================== */
TcpipManagerClass::TcpipManagerClass() :
    WinsockInitialised(FALSE), ListenSocket(INVALID_SOCKET), ConnectSocket(INVALID_SOCKET),
    UDPSocket(INVALID_SOCKET), Async(nullptr), IsServer(FALSE), Connected(FALSE),
    ConnectStatus(NOT_CONNECTING), UseUDP(FALSE), SocketReceiveBuffer(0), SocketSendBuffer(0),
    TXBufferHead(0), TXBufferTail(0), RXBufferHead(0), RXBufferTail(0) {
    memset(HostAddress, 0, sizeof(HostAddress));
    memset(ReceiveBuffer, 0, sizeof(ReceiveBuffer));
    memset(ClientName, 0, sizeof(ClientName));
    memset(HostBuff, 0, sizeof(HostBuff));
    memset(&WinsockInfo, 0, sizeof(WinsockInfo));
    memset(&ClientIPAddress, 0, sizeof(ClientIPAddress));
    memset(&UDPIPAddress, 0, sizeof(UDPIPAddress));
    memset(&Server, 0, sizeof(Server));
    memset(ReceiveBuffers, 0, sizeof(ReceiveBuffers));
    memset(TransmitBuffers, 0, sizeof(TransmitBuffers));
}
TcpipManagerClass::~TcpipManagerClass() {}
BOOL TcpipManagerClass::Init(void) { return FALSE; }
void TcpipManagerClass::Start_Server(void) {}
void TcpipManagerClass::Start_Client(void) {}
int TcpipManagerClass::Read(void *buffer, int buffer_len) { (void)buffer; (void)buffer_len; return 0; }
void TcpipManagerClass::Close(void) {}
void TcpipManagerClass::Set_Host_Address(char *address) { (void)address; }

/* ================================================================== */
/*  Instance_Class (DDE)                                               */
/* ================================================================== */
DWORD Instance_Class::id_inst = 0;
BOOL Instance_Class::process_pokes = FALSE;
char Instance_Class::ascii_name[32] = {};
BOOL (CALLBACK *Instance_Class::callback)(LPBYTE, long) = nullptr;

Instance_Class::Instance_Class(LPSTR local_name, LPSTR remote_name) {
    (void)local_name; (void)remote_name;
    instance = nullptr;
    hwnd = nullptr;
    this->remote_name = 0;
    this->local_name = 0;
    system_topic = 0;
    poke_topic = 0;
    poke_item = 0;
    conv_handle = 0;
    dde_error = FALSE;
}
Instance_Class::~Instance_Class() {}
BOOL Instance_Class::Poke_Server(LPBYTE data, DWORD len) { (void)data; (void)len; return FALSE; }
BOOL Instance_Class::Register_Server(BOOL CALLBACK (*func)(LPBYTE, long)) { (void)func; return FALSE; }
BOOL Instance_Class::Test_Server_Running(HSZ hsz) { (void)hsz; return FALSE; }
BOOL Instance_Class::Enable_Callback(BOOL enable) { (void)enable; return FALSE; }
BOOL Instance_Class::Open_Poke_Connection(HSZ hsz) { (void)hsz; return FALSE; }
BOOL Instance_Class::Close_Poke_Connection(void) { return FALSE; }

/* ================================================================== */
/*  FieldClass                                                         */
/* ================================================================== */
void FieldClass::Host_To_Net(void) {}
void FieldClass::Net_To_Host(void) {}

/* ================================================================== */
/*  GetCDClass                                                         */
/* ================================================================== */
GetCDClass::GetCDClass() {}
GetCDClass::~GetCDClass() {}

/* ================================================================== */
/*  IconCacheClass                                                     */
/* ================================================================== */
IconCacheClass::IconCacheClass() : TimesDrawn(0), TimesFailed(0), CacheSurface(nullptr), IsCached(FALSE), SurfaceLost(FALSE), DrawFrequency(0), IconSource(nullptr) {}
IconCacheClass::~IconCacheClass() {}
void IconCacheClass::Draw_It(LPDIRECTDRAWSURFACE dest_surface, int x_pixel, int y_pixel,
    int window_left, int window_top, int window_width, int window_height) {
    (void)dest_surface; (void)x_pixel; (void)y_pixel;
    (void)window_left; (void)window_top; (void)window_width; (void)window_height;
}

/* ================================================================== */
/*  SurfaceMonitorClass method stubs                                   */
/* ================================================================== */
SurfaceMonitorClass::SurfaceMonitorClass() : SurfacesRestored(FALSE), InFocus(FALSE) {
    memset(Surface, 0, sizeof(Surface));
}
void SurfaceMonitorClass::Add_DD_Surface(LPDIRECTDRAWSURFACE s) { (void)s; }
void SurfaceMonitorClass::Remove_DD_Surface(LPDIRECTDRAWSURFACE s) { (void)s; }
void SurfaceMonitorClass::Restore_Surfaces(void) {}
void SurfaceMonitorClass::Set_Surface_Focus(BOOL in_focus) { (void)in_focus; }

/* ================================================================== */
/*  MPGSettings                                                        */
/* ================================================================== */
/* Only used under #ifdef DVD.  The undefined symbol suggests the code
   still references it.  We provide the minimal ctor. */
#ifdef DVD
MPGSettings::MPGSettings(const char* deviceName) : mDeviceName(nullptr) { (void)deviceName; }
MPGSettings::~MPGSettings() {}
#endif

/* ================================================================== */
/*  TurretClass — vtable key functions never defined in source         */
/* ================================================================== */
void TurretClass::Code_Pointers(void) { DriveClass::Code_Pointers(); }
void TurretClass::Decode_Pointers(void) { DriveClass::Decode_Pointers(); }

/* ================================================================== */
/*  PaletteClass static member                                         */
/* ================================================================== */
PaletteClass PaletteClass::CurrentPalette;

/* ================================================================== */
/*  C++ linkage globals (declared in headers without extern "C")       */
/* ================================================================== */

/* WIN32LIB globals */
LPDIRECTDRAW DirectDrawObject = nullptr;
LPDIRECTDRAWSURFACE PaletteSurface = nullptr;
LPDIRECTSOUND SoundObject = nullptr;
LPDIRECTSOUNDBUFFER PrimaryBufferPtr = nullptr;
HWND MainWindow = nullptr;
BOOL OverlappedVideoBlits = FALSE;
SurfaceMonitorClass AllSurfaces;
void (*Misc_Focus_Loss_Function)(void) = nullptr;

/* Timer globals */
BOOL TimerSystemOn = FALSE;
HANDLE TimerThreadHandle = nullptr;
int InTimerCallback = 0;
/* WindowsTimer and TickCount are defined in GLOBALS.CPP */
CountDownTimerClass CountDown;

/* Icon caching */
IconCacheClass CachedIcons[500];
int CachedIconsDrawn = 0;
int UnCachedIconsDrawn = 0;

/* Game-code globals (EXTERNS.H) */
bool ConnectionLost = false;
bool GameStatisticsPacketSent = false;
void *PacketLater = nullptr;
bool SpawnedFromWChat = false;
char PlanetWestwoodIPAddress[40] = {};
bool PlanetWestwoodIsHost = false;
bool IsTheaterShape = false;
int ShowCommand = 0;
bool WindowsNT = false;

/* TcpipManagerClass */
TcpipManagerClass Winsock;
bool Server = false;

/* WinsockInterfaceClass pointer (from _WSPROTO.H) */
class WinsockInterfaceClass;
WinsockInterfaceClass *PacketTransport = nullptr;

/* Timer used by DDE code (CCDDE.CPP) */
TimerClass GameTimer(BT_SYSTEM, FALSE);
BOOL GameTimerInUse = FALSE;

/* Read_Game_Options — declared as int Read_Game_Options(char*) in TCPIP.H
   but also as void in the compat layer. The linker wants the C++ one. */
int Read_Game_Options(char *) { return 0; }

/* ================================================================== */
/*  C-linkage globals and functions                                    */
/* ================================================================== */
extern "C" {

/* WIN32LIB shape globals */
char *_ShapeBuffer = nullptr;
void *BackGroundPage = nullptr;
void *MaskPage = nullptr;

/* Random number seed - the linker wants _RandNumb as C-linkage */
int RandNumb = 0;

/* Audio misc */
int Misc = 0;

/* LPDIRECTDRAWPALETTE */
LPDIRECTDRAWPALETTE PalettePtr = nullptr;

/* WIN32LIB ASM / low-level stubs */
unsigned int Apply_XOR_Delta(char *source_ptr, char *delta_ptr) { (void)source_ptr; (void)delta_ptr; return 0; }
void Apply_XOR_Delta_To_Page_Or_Viewport(void *target, void *delta, int width, int nextrow, int copy) {
    (void)target; (void)delta; (void)width; (void)nextrow; (void)copy;
}
void Asm_Interpolate(unsigned char *src_ptr, unsigned char *dest_ptr, int lines, int src_width, int dest_width) {
    (void)src_ptr; (void)dest_ptr; (void)lines; (void)src_width; (void)dest_width;
}
void Asm_Interpolate_Line_Double(void) {}
void Asm_Interpolate_Line_Interpolate(void) {}
long Buffer_Frame_To_Page(int x, int y, int w, int h, void *Buffer, GraphicViewPortClass &view, int flags, ...) {
    (void)x; (void)y; (void)w; (void)h; (void)Buffer; (void)view; (void)flags; return 0;
}
void *Build_Fading_Table(void const *palette, void const *dest, long color, long frac) {
    (void)palette; (void)color; (void)frac; return (void*)dest;
}
void Force_VM_Page_In(void *buffer, int length) { (void)buffer; (void)length; }
int Get_Mouse_X(void) { return 0; }
int Get_Mouse_Y(void) { return 0; }
int Get_Random_Mask(int maxval) { (void)maxval; return 0; }
int Is_Icon_Cached(void const *icon_data, int icon) { (void)icon_data; (void)icon; return 0; }
unsigned long Largest_Mem_Block(void) { return 64 * 1024 * 1024; }
void ModeX_Blit(void) {}
void Pack_2_Plane(void *buffer, void *pageptr, int planebit) { (void)buffer; (void)pageptr; (void)planebit; }
void Set_Font_Palette_Range(void const *palette, int start_idx, int end_idx) { (void)palette; (void)start_idx; (void)end_idx; }
void Set_Shape_Buffer(void const *buffer, int size) { (void)buffer; (void)size; }
void Stop_Execution(void) {}
} /* extern "C" */

/* These are declared with C++ linkage in WIN32LIB headers */
void Register_Icon_Set(void *icon_data, BOOL pre_cache) { (void)icon_data; (void)pre_cache; }
void Wait_Blit(void) {}

/* Video mode */
BOOL Set_Video_Mode(HWND hwnd, int w, int h, int bits_per_pixel) {
    (void)hwnd; (void)w; (void)h; (void)bits_per_pixel; return FALSE;
}
unsigned Get_Free_Video_Memory(void) { return 0; }
unsigned Get_Video_Hardware_Capabilities(void) { return 0; }

extern "C" {
/* Mpeg stubs — extern "C" in MOVIE.H */
void MpgPause(void) {}
void MpgPlay(const char* name, IDirectDraw* dd, IDirectDrawSurface* surface, RECT* dstRect) {
    (void)name; (void)dd; (void)surface; (void)dstRect;
}
void MpgResume(void) {}
void MpgSetCallback(void* callback, void* user) { (void)callback; (void)user; }

/* System tick functions — extern "C" in TIMER.H */
long Get_System_Tick_Count(void) { return 0; }
long Get_User_Tick_Count(void) { return 0; }
} /* extern "C" */

/* Timer init/remove — C++ linkage in TIMER.H */
BOOL Init_Timer_System(unsigned int freq, int partial) { (void)freq; (void)partial; return TRUE; }
BOOL Remove_Timer_System(void) { return TRUE; }

/* ================================================================== */
/*  WOL (Westwood Online) text strings                                 */
/* ================================================================== */
const char *TXT_WOL_ACCEPT_DRAW = "";
const char *TXT_WOL_ACCEPT_DRAW_CONFIRM = "";
const char *TXT_WOL_AM_MISSIONS = "";
const char *TXT_WOL_CS_MISSIONS = "";
const char *TXT_WOL_DRAW = "";
const char *TXT_WOL_DRAW_PROPOSED_LOCAL = "";
const char *TXT_WOL_DRAW_PROPOSED_OTHER = "";
const char *TXT_WOL_DRAW_RETRACTED_LOCAL = "";
const char *TXT_WOL_DRAW_RETRACTED_OTHER = "";
const char *TXT_WOL_PROPOSE_DRAW = "";
const char *TXT_WOL_PROPOSE_DRAW_CONFIRM = "";
const char *TXT_WOL_RETRACT_DRAW = "";

/* ================================================================== */
/* main() provided by src/platform/entry_point.cpp */
