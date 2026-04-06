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

/*
 * Graphics primitives — C reimplementation of ASM routines.
 * These operate on GraphicViewPortClass which has this layout:
 *   long Offset;    // pointer to pixel data (stored as long)
 *   long Width;     // viewport width
 *   long Height;    // viewport height
 *   long XAdd;      // bytes to add to reach next line (pitch - width)
 *   long XPos;      // X position in parent buffer
 *   long YPos;      // Y position in parent buffer
 *   long Pitch;     // bytes per line in parent buffer
 */
struct GVPCLayout {
    long Offset;
    long Width;
    long Height;
    long XAdd;
    long XPos;
    long YPos;
    long Pitch;
};

void Buffer_Put_Pixel(void *thisptr, int x, int y, unsigned char color) {
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    if (x < 0 || y < 0 || x >= vp->Width || y >= vp->Height) return;
    unsigned char *buf = (unsigned char *)(intptr_t)vp->Offset;
    int pitch = (int)(vp->Width + vp->XAdd);
    buf[y * pitch + x] = color;
}

int Buffer_Get_Pixel(void *thisptr, int x, int y) {
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    if (x < 0 || y < 0 || x >= vp->Width || y >= vp->Height) return 0;
    unsigned char *buf = (unsigned char *)(intptr_t)vp->Offset;
    int pitch = (int)(vp->Width + vp->XAdd);
    return buf[y * pitch + x];
}

void Buffer_Clear(void *thisptr, unsigned char color) {
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    unsigned char *buf = (unsigned char *)(intptr_t)vp->Offset;
    if (!buf) return;
    int pitch = (int)(vp->Width + vp->XAdd);
    for (int y = 0; y < vp->Height; y++) {
        memset(buf + y * pitch, color, vp->Width);
    }
}

long Buffer_To_Buffer(void *thisptr, int x, int y, int w, int h, void *buff, long size) {
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    unsigned char *src = (unsigned char *)(intptr_t)vp->Offset;
    unsigned char *dst = (unsigned char *)buff;
    if (!src || !dst) return 0;
    int pitch = (int)(vp->Width + vp->XAdd);
    long copied = 0;
    for (int row = 0; row < h && copied < size; row++) {
        int bytes = (w < (size - copied)) ? w : (int)(size - copied);
        memcpy(dst + copied, src + (y + row) * pitch + x, bytes);
        copied += bytes;
    }
    return copied;
}

long Buffer_To_Page(int x, int y, int w, int h, void *Buffer, void *view) {
    GVPCLayout *vp = (GVPCLayout *)view;
    unsigned char *dst = (unsigned char *)(intptr_t)vp->Offset;
    unsigned char *src = (unsigned char *)Buffer;
    if (!src || !dst) return 0;
    int pitch = (int)(vp->Width + vp->XAdd);
    for (int row = 0; row < h; row++) {
        memcpy(dst + (y + row) * pitch + x, src + row * w, w);
    }
    return (long)(w * h);
}

