#pragma once

#include <fstream>
#include <string>

class Uart
{
private:
    std::string mDevice;
    std::fstream mFile;

public:
    Uart(std::string device = "/dev/ttyu0");
    ~Uart();

    std::string device();
    bool open();
    void write(std::string data);
    std::string read();
};
