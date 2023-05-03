#include <stdlib.h>
#include "pico/stdlib.h"

#define DELAY 100

int pins[] = { 16, 17, 18, 19, 20, 21, 22, 26, 27, 28 };
const int pins_len = sizeof(pins) / sizeof(pins[0]);

void setPinOuts(int pins[], int len) {
    for (int i = 0; i < len; i++) {
        int pin = pins[i];
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }
}

void pinOnFor(int pin, int ms) {
    gpio_put(pin, 1);
    sleep_ms(ms);
    gpio_put(pin, 0);
}

inline void flow(int pins[], int start, int end) { 
    if (end > start) {
        for (int i = start; i < end; i++) {
            pinOnFor(pins[i], DELAY);
        }
    } else {
        for (int i = start; i > end; i--) {
            pinOnFor(pins[i], DELAY);
        }
    }
}

int main() {
    setPinOuts(pins, pins_len);
    while (true) {
        // Flow up
        flow(pins, 0, pins_len - 1);

        // Flow down
        flow(pins, pins_len - 1, 0);
    }
}
