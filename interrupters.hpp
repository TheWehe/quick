#ifndef INTERRPUTERS_HPP
#define INTERRUPTERS_HPP

#include <exception>
#include "ast.hpp"

class ReturnInterruption : public std::exception {
public:
	ReturnInterruption(const ast::NodePtr& ret) : ret(ret) {}

	const ast::NodePtr& getRet() const { return ret; }

private:
	ast::NodePtr ret;
};

#endif
