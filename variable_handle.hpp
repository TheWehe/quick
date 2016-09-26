#ifndef VARIABLE_HANDLE_HPP
#define VARIABLE_HANDLE_HPP

#include "variable_mgr.hpp"

class VariableHandle {
	friend class VariableMgr;
	
public:
	VariableHandle() = default;
	VariableHandle(const VariableHandle& rhs) = delete;
	VariableHandle& operator=(const VariableHandle& rhs) = delete;
	VariableHandle(VariableHandle&& rhs)
		: owner(rhs.owner), index(rhs.index) { rhs.owner = nullptr; rhs.index = -1; }
	VariableHandle& operator=(VariableHandle&& rhs)
		{ owner = rhs.owner; index = rhs.index; rhs.owner = nullptr; rhs.index = -1; return *this; }
	
	bool isValid() const { return index != -1 && owner != nullptr; }
	VariableMgr* getOwner() const { return owner; }
	
	void assign(VariableHandle* h) { owner->assign(this, h); }
	DataType getType() { return owner->getType(this); }
	int& asInt() { return owner->asInt(this); }
	float& asFloat() { return owner->asFloat(this); }
	bool& asBool() { return owner->asBool(this); }
	std::string& asString() { return owner->asString(this); }


private:
	VariableHandle(VariableMgr* owner, int index) : owner(owner), index(index) {}

	VariableMgr* owner = nullptr;
	int index = -1;
};

#endif
