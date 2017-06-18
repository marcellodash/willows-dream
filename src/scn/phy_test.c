/*
 * File Name: phy_test.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "scene.h"
#include "scenes.h"
#include "resources.h"
#include "audio.h"

void SCN_phy_test_audio() {

}

void SCN_phy_test_display() {

}

void SCN_phy_test_init() {

}

void SCN_phy_test_sprite() {

}

void SCN_phy_test_joy(u16 joy, u16 changed, u16 state) {

}

void SCN_phy_test_updateLogic() {

}

void SCN_phy_test_updateGfx() {

}

Scene SCN_phy_test = {
    NULL, // SCN_audioFunc
    &SCN_phy_test_display, // SCN_displayFunc
    &SCN_phy_test_init, // SCN_initFunc
    &SCN_phy_test_sprite, // SCN_spriteFunc
    &SCN_phy_test_joy, // SCN_joyFunc
    &SCN_phy_test_updateLogic, // SCN_updateLogicFunc
    &SCN_phy_test_updateGfx, // SCN_updateGfxFunc
    NULL // SCN_cleanFunc
};
