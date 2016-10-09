#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include "variable_mgr.hpp"
#include "variable_handle.hpp"
#include "scope.hpp"
#include "tokenizer.hpp"
#include "function_handle.hpp"

class FunctionMgr;

namespace ast {
	class Node {
	public:
		virtual VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const = 0;
	};
	using NodePtr = std::shared_ptr<Node>;
	

	class VariableNode : public Node {
	public:
		VariableNode(const std::string& name) : name(name) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
		const std::string& getName() const { return name; }

	private:
		std::string name;
	};
	

	class NullNode : public Node {
	public:
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	};


	class IntNode : public Node {
	public:
		IntNode(int i) : i(i) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		int i;
	};


	class FloatNode : public Node {
	public:
		FloatNode(float f) : f(f) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		float f;
	};


	class InfNode : public Node {
	public:
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	};


	class BoolNode : public Node {
	public:
		BoolNode(bool b) : b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		bool b;
	};


	class StringNode : public Node {
	public:
		StringNode(const std::string& s) : s(s) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		std::string s;
	};


	class FuncCallNode : public Node {
	public:
		FuncCallNode(const std::string& name, const std::list<ast::NodePtr>& params, FunctionMgr& fmgr);
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		std::list<ast::NodePtr> nodeParams;
		FunctionHandle id;
	};
	

	class AssignNode : public Node {
	public:
		AssignNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};

	
	class AddNode : public Node {
	public:
		AddNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class SubNode : public Node {
	public:
		SubNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class MulNode : public Node {
	public:
		MulNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class DivNode : public Node {
	public:
		DivNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class ModNode : public Node {
	public:
		ModNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class NegNode : public Node {
	public:
		NegNode(const NodePtr& n) : n(n) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr n;
	};


	class NotNode : public Node {
	public:
		NotNode(const NodePtr& n) : n(n) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr n;
	};


	class EqualNode : public Node {
	public:
		EqualNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class NotEqualNode : public Node {
	public:
		NotEqualNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class LessNode : public Node {
	public:
		LessNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class GreaterNode : public Node {
	public:
		GreaterNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class AndNode : public Node {
	public:
		AndNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};


	class OrNode : public Node {
	public:
		OrNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		NodePtr a, b;
	};

	
	class BlockNode : public Node {
	public:
		BlockNode(const std::vector<ast::NodePtr>& b) : b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		std::vector<ast::NodePtr> b;
	};


	class IfNode : public Node {
	public:
		IfNode(const ast::NodePtr& mc, const ast::NodePtr& mb, const ast::NodePtr& eic, const ast::NodePtr& eib, const ast::NodePtr& eb) : mc(mc), mb(mb), eic(eic), eib(eib), eb(eb) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		ast::NodePtr mc, mb, eic, eib, eb;
	};


	class WhileNode : public Node {
	public:
		WhileNode(const ast::NodePtr& c, const ast::NodePtr& b) : c(c), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		ast::NodePtr c, b;
	};

	class ReturnNode : public Node {
	public:
		ReturnNode(const ast::NodePtr& r) : r(r) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	private:
		ast::NodePtr r;
	};

	class BreakNode : public Node {
	public:
		VariableHandle* eval(VariableMgr& mgr, Scope& scope, FunctionMgr& fmgr) const override;
	};
}

#endif
