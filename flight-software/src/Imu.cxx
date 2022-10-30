#include "Imu.hxx"

#include <memory>
#include <string.h>
#include <string>
#include <cstdlib>

#include "Uart.hxx"

Imu::Imu(std::shared_ptr<Uart> uart)
{
    mUart = uart;
    memset(&mData, 0, sizeof(mData));
}

Imu::~Imu()
{
}

void Imu::update()
{
    std::string line = mUart->read();

    size_t i = line.find(":");
    if (i == -1)
        return;
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string gxString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string gyString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string gzString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string axString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string ayString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string azString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string mxString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string myString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string mzString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string pressureString = line.substr(0, i);
    line = line.substr(i + 1);

    i = line.find(":");
    if (i == -1)
        return;
    std::string temperatureString = line.substr(0, i);
    line = line.substr(i + 1);

    std::string humidityString = line;

    mData.gx = std::atof(gxString.c_str());
    mData.gy = std::atof(gyString.c_str());
    mData.gz = std::atof(gzString.c_str());
    mData.ax = std::atof(axString.c_str());
    mData.ay = std::atof(ayString.c_str());
    mData.az = std::atof(azString.c_str());
    mData.mx = std::atof(mxString.c_str());
    mData.my = std::atof(myString.c_str());
    mData.mz = std::atof(mzString.c_str());
    mData.pressure = std::atof(pressureString.c_str());
    mData.temperature = std::atof(temperatureString.c_str());
    mData.humidity = std::atof(humidityString.c_str());
}

struct Imu::Data Imu::get()
{
    return mData;
}
