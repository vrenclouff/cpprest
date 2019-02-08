#pragma once

#include "Route.hpp"
#include "Filter.hpp"

#include <map>
#include <array>

namespace rest {
	
	class Router : public Route, public Filter {
	private:
		std::map<std::string, std::array<std::function<void(http_request, http_response)>, 10>> _routes;
		std::map<std::string, std::array<std::function<void(http_request, http_response)>, 2>> _filters;

	public:
		void processed(const method method, http_request & request);

		void register_filter(const int index, const std::string & path, std::function<void(http_request, http_response)> handle) override final;
		void register_route(const method method, const std::string & path, std::function<void(http_request, http_response)> handle) override final;
	};
}