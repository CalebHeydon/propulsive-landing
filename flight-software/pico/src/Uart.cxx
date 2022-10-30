#include "Uart.hxx"

#include <cstdint>
#include <pico/stdlib.h>
#include <string>
#include <string.h>

Uart::Uart(int uart, int gpio0, int gpio1, int baudrate)
{
    mUart = uart;
    mGpio0 = gpio0;
    mGpio1 = gpio1;
    mBaudrate = baudrate;

    mBuffer = new uint8_t[kBufferSize];

    uart_init(mUart == 0 ? uart0 : uart1, mBaudrate);
    gpio_set_function(mGpio0, GPIO_FUNC_UART);
    gpio_set_function(mGpio1, GPIO_FUNC_UART);
}

Uart::~Uart()
{
    delete[] mBuffer;
}

void Uart::write(std::string data)
{
    uart_puts(mUart == 0 ? uart0 : uart1, data.c_str());
}

std::string Uart::read()
{
    memset(mBuffer, 0, kBufferSize);
    uart_read_blocking(mUart == 0 ? uart0 : uart1, mBuffer, kBufferSize - 1);

    std::string result = "";
    uint8_t *pointer = mBuffer;
    while (*pointer != 0)
    {
        result += *pointer;
        pointer++;
    }

    return result;
}
