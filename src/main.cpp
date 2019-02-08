
#include "server/Server.hpp"

using namespace rest;

int main() {
	
	auto server = Server::init("http://localhost", 8080);

	server->route().get("/api", [](http_request request, http_response response) {
		std::cout << "GET /api" << std::endl;

		auto message = json::object();
		message[U("status")] = json::string(U("ok"));

		response.set_body(message);
		response.set_status_code(http_code::OK);
	});

	server->route().post("/api", [](http_request request, http_response response) {
		std::cout << "POST /api\n" << request.extract_utf8string().get() << std::endl;
	});

	server->filter().before("/api", [](http_request request, http_response response) {
		std::cout << "before /API" << std::endl;
	});

	server->filter().before([](http_request request, http_response response) {
		std::cout << "before /" << std::endl;
	});

	server->filter().after([](http_request request, http_response response) {
		std::cout << "afeter /" << std::endl;
	});

	server->start();

    return 0;
}

