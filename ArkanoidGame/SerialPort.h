#pragma once

#include <windows.h>
#include <iostream>

namespace ArkanoidGame 
{
    class SerialPort
    {
    private:
        HANDLE handler;
        bool connected;
        COMSTAT status;
        DWORD errors;

    public:
        SerialPort(const char *portName);
        ~SerialPort();

        int readSerialPort(char *buffer, unsigned int buf_size);
        bool isConnected();
    };
}