#include "stdafx.h"
#include <Windows.h>
#include "../include/debug.h"
#include "../include/handle.h"
#include "../include/util.h"

using KennyKerr::null_handle;
using KennyKerr::wait_all;

auto __stdcall work(void *) -> DWORD
{
	TRACE(L"thread %d\n", GetCurrentThreadId());
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
	VERIFY_(WAIT_OBJECT_0, wait_all(t1, t2));

	return 0;
}
