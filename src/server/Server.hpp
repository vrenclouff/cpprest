#pragma once

#include "Router.hpp"

namespace rest {

	class Server {
	private:
		Router _router;
		std::unique_ptr<http_listener> _listener;

	public:
		Server(const uri & url);

		static std::unique_ptr<Server> init(const std::string domain, const int port);
		static std::unique_ptr<Server> init(const int port);
		static std::unique_ptr<Server> init();
		
		void start();
		
		Route  & route()  { return _router; }
		Filter & filter() { return _router; }
	};
}