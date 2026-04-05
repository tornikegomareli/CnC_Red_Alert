/*
 * palette.h — Reconstructed PaletteClass definition for macOS port
 *
 * PaletteClass was missing from the EA open-source release of Red Alert.
 * This reconstruction is based on usage patterns found throughout the
 * CODE/ source files (GLOBALS.CPP, OPTIONS.CPP, JSHELL.CPP, VORTEX.CPP,
 * CONQUER.CPP, etc.).
 */

#ifndef PALETTE_CLASS_H
#define PALETTE_CLASS_H

#include "rgb.h"

class PaletteClass
{
public:
    enum { COLOR_COUNT = 256 };

    // Default constructor — zero-initialized palette
    PaletteClass(void) {
        for (int i = 0; i < COLOR_COUNT; i++) {
            Palette[i] = RGBClass();
        }
    }

    // Fill constructor — sets all entries to the given color
    PaletteClass(RGBClass const & rgb) {
        for (int i = 0; i < COLOR_COUNT; i++) {
            Palette[i] = rgb;
        }
    }

    // Array access
    RGBClass & operator[] (int index) { return Palette[index]; }
    RGBClass const & operator[] (int index) const { return Palette[index]; }

    // Implicit pointer conversion (for memcpy, Set_Pal, etc.)
    operator void* (void) { return &Palette[0]; }
    operator void const* (void) const { return &Palette[0]; }

    // Boolean test (false if palette is all black)
    bool operator! (void) const {
        for (int i = 0; i < COLOR_COUNT; i++) {
            if (Palette[i].Red_Component() || Palette[i].Green_Component() || Palette[i].Blue_Component()) {
                return false;
            }
        }
        return true;
    }

    // Assignment
    PaletteClass & operator= (PaletteClass const & other) {
        if (this != &other) {
            for (int i = 0; i < COLOR_COUNT; i++) {
                Palette[i] = other.Palette[i];
            }
        }
        return *this;
    }

    // Set the hardware palette to this palette's values (stub on macOS)
    void Set(int rate = 0, void (*callback)(void) = 0) const {
        (void)rate; (void)callback;
        // Copy to CurrentPalette when "setting" the palette
        if (this != &CurrentPalette) {
            for (int i = 0; i < COLOR_COUNT; i++) {
                ((PaletteClass &)CurrentPalette).Palette[i] = Palette[i];
            }
        }
    }

    // Adjust all palette entries towards another palette by the given ratio (0-255)
    void Adjust(int ratio, PaletteClass const & palette) {
        for (int i = 0; i < COLOR_COUNT; i++) {
            Palette[i].Adjust(ratio, palette.Palette[i]);
        }
    }

    // Adjust all palette entries towards CurrentPalette by the given ratio
    void Adjust(int ratio) {
        Adjust(ratio, CurrentPalette);
    }

    // Partial adjustment with a lookup table controlling which entries to adjust
    void Partial_Adjust(int ratio, PaletteClass const & palette, char const * lut) {
        for (int i = 0; i < COLOR_COUNT; i++) {
            if (lut && lut[i]) {
                Palette[i].Adjust(ratio, palette.Palette[i]);
            }
        }
    }

    // Partial adjustment with a lookup table only (towards black)
    void Partial_Adjust(int ratio, char const * lut) {
        RGBClass black;
        for (int i = 0; i < COLOR_COUNT; i++) {
            if (lut && lut[i]) {
                Palette[i].Adjust(ratio, black);
            }
        }
    }

    // Find the closest matching color index for the given RGB value
    int Closest_Color(RGBClass const & rgb) const {
        int best_index = 0;
        int best_diff = Palette[0].Difference(rgb);
        for (int i = 1; i < COLOR_COUNT; i++) {
            int diff = Palette[i].Difference(rgb);
            if (diff < best_diff) {
                best_diff = diff;
                best_index = i;
            }
        }
        return best_index;
    }

    // The "current" hardware palette
    static PaletteClass CurrentPalette;

private:
    RGBClass Palette[COLOR_COUNT];
};

/*
 * Declarations from WIN32LIB PALETTE.H (free functions).
 * We define PALETTE_H so the WIN32LIB header is not re-included
 * (it would pull in gbuffer.h prematurely).
 */
#ifndef PALETTE_H
#define PALETTE_H

#define RGB_BYTES       3
#define PALETTE_SIZE    256
#define PALETTE_BYTES   768

void __cdecl Set_Palette(void *palette);
void __cdecl Set_Palette_Color(void *palette, int color, void *data);
void Fade_Palette_To(void *palette1, unsigned int delay, void (*callback)() );
void __cdecl Load_Palette(char *palette_file_name, void *palette_pointer);
void __cdecl Morph_Palette(void *src_palette, void *dst_palette, unsigned int delay, void *callback);

#ifdef __cplusplus
extern "C" {
#endif
extern void __cdecl Set_Palette_Range(void *palette);
extern BOOL __cdecl Bump_Color(void *palette, int changable, int target);
#ifdef __cplusplus
}
#endif

extern "C" unsigned char CurrentPalette[];

#endif // PALETTE_H

#endif // PALETTE_CLASS_H
