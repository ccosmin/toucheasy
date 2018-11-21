// TouchEasy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>

static LPSTR GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return nullptr;

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	return messageBuffer;
}

int wmain(int argc, TCHAR* argv[])
{
	if (argc < 2) {
		return 1;
	}

	const TCHAR* fn = argv[1];
	HANDLE h = ::CreateFile(fn, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	LPSTR message = GetLastErrorAsString();
	if (message)
	{
		::MessageBoxA(NULL, message, "Error", MB_ICONERROR);
		::LocalFree(message);
		return 1;
	}

	FILETIME ft;
	SYSTEMTIME st;
	::GetSystemTime(&st);
	::SystemTimeToFileTime(&st, &ft);
	BOOL changed = ::SetFileTime(h, NULL, NULL, &ft);

	::CloseHandle(h);
}