int Linear_Blit_To_Linear(void *thisptr, void *dest, int x_pixel, int y_pixel,
    int dx_pixel, int dy_pixel, int pixel_width, int pixel_height, int trans) {
    GVPCLayout *src_vp = (GVPCLayout *)thisptr;
    GVPCLayout *dst_vp = (GVPCLayout *)dest;
    unsigned char *src = (unsigned char *)(intptr_t)src_vp->Offset;
    unsigned char *dst = (unsigned char *)(intptr_t)dst_vp->Offset;
    if (!src || !dst) return 0;
    int src_pitch = (int)(src_vp->Width + src_vp->XAdd);
    int dst_pitch = (int)(dst_vp->Width + dst_vp->XAdd);
    for (int row = 0; row < pixel_height; row++) {
        unsigned char *s = src + (y_pixel + row) * src_pitch + x_pixel;
        unsigned char *d = dst + (dy_pixel + row) * dst_pitch + dx_pixel;
        if (trans) {
            for (int col = 0; col < pixel_width; col++) {
                if (s[col] != 0) d[col] = s[col]; /* skip color 0 = transparent */
            }
        } else {
            memcpy(d, s, pixel_width);
        }
    }
    return 1;
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
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    unsigned char *buf = (unsigned char *)(intptr_t)vp->Offset;
    if (!buf) return;
    int pitch = (int)(vp->Width + vp->XAdd);
    /* Bresenham's line algorithm */
    int x0 = sx, y0 = sy, x1 = dx, y1 = dy;
    int steep = abs(y1-y0) > abs(x1-x0);
    if (steep) { int t=x0; x0=y0; y0=t; t=x1; x1=y1; y1=t; }
    if (x0 > x1) { int t=x0; x0=x1; x1=t; t=y0; y0=y1; y1=t; }
    int deltax = x1 - x0, deltay = abs(y1 - y0);
    int error = deltax / 2, ystep = (y0 < y1) ? 1 : -1, y = y0;
    for (int x = x0; x <= x1; x++) {
        int px = steep ? y : x, py = steep ? x : y;
        if (px >= 0 && px < vp->Width && py >= 0 && py < vp->Height)
            buf[py * pitch + px] = color;
        error -= deltay;
        if (error < 0) { y += ystep; error += deltax; }
    }
}

void Buffer_Fill_Rect(void *thisptr, int sx, int sy, int dx, int dy, unsigned char color) {
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    unsigned char *buf = (unsigned char *)(intptr_t)vp->Offset;
    if (!buf) return;
    int pitch = (int)(vp->Width + vp->XAdd);
    if (sx < 0) sx = 0; if (sy < 0) sy = 0;
    if (dx >= vp->Width) dx = (int)vp->Width - 1;
    if (dy >= vp->Height) dy = (int)vp->Height - 1;
    for (int y = sy; y <= dy; y++) {
        memset(buf + y * pitch + sx, color, dx - sx + 1);
    }
}

