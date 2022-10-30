#pragma once

#include <memory>
#include <string>

#include "Uart.hxx"

class Imu
{
public:
    struct Data
    {
        double gx, gy, gz;
        double ax, ay, az;
        double mx, my, mz;
        double pressure;
        double temperature;
        double humidity;
    };

private:
    std::shared_ptr<Uart> mUart;
    struct Data mData;

public:
    Imu(std::shared_ptr<Uart> uart);
    ~Imu();

    void update();
    struct Data get();
};
