#include <stdlib.h>
#include "pico/stdlib.h"

const int buzzer_pin = 15;
const int button_pin = 16;

int main() {
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_put(buzzer_pin, 0);
    while (true) {
        // TODO: Loop setting the buzzer pin high if the button pin is low
        gpio_put(buzzer_pin, gpio_get(button_pin) ?  1 : 0);
    }
}
