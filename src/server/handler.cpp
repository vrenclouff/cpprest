#include "handler.hpp"

using namespace utility::conversions;

rest::handler::handler() {
	not_found(std::bind(&handler::_default_not_found, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	exception(std::bind(&handler::_default_exception, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void rest::handler::_default_exception(const std::exception & exception, http_request & request, http_response & response) {
	auto message = json::object();
	const auto msg = to_string_t("Invoked exception '" + std::string(exception.what()) + "'.");
	message[U("error")] = json::string(msg);
	response.set_body(message);
	response.set_status_code(rest::http_code::InternalError);
}

void rest::handler::_default_not_found(const std::string & path, http_request & request, http_response & response) {
	auto message = json::object();
	const auto msg = to_string_t("The path '" + path + "' doesn't exist.");
	message[U("error")] = json::string(msg);
	response.set_body(message);
	response.set_status_code(rest::http_code::NotFound);
}

int rest::handler::invoke_handler(void* object, const handler_type type, http_request & request, http_response & response) {
	auto handler = _handlers[static_cast<uint8_t>(type)];
	if (handler == nullptr) { return 1; }
	handler(object, request, response);
	return 0;
}

void rest::handler::exception(std::function<void(std::exception, http_request, http_response)> handler) {
	_handlers[static_cast<uint8_t>(handler_type::EXCEPTION)] = [=](void* object, http_request & request, http_response & response) {
		handler(*static_cast<std::exception*>(object), request, response);
	};
}

void rest::handler::not_found(std::function<void(std::string, http_request, http_response)> handler){
	_handlers[static_cast<uint8_t>(handler_type::NOT_FOUND)] = [=](void* object, http_request & request, http_response & response) {
		handler(*static_cast<std::string*>(object), request, response);
	};
}
