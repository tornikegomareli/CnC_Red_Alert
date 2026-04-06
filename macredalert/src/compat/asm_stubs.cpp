/*
 * asm_stubs.cpp — Empty implementations of ASM-exported functions
 * These stubs allow the project to link. They will be replaced with
 * real C implementations in Phase 1.
 */

#include <string.h>
#include <stdlib.h>

extern "C" {

// ============================================================================
// From WIN32LIB/INCLUDE/DRAWBUFF.H — Graphics primitives
// ============================================================================

long Buffer_Size_Of_Region(void *thisptr, int w, int h) {
    (void)thisptr; return (long)w * h;
}

void Buffer_Put_Pixel(void *thisptr, int x, int y, unsigned char color) {
    (void)thisptr; (void)x; (void)y; (void)color;
}

int Buffer_Get_Pixel(void *thisptr, int x, int y) {
    (void)thisptr; (void)x; (void)y; return 0;
}

void Buffer_Clear(void *thisptr, unsigned char color) {
    (void)thisptr; (void)color;
}

long Buffer_To_Buffer(void *thisptr, int x, int y, int w, int h, void *buff, long size) {
    (void)thisptr; (void)x; (void)y; (void)w; (void)h; (void)buff; (void)size; return 0;
}

long Buffer_To_Page(int x, int y, int w, int h, void *Buffer, void *view) {
    (void)x; (void)y; (void)w; (void)h; (void)Buffer; (void)view; return 0;
}

int Linear_Blit_To_Linear(void *thisptr, void *dest, int x_pixel, int y_pixel,
    int dx_pixel, int dy_pixel, int pixel_width, int pixel_height, int trans) {
    (void)thisptr; (void)dest; (void)x_pixel; (void)y_pixel;
    (void)dx_pixel; (void)dy_pixel; (void)pixel_width; (void)pixel_height; (void)trans;
    return 0;
}

int Linear_Scale_To_Linear(void *src, void *dst, int sx, int sy, int dx, int dy,
    int sw, int sh, int dw, int dh, int trans, char *remap) {
    (void)src; (void)dst; (void)sx; (void)sy; (void)dx; (void)dy;
    (void)sw; (void)sh; (void)dw; (void)dh; (void)trans; (void)remap;
    return 0;
}

long Buffer_Print(void *thisptr, const char *str, int x, int y, int fcolor, int bcolor) {
    (void)thisptr; (void)str; (void)x; (void)y; (void)fcolor; (void)bcolor; return 0;
}

void Buffer_Draw_Line(void *thisptr, int sx, int sy, int dx, int dy, unsigned char color) {
    (void)thisptr; (void)sx; (void)sy; (void)dx; (void)dy; (void)color;
}

void Buffer_Fill_Rect(void *thisptr, int sx, int sy, int dx, int dy, unsigned char color) {
    (void)thisptr; (void)sx; (void)sy; (void)dx; (void)dy; (void)color;
}

void Buffer_Remap(void *thisptr, int sx, int sy, int width, int height, void *remap) {
    (void)thisptr; (void)sx; (void)sy; (void)width; (void)height; (void)remap;
}

void Buffer_Fill_Quad(void *thisptr, void *span_buff, int x0, int y0, int x1, int y1,
    int x2, int y2, int x3, int y3, int color) {
    (void)thisptr; (void)span_buff; (void)x0; (void)y0; (void)x1; (void)y1;
    (void)x2; (void)y2; (void)x3; (void)y3; (void)color;
}

void Buffer_Draw_Stamp(void const *thisptr, void const *icondata, int icon,
    int x_pixel, int y_pixel, void const *remap) {
    (void)thisptr; (void)icondata; (void)icon; (void)x_pixel; (void)y_pixel; (void)remap;
}

void Buffer_Draw_Stamp_Clip(void const *thisptr, void const *icondata, int icon,
    int x_pixel, int y_pixel, void const *remap, int a, int b, int c, int d) {
    (void)thisptr; (void)icondata; (void)icon; (void)x_pixel; (void)y_pixel;
    (void)remap; (void)a; (void)b; (void)c; (void)d;
}

void *Get_Font_Palette_Ptr(void) {
    static unsigned char font_palette[256 * 16] = {0};
    return font_palette;
}

// ============================================================================
// From WIN32LIB/PALETTE/PALETTE.H — Palette functions
// ============================================================================

unsigned char CurrentPalette[768] = {0};

void Set_Palette_Range(void *palette) {
    if (palette) memcpy(CurrentPalette, palette, 768);
}

// ============================================================================
// From various — Compression/decompression
// ============================================================================

int LCW_Uncomp(void const *source, void *dest, unsigned long /*length*/) {
    (void)source; (void)dest; return 0;
}

int LCW_Comp(void const *source, void *dest, int length) {
    (void)source; (void)dest; (void)length; return 0;
}

// ============================================================================
// From MISC — Support functions
// ============================================================================

unsigned int Cardinal_To_Fixed(unsigned int base, unsigned int cardinal) {
    if (base == 0) return 0;
    return (cardinal * 256) / base;
}

unsigned int Fixed_To_Cardinal(unsigned int base, unsigned int fixed) {
    return (base * fixed) / 256;
}

long __cdecl Reverse_Long(long value) {
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) |
           ((value & 0xFF0000) >> 8) | ((value >> 24) & 0xFF);
}

