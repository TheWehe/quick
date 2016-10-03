#ifndef FUNCTION_MGR_HPP
#define FUNCTION_MGR_HPP

#include <string>
#include <vector>
#include <functional>
#include "variable_handle.hpp"
#include "ast.hpp"

using ParamList = std::vector<VariableHandle*>;

struct CFunction {
	std::string name;
	std::function<VariableHandle*(VariableMgr&, const ParamList&)> callback;
};

class FunctionMgr {
public:
	void addCFunc(const CFunction& function);
	int findFunc(const std::string& name);
	VariableHandle* call(VariableMgr& mgr, int id, const ParamList& params);

private:
	std::vector<CFunction> cFuncs;
};

#endif
