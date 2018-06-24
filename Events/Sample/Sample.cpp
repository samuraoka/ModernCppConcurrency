#include "stdafx.h"
#include "../include/handle.h"

using KennyKerr::null_handle;

auto main() -> int
{
	auto e = null_handle
	{
		CreateEvent(nullptr, true, false, nullptr)
	};

	VERIFY(SetEvent(e.get()));
	VERIFY(ResetEvent(e.get()));

	WaitForSingleObject(e.get(), INFINITE);

    return 0;
}
