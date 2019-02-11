#pragma once

#include "route.hpp"
#include "filter.hpp"
#include "handler.hpp"

#include <map>
#include <array>

namespace rest {
	
	class router : public route, public filter, public handler {
	public:
		void processed(const method method, http_request & request);
	};
}