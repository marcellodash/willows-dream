/*
 * File Name: title.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include "scene.h"
#include "scenes.h"

void SCN_title_init() {

}

void SCN_title_joy() {

}

void SCN_title_updateLogic() {

}

void SCN_title_updateGfx() {

}

Scene SCN_title = {
    &SCN_title_init, // SCN_initFunc
    &SCN_title_joy, // SCN_joyFunc
    &SCN_title_updateLogic, // SCN_updateLogicFunc
    &SCN_title_updateGfx, // SCN_updateGfxFunc
    &SCN_title_input, // SCN_inputFunc
    NULL // SCN_cleanFunc
};
