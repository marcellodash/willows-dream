/*
 * File Name: scene.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <genesis.h>

typedef void SCN_loadFunc();
typedef void SCN_initFunc();
typedef void SCN_joyFunc(u16 joy, u16 changed, u16 state);
typedef void SCN_updateLogicFunc();
typedef void SCN_updateGfxFunc();
typedef void SCN_inputFunc();
typedef void SCN_cleanFunc();

typedef struct sceneData {
    SCN_loadFunc *load;
    SCN_initFunc *init;
    SCN_joyFunc *joy;
    SCN_updateLogicFunc *updateLogic;
    SCN_updateGfxFunc *updateGfx;
    SCN_inputFunc *input;
    SCN_cleanFunc *clean;
} Scene;

Scene *SCN_active;
u32 SCN_counter;

void SCN_loadScene(Scene *scene);
void SCN_joyHandler(u16 joy, u16 changed, u16 state);
void SCN_updateScene();
void SCN_cleanScene();

#endif
