#include "function_mgr.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>
#include "interrupters.hpp"


void FunctionMgr::addCFunc(const CFunction& function) {
	cFuncs.push_back(function);
}

ScriptFunction* FunctionMgr::addScriptFunc(const ScriptFunction& function) {
	scriptFuncs.push_back(function);
	return &scriptFuncs[scriptFuncs.size() - 1];
}

FunctionHandle FunctionMgr::findFunc(const std::string& name) {
	FunctionHandle h;
	h.a = -1;
	h.b = -1;

	for (unsigned i = 0; i < cFuncs.size(); i++) {
		if (cFuncs[i].name == name) {
			h.a = 0;
			h.b = i;
		}
	}

	if (h.a == -1) {
		for (unsigned i = 0; i < scriptFuncs.size(); i++) {
			if (scriptFuncs[i].name == name) {
				h.a = 1;
				h.b = i;
			}
		}
	}

	return h;
}

VariableHandle* FunctionMgr::call(VariableMgr& mgr, const FunctionHandle& h, const ParamList& params) {
	if (h.a == 0) {
		return cFuncs[h.b].callback(mgr, params);
	}
	else if (h.a == 1) {
		Scope scope(mgr, nullptr);
		for (unsigned i = 0; i < scriptFuncs[h.b].params.size(); i++) {
			scope.add(scriptFuncs[h.b].params[i], mgr.createCopy(params[i]));
		}

		try {
			mgr.destroy(scriptFuncs[h.b].exec->eval(mgr, scope, *this));
		}
		catch (const std::exception& e) {
			if (e.what() == "ret") {
				auto ret = *static_cast<const ReturnInterruption*>(&e);
				return ret.getRet()->eval(mgr, scope, *this);
			}
			else {
				throw e;
			}
		}

		return mgr.createNull();
	}

	return nullptr;
}
