/*
 * entry_point.cpp — macOS Raylib entry point for C&C Red Alert
 * Replaces WinMain from CODE/STARTUP.CPP and CODE/WINSTUB.CPP
 *
 * Phase 3: Basic Raylib window initialization.
 * Later phases will connect to the actual game init sequence.
 */

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

// Game's original entry — declared in FUNCTION.H
extern int Main_Game(int argc, char *argv[]);
extern void Init_Random(void);

// Globals the game expects (defined in game code, we just reference them)
extern bool GameActive;
extern bool GameInFocus;

int main(int argc, char **argv) {
    // Initialize Raylib window (640x400 scaled 2x)
    const int GAME_WIDTH = 640;
    const int GAME_HEIGHT = 400;
    const int SCALE = 2;

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(GAME_WIDTH * SCALE, GAME_HEIGHT * SCALE, "C&C Red Alert — macOS Port");
    SetTargetFPS(30);

    // Create the framebuffer texture (8-bit indexed will be converted to RGBA)
    Image framebuffer = GenImageColor(GAME_WIDTH, GAME_HEIGHT, BLACK);
    Texture2D fbTexture = LoadTextureFromImage(framebuffer);
    UnloadImage(framebuffer);

    // Placeholder: draw a test pattern until game rendering is connected
    unsigned char *pixels = (unsigned char *)RL_CALLOC(GAME_WIDTH * GAME_HEIGHT * 4, 1);

    printf("C&C Red Alert — macOS Raylib Port\n");
    printf("Window: %dx%d (game: %dx%d)\n", GAME_WIDTH * SCALE, GAME_HEIGHT * SCALE, GAME_WIDTH, GAME_HEIGHT);
    printf("Press ESC to exit.\n");

    // Test pattern: red/green/blue gradient
    for (int y = 0; y < GAME_HEIGHT; y++) {
        for (int x = 0; x < GAME_WIDTH; x++) {
            int idx = (y * GAME_WIDTH + x) * 4;
            pixels[idx + 0] = (unsigned char)(x * 255 / GAME_WIDTH);   // R
            pixels[idx + 1] = (unsigned char)(y * 255 / GAME_HEIGHT);  // G
            pixels[idx + 2] = 128;                                      // B
            pixels[idx + 3] = 255;                                      // A
        }
    }
    UpdateTexture(fbTexture, pixels);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw framebuffer scaled to window
        DrawTexturePro(
            fbTexture,
            (Rectangle){ 0, 0, (float)GAME_WIDTH, (float)GAME_HEIGHT },
            (Rectangle){ 0, 0, (float)(GAME_WIDTH * SCALE), (float)(GAME_HEIGHT * SCALE) },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );

        // Overlay info text
        DrawText("C&C Red Alert — macOS Port", 10, 10, 20, RAYWHITE);
        DrawText("Phase 3: Raylib window active", 10, 35, 16, GREEN);
        DrawText("Game engine compiled & linked", 10, 55, 16, GREEN);
        DrawText("Next: File I/O + game init", 10, 75, 16, YELLOW);

        DrawFPS(GAME_WIDTH * SCALE - 90, 10);
        EndDrawing();
    }

    RL_FREE(pixels);
    UnloadTexture(fbTexture);
    CloseWindow();

    return 0;
}
