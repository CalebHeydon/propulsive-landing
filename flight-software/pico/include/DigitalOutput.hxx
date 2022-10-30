#pragma once

class DigitalOutput
{
private:
    int mGpio;

public:
    DigitalOutput(int gpio);
    ~DigitalOutput();

    void write(bool output);
};