short __cdecl Reverse_Short(short value) {
    return ((value & 0xFF) << 8) | ((value >> 8) & 0xFF);
}

int __cdecl Clip_Rect(int *x, int *y, int *dw, int *dh, int width, int height) {
    (void)x; (void)y; (void)dw; (void)dh; (void)width; (void)height; return 0;
}

int __cdecl Confine_Rect(int *x, int *y, int dw, int dh, int width, int height) {
    (void)x; (void)y; (void)dw; (void)dh; (void)width; (void)height; return 0;
}

void __cdecl Fat_Put_Pixel(int x, int y, int color, int size, void *surface) {
    (void)x; (void)y; (void)color; (void)size; (void)surface;
}

void __cdecl Mem_Copy(void const *source, void *dest, unsigned long bytes_to_copy) {
    if (source && dest && bytes_to_copy) memmove(dest, source, bytes_to_copy);
}

long __cdecl strtrim(char *str) {
    if (!str) return 0;
    // trim trailing spaces
    long len = (long)strlen(str);
    while (len > 0 && str[len-1] == ' ') { str[--len] = '\0'; }
    return len;
}

// ============================================================================
// Shape drawing
// ============================================================================

void CC_Draw_Shape(void const *shapefile, int shapenum, int x, int y,
    int window, const void *fadingdata, ...) {
    (void)shapefile; (void)shapenum; (void)x; (void)y; (void)window; (void)fadingdata;
}

int Get_Build_Frame_Count(void const *dataptr) {
    (void)dataptr; return 0;
}

int Get_Build_Frame_X(void const *dataptr) {
    (void)dataptr; return 0;
}

int Get_Build_Frame_Y(void const *dataptr) {
    (void)dataptr; return 0;
}

int Get_Build_Frame_Width(void const *dataptr) {
    (void)dataptr; return 0;
}

int Get_Build_Frame_Height(void const *dataptr) {
    (void)dataptr; return 0;
}

// ============================================================================
// Audio codecs
// ============================================================================

void __cdecl Decompress_Frame(void *source, void *dest, int size) {
    (void)source; (void)dest; (void)size;
}

long __cdecl Decompress_Frame_Count(void *source) {
    (void)source; return 0;
}

// ============================================================================
// Mouse ASM
// ============================================================================

void Mouse_Shadow_Buffer(void *thisptr, void *buffer, void *mouse, int x, int y, int hotx, int hoty, int store) {
    (void)thisptr; (void)buffer; (void)mouse; (void)x; (void)y; (void)hotx; (void)hoty; (void)store;
}

void Mouse_Draw(void *thisptr, void *buffer, void *mouse, int x, int y, int hotx, int hoty, int store) {
    (void)thisptr; (void)buffer; (void)mouse; (void)x; (void)y; (void)hotx; (void)hoty; (void)store;
}

void *Mouse_Set_Cursor(void *thisptr, int hotx, int hoty, void *cursor) {
    (void)thisptr; (void)hotx; (void)hoty;
    return cursor;
}

// ============================================================================
// CRC
// ============================================================================

long __cdecl Calculate_CRC(void *buffer, long length) {
    (void)buffer; (void)length; return 0;
}

// ============================================================================
// Misc math
// ============================================================================

unsigned int __cdecl Square_Root(unsigned int value) {
    if (value == 0) return 0;
    unsigned int r = 1;
    while (r * r < value) r++;
    if (r * r > value) r--;
    return r;
}

} // extern "C"

/*
** Fancy_Text_Print overloads that accept plain unsigned fore color
** instead of RemapControlType*. These just call through to the
** RemapControlType* version with NULL (the drawing code handles it).
*/
#include "FUNCTION.H"

void Fancy_Text_Print(char const *text, unsigned x, unsigned y, unsigned fore, unsigned back, TextPrintType flag, ...) {
    (void)fore;
    Fancy_Text_Print(text, x, y, (RemapControlType *)NULL, back, flag);
}
void Fancy_Text_Print(int text, unsigned x, unsigned y, unsigned fore, unsigned back, TextPrintType flag, ...) {
    (void)fore;
    Fancy_Text_Print(text, x, y, (RemapControlType *)NULL, back, flag);
}
