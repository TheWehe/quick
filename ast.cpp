#include "ast.hpp"


std::string boolToString(bool b)
{
	if(b == true) return "true";
	else return "false";
}

namespace ast {
	VariableHandle VariableNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto h = scope.find(name);
		if(h.isValid()) return h;
		
		h = mgr.createNull();
		scope.add(name, h);
		return h;
	}
	
	VariableHandle PrimitiveNode::eval(VariableMgr& mgr, Scope& scope) const {
		switch(token.type) {
		case TT_NULL: return mgr.createNull();
		case TT_PINF: return mgr.createPInf();
		case TT_NINF: return mgr.createNInf();
		case TT_INT: return mgr.createInt(token.i);
		case TT_FLOAT: return mgr.createFloat(token.f);
		case TT_BOOL: return mgr.createBool(token.b);
		case TT_STRING: return mgr.createString(token.s);
		default: return VariableHandle();
		}
	}
	
	VariableHandle AssignNode::eval(VariableMgr& mgr, Scope& scope) const {
		return VariableHandle();
	}
	
	VariableHandle AddNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto ah = a->eval(mgr, scope);
		auto bh = b->eval(mgr, scope);
		
		if(ah.getType() == DT_NULL) {
			if(bh.getType() == DT_STRING) {
				return mgr.createString("null" + bh.asString());
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_PINF) {
			if(bh.getType() == DT_INT) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_FLOAT) {
				return mgr.createPInf();
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_NINF) {
			if(bh.getType() == DT_INT) {
				return mgr.createNInf();
			}
			if(bh.getType() == DT_FLOAT) {
				return mgr.createNInf();
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_INT) {
			if(bh.getType() == DT_PINF) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_NINF) {
				return mgr.createNInf();
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asInt() + bh.asInt();
				return mgr.createInt(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = static_cast<float>(ah.asInt()) + bh.asFloat();
				return mgr.createFloat(r);
			}
			if(bh.getType() == DT_STRING) {
				auto r = std::to_string(ah.asInt()) + bh.asString();
				return mgr.createString(r);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_FLOAT) {
			if(bh.getType() == DT_PINF) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_NINF) {
				return mgr.createNInf();
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asFloat() + static_cast<float>(bh.asInt());
				return mgr.createFloat(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = ah.asFloat() + bh.asFloat();
				return mgr.createFloat(r);
			}
			if(bh.getType() == DT_STRING) {
				auto r = std::to_string(ah.asFloat()) + bh.asString();
				return mgr.createString(r);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_BOOL) {
			if(bh.getType() == DT_STRING) {
				auto r = boolToString(ah.asBool()) + bh.asString();
				return mgr.createString(r);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_STRING) {
			if(bh.getType() == DT_NULL) {
				auto r = ah.asString() + "null";
				return mgr.createString(r);
			}
			if(bh.getType() == DT_PINF) {
				auto r = ah.asString() + "pinf";
				return mgr.createString(r);
			}
			if(bh.getType() == DT_NINF) {
				auto r = ah.asString() + "ninf";
				return mgr.createString(r);
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asString() + std::to_string(bh.asInt());
				return mgr.createString(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = ah.asString() + std::to_string(bh.asFloat());
				return mgr.createString(r);
			}
			if(bh.getType() == DT_BOOL) {
				auto r = ah.asString() + boolToString(bh.asBool());
				return mgr.createString(r);
			}
			if(bh.getType() == DT_STRING) {
				auto r = ah.asString() + bh.asString();
				return mgr.createString(r);
			}
			
			return mgr.createNull();
		}
		
		return mgr.createNull();
	}
	
	VariableHandle SubNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto ah = a->eval(mgr, scope);
		auto bh = b->eval(mgr, scope);
		
		if(ah.getType() == DT_PINF) {
			if(bh.getType() == DT_INT) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_FLOAT) {
				return mgr.createPInf();
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_NINF) {
			if(bh.getType() == DT_INT) {
				return mgr.createNInf();
			}
			if(bh.getType() == DT_FLOAT) {
				return mgr.createNInf();
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_INT) {
			if(bh.getType() == DT_PINF) {
				return mgr.createNInf();
			}
			if(bh.getType() == DT_NINF) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asInt() - bh.asInt();
				return mgr.createInt(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = static_cast<float>(ah.asInt()) - bh.asFloat();
				return mgr.createFloat(r);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_FLOAT) {
			if(bh.getType() == DT_NINF) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_NINF) {
				return mgr.createPInf();
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asFloat() - static_cast<float>(bh.asInt());
				return mgr.createFloat(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = ah.asFloat() +- bh.asFloat();
				return mgr.createFloat(r);
			}
			
			return mgr.createNull();
		}
		
		return mgr.createNull();
	}
	
	VariableHandle MulNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto ah = a->eval(mgr, scope);
		auto bh = b->eval(mgr, scope);
		
		if(ah.getType() == DT_PINF) {
			if(bh.getType() == DT_INT) {
				if(ah.asFloat() > 0) return mgr.createPInf();
				if(ah.asFloat() < 0) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if(bh.getType() == DT_FLOAT) {
				if(ah.asFloat() > 0.f) return mgr.createPInf();
				if(ah.asFloat() < 0.f) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_NINF) {
			if(bh.getType() == DT_INT) {
				if(ah.asFloat() > 0) return mgr.createNInf();
				if(ah.asFloat() < 0) return mgr.createPInf();
				else return mgr.createInt(0);
			}
			if(bh.getType() == DT_FLOAT) {
				if(ah.asFloat() > 0.f) return mgr.createNInf();
				if(ah.asFloat() < 0.f) return mgr.createPInf();
				else return mgr.createInt(0);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_INT) {
			if(bh.getType() == DT_PINF) {
				if(ah.asFloat() > 0) return mgr.createPInf();
				if(ah.asFloat() < 0) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if(bh.getType() == DT_NINF) {
				if(ah.asFloat() > 0) return mgr.createNInf();
				if(ah.asFloat() < 0) return mgr.createPInf();
				else return mgr.createInt(0);
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asInt() * bh.asInt();
				return mgr.createInt(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = static_cast<float>(ah.asInt()) * bh.asFloat();
				return mgr.createFloat(r);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_FLOAT) {
			if(bh.getType() == DT_PINF) {
				if(ah.asFloat() > 0.f) return mgr.createPInf();
				if(ah.asFloat() < 0.f) return mgr.createNInf();
				else return mgr.createInt(0);
			}
			if(bh.getType() == DT_NINF) {
				if(ah.asFloat() > 0.f) return mgr.createNInf();
				if(ah.asFloat() < 0.f) return mgr.createPInf();
				else return mgr.createInt(0);
			}
			if(bh.getType() == DT_INT) {
				auto r = ah.asFloat() * static_cast<float>(bh.asInt());
				return mgr.createFloat(r);
			}
			if(bh.getType() == DT_FLOAT) {
				auto r = ah.asFloat() * bh.asFloat();
				return mgr.createFloat(r);
			}
			
			return mgr.createNull();
		}
		
		return mgr.createNull();
	}
	
	VariableHandle DivNode::eval(VariableMgr& mgr, Scope& scope) const {
		auto ah = a->eval(mgr, scope);
		auto bh = b->eval(mgr, scope);
		
		if(ah.getType() == DT_PINF) {
			if(bh.getType() == DT_INT) {
				if(ah.asInt() > 0) return mgr.createNInf();
				if(ah.asInt() < 0) return mgr.createPInf();
				else return mgr.createPInf();
			}
			if(bh.getType() == DT_FLOAT) {
				if(ah.asFloat() > 0.f) return mgr.createNInf();
				if(ah.asFloat() < 0.f) return mgr.createPInf();
				else return mgr.createPInf();
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_NINF) {
			if(bh.getType() == DT_INT) {
				if(ah.asFloat() > 0) return mgr.createPInf();
				if(ah.asFloat() < 0) return mgr.createNInf();
				else return mgr.createNInf();
			}
			if(bh.getType() == DT_FLOAT) {
				if(ah.asFloat() > 0.f) return mgr.createPInf();
				if(ah.asFloat() < 0.f) return mgr.createNInf();
				else return mgr.createNInf();
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_INT) {
			if(bh.getType() == DT_PINF) {
				return mgr.createInt(0);
			}
			if(bh.getType() == DT_NINF) {
				return mgr.createInt(0);
			}
			if(bh.getType() == DT_INT) {
				if(bh.asInt() == 0) {
					if(ah.asInt() > 0) return mgr.createPInf();
					else if(ah.asInt() < 0) return mgr.createPInf();
					else return mgr.createNull();
				}
				
				auto r = ah.asInt() / bh.asInt();
				return mgr.createInt(r);
			}
			if(bh.getType() == DT_FLOAT) {
				if(bh.asFloat() == 0) {
					if(ah.asInt() > 0) return mgr.createPInf();
					else if(ah.asInt() < 0) return mgr.createPInf();
					else return mgr.createNull();
				}
				
				auto r = static_cast<float>(ah.asInt()) / bh.asFloat();
				return mgr.createFloat(r);
			}
			
			return mgr.createNull();
		}
		if(ah.getType() == DT_FLOAT) {
			if(bh.getType() == DT_PINF) {
				return mgr.createInt(0);
			}
			if(bh.getType() == DT_NINF) {
				return mgr.createInt(0);
			}
			if(bh.getType() == DT_INT) {
				if(bh.asInt() == 0) {
					if(ah.asFloat() > 0.f) return mgr.createPInf();
					else if(ah.asFloat() < 0.f) return mgr.createPInf();
					else return mgr.createNull();
				}
				
				auto r = ah.asFloat() / static_cast<float>(bh.asInt());
				return mgr.createFloat(r);
			}
			if(bh.getType() == DT_FLOAT) {
				if(bh.asInt() == 0) {
					if(ah.asFloat() > 0.f) return mgr.createPInf();
					else if(ah.asFloat() < 0.f) return mgr.createPInf();
					else return mgr.createNull();
				}
				
				auto r = ah.asFloat() / bh.asFloat();
				return mgr.createFloat(r);
			}
			
			return mgr.createNull();
		}
		
		return mgr.createNull();
	} 
}
