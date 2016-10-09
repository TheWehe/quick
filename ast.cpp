#include "ast.hpp"

#include "op.hpp"
#include "function_mgr.hpp"
#include "interrupters.hpp"
#include <cassert>


namespace ast {
	VariableHandle* VariableNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h = scope.find(name);
		if (h != nullptr) {
			return h;
		}
		else {
			scope.add(name, mgr.createNull());
			return scope.find(name);
		}
	}


	VariableHandle* NullNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		return mgr.createNull();
	}


	VariableHandle* IntNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		return mgr.createInt(i);
	}


	VariableHandle* FloatNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		return mgr.createFloat(f);
	}


	VariableHandle* InfNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		return mgr.createPInf();
	}


	VariableHandle* BoolNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		return mgr.createBool(b);
	}


	VariableHandle* StringNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		return mgr.createString(s);
	}


	FuncCallNode::FuncCallNode(const std::string& name, const std::list<ast::NodePtr>& params, FunctionMgr& fmgr)
	: nodeParams(params) {
		id = fmgr.findFunc(name);
	}
	VariableHandle* FuncCallNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		ParamList pl;
		for (auto& p : nodeParams) {
			pl.push_back(p->eval(mgr, scope, fmgr));
		}
		
		auto h = fmgr.call(mgr, id, pl);

		for (auto& p : pl) mgr.destroy(p);

		return h;
	}


	VariableHandle* AssignNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		h1->assign(h2);

		auto r =  mgr.createRef(h1);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return r;
	}


	VariableHandle* AddNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::add(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* SubNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::subtract(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* MulNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::multiply(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* DivNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::divide(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* ModNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::modulo(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* NegNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = n->eval(mgr, scope, fmgr);

		auto h = op::negate(mgr, h1);

		mgr.destroy(h1);

		return h;
	}


	VariableHandle* NotNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = n->eval(mgr, scope, fmgr);

		auto h = op::not(mgr, h1);

		mgr.destroy(h1);

		return h;
	}


	VariableHandle* EqualNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::equal(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* NotEqualNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::notEqual(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* LessNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::less(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* GreaterNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::greater(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* AndNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::and(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* OrNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto h1 = a->eval(mgr, scope, fmgr);
		auto h2 = b->eval(mgr, scope, fmgr);

		auto h = op::or(mgr, h1, h2);

		mgr.destroy(h1);
		mgr.destroy(h2);

		return h;
	}


	VariableHandle* BlockNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		Scope child(mgr, &scope);
		
		for (auto& x : b) {
			mgr.destroy(x->eval(mgr, child, fmgr));
		}

		return nullptr;
	}


	VariableHandle* IfNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		auto exec = mc->eval(mgr, scope, fmgr);
		assert(exec->getType() == DT_BOOL);

		if (exec->asBool()) {
			Scope child(mgr, &scope);
			mgr.destroy(mb->eval(mgr, child, fmgr));
			mgr.destroy(exec);
			return nullptr;
		}
		if (eic != nullptr) {
			exec = eic->eval(mgr, scope, fmgr);
			assert(exec->getType() == DT_BOOL);

			if (exec->asBool()) {
				Scope child(mgr, &scope);
				mgr.destroy(eib->eval(mgr, child, fmgr));
				mgr.destroy(exec);
				return nullptr;
			}
		}
		if (eb != nullptr) {
			Scope child(mgr, &scope);
			mgr.destroy(eb->eval(mgr, child, fmgr));
		}

		mgr.destroy(exec);
		return nullptr;
	}


	VariableHandle* WhileNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		while (true) {
			auto exec = c->eval(mgr, scope, fmgr);
			assert(exec->getType() == DT_BOOL);

			auto r = exec->asBool();
			mgr.destroy(exec);
			if (!r) break;

			try {
				Scope child(mgr, &scope);
				mgr.destroy(b->eval(mgr, child, fmgr));
			}
			catch (const std::exception& e) {
				if(e.what() == "br") break;
				else throw e;
			}
		}

		return nullptr;
	}

	VariableHandle* ReturnNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		throw ReturnInterruption(r);
	}

	VariableHandle* BreakNode::eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const {
		throw BreakInterruption();
	}
}
