#include <stdlib.h>
#include "pico/stdlib.h"

#define DELAY_ON 250
#define DELAY_OFF 500

int main() {
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(DELAY_ON);
        gpio_put(LED_PIN, 0);
        sleep_ms(DELAY_OFF);
    }
}
