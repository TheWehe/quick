#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* negate(VariableMgr& mgr, VariableHandle* h) {
		assert(h != nullptr);

		if (h->getType() == DT_INT) {
			return mgr.createInt(-h->asInt());
		}
		if (h->getType() == DT_FLOAT) {
			return mgr.createFloat(-h->asFloat());
		}
		if (h->getType() == DT_PINF) {
			return mgr.createNInf();
		}
		if (h->getType() == DT_NINF) {
			return mgr.createPInf();
		}

		return mgr.createNull();
	}

	VariableHandle * not(VariableMgr& mgr, VariableHandle* h) {
		assert(h != nullptr);

		if (h->getType() == DT_BOOL) {
			return mgr.createBool(!h->asBool());
		}

		return mgr.createNull();
	}
}
