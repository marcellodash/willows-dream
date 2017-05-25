/*
 * File Name: main.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "resources.h"
#include "helper.h"

#define GLOBALS_PAUSED 1

u32 globals = 0x00000000;

fix32 camposx;
fix32 camposy;

static void loop();
static void joyHandler(u16 joy, u16 changed, u16 state);
static void updateCamera(fix32 x, fix32 y);

int main() {
    u16 palette[16];
    u16 ind;

    SYS_disableInts(); // Disable interrupt when accessing VDP
    VDP_setScreenWidth320(); // Screen Initialization

    VDP_drawText("Game Paused", ((screenWidth >> 3) - 11) >> 1, (screenHeight >> 4) - 1);

    ind = TILE_USERINDEX;
    /*
    VDP_drawImageEx(PLAN_B, &imagetest, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += imagetest.tileset->numTile;
    */

    // VDP process done, we can re-enable interrupts
    SYS_enableInts();

    // Init scrolling
    updateCamera(FIX32(0), FIX32(0));

    // Prepare palettes
    // memcpy(&palette[0], imagetest.palette->data, 16 * 2);

    // Fade in
    // VDP_fadeIn(0, (1 * 16) - 1, palette, 20, FALSE);

    // Initialize Joystick
    JOY_init();
    JOY_setEventHandler(&joyHandler);

    while (1) {
        if (bit(globals, GLOBALS_PAUSED) == 0) {
            loop(); // Call game loop
        } else {
            //drawTextCenter("Game Paused", screenWidth >> 1, screenHeight >> 1);
        }

        // Wait for screen refresh
        VDP_waitVSync();
    }

    return 0;
}

static void loop() {
    // Game loop
    updateCamera(camposx, camposy);
}

static void joyHandler(u16 joy, u16 changed, u16 state) {
    if (joy == JOY_1) {
        if (changed & BUTTON_START) { // Start button released
            toggle(&globals, GLOBALS_PAUSED); // Toggle paused bit
        }
        if (state & BUTTON_RIGHT) { // Right button pressed
            camposx++;
        }
        if (state & BUTTON_LEFT) { // Left button pressed
            camposx--;
        }
        if (state & BUTTON_UP) { // Up button pressed
            camposy--;
        }
        if (state & BUTTON_DOWN) { // Down button pressed
            camposy++;
        }
    }
}

static void updateCamera(fix32 x, fix32 y) {
    if ((x != camposx) || (y != camposy)) {
        camposx = x;
        camposy = y;
        VDP_setHorizontalScroll(PLAN_A, fix32ToInt(-camposx));
        VDP_setHorizontalScroll(PLAN_B, fix32ToInt(-camposx) >> 3);
        VDP_setVerticalScroll(PLAN_A, fix32ToInt(camposy));
        VDP_setVerticalScroll(PLAN_B, fix32ToInt(camposy) >> 3);
    }
}
