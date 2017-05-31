/*
 * File Name: scene.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <genesis.h>

typedef void (*SCN_initFunc)(struct sceneData *);
typedef void (*SCN_joyFunc)(struct sceneData *, u16 joy, u16 changed, u16 state);
typedef void (*SCN_updateLogicFunc)(struct sceneData *);
typedef void (*SCN_updateGfxFunc)(struct sceneData *);
typedef void (*SCN_inputFunc)(struct sceneData *);
typedef void (*SCN_cleanFunc)(struct sceneData *);

typedef struct sceneData {
    SCN_initFunc *init;
    SCN_joyFunc *joy;
    SCN_updateLogicFunc *updateLogic;
    SCN_updateGfxFunc *updateGfx;
    SCN_inputFunc *input;
    SCN_cleanFunc *clean;
} Scene = {NULL, NULL, NULL, NULL, NULL};

Scene *SCN_active;

void SCN_loadScene(Scene *scene);
void SCN_joyHandler(u16 joy, u16 changed, u16 state);
void SCN_updateScene();
void SCN_cleanScene();

#endif
