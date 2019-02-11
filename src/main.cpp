
#include "server/Server.hpp"

using namespace rest;

int main() {
	
	auto server = rest::server::init("http://localhost", 8080);

	server->route().get("/api", [](http_request request, http_response response) {
		std::cout << "GET /api" << std::endl;

		auto message = json::object();
		message[U("status")] = json::string(U("ok"));

		response.set_body(message);
		response.set_status_code(http_code::OK);
	});

	server->route().get("/api/exception", [](http_request request, http_response response) {
		throw std::exception("Something was wrong");
	});

	server->filter().before("/api", [](http_request request, http_response response) {
		std::cout << "Before /api" << std::endl;
	});

	server->filter().before([](http_request request, http_response response) {
		std::cout << "Before /" << std::endl;
	});

	server->filter().after([](http_request request, http_response response) {
		std::cout << "After /" << std::endl;
	});


	server->start();

    return 0;
}

