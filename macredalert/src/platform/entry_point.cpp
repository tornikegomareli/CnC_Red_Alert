/*
 * entry_point.cpp — macOS Raylib entry point for C&C Red Alert
 * Replaces WinMain from CODE/STARTUP.CPP
 */

#include <stdio.h>
#include <stdlib.h>
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

// Now include Raylib
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmacro-redefined"
#include "raylib.h"
#pragma clang diagnostic pop

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

int main(int argc, char **argv) {
    g_log = fopen("ra_port.log", "w");
    ra_log("=== C&C Red Alert macOS Port ===\n");
    ra_log("Starting initialization...\n");

    // Initialize Raylib
    const int GAME_WIDTH = 640;
    const int GAME_HEIGHT = 400;
    const int SCALE = 2;

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(GAME_WIDTH * SCALE, GAME_HEIGHT * SCALE, "C&C Red Alert — macOS Port");
    SetTargetFPS(30);

    // Set globals the game expects
    GameActive = true;
    GameInFocus = true;
    ScreenWidth = GAME_WIDTH;
    ScreenHeight = GAME_HEIGHT;

    ra_log("Raylib window initialized: %dx%d\n", GAME_WIDTH * SCALE, GAME_HEIGHT * SCALE);

    // Create the keyboard object (normally done in WinMain/STARTUP.CPP)
    {
        extern KeyboardClass *Keyboard;
        Keyboard = new KeyboardClass();
        ra_log("Keyboard object created\n");
    }

    // Try calling the game's Init_Game
    ra_log("Calling Init_Game()...\n");

    bool init_ok = false;
    // Catch crashes
    signal(SIGSEGV, [](int) {
        ra_log("CRASH: Segmentation fault during init!\n");
        if (g_log) fclose(g_log);
        _exit(1);
    });
    signal(SIGABRT, [](int) {
        ra_log("CRASH: Abort during init!\n");
        if (g_log) fclose(g_log);
        _exit(1);
    });

    // The game's Init_Game calls Bootstrap() which calls Init_Bootstrap_Mixfiles()
    // which tries to open MIX files. Let's trace the crash.
    ra_log("About to call Init_Game...\n");
    ra_log("CWD test: ");
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd))) ra_log("%s\n", cwd);
        else ra_log("(unknown)\n");
    }
    init_ok = Init_Game(argc, argv);
    ra_log("Init_Game returned: %s\n", init_ok ? "true" : "false");

    // Framebuffer for display
    Image framebuffer = GenImageColor(GAME_WIDTH, GAME_HEIGHT, BLACK);
    Texture2D fbTexture = LoadTextureFromImage(framebuffer);
    UnloadImage(framebuffer);
    unsigned char *pixels = (unsigned char *)calloc(GAME_WIDTH * GAME_HEIGHT * 4, 1);

    // Simple gradient test pattern
    for (int y = 0; y < GAME_HEIGHT; y++) {
        for (int x = 0; x < GAME_WIDTH; x++) {
            int idx = (y * GAME_WIDTH + x) * 4;
            pixels[idx + 0] = (unsigned char)(x * 255 / GAME_WIDTH);
            pixels[idx + 1] = (unsigned char)(y * 255 / GAME_HEIGHT);
            pixels[idx + 2] = init_ok ? 200 : 50;
            pixels[idx + 3] = 255;
        }
    }
    UpdateTexture(fbTexture, pixels);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            fbTexture,
            (Rectangle){ 0, 0, (float)GAME_WIDTH, (float)GAME_HEIGHT },
            (Rectangle){ 0, 0, (float)(GAME_WIDTH * SCALE), (float)(GAME_HEIGHT * SCALE) },
            (Vector2){ 0, 0 }, 0.0f, WHITE
        );
        DrawText("C&C Red Alert — macOS Port", 10, 10, 20, RAYWHITE);
        if (init_ok) {
            DrawText("Init_Game() succeeded!", 10, 35, 16, GREEN);
        } else {
            DrawText("Init_Game() failed — check ra_port.log", 10, 35, 16, RED);
        }
        DrawFPS(GAME_WIDTH * SCALE - 90, 10);
        EndDrawing();
    }

    free(pixels);
    UnloadTexture(fbTexture);
    CloseWindow();
    if (g_log) fclose(g_log);
    return 0;
}
