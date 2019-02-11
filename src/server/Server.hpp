#pragma once

#include "router.hpp"

namespace rest {

	class server {
	private:
//		std::unique_ptr<router> _router;
		router _router;
		std::unique_ptr<http_listener> _listener;

	public:
		server(const uri & url);

		static std::unique_ptr<server> init(const std::string domain, const int port);
		static std::unique_ptr<server> init(const int port);
		static std::unique_ptr<server> init();
		
		void start();
		
		route	& route()  { return _router; }
		filter	& filter() { return _router; }
		handler & handle() { return _router; }
	};
}