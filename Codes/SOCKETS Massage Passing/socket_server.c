// for more details refer to http://www.codeproject.com/Articles/13724/Windows-IPC

#include <stdio.h>
#include "windows.h"

// Name given to the Mailslot
#define my_mailSlot "\\\\.\\mailslot\\MyMailSlot"
// Mailslot name format - \\.\mailslot\mailslotname

#define BUFFER_SIZE 1024 // 1 KB

int main(int argc, char* argv[])
{
  HANDLE hMailslot;

	hMailslot = CreateMailslot(
		my_mailSlot,              // mailslot name
		BUFFER_SIZE,              // input buffer size
		MAILSLOT_WAIT_FOREVER,    // no timeout
		NULL                      // default security attribute
	);                    

	if (INVALID_HANDLE_VALUE == hMailslot) {
		printf("\nError occurred while creating the mailslot: %d", GetLastError());
		return 1;  // Error occurred
	}
	else {
		printf("\nCreateMailslot() was successful.");
	}

	//Mailslot is one-way communication
	//Server will only read
	//Using ReadFile()
	char szBuffer[BUFFER_SIZE];
	DWORD cbBytes;
	BOOL bResult;

	printf("\nWaiting for client connection...");

	while(1) //Infinite, till user terminates the console app
	{
		//Read client message
		bResult = ReadFile(
			hMailslot,           // handle to mailslot
			szBuffer,            // buffer to receive data
			sizeof(szBuffer),    // size of buffer
			&cbBytes,            // number of bytes read
			NULL                 // not overlapped I/O
		);               

		if ( (!bResult) || (0 == cbBytes) )
		{
			printf("\nError occurred while reading from the client: %d", GetLastError());
			CloseHandle(hMailslot);
			return 1;  // Error occurred
		}
		else
		{
			printf("\nReadFile() was successful.");
		}

		printf("\nClient sent the following message: %s", szBuffer);
	}

	CloseHandle(hMailslot);

	return 0; // Success
}