void Buffer_Remap(void *thisptr, int sx, int sy, int width, int height, void *remap) {
    GVPCLayout *vp = (GVPCLayout *)thisptr;
    unsigned char *buf = (unsigned char *)(intptr_t)vp->Offset;
    unsigned char *table = (unsigned char *)remap;
    if (!buf || !table) return;
    int pitch = (int)(vp->Width + vp->XAdd);
    for (int y = 0; y < height; y++) {
        unsigned char *row = buf + (sy + y) * pitch + sx;
        for (int x = 0; x < width; x++) {
            row[x] = table[row[x]];
        }
    }
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

/*
 * LCW decompression (Format 80) — C reimplementation of the ASM routine.
 * LCW is Westwood's custom compression format used in MIX archives.
 *
 * Command formats:
 *   Cmd 1 (2 bytes): 0CCCOOOO OOOOOOOO
 *     Count = ((flag >> 4) & 7) + 3, Offset = 12-bit relative (backwards from dst)
 *     Copy count bytes from (dst - offset) to dst.
 *
 *   Cmd 2 (1 byte):  10CCCCCC
 *     Count = flag & 0x3F (1..63). Copy count literal bytes from src to dst.
 *     If count == 0 (i.e. flag == 0x80), this is the end-of-data marker.
 *
 *   Cmd 3 (3 bytes): 11CCCCCC OOOOOOOO OOOOOOOO
 *     Count = (flag & 0x3F) + 3, Offset = 16-bit absolute from dest start.
 *     Copy count bytes from (dst_start + offset) to dst.
 *
 *   Cmd 4 (4 bytes): 11111110 CCCC CCCC VVVV VVVV
 *     Count = 16-bit, Value = byte. Fill count bytes with value.
 *
 *   Cmd 5 (5 bytes): 11111111 CCCC CCCC OOOO OOOO
 *     Count = 16-bit, Offset = 16-bit absolute from dest start.
 *     Copy count bytes from (dst_start + offset) to dst.
 *
 * The `length` parameter is the output buffer size (max bytes to write).
 * Returns the number of bytes written to dest.
 */
int LCW_Uncomp(void const *source, void *dest, unsigned long length) {
    const unsigned char *src = (const unsigned char *)source;
    unsigned char *dst = (unsigned char *)dest;
    unsigned char *dst_start = dst;
    unsigned char *dst_end = dst + length;

    while (dst < dst_end) {
        unsigned char flag = *src++;

        if (!(flag & 0x80)) {
            /*
             * Command 1: 0CCCOOOO OOOOOOOO
             * Short relative copy from already-decompressed output.
             */
            unsigned int count = ((flag >> 4) & 7) + 3;
            unsigned int offset = ((unsigned int)(flag & 0x0F) << 8) | *src++;
            unsigned char *copy_src = dst - offset;
            /* Byte-by-byte copy handles overlapping regions correctly
             * (e.g. RLE-like patterns where offset < count). */
            unsigned int i;
            for (i = 0; i < count && dst < dst_end; i++) {
                *dst++ = copy_src[i];
            }

        } else if (!(flag & 0x40)) {
            /*
             * Command 2: 10CCCCCC
             * Literal copy from source stream.
             * Special case: flag == 0x80 (count == 0) is end-of-data.
             */
            unsigned int count = flag & 0x3F;
            if (count == 0) {
                break;  /* 0x80 end marker */
            }
            unsigned int i;
            for (i = 0; i < count && dst < dst_end; i++) {
                *dst++ = *src++;
            }

        } else {
            /* flag has bits 7 and 6 set: 11xxxxxx */

            if (flag == 0xFE) {
                /*
                 * Command 4: 11111110 CC CC VV
                 * Fill count bytes with value.
                 */
                unsigned int count = (unsigned int)src[0] | ((unsigned int)src[1] << 8);
                src += 2;
                unsigned char val = *src++;
                unsigned int i;
                for (i = 0; i < count && dst < dst_end; i++) {
                    *dst++ = val;
                }

            } else if (flag == 0xFF) {
                /*
                 * Command 5: 11111111 CC CC OO OO
                 * Long absolute copy from output buffer.
                 */
                unsigned int count = (unsigned int)src[0] | ((unsigned int)src[1] << 8);
                src += 2;
                unsigned int offset = (unsigned int)src[0] | ((unsigned int)src[1] << 8);
                src += 2;
                unsigned char *copy_src = dst_start + offset;
                unsigned int i;
                for (i = 0; i < count && dst < dst_end; i++) {
                    *dst++ = copy_src[i];
                }

            } else {
                /*
                 * Command 3: 11CCCCCC OO OO
                 * Medium absolute copy from output buffer.
                 */
                unsigned int count = (flag & 0x3F) + 3;
                unsigned int offset = (unsigned int)src[0] | ((unsigned int)src[1] << 8);
                src += 2;
                unsigned char *copy_src = dst_start + offset;
                unsigned int i;
                for (i = 0; i < count && dst < dst_end; i++) {
                    *dst++ = copy_src[i];
                }
            }
        }
    }

    return (int)(dst - dst_start);
}

int LCW_Comp(void const *source, void *dest, int length) {
    /* Compression not needed for the port — just store uncompressed */
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

void __cdecl strtrim(char *str) {
    if (!str) return;
    // trim trailing spaces
    int len = (int)strlen(str);
    while (len > 0 && str[len-1] == ' ') { str[--len] = '\0'; }
}

// ============================================================================
// Shape drawing
// ============================================================================

void CC_Draw_Shape(void const *shapefile, int shapenum, int x, int y,
    int window, const void *fadingdata, ...) {
    (void)shapefile; (void)shapenum; (void)x; (void)y; (void)window; (void)fadingdata;
}

unsigned short Get_Build_Frame_Count(void const *dataptr) {
    (void)dataptr; return 0;
}

unsigned short Get_Build_Frame_X(void const *dataptr) {
    (void)dataptr; return 0;
}

unsigned short Get_Build_Frame_Y(void const *dataptr) {
    (void)dataptr; return 0;
}

unsigned short Get_Build_Frame_Width(void const *dataptr) {
    (void)dataptr; return 0;
}

unsigned short Get_Build_Frame_Height(void const *dataptr) {
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

/* Calculate_CRC defined in game code (INIT.CPP) */

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

/*
 * Load_Title_Screen — Load a PCX file into a graphics page.
 * PCX is a simple RLE-compressed image format used for title screens.
 */
void Load_Title_Screen(char *name, GraphicViewPortClass *video_page, unsigned char *palette) {
    extern void ra_log(const char *fmt, ...);
    ra_log("[PCX] Loading '%s'...\n", name ? name : "NULL");

    if (!name || !video_page) return;

    /* Open the file from MIX or filesystem */
    CCFileClass file(name);
    if (!file.Is_Available()) {
        ra_log("[PCX] File not available\n");
        return;
    }

    int file_size = file.Size();
    ra_log("[PCX] File size: %d\n", file_size);

    unsigned char *data = new unsigned char[file_size];
    file.Open(READ);
    file.Read(data, file_size);
    file.Close();

    /* PCX header: 128 bytes */
    if (file_size < 128) { delete[] data; return; }

    int xmin = data[4] | (data[5] << 8);
    int ymin = data[6] | (data[7] << 8);
    int xmax = data[8] | (data[9] << 8);
    int ymax = data[10] | (data[11] << 8);
    int width = xmax - xmin + 1;
    int height = ymax - ymin + 1;
    int bpp = data[3]; /* bits per pixel per plane */
    int planes = data[65];

    ra_log("[PCX] %dx%d, %d bpp, %d planes\n", width, height, bpp, planes);

    /* Only handle 8-bit (256 color) PCX */
    if (bpp != 8 || planes != 1) {
        ra_log("[PCX] Unsupported format\n");
        delete[] data;
        return;
    }

    /* Decode RLE pixel data (starts at offset 128) */
    unsigned char *src = data + 128;
    unsigned char *src_end = data + file_size;

    if (video_page->Lock()) {
        unsigned char *dst_buf = (unsigned char *)(intptr_t)video_page->Get_Offset();
        int dst_w = video_page->Get_Width();
        int dst_h = video_page->Get_Height();
        int pitch = dst_w + video_page->Get_XAdd();

        int x = 0, y = 0;
        while (src < src_end && y < height && y < dst_h) {
            unsigned char byte = *src++;
            int count = 1;
            unsigned char value;

            if ((byte & 0xC0) == 0xC0) {
                count = byte & 0x3F;
                if (src >= src_end) break;
                value = *src++;
            } else {
                value = byte;
            }

            while (count-- > 0 && y < height && y < dst_h) {
                if (x < dst_w) {
                    dst_buf[y * pitch + x] = value;
                }
                x++;
                if (x >= width) {
                    x = 0;
                    y++;
                }
            }
        }
        video_page->Unlock();
        ra_log("[PCX] Decoded %dx%d pixels\n", width, y);
    }

    /* Read 256-color palette from end of file (last 769 bytes: 0x0C marker + 768 RGB) */
    if (palette && file_size > 769) {
        unsigned char *pal_start = data + file_size - 769;
        if (*pal_start == 0x0C) {
            /* PCX palette is 8-bit RGB, game uses 6-bit (0-63) */
            for (int i = 0; i < 768; i++) {
                palette[i] = pal_start[1 + i] >> 2;
            }
            ra_log("[PCX] Palette loaded (256 colors)\n");
        }
    }

    delete[] data;
}

/* Stub for Write_PCX_File */
int Write_PCX_File(char *name, GraphicViewPortClass& pic, unsigned char *palette) {
    (void)name; (void)pic; (void)palette;
    return 0;
}

/* Overload taking a FileClass (CDFileClass is derived from it) */
int Write_PCX_File(FileClass& file, GraphicViewPortClass& pic, PaletteClass * palette) {
    (void)file; (void)pic; (void)palette;
    return 0;
}
