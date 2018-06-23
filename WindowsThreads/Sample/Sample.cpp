#include "stdafx.h"

using KennyKerr::null_handle;

auto WINAPI work(LPVOID) -> DWORD
{
	TRACE(L"work!\n");
	return 123;
}

struct windows_exception
{
	DWORD error;

	explicit windows_exception(DWORD const value = GetLastError()) :
		error{ value }
	{}
};

auto wait_one(HANDLE const h, DWORD const milliseconds = INFINITE) -> bool
{
	auto const result = WaitForSingleObject(h, milliseconds);

	if (result == WAIT_OBJECT_0) return true;

	if (result == WAIT_TIMEOUT) return false;

	throw windows_exception();
}

auto main() -> int
{
	auto t = null_handle
	{
		CreateThread(nullptr, 0, work, nullptr, 0, nullptr)
	};

	if (t)
	{
		while (!wait_one(t.get(), 0))
		{
			TRACE(L"work has not yet done.\n");
			Sleep(1);
		}

		auto exit = DWORD{};
		VERIFY(GetExitCodeThread(t.get(), &exit));
		ASSERT(exit == 123); // STILL_ACTIVE (259)
	}

    return 0;
}
