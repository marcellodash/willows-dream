/*
 * File Name: joy.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef JOY_H_
#define JOY_H_

#include <genesis.h>

u8 JOY_paused;

void JOY_inputHandler(u16 joy, u16 changed, u16 state);

#endif
