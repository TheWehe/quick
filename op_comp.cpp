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
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(static_cast<float>(a->asInt()) == b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(false);
			}
		}                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asFloat() == static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(a->asFloat() == b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(false);
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(false);
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(false);
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
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(static_cast<float>(a->asInt()) != b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(true);
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asFloat() != static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(a->asFloat() != b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(true);
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(true);
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(true);
			}
		}

		return mgr.createNull();
	}


	VariableHandle* less(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asInt() < b->asInt());
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(static_cast<float>(a->asInt()) < b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_NINF) {
				return mgr.createBool(false);
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asFloat() < static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(a->asFloat() < b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_NINF) {
				return mgr.createBool(false);
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(false);
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(true);
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
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(static_cast<float>(a->asInt()) > b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_NINF) {
				return mgr.createBool(true);
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(a->asFloat() > static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(a->asFloat() > b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_NINF) {
				return mgr.createBool(true);
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(true);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(true);
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				return mgr.createBool(false);
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createBool(false);
			}
		}

		return mgr.createNull();
	}
}
