#pragma once

#include "Definitions.hpp"

namespace rest {

	class Filter {
	protected:
		virtual void register_filter(const int index, const std::string & path, std::function<void(http_request, http_response)> handle) = 0;
	public:
		void before(std::function<void(http_request, http_response)> handle) { register_filter(0, "/", handle); };
		void after(std::function<void(http_request, http_response)> handle) { register_filter(1, "/", handle); };
		void before(const std::string & path, std::function<void(http_request, http_response)> handle) { register_filter(0, path, handle); };
		void after(const std::string & path, std::function<void(http_request, http_response)> handle)  { register_filter(1, path, handle); };
	};
}