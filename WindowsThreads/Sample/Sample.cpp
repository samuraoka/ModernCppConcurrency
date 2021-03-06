#include "stdafx.h"

using KennyKerr::null_handle;
using KennyKerr::wait_one;

auto WINAPI work(LPVOID) -> DWORD
{
	TRACE(L"work!\n");
	return 123;
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
