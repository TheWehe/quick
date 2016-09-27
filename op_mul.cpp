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
			if (b->getType() == DT_FLOAT) {
				return mgr.createFloat(static_cast<float>(a->asInt()) * b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				if (a->asInt() > 0) return mgr.createPInf();
				else if (a->asInt() < 0) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if (b->getType() == DT_NINF) {
				if (a->asInt() > 0) return mgr.createNInf();
				else if (a->asInt() < 0) return mgr.createPInf();
				else return mgr.createInt(0);
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				return mgr.createFloat(a->asFloat() * static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				return mgr.createFloat(a->asFloat() * b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				if (a->asFloat() > 0.f) return mgr.createPInf();
				else if (a->asFloat() < 0.f) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if (b->getType() == DT_NINF) {
				if (a->asFloat() > 0.f) return mgr.createNInf();
				else if (a->asFloat() < 0.f) return mgr.createPInf();
				else return mgr.createInt(0);
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				if (b->asInt() > 0) return mgr.createPInf();
				else if (b->asInt() < 0) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if (b->getType() == DT_FLOAT) {
				if (b->asFloat() > 0.f) return mgr.createPInf();
				else if (b->asFloat() < 0.f) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if (b->getType() == DT_PINF) {
				return mgr.createPInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createNInf();
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				if (b->asInt() > 0) return mgr.createNInf();
				else if (b->asInt() < 0) return mgr.createPInf();
				else return mgr.createInt(0);
			}
			if (b->getType() == DT_FLOAT) {
				if (b->asFloat() > 0.f) return mgr.createNInf();
				else if (b->asFloat() < 0.f) return mgr.createPInf();
				else return mgr.createInt(0);
			}
			if (b->getType() == DT_PINF) {
				return mgr.createNInf();
			}
			if (b->getType() == DT_NINF) {
				return mgr.createPInf();
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
					if (a->asInt() > 0) return mgr.createPInf();
					else if (a->asInt() < 0) return mgr.createNInf();
					else return mgr.createNull();
				}

				return mgr.createInt(a->asInt() / b->asInt());
			}
			if (b->getType() == DT_FLOAT) {
				if (b->asFloat() == 0.f) {
					if (a->asInt() > 0) return mgr.createPInf();
					else if (a->asInt() < 0) return mgr.createNInf();
					else return mgr.createNull();
				}

				return mgr.createFloat(static_cast<float>(a->asInt()) / b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createInt(0);
			}
			if (b->getType() == DT_NINF) {
				return mgr.createInt(0);
			}
		}
		if (a->getType() == DT_FLOAT) {
			if (b->getType() == DT_INT) {
				if (b->asInt() == 0) {
					if (a->asFloat() > 0.f) return mgr.createPInf();
					else if (a->asFloat() < 0.f) return mgr.createNInf();
					else return mgr.createNull();
				}

				return mgr.createFloat(a->asFloat() / static_cast<float>(b->asInt()));
			}
			if (b->getType() == DT_FLOAT) {
				if (b->asFloat() == 0.f) {
					if (a->asFloat() > 0.f) return mgr.createPInf();
					else if (a->asFloat() < 0.f) return mgr.createNInf();
					else return mgr.createNull();
				}

				return mgr.createFloat(a->asFloat() / b->asFloat());
			}
			if (b->getType() == DT_PINF) {
				return mgr.createInt(0);
			}
			if (b->getType() == DT_NINF) {
				return mgr.createInt(0);
			}
		}
		if (a->getType() == DT_PINF) {
			if (b->getType() == DT_INT) {
				if (b->asInt() > 0) return mgr.createPInf();
				else if (b->asInt() < 0) return mgr.createNInf();
				else return mgr.createPInf();
			}
			if (b->getType() == DT_FLOAT) {
				if (b->asFloat() > 0.f) return mgr.createPInf();
				else if (b->asFloat() < 0.f) return mgr.createNInf();
				else return mgr.createPInf();
			}
		}
		if (a->getType() == DT_NINF) {
			if (b->getType() == DT_INT) {
				if (b->asInt() > 0) return mgr.createNInf();
				else if (b->asInt() < 0) return mgr.createPInf();
				else return mgr.createNInf();
			}
			if (b->getType() == DT_FLOAT) {
				if (b->asFloat() > 0.f) return mgr.createNInf();
				else if (b->asFloat() < 0.f) return mgr.createPInf();
				else return mgr.createNInf();
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
