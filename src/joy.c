/*
 * File Name: joy.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "joy.h"

u8 JOY_paused = FALSE;

void JOY_inputHandler(u16 joy, u16 changed, u16 state) {
    if (changed & state & BUTTON_START) {
        JOY_paused = TRUE;
    }
}
