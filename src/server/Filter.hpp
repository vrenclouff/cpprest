#pragma once

#include "definitions.hpp"
#include <map>
#include <array>
#include <memory>

namespace rest {

	struct invocation_node {
		std::map<utility::string_t, std::unique_ptr<invocation_node>> children;
		bool invoke;
		std::function<void(http_request, http_response)> function;

		invocation_node() : invoke(false), function(nullptr) {}
	};

	class filter {
	private:
		std::unique_ptr<invocation_node> _before, _after;

		int _register(std::unique_ptr<invocation_node> & root, const std::string & path, std::function<void(http_request, http_response)> handle);
		int _invoke(std::unique_ptr<invocation_node> & root, const std::vector<utility::string_t> & path_components, http_request & request, http_response & response);

	protected:
		filter() : _before(std::make_unique<invocation_node>()), _after(std::make_unique<invocation_node>()) {};

		int invoke_filter_before(const std::vector<utility::string_t> & path_components, http_request request, http_response response) {
			return _invoke(_before, path_components, request, response);
		};
		int invoke_filter_after(const std::vector<utility::string_t> & path_components, http_request request, http_response response) {
			return _invoke(_after, path_components, request, response);
		};

	public:
		void before(std::function<void(http_request, http_response)> handle) { _register(_before, "/*", handle); };
		void after(std::function<void(http_request, http_response)> handle) { _register(_after, "/*", handle); };
		void before(const std::string & path, std::function<void(http_request, http_response)> handle) { _register(_before, path, handle); };
		void after(const std::string & path, std::function<void(http_request, http_response)> handle)  { _register(_after, path, handle); };
	};
}