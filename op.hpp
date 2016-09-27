#ifndef OP_HPP
#define OP_HPP

#include "variable_mgr.hpp"
#include "variable_handle.hpp"

namespace op {
	VariableHandle* add(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* subtract(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* multiply(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* divide(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* modulo(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* negate(VariableMgr& mgr, VariableHandle* h);
	VariableHandle* equal(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* notEqual(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* less(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* greater(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* and(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
	VariableHandle* or(VariableMgr& mgr, VariableHandle* a, VariableHandle* b);
}

#endif
