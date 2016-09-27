#include "op.hpp"

#include <cassert>


namespace op {
	VariableHandle* add(VariableMgr& mgr, VariableHandle* a, VariableHandle* b) {
		assert(a != nullptr);
		assert(b != nullptr);

		if (a->getType() == DT_NULL) {
			if (b->getType() == DT_STRING) {
				return mgr.createString("null" + b->asString());
			}
		}
		if (a->getType() == DT_INT) {
			if (b->getType() == DT_INT) {
				return mgr.createInt(a->asInt() + b->asInt());
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createFloat(static_cast<float>(a->asInt()) + b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_STRING) {
				return mgr.createString(std::to_string(a->asInt()) + b->asString());
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createFloat(a->asFloat() + static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createFloat(a->asFloat() + b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_STRING) {
				return mgr.createString(std::to_string(a->asFloat()) + b->asString());
			}
		}
		if (a->getType() == DT_BOOL) {
			if (b->getType() == DT_STRING) {
				if (a->asBool()) return mgr.createString("true" + b->asString());
				else mgr.createString("false" + b->asString());
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_PINF) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_STRING) {
				return mgr.createString("inf" + b->asString());
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_STRING) {
				return mgr.createString("-inf" + b->asString());
			}
		}
		if (a->getType() == DT_STRING) {
			if (b->getType() == DT_NULL) {
				return mgr.createString(a->asString() + "null");
			}
			if (b->getType() == DT_INT) {
				return mgr.createString(a->asString() + std::to_string(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createString(a->asString() + std::to_string(b->asFloat()));
			}
			if (b->getType() == DT_BOOL) {
				if (b->asBool()) return mgr.createString(a->asString() + "true");
				else mgr.createString(a->asString() + "false");
			}
			if (b->getType() == DT_PINF) {
				return mgr.createString(a->asString() + "inf");
			}
			if (b->getType() == DT_NINF) {
				return mgr.createString(a->asString() + "-inf");
			}
			if (b->getType() == DT_STRING) {
				return mgr.createString(a->asString() + b->asString());
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
			if (b->getType() == DT_FLOAT) {
				return mgr.createFloat(static_cast<float>(a->asInt()) - b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createPInf();
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createFloat(a->asFloat() - static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createFloat(a->asFloat() - b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createPInf();
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createPInf();
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_PINF) {
				return mgr.createNInf();
			}
		}
		
		return mgr.createNull();
	}
}
