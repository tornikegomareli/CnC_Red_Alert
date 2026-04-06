/*
 * entry_point.cpp — macOS Raylib entry point for C&C Red Alert
 * Replaces WinMain from CODE/STARTUP.CPP
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "platform.h"

// Pull in game types first
#include "FUNCTION.H"

// Undefine game macros that conflict with Raylib
#undef Color
#undef BLACK
#undef WHITE
#undef GREEN
#undef RED
#undef YELLOW
#undef BLUE
#undef PURPLE
#undef CYAN
#undef GREY
#undef LTGREY
#undef LTGREEN
#undef LTCYAN
#undef LTBLUE
#undef BROWN
#undef PINK

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmacro-redefined"
#include "raylib.h"
#pragma clang diagnostic pop

// Globals the game expects
extern bool GameActive;
extern bool GameInFocus;
extern int ScreenWidth;
extern int ScreenHeight;

// Game's palette (6-bit RGB, 256 entries × 3 bytes)
extern unsigned char CurrentPalette[768];

// Our log
static FILE *g_log = NULL;
void ra_log(const char *fmt, ...) {
    if (!g_log) g_log = fopen("ra_port.log", "w");
    if (g_log) {
        va_list ap;
        va_start(ap, fmt);
        vfprintf(g_log, fmt, ap);
        va_end(ap);
        fflush(g_log);
    }
}

/*
 * Convert the game's 8-bit indexed framebuffer to 32-bit RGBA
 * using the current palette. The palette entries are 6-bit (0-63),
 * so we shift left by 2 to get 8-bit (0-252).
 */
static void Convert_Palette_To_RGBA(unsigned char *indexed, unsigned char *rgba,
                                     int width, int height, int pitch) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char idx = indexed[y * pitch + x];
            int pal_offset = idx * 3;
            rgba[(y * width + x) * 4 + 0] = CurrentPalette[pal_offset + 0] << 2;  // R
            rgba[(y * width + x) * 4 + 1] = CurrentPalette[pal_offset + 1] << 2;  // G
            rgba[(y * width + x) * 4 + 2] = CurrentPalette[pal_offset + 2] << 2;  // B
            rgba[(y * width + x) * 4 + 3] = 255;                                    // A
        }
    }
}

// Shared state for render callback
static Texture2D g_fbTexture = {0};
static unsigned char *g_rgba_pixels = NULL;
static int g_game_width = 640;
static int g_game_height = 400;
static bool g_render_ready = false;

/*
 * Called from Raylib_Poll_Input (inside the game's event loop)
 * to update the display with the current framebuffer contents.
 */
extern "C" void Raylib_Render_Frame(void) {
    if (!g_render_ready || !g_rgba_pixels) return;
    unsigned char *game_buffer = (unsigned char *)(intptr_t)VisiblePage.Get_Offset();
    if (game_buffer) {
        Convert_Palette_To_RGBA(game_buffer, g_rgba_pixels,
                                g_game_width, g_game_height, g_game_width);
        UpdateTexture(g_fbTexture, g_rgba_pixels);
    }

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(
        g_fbTexture,
        (Rectangle){ 0, 0, (float)g_game_width, (float)g_game_height },
        (Rectangle){ 0, 0, (float)(g_game_width * 2), (float)(g_game_height * 2) },
        (Vector2){ 0, 0 }, 0.0f, WHITE
    );
    DrawFPS(g_game_width * 2 - 90, 10);
    EndDrawing();
}

int main(int argc, char **argv) {
    g_log = fopen("ra_port.log", "w");
    ra_log("=== C&C Red Alert macOS Port ===\n");

    const int GAME_WIDTH = 640;
    const int GAME_HEIGHT = 400;
    const int SCALE = 2;

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(GAME_WIDTH * SCALE, GAME_HEIGHT * SCALE, "C&C Red Alert — macOS Port");
    SetTargetFPS(30);

    GameActive = true;
    GameInFocus = true;
    ScreenWidth = GAME_WIDTH;
    ScreenHeight = GAME_HEIGHT;

    ra_log("Raylib window initialized: %dx%d\n", GAME_WIDTH * SCALE, GAME_HEIGHT * SCALE);

    // Create objects normally done in WinMain/STARTUP.CPP
    {
        extern KeyboardClass *Keyboard;
        Keyboard = new KeyboardClass();

        extern int MouseInstalled;
        MouseInstalled = 1;

        extern GraphicBufferClass VisiblePage;
        extern GraphicBufferClass HiddenPage;
        extern GraphicViewPortClass SeenBuff;
        extern GraphicViewPortClass HidPage;

        VisiblePage.Init(GAME_WIDTH, GAME_HEIGHT, NULL, GAME_WIDTH * GAME_HEIGHT, GBC_NONE);
        HiddenPage.Init(GAME_WIDTH, GAME_HEIGHT, NULL, GAME_WIDTH * GAME_HEIGHT, GBC_NONE);
        SeenBuff.Attach(&VisiblePage, 0, 0, GAME_WIDTH, GAME_HEIGHT);
        HidPage.Attach(&HiddenPage, 0, 0, GAME_WIDTH, GAME_HEIGHT);

        CCFileClass::Set_Search_Drives("./");
        extern int RequiredCD;
        RequiredCD = -2;

        ra_log("Platform initialized\n");
    }

    // Crash handlers
    signal(SIGSEGV, [](int) { ra_log("CRASH: SIGSEGV\n"); if(g_log) fclose(g_log); _exit(1); });
    signal(SIGABRT, [](int) { ra_log("CRASH: SIGABRT\n"); if(g_log) fclose(g_log); _exit(1); });

    // Initialize the game
    ra_log("Calling Init_Game()...\n");
    bool init_ok = Init_Game(argc, argv);
    ra_log("Init_Game returned: %s\n", init_ok ? "true" : "false");

    // Create Raylib texture for the game framebuffer
    Image fbImage = GenImageColor(GAME_WIDTH, GAME_HEIGHT, BLACK);
    g_fbTexture = LoadTextureFromImage(fbImage);
    UnloadImage(fbImage);
    g_rgba_pixels = (unsigned char *)calloc(GAME_WIDTH * GAME_HEIGHT * 4, 1);
    g_game_width = GAME_WIDTH;
    g_game_height = GAME_HEIGHT;
    g_render_ready = true;

    // Get pointer to the game's visible page buffer
    extern GraphicBufferClass VisiblePage;

    // Run the game's main menu (Select_Game)
    // This blocks in its own event loop, but our Fill_Buffer_From_System
    // hook calls Raylib_Poll_Input which pumps Raylib events and renders.
    if (init_ok) {
        ra_log("Calling Select_Game()...\n");
        extern bool Select_Game(bool);
        Select_Game(true);
        ra_log("Select_Game returned\n");
    }

    // If we get here, Select_Game returned (game started or user quit)
    ra_log("Game loop ended\n");

    free(g_rgba_pixels);
    UnloadTexture(g_fbTexture);
    CloseWindow();
    if (g_log) fclose(g_log);
    return 0;
}
