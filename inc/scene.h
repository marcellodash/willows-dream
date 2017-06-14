/*
 * File Name: scene.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <genesis.h>

#define SCN_NUM_PALETTES 4
#define SCN_PALETTE_SIZE 16

typedef void SCN_audioFunc();
typedef void SCN_displayFunc();
typedef void SCN_initFunc();
typedef void SCN_spriteFunc();
typedef void SCN_joyFunc(u16 joy, u16 changed, u16 state);
typedef void SCN_updateLogicFunc();
typedef void SCN_updateGfxFunc();
typedef void SCN_inputFunc();
typedef void SCN_cleanFunc();

typedef struct sceneData {
    SCN_audioFunc *audio;
    SCN_displayFunc *display;
    SCN_initFunc *init;
    SCN_spriteFunc *sprite;
    SCN_joyFunc *joy;
    SCN_updateLogicFunc *updateLogic;
    SCN_updateGfxFunc *updateGfx;
    SCN_inputFunc *input;
    SCN_cleanFunc *clean;
} Scene;

Scene *SCN_active;
u32 SCN_counter;
u16 SCN_palette[SCN_PALETTE_SIZE];

void SCN_loadScene(Scene *scene);
void SCN_joyHandler(u16 joy, u16 changed, u16 state);
void SCN_updateScene();
void SCN_cleanScene();
void SCN_setPalette(u8 index, const u16 *palette);
void SCN_resetPalettes();

#endif
