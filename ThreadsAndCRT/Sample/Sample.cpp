#include "stdafx.h"

using KennyKerr::null_handle;
using KennyKerr::wait_one;

auto __stdcall work(void *) -> unsigned
{
	TRACE(L"work!\n");
	return 0;
}

auto main() -> int
{
	auto t = null_handle
	{
		reinterpret_cast<HANDLE>(
			_beginthreadex(nullptr, 0, work, nullptr, 0, nullptr))
	};

	if (t)
	{
		wait_one(t.get(), INFINITE);
	}

    return 0;
}
