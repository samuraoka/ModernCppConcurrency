#include "stdafx.h"
#include "../include/handle.h"
#include "../include/event.h"

using KennyKerr::null_handle;
using KennyKerr::event;
using KennyKerr::event_type;
using std::move;

auto main() -> int
{
	auto e = event { event_type::manual_reset };
	ASSERT(!e.wait(0));

	e.set();
	ASSERT(e.wait());

	e.clear();
	ASSERT(!e.wait(0));

	//auto e2 = e; // C2280 attempting to reference a deleted function 
	auto e2 = move(e);
	e2.set();

	e.set(); // This statement causes an assertion error.

    return 0;
}
