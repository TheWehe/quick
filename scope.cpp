#include "scope.hpp"

#include <iostream> // temp


VariableHandle Scope::find(const std::string& name) const {
	auto found = namedVars.find(name);
	
	if(found != namedVars.end()) {
		std::cout << "a"; // temp
		return found->second;
	}
	else if(parent != nullptr) {
		return parent->find(name);
	}
	
	return VariableHandle();
}

void Scope::add(const std::string& name, VariableHandle var) {
	namedVars.insert(std::pair<std::string, VariableHandle>(name, var));
}
