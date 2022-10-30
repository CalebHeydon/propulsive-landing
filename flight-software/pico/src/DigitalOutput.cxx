#include "DigitalOutput.hxx"

#include <pico/stdlib.h>

DigitalOutput::DigitalOutput(int gpio)
{
    mGpio = gpio;

    gpio_init(mGpio);
    gpio_set_dir(mGpio, GPIO_OUT);
}

DigitalOutput::~DigitalOutput()
{
}

void DigitalOutput::write(bool output)
{
    gpio_put(mGpio, output);
}
