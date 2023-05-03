#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

const int pin = 16;
const bool isRgbw = false;

static inline void put_pixel(PIO pio, uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, 0, pixel_grb << 8u);
}

const uint32_t GRB_red = 0x00FF00;
const uint32_t GRB_green = 0xFF0000;
const uint32_t GRB_blue = 0x0000FF;

int main() {
    PIO pio = pio0;
    int sm = 0;

    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, pin, 800000, isRgbw);
    put_pixel(pio, GRB_red);
    put_pixel(pio, GRB_green);
    put_pixel(pio, GRB_blue);
    return 0;
}
