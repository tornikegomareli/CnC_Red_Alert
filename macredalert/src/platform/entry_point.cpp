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
    Texture2D fbTexture = LoadTextureFromImage(fbImage);
    UnloadImage(fbImage);
    unsigned char *rgba_pixels = (unsigned char *)calloc(GAME_WIDTH * GAME_HEIGHT * 4, 1);

    // Get pointer to the game's visible page buffer
    extern GraphicBufferClass VisiblePage;

    // Try to render something to prove the framebuffer pipeline works
    if (init_ok) {
        extern GraphicViewPortClass HidPage;
        extern GraphicViewPortClass SeenBuff;

        // Try loading a title screen image into the framebuffer
        ra_log("Trying to load title screen...\n");

        // Try to retrieve and display TITLE.PCX or PROLOG.PCX
        void const *title_data = MFCD::Retrieve("TITLE.CPS");
        if (!title_data) title_data = MFCD::Retrieve("PROLOG.CPS");
        if (!title_data) title_data = MFCD::Retrieve("GREYEARL.CPS");
        ra_log("Title data: %p\n", title_data);

        // Even without a title image, set a visible palette so we see SOMETHING
        // Set palette to a gradient so non-black pixels show up
        for (int i = 0; i < 256; i++) {
            CurrentPalette[i*3+0] = i / 4;  // R
            CurrentPalette[i*3+1] = i / 4;  // G
            CurrentPalette[i*3+2] = i / 4;  // B
        }

        // Draw a test pattern directly to VisiblePage using game's graphics system
        if (VisiblePage.Lock()) {
            // Fill with a gradient pattern to verify the pipeline
            unsigned char *buf = (unsigned char *)(intptr_t)VisiblePage.Get_Offset();
            if (buf) {
                for (int y = 0; y < GAME_HEIGHT; y++) {
                    for (int x = 0; x < GAME_WIDTH; x++) {
                        buf[y * GAME_WIDTH + x] = (unsigned char)((x + y) & 0xFF);
                    }
                }
                ra_log("Test pattern written to VisiblePage\n");
            }
            VisiblePage.Unlock();
        }
    }

    ra_log("Entering main loop...\n");

    while (!WindowShouldClose()) {
        // Convert game's 8-bit framebuffer to RGBA via palette
        unsigned char *game_buffer = (unsigned char *)(intptr_t)VisiblePage.Get_Offset();
        if (game_buffer) {
            Convert_Palette_To_RGBA(game_buffer, rgba_pixels,
                                    GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH);
            UpdateTexture(fbTexture, rgba_pixels);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the game's framebuffer scaled to window
        DrawTexturePro(
            fbTexture,
            (Rectangle){ 0, 0, (float)GAME_WIDTH, (float)GAME_HEIGHT },
            (Rectangle){ 0, 0, (float)(GAME_WIDTH * SCALE), (float)(GAME_HEIGHT * SCALE) },
            (Vector2){ 0, 0 }, 0.0f, WHITE
        );

        // Overlay status
        DrawText("C&C Red Alert — macOS Port", 10, 10, 20, RAYWHITE);
        if (init_ok) {
            DrawText("Init_Game() OK — Displaying game framebuffer", 10, 35, 14, GREEN);
        } else {
            DrawText("Init_Game() FAILED", 10, 35, 14, RED);
        }
        DrawFPS(GAME_WIDTH * SCALE - 90, 10);

        EndDrawing();
    }

    free(rgba_pixels);
    UnloadTexture(fbTexture);
    CloseWindow();
    if (g_log) fclose(g_log);
    return 0;
}
