#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "variable_handle.hpp"
#include <map>

class Scope {
public:
	Scope(VariableMgr& mgr, Scope* parent) :mgr(mgr), parent(parent) {}
	~Scope();

	void add(const std::string& name, VariableHandle* h);
	VariableHandle* find(const std::string& name);
	void destroy(const std::string& name);

private:
	VariableMgr& mgr;
	Scope* parent;
	std::map<std::string, VariableHandle*> namedVars;
};

#endif
