/*
 * File Name: title.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include "scene.h"
#include "scenes.h"
#include "resources.h"

void SCN_title_load() {
    u16 palette[64];
    u16 ind = TILE_USERINDEX;

    SPR_init(16, 256, 256); // Init sprites engine
    //VDP_setPaletteColors(0, (u16*)palette_black, 64); // Set all palette to black

    // Draw Background
    VDP_drawImageEx(PLAN_B, &res_title_background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += res_title_background.tileset->numTile;

    // Draw Logo
    VDP_drawImageEx(PLAN_A, &res_title_logo, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 5, 4, FALSE, TRUE);
    ind += res_title_logo.tileset->numTile;

    // Prepare Palettes
    memcpy(&palette[0], res_title_background.palette->data, 16 * 2);
    memcpy(&palette[16], res_title_logo.palette->data, 16 * 2);
    memcpy(&palette[32], palette_grey, 16 * 2);
    memcpy(&palette[48], palette_grey, 16 * 2);

    // Fade In Palettes
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);
}

void SCN_title_init() {

}

void SCN_title_joy() {

}

void SCN_title_updateLogic() {

}

void SCN_title_updateGfx() {
    if (SCN_counter % 120 == 0) {
        VDP_drawText("Press Start", 14, 24);
    } else if (SCN_counter % 120 == 60) {
        VDP_clearText(14, 24, 11);
    }
}

void SCN_title_input() {

}

Scene SCN_title = {
    &SCN_title_load, // SCN_loadFunc
    &SCN_title_init, // SCN_initFunc
    &SCN_title_joy, // SCN_joyFunc
    &SCN_title_updateLogic, // SCN_updateLogicFunc
    &SCN_title_updateGfx, // SCN_updateGfxFunc
    &SCN_title_input, // SCN_inputFunc
    NULL // SCN_cleanFunc
};
