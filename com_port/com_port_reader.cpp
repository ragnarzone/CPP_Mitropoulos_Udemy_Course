#include <iostream>
#include <string>
#include <Windows.h>

int main() {

	HANDLE hSerial;
	hSerial = CreateFile(L"COM4",
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			//serial port does not exist. Inform user.
			std::cout << "Serial port does not exist" << std::endl;
		}
		//some other error occurred. Inform user.
	}

	DCB dcbSerialParams = { 0 };

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		//error getting state
	}

	dcbSerialParams.BaudRate = CBR_115200;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams)) {
		//error setting serial port state
		std::cout << "Unable to set serial port state" << std::endl;
	}

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		//error occureed. Inform user
		std::cout << "Unable to set serial port timeouts" << std::endl;
	}


	// read
	const int n { 1024 };
	char szBuff[n + 1] = { 0 };
	DWORD dwBytesRead = 0;

	
	while (true) {
		if (!ReadFile(hSerial, szBuff, n, &dwBytesRead, NULL)) {
			//error occurred. Report to user.
			std::cout << "Unable to read data!" << std::endl;
		}
		std::cout << szBuff << std::endl;
	}

	CloseHandle(hSerial);	
	
	return 0;
}