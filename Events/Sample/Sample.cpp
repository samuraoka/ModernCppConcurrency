#include "stdafx.h"
#include "../include/handle.h"

using KennyKerr::null_handle;

class event
{
	null_handle h;

public:
	// Meaning of = delete after function declaration
	// https://stackoverflow.com/questions/5513881/meaning-of-delete-after-function-declaration
	event(event const &) = delete;
	auto operator=(event const &)->event & = delete;
	~event() = default;
};

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
