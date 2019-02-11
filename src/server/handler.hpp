#pragma once

#include "definitions.hpp"

#include <array>
#include <functional>

namespace rest {

	class handler {
	private:
		std::array<std::function<void(void*, http_request, http_response)>, static_cast<size_t>(handler_type::count)> _handlers;

		void _default_exception(const std::exception & exception, http_request & request, http_response & response);
		void _default_not_found(const std::string & path, http_request & request, http_response & response);

	protected:
		int invoke_handler(void* object, const handler_type type, http_request & request, http_response & response);

		handler();

	public:
		void exception(std::function<void(std::exception, http_request, http_response)> handler);
		void not_found(std::function<void(std::string, http_request, http_response)> handler);
	};
}