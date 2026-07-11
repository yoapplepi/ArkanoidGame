#include "SerialPort.h"

namespace ArkanoidGame
{
    SerialPort::SerialPort(const char *portName) : status(), errors(0)
    {
        this->connected = false;

        this->handler = CreateFileA(static_cast<LPCSTR>(portName),
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);

        if (this->handler == INVALID_HANDLE_VALUE)
        {
            if (GetLastError() == ERROR_FILE_NOT_FOUND)
            {
                std::cerr << "ERROR: Handle was not attached. Reason: Choose another port.\n";
            }
            else
            {
                std::cerr << "ERROR: Unknown error.\n";
            }
        }
        else
        {
            DCB dcbSerialParameters = {0};

            if (!GetCommState(this->handler, &dcbSerialParameters))
            {
                std::cerr << "failed to get current serial parameters!\n";
            }
            else
            {
                dcbSerialParameters.BaudRate = CBR_9600;
                dcbSerialParameters.ByteSize = 8;
                dcbSerialParameters.StopBits = ONESTOPBIT;
                dcbSerialParameters.Parity = NOPARITY;
                dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

                if (!SetCommState(handler, &dcbSerialParameters))
                {
                    std::cout << "ALERT: Could not set Serial Port parameters\n";
                }
                else
                {
                    this->connected = true;
                    PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                    Sleep(2000);
                }
            }
        }
    }

    SerialPort::~SerialPort()
    {
        if (this->connected) {
            this->connected = false;
            CloseHandle(this->handler);
        }
    }

    int SerialPort::readSerialPort(char *buffer, unsigned int buf_size)
    {
        DWORD bytesRead;
        unsigned int toRead = 0;

        ClearCommError(this->handler, &this->errors, &this->status);

        if (this->status.cbInQue > 0) {
            if (this->status.cbInQue > buf_size) {
                toRead = buf_size;
            } else {
                toRead = this->status.cbInQue;
            }

            if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL)) {
                return bytesRead;
            }
        }

        return 0;
    }

    bool SerialPort::isConnected()
    {
        return this->connected;
    }
}