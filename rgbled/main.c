#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const int pin = 15;

void on_pwm_wrap() {
    static int fade = 0;
    static bool going_up = true;
    
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(pin));

    if (going_up) {
        ++fade;
        if (fade > 255) {
            fade = 255;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(pin, fade * fade);
}

void init_pin(int pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_clear_irq(slice);
    pwm_set_irq_enabled(slice, false);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice, &config, true);
}

void set_pin(int pin, int level) {
    pwm_set_gpio_level(pin, level * level);
}

const int red_pin = 13;
const int green_pin = 12;
const int blue_pin = 11;

int main() {
    init_pin(red_pin);
    init_pin(green_pin);
    init_pin(blue_pin);

    while (1) {
        int red = random() % 25;
        int green = random() % 25;
        int blue = random() % 25;

        set_pin(red_pin, 255 - red);
        set_pin(green_pin, 255 - green);
        set_pin(blue_pin, 255 - blue);

        sleep_ms(100);
    }

    return 0;
}
