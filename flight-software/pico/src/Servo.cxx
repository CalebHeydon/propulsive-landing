#include "Servo.hxx"

#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <math.h>

Servo::Servo(int gpio)
{
    mGpio = gpio;

    gpio_set_function(mGpio, GPIO_FUNC_PWM);
    mSlice = pwm_gpio_to_slice_num(mGpio);
    mChannel = pwm_gpio_to_channel(mGpio);

    pwm_set_clkdiv(mSlice, 256.0f);
    pwm_set_wrap(mSlice, 9804);
}

Servo::~Servo()
{
    stop();
}

void Servo::write(int microseconds)
{
    pwm_set_gpio_level(mGpio, round((microseconds / 20000.0f) * 9804));
    pwm_set_enabled(mSlice, true);
}

void Servo::stop()
{
    pwm_set_enabled(mSlice, false);
}
