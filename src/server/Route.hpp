#pragma once

#include "Definitions.hpp"

namespace rest {

	class Route {
	protected:
		virtual void register_route(const method method, const std::string & path, std::function<void(http_request, http_response)> handle) = 0;
	public:
		void del(const std::string & path, std::function<void(http_request, http_response)> handle)		{ register_route(method::DEL, path, handle); };
		void get(const std::string & path, std::function<void(http_request, http_response)> handle)		{ register_route(method::GET, path, handle); };
		void put(const std::string & path, std::function<void(http_request, http_response)> handle)		{ register_route(method::PUT, path, handle); };
		void post(const std::string & path, std::function<void(http_request, http_response)> handle)	{ register_route(method::POST, path, handle); };
	};

}