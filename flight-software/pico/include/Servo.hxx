#pragma once

class Servo
{
private:
    int mGpio;
    int mSlice;
    int mChannel;

public:
    Servo(int gpio);
    ~Servo();

    void write(int microseconds);
    void stop();
};
