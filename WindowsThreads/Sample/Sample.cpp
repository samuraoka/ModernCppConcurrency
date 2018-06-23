#include "stdafx.h"

using KennyKerr::null_handle;

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
		VERIFY_(WAIT_OBJECT_0, WaitForSingleObject(t.get(), INFINITE));

		auto exit = DWORD{};
		VERIFY(GetExitCodeThread(t.get(), &exit));
		ASSERT(exit == 123); // STILL_ACTIVE (259)
	}

    return 0;
}
