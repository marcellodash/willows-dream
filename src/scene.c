/*
 * File Name: scene.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "scene.h"
#include "joy.h"

void SCN_loadScene(Scene *scene) {
    if ((SCN_active)) SCN_cleanScene();
    SCN_counter = 0;
    SCN_resetPalettes();

    if ((SCN_active = scene)) {
        SYS_disableInts();
        VDP_setScreenWidth320();
        VDP_setScreenHeight224();

        if ((SCN_active->audio)) SCN_active->audio();

        //VDP_resetSprites();
        SPR_init(16, 256, 256);

        if ((SCN_active->display)) SCN_active->display();
        SYS_enableInts();

        if ((SCN_active->init)) SCN_active->init();

        if ((SCN_active->sprite)) SCN_active->sprite();
        SPR_update();

        VDP_fadeIn(0, (SCN_NUM_PALETTES * SCN_PALETTE_SIZE) - 1, SCN_palette, SCN_FADE_DURATION, FALSE);

        JOY_setEventHandler(&SCN_joyHandler);
    }
}

void SCN_joyHandler(u16 joy, u16 changed, u16 state) {
    if (!(SCN_active)) return;

    JOY_inputHandler(joy, changed, state); // General joystick input actions
    if ((SCN_active->joy)) SCN_active->joy(joy, changed, state); // Scene specific joystick input actions
}

void SCN_updateScene() {
    if (!(SCN_active)) return;

    if ((SCN_active->updateLogic)) SCN_active->updateLogic();
    if ((SCN_active->updateGfx)) SCN_active->updateGfx();

    SPR_update();

    SCN_counter++;
}

void SCN_cleanScene() {
    if (!(SCN_active)) return;

    JOY_setEventHandler(NULL);

    VDP_fadeOut(0, (SCN_NUM_PALETTES * SCN_PALETTE_SIZE) - 1, SCN_FADE_DURATION, FALSE);
    SCN_resetPalettes();
    SPR_clear();

    if ((SCN_active->clean)) SCN_active->clean();
    SCN_active = NULL;
}

void SCN_setPalette(u8 index, const u16 *palette) {
    if (index < 0 || index >= SCN_NUM_PALETTES) return;
    memcpy(&SCN_palette[SCN_PALETTE_SIZE * index], palette, SCN_PALETTE_SIZE * sizeof(u16));
}

void SCN_resetPalettes() {
    u8 i;
    for (i = 0; i < SCN_NUM_PALETTES; i++) {
        SCN_setPalette(i, palette_black);
    }
}
