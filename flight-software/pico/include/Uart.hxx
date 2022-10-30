#pragma once

#include <cstdint>
#include <string>

class Uart
{
private:
    static const int kBufferSize = 1024;

    int mUart, mGpio0, mGpio1, mBaudrate;
    uint8_t *mBuffer;

public:
    Uart(int uart = 0, int gpio0 = 0, int gpio1 = 1, int baudrate = 115200);
    ~Uart();

    void write(std::string data);
    std::string read();
};
