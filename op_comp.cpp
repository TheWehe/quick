#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* equal(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asInt() == b->asInt());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* notEqual(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asInt() != b->asInt());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* not(VariableMgr& mgr, VariableHandle* h) {
		assert(h != nullptr);

		return mgr.createNull();
	}


	VariableHandle* less(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asInt() < b->asInt());
			}
		}

		return mgr.createNull();
	}


	VariableHandle* greater(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asInt() > b->asInt());
			}
		}

		return mgr.createNull();
	}
}
