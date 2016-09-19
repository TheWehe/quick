#include "variable_mgr.hpp"

#include <iostream>
#include <memory>
#include "variable_handle.hpp"


VariableHandle VariableMgr::createNull() {
	auto handle = create();
	handle.setType(DT_NULL);
	return handle;
}

VariableHandle VariableMgr::createPInf() {
	auto handle = create();
	handle.setType(DT_PINF);
	return handle;
}

VariableHandle VariableMgr::createNInf() {
	auto handle = create();
	handle.setType(DT_NINF);
	return handle;
}

VariableHandle VariableMgr::createInt(int i) {
	auto handle = create();
	handle.setType(DT_INT);
	dataSlots[handle.index].data = new int(i);
	return handle;
}

VariableHandle VariableMgr::createFloat(float f) {
	auto handle = create();
	handle.setType(DT_FLOAT);
	dataSlots[handle.index].data = new float(f);
	return handle;
}

VariableHandle VariableMgr::createBool(bool b) {
	auto handle = create();
	handle.setType(DT_BOOL);
	dataSlots[handle.index].data = new bool(b);
	return handle;
}

VariableHandle VariableMgr::createString(const std::string& s) {
	auto handle = create();
	handle.setType(DT_STRING);
	dataSlots[handle.index].data = new std::string(s);
	return handle;
}

VariableHandle VariableMgr::createString(std::string&& s) {
	auto handle = create();
	handle.setType(DT_STRING);
	dataSlots[handle.index].data = new std::string(std::move(s));
	return handle;
}

/*VariableHandle VariableMgr::createArray(const std::vector<VariableHandle>& a) {
	auto handle = create();
	handle.setType(DT_ARRAY);
	dataSlots[handle.index].data = new std::vector<VariableHandle>(a);
	return handle;
}

VariableHandle VariableMgr::createArray(std::vector<VariableHandle>&& a) {
	auto handle = create();
	handle.setType(DT_ARRAY);
	dataSlots[handle.index].data = new std::vector<VariableHandle>(std::move(a));
	return handle;
}*/

VariableHandle VariableMgr::create() {
	int index;
	
	if(freeSlots.empty()) {
		dataSlots.push_back(VariableData());
		index = dataSlots.size() - 1;
	}
	else {
		index = freeSlots.top();
		freeSlots.pop();
	}
	
	return VariableHandle(this, index);
}

void VariableMgr::increaseRef(int index) {
	dataSlots[index].refCount++;
}

void VariableMgr::decreaseRef(int index) {
	dataSlots[index].refCount--;
	
	if(dataSlots[index].refCount == 0) {
		switch(dataSlots[index].type) {
		case DT_INT: delete static_cast<int*>(dataSlots[index].data); break;
		case DT_FLOAT: delete static_cast<float*>(dataSlots[index].data); break;
		case DT_BOOL: delete static_cast<bool*>(dataSlots[index].data); break;
		case DT_STRING: delete static_cast<std::string*>(dataSlots[index].data); break;
		//case DT_ARRAY: delete static_cast<std::vector<VariableHandle>*>(dataSlots[index].data); break;
		default: break;
		}
		
		dataSlots[index].type = DT_NULL;
		dataSlots[index].data = nullptr;
		freeSlots.push(index);
	}
}
