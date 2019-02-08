#pragma once

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>

#define LOCALHOST	"http://127.0.0.1"
#define PORT		8080

namespace rest {

	using http_request = web::http::http_request;
	using http_response = web::http::http_response;
	using http_listener = web::http::experimental::listener::http_listener;
	using uri = web::uri;
	using http_method = web::http::methods;
	using json = web::json::value;

	using http_code = web::http::status_codes;

	enum class method : uint8_t {
		CONNECT,
		DEL,
		GET,
		HEAD,
		MERGE,
		OPTIONS,
		PATCH,
		POST,
		PUT,
		TRCE,
	};
}