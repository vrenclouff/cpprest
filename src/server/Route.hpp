#pragma once

#include "Definitions.hpp"
#include <map>
#include <array>

namespace rest {

	class route {
	private:
		std::map<std::string, std::array<std::function<void(http_request, http_response)>, static_cast<size_t>(method::count)>> _routes;

	protected:
		int register_route(const method method, const std::string & path, std::function<void(http_request, http_response)> handle);
		int invoke_route(const std::string & path, const method method, http_request & request, http_response & response);
	public:
		void del(const std::string & path, std::function<void(http_request, http_response)> handle)		{ register_route(method::DEL, path, handle); };
		void get(const std::string & path, std::function<void(http_request, http_response)> handle)		{ register_route(method::GET, path, handle); };
		void put(const std::string & path, std::function<void(http_request, http_response)> handle)		{ register_route(method::PUT, path, handle); };
		void post(const std::string & path, std::function<void(http_request, http_response)> handle)	{ register_route(method::POST, path, handle); };
	};

}