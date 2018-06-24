#include "stdafx.h"
#include <Windows.h>
#include "../include/debug.h"
#include "../include/handle.h"

using KennyKerr::null_handle;

auto __stdcall work(void *) -> DWORD
{
	TRACE(L"a thread has started.");
	return 0;
}

auto main() -> int
{
	auto t1 = null_handle
	{
		CreateThread(nullptr, 0, work, nullptr, CREATE_SUSPENDED, nullptr)
	};

	auto t2 = null_handle
	{
		CreateThread(nullptr, 0, work, nullptr, CREATE_SUSPENDED, nullptr)
	};

	ResumeThread(t1.get());
	ResumeThread(t2.get());

	HANDLE handles[] = { t1.get(), t2.get() };
	VERIFY_(WAIT_OBJECT_0,
		WaitForMultipleObjects(_countof(handles), handles, true, INFINITE));

	return 0;
}
