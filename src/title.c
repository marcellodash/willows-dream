/*
 * File Name: title.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "scene.h"
#include "scenes.h"
#include "resources.h"
#include "audio.h"

#define SCN_TITLE_NUM_STARS 6

Sprite* SCN_title_stars[SCN_TITLE_NUM_STARS];
fix32 SCN_title_stars_x[SCN_TITLE_NUM_STARS];
fix32 SCN_title_stars_y[SCN_TITLE_NUM_STARS];
fix32 SCN_title_stars_rate[SCN_TITLE_NUM_STARS];
u16 SCN_title_stars_osc_rate[SCN_TITLE_NUM_STARS];
fix32 SCN_title_stars_osc_depth[SCN_TITLE_NUM_STARS];

void SCN_title_audio() {
    // Load SFX
    // AUD_loadSfx()...

    // Play Title Music
    AUD_playMusic(res_title_music);
}

void SCN_title_display() {
    u16 ind = TILE_USERINDEX;

    // Draw Background
    VDP_drawImageEx(PLAN_B, &res_title_background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += res_title_background.tileset->numTile;

    // Prepare Palettes
    SCN_setPalette(PAL0, res_title_background.palette->data);
}

void SCN_title_init() {
    u8 i;

    for (i = 0; i < SCN_TITLE_NUM_STARS; i++) {
        SCN_title_stars_x[i] = FIX32(random() % VDP_getScreenWidth());
        SCN_title_stars_y[i] = FIX32(random() % VDP_getScreenHeight());
        SCN_title_stars_rate[i] = FIX32(random()) % FIX32(0.25) + FIX32(0.125);
        SCN_title_stars_osc_rate[i] = (random() % 511 + 511) / 60; // cycle: 0-1023
        SCN_title_stars_osc_depth[i] = FIX32(random() % 10 + 5);
    }
}

void SCN_title_sprite() {
    u8 i;

    for (i = 0; i < SCN_TITLE_NUM_STARS; i++) {
        SCN_title_stars[i] = SPR_addSprite(&res_title_star, fix32ToInt(SCN_title_stars_x[i]), fix32ToInt(SCN_title_stars_y[i]), TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
        SPR_setFrame(SCN_title_stars[i], random() % 4);
    }

    // Prepare palettes
    SCN_setPalette(PAL2, res_title_star.palette->data);
}

void SCN_title_joy(u16 joy, u16 changed, u16 state) {

}

void SCN_title_updateLogic() {

}

void SCN_title_updateGfx() {
    u8 i;
    //fix32 posx;

    for (i = 0; i < SCN_TITLE_NUM_STARS; i++) {
        SCN_title_stars_y[i] += FIX32(0.25); // SCN_title_stars_rate[i];
        if (fix32ToInt(SCN_title_stars_y[i]) > VDP_getScreenHeight()) {
            //SCN_title_stars_x[i] = FIX32(random() % VDP_getScreenWidth());
            SCN_title_stars_y[i] = FIX32(-8);
        }

        //posx = fix32Add(SCN_title_stars_x[i], fix32Mul(sinFix32(fix32Mul(SCN_title_stars_osc_rate[i], FIX32(SCN_counter))), SCN_title_stars_osc_depth[i]));
        //posx = SCN_title_stars_x[i] + sinFix32(SCN_title_stars_osc_rate[i] * SCN_counter) * SCN_title_stars_osc_depth[i];

        SPR_setPosition(SCN_title_stars[i], fix32ToInt(SCN_title_stars_x[i]), fix32ToInt(SCN_title_stars_y[i]));
    }

    if (SCN_counter % 120 == 0) {
        VDP_drawText("Press Start", 14, 24);
    } else if (SCN_counter % 120 == 60) {
        VDP_clearText(14, 24, 11);
    }
}

void SCN_title_input() {

}

Scene SCN_title = {
    &SCN_title_audio, // SCN_audioFunc
    &SCN_title_display, // SCN_displayFunc
    &SCN_title_init, // SCN_initFunc
    &SCN_title_sprite, // SCN_spriteFunc
    &SCN_title_joy, // SCN_joyFunc
    &SCN_title_updateLogic, // SCN_updateLogicFunc
    &SCN_title_updateGfx, // SCN_updateGfxFunc
    &SCN_title_input, // SCN_inputFunc
    NULL // SCN_cleanFunc
};
