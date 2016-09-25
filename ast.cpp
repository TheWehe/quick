#include "ast.hpp"

#include <cassert>


namespace ast {
	VariableHandle* VariableNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h = scope.find(name);
		if (h != nullptr) {
			return mgr.createRef(h);
		}
		else {
			scope.add(name, mgr.createNull());
			return mgr.createRef(scope.find(name));
		}
	}

	VariableHandle* IntNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createInt(i);
	}

	VariableHandle* AssignNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		h1->assign(h2);

		mgr.destroy(h2);

		return mgr.createRef(h1);
	}

	VariableHandle* AddNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		VariableHandle* h = nullptr;

		if (h1->getType() == DT_INT) {
			if (h2->getType() == DT_INT) {
				h = mgr.createInt(h1->asInt() + h2->asInt());
			}
		}

		mgr.destroy(h1);
		mgr.destroy(h2);

		if (h == nullptr) h = mgr.createNull();

		return h;
	}
}
