#include "scope.hpp"


Scope::~Scope() {
	for (auto& x : namedVars) {
		mgr.destroy(x.second);
	}
}

void Scope::add(const std::string& name, VariableHandle* h) {
	namedVars.insert(std::pair<std::string, VariableHandle*>(name, h));
}

VariableHandle* Scope::find(const std::string& name) {
	auto found = namedVars.find(name);

	if (found == namedVars.end()) {
		if (parent != nullptr) {
			return parent->find(name);
		}
	}
	else {
		return mgr.createRef(found->second);
	}

	return nullptr;
}

void Scope::destroy(const std::string& name) {
	auto found = namedVars.find(name);

	if (found != namedVars.end()) {
		mgr.destroy(found->second);
	}
}
