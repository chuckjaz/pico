#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"

const int buzzer_pin = 15;
const int button_pin = 16;

void alert(void);
void freq(int pin, int freqs, int times);

int main() {
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);
    gpio_put(buzzer_pin, 0);

    while (true) {
        if (gpio_get(button_pin) == 0) {
            alert();
        } else {
            gpio_put(buzzer_pin, 0);
        }
    }
}

void alert() {
    float sinVal;
    int toneVal;
     
    for (int x = 0; x < 360; x += 10) {
        sinVal = sin(x * (M_PI / 180));
        toneVal = 2000 + sinVal * 500;
        freq(buzzer_pin, toneVal, 10);
    }
}

void freq(int pin, int freqs, int times) {
    if (freqs == 0) {
        gpio_put(buzzer_pin, 0);
        return;
    }

    for (int i = 0; i < times * freqs / 1000; i++) {
        gpio_put(buzzer_pin, 1);
        sleep_ms(1000000 / freqs / 2);
        gpio_put(buzzer_pin, 0);
        sleep_ms(1000000 / freqs / 2);
    }
}
