#include <vector>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>

#include "Uart.hxx"
#include "Imu.hxx"

std::shared_ptr<Imu> imu;
std::shared_ptr<struct Imu::Data> imuData;
std::mutex imuMutex;

int main(int argc, char **argv)
{
	std::string baseDevice;
#ifdef __FreeBSD__
	baseDevice = "/dev/ttyu";
#else
	baseDevice = "/dev/ttyACM";
#endif

	std::vector<std::shared_ptr<Uart>> uarts;
	for (int i = 0; true; i++)
	{
		std::stringstream stream;
		stream << baseDevice;
		stream << i;
		std::shared_ptr<Uart> uart = std::make_shared<Uart>(stream.str());

		if (!uart->open())
			break;
		uarts.push_back(uart);
	}

	std::shared_ptr<Uart> picoUart;
	std::shared_ptr<Uart> imuUart;

	for (std::shared_ptr<Uart> uart : uarts)
	{
		std::stringstream stream;
#ifdef __FreeBSD__
		stream << "stty -f ";
#else
		stream << "stty -F ";
#endif
		stream << uart->device() << " 115200";

		if (system(stream.str().c_str()) == -1)
			continue;

		std::string line;
		while (true)
		{
			line = uart->read();

			if (line.starts_with("pico"))
			{
				picoUart = uart;
				break;
			}
			else if (line.starts_with("imu"))
			{
				imuUart = uart;
				break;
			}
		}
	}

	std::cout << "pico: ";
	if (picoUart == nullptr)
		std::cout << "not found\n";
	else
		std::cout << picoUart->device() << "\n";

	std::cout << "imu: ";
	if (imuUart == nullptr)
		std::cout << "not found\n";
	else
		std::cout << imuUart->device() << "\n";

	if (imuUart == nullptr)
		return -1;

	imu = std::make_shared<Imu>(imuUart);
	imuData = std::make_shared<struct Imu::Data>();

	std::thread imuThread{[]()
						  {
							  while (true)
							  {
								  imu->update();

								  imuMutex.lock();
								  *imuData = imu->get();
								  imuMutex.unlock();
							  }
						  }};

	while (true)
	{
		imuMutex.lock();
		std::cout << "gx: " << imuData->gx << ", gy: " << imuData->gy << ", gz: " << imuData->gz << ", ax: " << imuData->ax << ", ay: " << imuData->ay << ", az: " << imuData->az << "\n";
		imuMutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	return 0;
}
