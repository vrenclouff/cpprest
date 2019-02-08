#include "Router.hpp"

void rest::Router::processed(const method method, http_request & request) {
	const auto path_t = uri::decode(request.relative_uri().path());
	const auto path_s = utility::conversions::to_utf8string(path_t);

	if (_routes.find(path_s) == _routes.end()) {
		request.reply(http_code::NotFound);
		return;
	}

	std::vector<utility::string_t> paths = uri::split_path(path_t);
	paths.push_back(U("/"));
	std::rotate(paths.rbegin(), paths.rbegin() + 1, paths.rend());

	http_response response(http_code::OK);

	std::string tempPath = "";
	std::vector<std::function<void(http_request, http_response)>> postFilters;
	for (const auto & path : paths) {
		tempPath += utility::conversions::to_utf8string(path);

		if (_filters[tempPath][0]) {
			_filters[tempPath][0](request, response);
		}
		if (_filters[tempPath][1]) {
			postFilters.push_back(_filters[tempPath][1]);
		}
	}

	_routes[path_s][static_cast<uint8_t>(method)](request, response);

	for (const auto & fnc : postFilters) {
		fnc(request, response);
	}

	request.reply(response);
}

void rest::Router::register_filter(const int index, const std::string & path, std::function<void(http_request, http_response)> handle) {
	_filters[path][index] = handle;
}
void rest::Router::register_route(const method method, const std::string & path, std::function<void(http_request, http_response)> handle) {
	_routes[path][static_cast<uint8_t>(method)] = handle;
}

