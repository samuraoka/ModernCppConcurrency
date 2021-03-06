#include "stdafx.h"
#include <Windows.h>
#include "../include/debug.h"
#include "../include/handle.h"
#include "../include/util.h"
#include "../include/event.h"

using KennyKerr::null_handle;
using KennyKerr::wait_all;
using KennyKerr::event;
using KennyKerr::event_type;

static auto e = event { event_type::auto_reset };

auto __stdcall work(void *) -> DWORD
{
	TRACE(L"thread %d\n", GetCurrentThreadId());
	e.wait();
	TRACE(L"run %d\n", GetCurrentThreadId());

	e.set();
	Sleep(100);

	return 0;
}

auto main() -> int
{
	auto t1 = null_handle
	{
		CreateThread(nullptr, 0, work, nullptr, 0, nullptr)
	};

	auto t2 = null_handle
	{
		CreateThread(nullptr, 0, work, nullptr, 0, nullptr)
	};

	Sleep(100);
	e.set();
	Sleep(100);

	wait_all(t1, t2);

	return 0;
}
