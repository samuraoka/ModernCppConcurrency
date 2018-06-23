#include "stdafx.h"
#include <Windows.h>
#include <process.h>
#include "..\include\debug.h"


auto __stdcall work(void *) -> unsigned
{
	TRACE(L"work!\n");
	return 0;
}

auto main() -> int
{
	auto t = uintptr_t
	{
		_beginthreadex(nullptr, 0, work, nullptr, 0, nullptr)
	};

	if (t)
	{
		VERIFY_(WAIT_OBJECT_0,
			WaitForSingleObject(reinterpret_cast<HANDLE>(t), INFINITE));
		VERIFY(CloseHandle(reinterpret_cast<HANDLE>(t)));
	}

    return 0;
}
