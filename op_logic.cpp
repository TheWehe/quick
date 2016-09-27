#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* and(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_BOOL) {
			if (b->getType() == DT_BOOL) {
				return mgr.createBool(a->asBool() && b->asBool());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* or(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_BOOL) {
			if (b->getType() == DT_BOOL) {
				return mgr.createBool(a->asBool() || b->asBool());
			}
		}

		return mgr.createNull();
	}
}
