// for more details refer to http://www.codeproject.com/Articles/13724/Windows-IPC

#include <stdio.h>
#include "windows.h"

// Name given to the Mailslot
#define my_mailSlot "\\\\.\\mailslot\\MyMailSlot"
// Mailslot name format - \\.\mailslot\mailslotname
/*
  This mailslot is for server on the same computer, however,
  mailslots can be used to connect to a remote server.
*/

#define BUFFER_SIZE 1024 // 1 KB

int main(int argc, char* argv[])
{
	HANDLE hMailslot;

	// Connect to the server mailslot using CreateFile()
	hMailslot = CreateFile(
		my_mailSlot,           // mailslot name
		GENERIC_WRITE,         // mailslot write only
		FILE_SHARE_READ,       // required for mailslots
		NULL,                  // default security attributes
		OPEN_EXISTING,         // opens existing mailslot
		FILE_ATTRIBUTE_NORMAL, // normal attributes
		NULL                   // no template file
	);                 

	if (INVALID_HANDLE_VALUE == hMailslot) {
		printf("\nError occurred while connecting to the server: %d", GetLastError());
		return 1;  // Error occurred
	}
	else {
		printf("\nCreateFile() was successful.");
	}

	// We are done connecting to the mailslot,
	// Mailslot communication is one-way,
	// client will just write to mailslot
	// Using WriteFile()

	char szBuffer[BUFFER_SIZE];

	printf("\nEnter a message to be sent to the server: ");
	gets(szBuffer);

	DWORD cbBytes;

	//Send the message to server
	BOOL bResult = WriteFile(
		hMailslot,            // handle to mailslot
		szBuffer,             // buffer to write from
		strlen(szBuffer)+1,   // number of bytes to write, include the NULL
		&cbBytes,             // number of bytes written
		NULL                  // not overlapped I/O
	);                

	if ( (!bResult) || (strlen(szBuffer)+1 != cbBytes)) {
		printf("\nError occurred while writing to the server: %d", GetLastError());
		CloseHandle(hMailslot);
		return 1;  // Error occurred
	}
	else {
		printf("\nWriteFile() was successful.");
	}

	CloseHandle(hMailslot);
	
	return 0; // Success
}
