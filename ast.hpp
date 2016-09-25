#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include "variable_mgr.hpp"
#include "variable_handle.hpp"
#include "scope.hpp"
#include "tokenizer.hpp"

namespace ast {
	class Node {
	public:
		virtual VariableHandle* eval(VariableMgr& mgr, Scope& scope) const = 0;
	};
	
	using NodePtr = std::shared_ptr<Node>;
	

	class VariableNode : public Node {
	public:
		VariableNode(const std::string& name) : name(name) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope) const override;
		const std::string& getName() const { return name; }
		
	private:
		std::string name;
	};
	

	class IntNode : public Node {
	public:
		IntNode(int i) : i(i) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope) const override;
	
	private:
		int i;
	};
	

	class AssignNode : public Node {
	public:
		AssignNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope) const override;
		
	private:
		NodePtr a, b;
	};

	
	class AddNode : public Node {
	public:
		AddNode(const NodePtr& a, const NodePtr& b) : a(a), b(b) {}
		VariableHandle* eval(VariableMgr& mgr, Scope& scope) const override;
		
	private:
		NodePtr a, b;
	};
}

#endif
