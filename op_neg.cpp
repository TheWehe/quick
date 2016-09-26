#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* negate(VariableMgr& mgr, VariableHandle* h) {
		assert(h != nullptr);

		if (h->getType() == DT_INT) {
			return mgr.createInt(-h->asInt());
		}

		return mgr.createNull();
	}
}
