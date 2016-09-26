#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* and(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		return mgr.createNull();
	}


	VariableHandle* or(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		return mgr.createNull();
	}
}
