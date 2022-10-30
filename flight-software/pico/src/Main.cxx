#include <memory>
#include <map>
#include <pico/stdlib.h>
#include <iostream>
#include <pico/multicore.h>
#include <string>
#include <cstdlib>

#include "DigitalOutput.hxx"
#include "Servo.hxx"
#include "Uart.hxx"

std::unique_ptr<std::map<int, DigitalOutput>> digitalOutputs;
std::unique_ptr<std::map<int, Servo>> servos;
std::unique_ptr<Uart> uart;

void ioThread()
{
    while (uart == nullptr)
        std::cout << "pico\n";

    while (true)
        std::cout << uart->read();
}

int main(int argc, char **argv)
{
    digitalOutputs = std::make_unique<std::map<int, DigitalOutput>>();
    servos = std::make_unique<std::map<int, Servo>>();

    stdio_usb_init();
    multicore_launch_core1(ioThread);

    std::string line;
    while (true)
    {
        std::cin >> line;

        size_t i = line.find(':');
        if (i == -1)
            continue;

        std::string mode = line.substr(0, i);
        line = line.substr(i + 1, line.size() - 1);

        if (mode[0] == 'd')
        {
            i = line.find(':');
            if (i == -1)
                continue;

            std::string gpioString = line.substr(0, i);
            std::string outputString = line.substr(i + 1, line.size() - i);

            int gpio = std::atoi(gpioString.c_str());
            bool output = outputString[0] == '0' ? false : true;

            if (servos->find(gpio) != servos->end())
                continue;
            if (digitalOutputs->find(gpio) == digitalOutputs->end())
                digitalOutputs->insert(std::pair<int, DigitalOutput>{gpio, DigitalOutput{gpio}});

            digitalOutputs->at(gpio).write(output);
        }
        else if (mode[0] == 's')
        {
            i = line.find(':');
            if (i == -1)
                continue;

            std::string gpioString = line.substr(0, i);
            std::string microsecondsString = line.substr(i + 1, line.size() - i);

            int gpio = std::atoi(gpioString.c_str());
            int microseconds = std::atoi(microsecondsString.c_str());

            if (digitalOutputs->find(gpio) != digitalOutputs->end())
                continue;
            if (servos->find(gpio) == servos->end())
                servos->insert(std::pair<int, Servo>{gpio, Servo{gpio}});

            if (microseconds > 0)
                servos->at(gpio).write(microseconds);
            else
                servos->at(gpio).stop();
        }
        else if (mode[0] == 'u')
        {
            if (uart == nullptr)
                uart = std::make_unique<Uart>();

            uart->write(line);
        }
    }

    return 0;
}
