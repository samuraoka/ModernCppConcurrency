#include "stdafx.h"
#include <utility>
#include "../include/handle.h"
#include "../include/util.h"

using KennyKerr::null_handle;
using KennyKerr::windows_exception;
using std::move;

enum class event_type
{
	auto_reset,
	manual_reset,
};

class event
{
	null_handle h;

public:
	// Meaning of = delete after function declaration
	// https://stackoverflow.com/questions/5513881/meaning-of-delete-after-function-declaration
	event(event const &) = delete;
	auto operator=(event const &)->event & = delete;
	~event() = default;

	explicit event(event_type type) :
		h { CreateEvent(nullptr, static_cast<BOOL>(type), false, nullptr) }
	{
		if (!h) throw windows_exception();
	}

	// Move Constructors and Move Assignment Operators (C++)
	// https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp
	// 
	// Throw keyword in function's signature
	// https://stackoverflow.com/questions/1055387/throw-keyword-in-functions-signature
	event(event && other) throw() :
		h { other.h.release() }
	{}

	auto operator=(event && other) throw()->event &
	{
		// std::move
		// https://en.cppreference.com/w/cpp/utility/move
		h = move(other.h);
	}

	auto set() throw() -> void
	{
		VERIFY(SetEvent(h.get()));
	}

	auto clear() throw() -> void
	{
		VERIFY(ResetEvent(h.get()));
	}

	auto wait(DWORD const milliseconds = INFINITE) throw() -> bool
	{
		auto const result = WaitForSingleObject(h.get(), milliseconds);
		ASSERT(result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT);

		return result == WAIT_OBJECT_0;
	}

	auto get() const throw() -> HANDLE
	{
		return h.get();
	}
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
