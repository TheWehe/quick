#include "function_mgr.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>


void FunctionMgr::addCFunc(const CFunction& function) {
	cFuncs.push_back(function);
}

int FunctionMgr::findFunc(const std::string& name) {
	for (unsigned i = 0; i < cFuncs.size(); i++) {
		if (cFuncs[i].name == name) return i;
	}

	return -1;
}

VariableHandle* FunctionMgr::call(VariableMgr& mgr, int id, const ParamList& params) {
	assert(id >= 0 && id < cFuncs.size());

	return cFuncs[id].callback(mgr, params);
}
