#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* add(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createInt(a->asInt() + b->asInt());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* subtract(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createInt(a->asInt() - b->asInt());
			}
		}

		return mgr.createNull();
	}
}
