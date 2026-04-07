/*
 * raylib_input.cpp — Bridge between Raylib input and game's KeyboardClass
 *
 * Called from Fill_Buffer_From_System() every time the game checks for input.
 * Polls Raylib for keyboard/mouse events and feeds them into the game's
 * key buffer via Put_Key_Message().
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

// Include game headers for KeyboardClass
#include "FUNCTION.H"

// Undef game colors before including raylib
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

/* Map Raylib key codes to Windows VK_ codes used by the game */
static unsigned short Raylib_To_VK(int ray_key) {
    switch (ray_key) {
        case KEY_ESCAPE:    return VK_ESCAPE;
        case KEY_ENTER:     return VK_RETURN;
        case KEY_SPACE:     return VK_SPACE;
        case KEY_BACKSPACE: return VK_BACK;
        case KEY_TAB:       return VK_TAB;
        case KEY_LEFT:      return VK_LEFT;
        case KEY_RIGHT:     return VK_RIGHT;
        case KEY_UP:        return VK_UP;
        case KEY_DOWN:      return VK_DOWN;
        case KEY_HOME:      return VK_HOME;
        case KEY_END:       return VK_END;
        case KEY_PAGE_UP:   return VK_PRIOR;
        case KEY_PAGE_DOWN: return VK_NEXT;
        case KEY_INSERT:    return VK_INSERT;
        case KEY_DELETE:    return VK_DELETE;
        case KEY_F1:        return VK_F1;
        case KEY_F2:        return VK_F2;
        case KEY_F3:        return VK_F3;
        case KEY_F4:        return VK_F4;
        case KEY_F5:        return VK_F5;
        case KEY_F6:        return VK_F6;
        case KEY_F7:        return VK_F7;
        case KEY_F8:        return VK_F8;
        case KEY_F9:        return VK_F9;
        case KEY_F10:       return VK_F10;
        case KEY_F11:       return VK_F11;
        case KEY_F12:       return VK_F12;
        default:
            /* Alphanumeric keys: Raylib uses ASCII */
            if (ray_key >= KEY_A && ray_key <= KEY_Z) return (unsigned short)ray_key;
            if (ray_key >= KEY_ZERO && ray_key <= KEY_NINE) return (unsigned short)ray_key;
            return 0;
    }
}

/* Global mouse position scaled to game resolution */
static int g_mouse_x = 0;
static int g_mouse_y = 0;

extern "C" {

/*
 * Called by WWKeyboardClass::Fill_Buffer_From_System()
 * Polls all Raylib input and feeds it to the game.
 */
void Raylib_Poll_Input(WWKeyboardClass *kbd) {
    /* CRITICAL: Call PollInputEvents so Raylib processes OS events.
     * Without this, the window becomes unresponsive. */
    PollInputEvents();

    /* Scale mouse position from window coords to game coords */
    int window_w = GetScreenWidth();
    int window_h = GetScreenHeight();
    Vector2 mpos = GetMousePosition();
    g_mouse_x = (int)(mpos.x * 640.0f / window_w);
    g_mouse_y = (int)(mpos.y * 400.0f / window_h);
    if (g_mouse_x < 0) g_mouse_x = 0;
    if (g_mouse_y < 0) g_mouse_y = 0;
    if (g_mouse_x >= 640) g_mouse_x = 639;
    if (g_mouse_y >= 400) g_mouse_y = 399;

    /* Feed mouse button events via public Put() method.
     * Mouse keys must be followed by X,Y coordinates in the buffer
     * because Buff_Get() reads 2 extra elements for mouse events. */
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        kbd->Put(VK_LBUTTON);
        kbd->Put((unsigned short)g_mouse_x);
        kbd->Put((unsigned short)g_mouse_y);
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        kbd->Put(VK_LBUTTON | 0x0800);  /* WWKEY_RLS_BIT */
        kbd->Put((unsigned short)g_mouse_x);
        kbd->Put((unsigned short)g_mouse_y);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        kbd->Put(VK_RBUTTON);
        kbd->Put((unsigned short)g_mouse_x);
        kbd->Put((unsigned short)g_mouse_y);
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        kbd->Put(VK_RBUTTON | 0x0800);
        kbd->Put((unsigned short)g_mouse_x);
        kbd->Put((unsigned short)g_mouse_y);
    }

    /* Feed keyboard events */
    int key;
    while ((key = GetKeyPressed()) != 0) {
        unsigned short vk = Raylib_To_VK(key);
        if (vk) {
            /* Add modifier bits */
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                vk |= 0x0100;  /* WWKEY_SHIFT_BIT */
            if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
                vk |= 0x0200;  /* WWKEY_CTRL_BIT */
            if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
                vk |= 0x0400;  /* WWKEY_ALT_BIT */
            kbd->Put(vk);
        }
    }

    /* Check for window close */
    if (WindowShouldClose()) {
        GameActive = false;
    }

    /* Render the game's framebuffer to the Raylib window.
     * This is called from within the game's event loop so the display
     * stays updated even when Select_Game() is blocking. */
    extern void Raylib_Render_Frame(void);
    Raylib_Render_Frame();
}

/* Override Get_Mouse_X/Y to return Raylib-scaled positions */
int Get_Mouse_X(void) { return g_mouse_x; }
int Get_Mouse_Y(void) { return g_mouse_y; }

/*
 * GetAsyncKeyState — replaces the Windows API stub.
 * The gadget system calls this to check if mouse buttons are held down.
 * Returns non-zero if the key is currently pressed.
 */
short GetAsyncKeyState(int vk) {
    switch (vk) {
        case 0x01: /* VK_LBUTTON */
            return IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? (short)0x8000 : 0;
        case 0x02: /* VK_RBUTTON */
            return IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? (short)0x8000 : 0;
        case 0x10: /* VK_SHIFT */
            return (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? (short)0x8000 : 0;
        case 0x11: /* VK_CONTROL */
            return (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) ? (short)0x8000 : 0;
        case 0x12: /* VK_MENU (Alt) */
            return (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) ? (short)0x8000 : 0;
        default:
            return 0;
    }
}

} /* extern "C" */
