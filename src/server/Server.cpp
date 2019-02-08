#include "Server.hpp"

#include <signal.h>
#include <mutex>

std::condition_variable _cnd;
std::mutex _mtx;

rest::Server::Server(const uri & url) : _listener(std::make_unique<http_listener>(url)) {
	_listener->support(http_method::CONNECT, std::bind(&Router::processed, &_router, method::CONNECT, std::placeholders::_1));
	_listener->support(http_method::DEL, std::bind(&Router::processed, &_router, method::DEL, std::placeholders::_1));
	_listener->support(http_method::GET, std::bind(&Router::processed, &_router, method::GET, std::placeholders::_1));
	_listener->support(http_method::HEAD, std::bind(&Router::processed, &_router, method::HEAD, std::placeholders::_1));
	_listener->support(http_method::MERGE, std::bind(&Router::processed, &_router, method::MERGE, std::placeholders::_1));
	_listener->support(http_method::OPTIONS, std::bind(&Router::processed, &_router, method::OPTIONS, std::placeholders::_1));
	_listener->support(http_method::PATCH, std::bind(&Router::processed, &_router, method::PATCH, std::placeholders::_1));
	_listener->support(http_method::POST, std::bind(&Router::processed, &_router, method::POST, std::placeholders::_1));
	_listener->support(http_method::PUT, std::bind(&Router::processed, &_router, method::PUT, std::placeholders::_1));
	_listener->support(http_method::TRCE, std::bind(&Router::processed, &_router, method::TRCE, std::placeholders::_1));
};

std::unique_ptr<rest::Server> rest::Server::init(const std::string domain, const int port) {
	const auto host = domain + ":" + std::to_string(port);
	const auto url = utility::conversions::to_string_t(host);
	return std::make_unique<Server>(url);
}

std::unique_ptr<rest::Server> rest::Server::init(const int port) {
	return init(LOCALHOST, port);
}
std::unique_ptr<rest::Server> rest::Server::init() {
	return init(LOCALHOST, PORT);
}
void rest::Server::start() {
	std::unique_lock<std::mutex> lock(_mtx);
	signal(SIGINT, [](int signal) {
		switch (signal) {
		case SIGINT: _cnd.notify_one(); return;
		}
	});

	_listener->open().wait();

	std::wcout << "Starting server at " << _listener->uri().to_string() << std::endl;

	_cnd.wait(lock);

	_listener->close().wait();

	std::cout << "Server stopped." << std::endl;
}
