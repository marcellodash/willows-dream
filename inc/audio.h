/*
 * File Name: audio.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <genesis.h>

#define AUD_DRIVER Z80_DRIVER_XGM
#define AUD_DMA_METHOD 0
#define AUD_PCM_PRIORITY 15 // 0 (lowest) -> 15 (highest)
#define AUD_PCM_ID 64 // Offset to make ids zero-based
#define AUD_NUM_CHANNELS 4

static const u16 AUD_channels[AUD_NUM_CHANNELS] = {
    SOUND_PCM_CH1_MSK,
    SOUND_PCM_CH2_MSK,
    SOUND_PCM_CH3_MSK,
    SOUND_PCM_CH4_MSK,
};
u16 AUD_channel_history[AUD_NUM_CHANNELS];

void AUD_init();
void AUD_vInt();

void AUD_loadSfx(const u8 id, const u8 *sfx);
void AUD_playSfx(const u8 id);
void AUD_stopSfx();

void AUD_playMusic(const u8 *song);
void AUD_toggleMusic();
void AUD_stopMusic();
u8 AUD_isPlaying();
void AUD_pauseMusic();
void AUD_resumeMusic();

#endif
