/*
 * File Name: audio.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "audio.h"

void AUD_init() {
    u8 i;
    for (i = 0; i < AUD_NUM_CHANNELS; i++) {
        AUD_channel_history[i] = 0;
    }

    // disable ints when requesting Z80 BUS
    SYS_disableInts();

    // load the appropriate driver if not already done
    Z80_loadDriver(AUD_DRIVER, TRUE);

    // re-enable ints
    SYS_enableInts();

    SYS_setVIntCallback(AUD_vInt);
}
void AUD_vInt() {
    if (AUD_DMA_METHOD <= 0) {
        return;
    }

    u16 in, i;

    in = GET_VCOUNTER;
    if ((in >= 224) && (in <= 230)) {
        XGM_set68KBUSProtection(TRUE);
        switch (AUD_DMA_METHOD) {
            case 1:
                VDP_doDMAEx(VDP_DMA_VRAM, 0, 0x8000, (6 * 1024) / 2, 2);
                break;
            case 2:
                for (i = 0; i < 4; i++) {
                    VDP_doDMAEx(VDP_DMA_VRAM, 0, 0x8000, 1024 / 2, 2);
                    waitSubTick(0);
                }
                break;
            case 3:
                for (i = 0; i < 8; i++) {
                    VDP_doDMAEx(VDP_DMA_VRAM, 0, 0x8000, 256 / 2, 2);
                    waitSubTick(0);
                }
                break;
        }
        XGM_set68KBUSProtection(FALSE);
    }
}

void AUD_loadSfx(const u8 id, const u8 *sfx) {
    XGM_setPCM(id + AUD_PCM_ID, sfx, sizeof(sfx));
}
void AUD_playSfx(const u8 id) {
    u8 i, c = AUD_NUM_CHANNELS;

    // Find available channel
    for (i = 0; i < AUD_NUM_CHANNELS; i++) {
        if (XGM_isPlayingPCM(AUD_channels[i]) == FALSE) {
            c = i;
            break;
        }
    }

    // Get channel from history if full
    if (c >= AUD_NUM_CHANNELS) {
        c = AUD_channel_history[AUD_NUM_CHANNELS - 1];
        if (c == 0) c = AUD_channels[AUD_NUM_CHANNELS - 1];
    }

    // Play sample
    XGM_startPlayPCM(id + AUD_PCM_ID, AUD_PCM_PRIORITY, AUD_channels[c]);

    // Shift history
    for (i = 1; i < AUD_NUM_CHANNELS; i++) {
        AUD_channel_history[i] = AUD_channel_history[i - 1];
    }
    AUD_channel_history[0] = c;
}
void AUD_stopSfx() {
    u8 i;
    for (i = 0; i < AUD_NUM_CHANNELS; i++) {
        XGM_stopPlayPCM(AUD_channels[i]);
        AUD_channel_history[i] = 0;
    }
}

void AUD_playMusic(const u8 *song) {
    AUD_stopMusic();
    XGM_startPlay(song);
}
void AUD_toggleMusic() {
    if (AUD_isPlaying()) {
        AUD_pauseMusic();
    }  else {
        AUD_resumeMusic();
    }
}
void AUD_stopMusic() {
    if (AUD_isPlaying()) {
        XGM_stopPlay();
    }
}
u8 AUD_isPlaying() {
    return XGM_isPlaying();
}
void AUD_pauseMusic() {
    XGM_pausePlay();
}
void AUD_resumeMusic() {
    XGM_resumePlay();
}
