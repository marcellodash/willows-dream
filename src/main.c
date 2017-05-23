#include <genesis.h>

int main() {
    VDP_drawText("Hello World!", 10, 13);

    while (1) {
        // Wait for screen refresh
        VDP_waitVSync();
    }

    return (0);
}
