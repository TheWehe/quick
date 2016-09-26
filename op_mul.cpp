#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* multiply(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createInt(a->asInt() * b->asInt());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* divide(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				if (b->asInt() == 0) {
					if (a->asInt() > 0) {
						return mgr.createPInf();
					}
					else if (a->asInt() < 0) {
						return mgr.createNInf();
					}
					else {
						return mgr.createNull();
					}
				}

				return mgr.createInt(a->asInt() / b->asInt());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* modulo(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createInt(a->asInt() % b->asInt());
			}
		}

		return mgr.createNull();
	}
}
