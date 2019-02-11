#include "filter.hpp"

int rest::filter::_invoke(std::unique_ptr<invocation_node> & root, const std::vector<utility::string_t> & path_components, http_request & request, http_response & response) {
	size_t index = 0;
	auto* node = root.get();
	do {
		if (node->invoke) {
			node->function(request, response);
		}

		const auto & el = path_components[index];
		if (node->children.find(el) != node->children.end()) {
			node = node->children[el].get();
			index++;
		}
		else break;

	} while (index < path_components.size());

	if (index == path_components.size()) {
		node->function(request, response);
	}

	return 0;
}

int rest::filter::_register(std::unique_ptr<invocation_node> & root, const std::string & path, std::function<void(http_request, http_response)> handle) {
	const auto path_components = uri::split_path(utility::conversions::to_string_t(path));

	auto* node = root.get();
	for (const auto & path : path_components) {
		if (path == U("*")) {
			node->invoke = true; break;
		}
		if (node->children.find(path) == node->children.end()) {
			node->children[path] = std::make_unique<invocation_node>();
		}
		node = node->children[path].get();
	}
	node->function = handle;

	return 0;
}