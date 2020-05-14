# C++ REST

The C++ REST is a server-side project wrapped [cpprestsdk](https://github.com/Microsoft/cpprestsdk) SDK. Allows to easily add new routes and filters using a modern C++. 

## Include

````c++
#include "server/Server.hpp"
````

## Initialization

By default, server runs on localhost on port 8080. If you want to set another port and hostname, add as param port or hostname and port.

````c++
auto server = rest::Server::init();
auto server = rest::Server::init(8080);
auto server = rest::Server::init("http://localhost", 8080);
````

## Routes



````c++
server->route().get("/api", [](http_request request, http_response response) {
	// Show something
});
````

## Filters

Before-filters are evaluated before each request, and can read the request and read/modify the response.

````c++
server->filter().before([](http_request request, http_response response) {
	// Do something
});
````

After-filters are evaluated after each request, and can read the request and read/modify the response:

````c++
server->filter().after([](http_request request, http_response response) {
	// Do something
});
````

Filters optionally take a pattern, causing them to be evaluated only if the request path matches that pattern:

````c++
server->filter().before("/api", [](http_request request, http_response response) {
	// Do something
});
````

## Example

````c++
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


````
