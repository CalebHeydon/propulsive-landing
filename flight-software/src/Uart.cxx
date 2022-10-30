#include "Uart.hxx"

#include <string>
#include <fstream>

Uart::Uart(std::string device)
{
    mDevice = device;
    mFile.open(mDevice, std::ifstream::in | std::ifstream::out);
}

Uart::~Uart()
{
    mFile.close();
}

std::string Uart::device()
{
    return mDevice;
}

bool Uart::open()
{
    return mFile.is_open();
}

void Uart::write(std::string data)
{
    mFile << data;
}

std::string Uart::read()
{
    std::string line;
    mFile >> line;
    return line;
}
