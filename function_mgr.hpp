#ifndef FUNCTION_MGR_HPP
#define FUNCTION_MGR_HPP

#include <string>
#include <vector>
#include <functional>
#include "variable_handle.hpp"
#include "ast.hpp"
#include "function_handle.hpp"

using ParamList = std::vector<VariableHandle*>;

struct CFunction {
	std::string name;
	std::function<VariableHandle*(VariableMgr&, const ParamList&)> callback;
};

struct ScriptFunction {
	std::string name;
	std::vector<std::string> params;
	ast::NodePtr exec;
};

class FunctionMgr {
public:
	void addCFunc(const CFunction& function);
	ScriptFunction* addScriptFunc(const ScriptFunction& function);
	FunctionHandle findFunc(const std::string& name);
	VariableHandle* call(VariableMgr& mgr, const FunctionHandle& h, const ParamList& params);

private:
	std::vector<CFunction> cFuncs;
	std::vector<ScriptFunction> scriptFuncs;
};

#endif
