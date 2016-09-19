#ifndef VARIABLE_HANDLE_HPP
#define VARIABLE_HANDLE_HPP

#include "variable_mgr.hpp"

class VariableHandle {
	friend class VariableMgr;
	
public:
	VariableHandle() = default;
	VariableHandle(const VariableHandle& rhs) 
		: owner(rhs.owner), index(rhs.index) { if(index != -1) owner->increaseRef(index); }
	VariableHandle(VariableHandle&& rhs)
		: owner(rhs.owner), index(rhs.index) { rhs.owner = nullptr; rhs.index = -1; }
	~VariableHandle() { if(index != -1) owner->decreaseRef(index); }
	VariableHandle& operator=(const VariableHandle& rhs)
		{ owner = rhs.owner; index = rhs.index; if(index != -1) owner->decreaseRef(index); return *this; }
	VariableHandle& operator=(VariableHandle&& rhs)
		{ owner = rhs.owner; index = rhs.index; rhs.owner = nullptr; rhs.index = -1; return *this; }
	
	bool isValid() const { return index != -1; }
	void setType(DataType type) { owner->dataSlots[index].type = type; }
	DataType getType() const { return owner->dataSlots[index].type; }
	int& asInt() { return *static_cast<int*>(owner->dataSlots[index].data); }
	float& asFloat() { return *static_cast<float*>(owner->dataSlots[index].data); }
	bool& asBool() { return *static_cast<bool*>(owner->dataSlots[index].data); }
	std::string& asString() { return *static_cast<std::string*>(owner->dataSlots[index].data); }
	std::vector<VariableHandle>& asArray()
		{ return *static_cast<std::vector<VariableHandle>*>(owner->dataSlots[index].data); }
	
private:
	VariableHandle(VariableMgr* owner, int index)
		: owner(owner), index(index) { if(index != -1) owner->increaseRef(index); }
	
	VariableMgr* owner = nullptr;
	int index = -1;
};

#endif
