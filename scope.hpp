#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <string>
#include <map>
#include "variable_handle.hpp"

class Scope {
public:
	Scope(Scope* parent) : parent(parent) {}
	Scope(const Scope& rhs) = delete;
	Scope(Scope&& rhs) = delete;
	Scope& operator=(const Scope& rhs) = delete;
	Scope& operator=(Scope&& rhs) = delete;
	
	VariableHandle find(const std::string& name) const;
	void add(const std::string& name, VariableHandle var);
	Scope* getParent() const { return parent; }
	
private:
	Scope* parent = nullptr;
	std::map<std::string, VariableHandle> namedVars;
};

#endif
