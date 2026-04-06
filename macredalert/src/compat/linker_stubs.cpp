/*
 * linker_stubs.cpp — Stub definitions for all undefined symbols
 * Signatures match FUNCTION.H declarations exactly.
 */

#include "FUNCTION.H"
#include <string.h>
#include <stdlib.h>

// Audio
void Sound_Effect(VocType voc, COORDINATE coord, int variation, HousesType house) {
    (void)voc; (void)coord; (void)variation; (void)house;
}
void Speak(VoxType voice) { (void)voice; }
void Speak_AI(void) {}
void Stop_Speaking(void) {}
bool Is_Speaking(void) { return false; }
void VQA_PauseAudio(void) {}
void Check_VQ_Palette_Set(void) {}

// Platform (Phase 3)
void Create_Main_Window(HANDLE inst, int show, int w, int h) { (void)inst; (void)show; (void)w; (void)h; }
void Prog_End(const char *msg, bool fatal) { (void)msg; (void)fatal; }
/* Emergency_Exit defined in game code */
void Check_For_Focus_Loss(void) {}
void Memory_Error_Handler(void) {}
void Read_Game_Options(char *) {}
/* Reallocate_Big_Shape_Buffer defined in game code */
void Reset_Theater_Shapes(void) {}

// Mouse
void Block_Mouse(GraphicBufferClass *buf) { (void)buf; }
void Unblock_Mouse(GraphicBufferClass *buf) { (void)buf; }

// Network
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

// Dialogs
char const * Map_Selection(void) { return NULL; }
int Surrender_Dialog(int text) { (void)text; return 0; }
int Surrender_Dialog(const char *text) { (void)text; return 0; }
int Com_Scenario_Dialog(bool skirmish) { (void)skirmish; return 0; }
GameType Select_MPlayer_Game(void) { return GAME_NORMAL; }
GameType Select_Serial_Dialog(void) { return GAME_NORMAL; }

// Score
void Register_Game_End_Time(void) {}
void Register_Game_Start_Time(void) {}
void Send_Statistics_Packet(void) {}

// Misc
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

// Crypto
Int<MAX_UNIT_PRECISION> Generate_Prime(Straw &rng, int bits, Int<MAX_UNIT_PRECISION> const *test) {
    (void)rng; (void)bits; (void)test;
    Int<MAX_UNIT_PRECISION> result;
    return result;
}

// Entry point
int main(int argc, char **argv) {
    (void)argc; (void)argv;
    return 0;
}
