#include "route.hpp"

int rest::route::register_route(const method method, const std::string & path, std::function<void(http_request, http_response)> handle) {
	_routes[path][static_cast<uint8_t>(method)] = handle;
	return 0;
}

int rest::route::invoke_route(const std::string & path, const method method, http_request & request, http_response & response) {
	if (_routes.find(path) == _routes.end()) {
		return 1;
	}
	const auto & fnc = _routes[path][static_cast<uint8_t>(method)];
	if (fnc == nullptr) {
		return 2;
	}
	fnc(request, response);
	return 0;
}
