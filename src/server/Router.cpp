#include "router.hpp"

using namespace utility::conversions;

void rest::router::processed(const method method, http_request & request) {
	const auto path = uri::decode(request.relative_uri().path());
	const auto path_components = uri::split_path(path);

	http_response response(http_code::OK);
	
	try {
		invoke_filter_before(path_components, request, response);

		auto path_str = to_utf8string(path);
		if (invoke_route(path_str, method, request, response)) {
			invoke_handler(&path_str, handler_type::NOT_FOUND, request, response);
		}

		invoke_filter_after(path_components, request, response);
	}
	catch (std::exception & e) {
		invoke_handler(&e, handler_type::EXCEPTION, request, response);
	}

	request.reply(response);
}

