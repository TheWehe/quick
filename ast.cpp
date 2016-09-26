#include "ast.hpp"

#include "op.hpp"


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


	VariableHandle* NullNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createNull();
	}


	VariableHandle* IntNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createInt(i);
	}


	VariableHandle* FloatNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createFloat(f);
	}


	VariableHandle* InfNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createPInf();
	}


	VariableHandle* BoolNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createBool(b);
	}


	VariableHandle* StringNode::eval(VariableMgr& mgr, Scope& scope) const {
		return mgr.createString(s);
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

		auto h = op::add(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* SubNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::subtract(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* MulNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::multiply(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* DivNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::divide(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* ModNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::modulo(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* NegNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = n->eval(mgr, scope);

		auto h = op::negate(mgr, h1);

		mgr.destroy(h1);

		return h;
	}


	VariableHandle* EqualNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::equal(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* NotEqualNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::notEqual(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* LessNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::less(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* GreaterNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::greater(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* AndNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::and(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* OrNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h1 = a->eval(mgr, scope);
		auto h2 = b->eval(mgr, scope);

		auto h = op::or(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}
}
