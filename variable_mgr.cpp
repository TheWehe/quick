#include "variable_mgr.hpp"

#include "variable_handle.hpp"
#include <algorithm>


VariableMgr::~VariableMgr() {
	for (auto& x : dataSlots) {
		if (x.originalRef != nullptr) delete x.originalRef;
	}
}

VariableHandle* VariableMgr::createNull() {
	auto h = create();
	dataSlots[h->index].type = DT_NULL;

	return h;
}

VariableHandle* VariableMgr::createInt(int i) {
	auto h = create();
	dataSlots[h->index].type = DT_INT;
	dataSlots[h->index].data = new int(i);

	return h;
}

VariableHandle* VariableMgr::createFloat(float f) {
	auto h = create();
	dataSlots[h->index].type = DT_FLOAT;
	dataSlots[h->index].data = new float(f);

	return h;
}

VariableHandle* VariableMgr::createPInf() {
	auto h = create();
	dataSlots[h->index].type = DT_PINF;

	return h;
}

VariableHandle* VariableMgr::createNInf() {
	auto h = create();
	dataSlots[h->index].type = DT_NINF;

	return h;
}

VariableHandle* VariableMgr::createBool(bool b) {
	auto h = create();
	dataSlots[h->index].type = DT_BOOL;
	dataSlots[h->index].data = new bool(b);

	return h;
}

VariableHandle* VariableMgr::createString(const std::string& s) {
	auto h = create();
	dataSlots[h->index].type = DT_STRING;
	dataSlots[h->index].data = new std::string(s);

	return h;
}

VariableHandle* VariableMgr::createCopy(VariableHandle* target) {
	auto h = create();
	dataSlots[h->index].type = target->getType();

	switch (dataSlots[h->index].type) {
	case DT_INT: dataSlots[h->index].data = new int(target->asInt()); break;
	case DT_FLOAT: dataSlots[h->index].data = new float(target->asFloat()); break;
	case DT_BOOL: dataSlots[h->index].data = new bool(target->asBool()); break;
	case DT_STRING: dataSlots[h->index].data = new std::string(target->asString()); break;
	default: break;
	}

	return h;
}

VariableHandle* VariableMgr::createRef(VariableHandle* target) {
	auto h = create();
	dataSlots[h->index].type = DT_REF;

	if (dataSlots[target->index].type != DT_REF) {
		dataSlots[h->index].data = new int(target->index);
		addRef(target, h);
	}
	else {
		int targetIndex = *static_cast<int*>(dataSlots[target->index].data);
		dataSlots[h->index].data = new int(targetIndex);
		dataSlots[targetIndex].refs.push_back(h);
	}

	return h;
}

void VariableMgr::destroy(VariableHandle* h) {
	destroyRef(h, h);
}

VariableHandle* VariableMgr::create() {
	int index;

	if (freeSlots.empty()) {
		dataSlots.push_back(VariableData());
		index = dataSlots.size() - 1;
	}
	else {
		index = freeSlots.top();
		freeSlots.pop();
	}

	dataSlots[index].originalRef = new VariableHandle();
	dataSlots[index].originalRef->owner = this;
	dataSlots[index].originalRef->index = index;

	return dataSlots[index].originalRef;
}

void VariableMgr::addRef(VariableHandle* target, VariableHandle* ref) {
	dataSlots[target->index].refs.push_back(ref);
}

void VariableMgr::destroyRef(VariableHandle* target, VariableHandle* ref, bool deleteHandle) {
	if (target == nullptr) return;

	int index = target->index;

	if (target == ref) {
		if(deleteHandle) delete dataSlots[index].originalRef;
		dataSlots[index].originalRef = nullptr;
	}
	else {
		dataSlots[index].refs.remove(ref);
	}

	if (dataSlots[index].originalRef == nullptr &&
		dataSlots[index].refs.size() == 0) {
		
		switch (dataSlots[index].type) {
		case DT_REF: 
			destroyRef(&VariableHandle(this, *static_cast<int*>(dataSlots[index].data)), target);
		case DT_INT: delete static_cast<int*>(dataSlots[index].data); break;
		case DT_FLOAT: delete static_cast<float*>(dataSlots[index].data); break;
		case DT_BOOL: delete static_cast<bool*>(dataSlots[index].data); break;
		case DT_STRING: delete static_cast<std::string*>(dataSlots[index].data); break;
		default: break;
		}

		dataSlots[index].type = DT_NULL;
		dataSlots[index].data = nullptr;
		dataSlots[index].originalRef = nullptr;

		freeSlots.push(index);
	}
}

void VariableMgr::assign(VariableHandle* target, VariableHandle* toCopy) {
	if (dataSlots[target->index].type == DT_REF) {
		int refIndex = *static_cast<int*>(dataSlots[target->index].data);

		switch (dataSlots[refIndex].type) {
		case DT_INT: delete static_cast<int*>(dataSlots[refIndex].data); break;
		case DT_FLOAT: delete static_cast<float*>(dataSlots[refIndex].data); break;
		case DT_BOOL: delete static_cast<bool*>(dataSlots[refIndex].data); break;
		case DT_STRING: delete static_cast<std::string*>(dataSlots[refIndex].data); break;
		default: break;
		}

		switch (toCopy->getType()) {
		case DT_INT: dataSlots[refIndex].data = new int(toCopy->asInt()); break;
		case DT_FLOAT: dataSlots[refIndex].data = new float(toCopy->asFloat()); break;
		case DT_BOOL: dataSlots[refIndex].data = new bool(toCopy->asBool()); break;
		case DT_STRING: dataSlots[refIndex].data = new std::string(toCopy->asString()); break;
		default: break;
		}

		dataSlots[refIndex].type = toCopy->getType();
	}
	else {
		auto h = createCopy(toCopy);
		VariableHandle* t = target;

		destroyRef(target, target, false);

		t->index = h->index;
		t->owner = h->owner;

		dataSlots[h->index].originalRef = t;

		delete h;
	}
}

DataType VariableMgr::getType(VariableHandle* h) {
	if (dataSlots[h->index].type == DT_REF) return 
		dataSlots[*static_cast<int*>(dataSlots[h->index].data)].type;
	else return dataSlots[h->index].type;
}

int& VariableMgr::asInt(VariableHandle* h) {
	void* data;
	if (dataSlots[h->index].type == DT_REF) data = 
		dataSlots[*static_cast<int*>(dataSlots[h->index].data)].data;
	else
		data = dataSlots[h->index].data;

	return *static_cast<int*>(data);
}

float& VariableMgr::asFloat(VariableHandle* h) {
	void* data;
	if (dataSlots[h->index].type == DT_REF) data = 
		dataSlots[*static_cast<int*>(dataSlots[h->index].data)].data;
	else
		data = dataSlots[h->index].data;

	return *static_cast<float*>(data);
}

bool& VariableMgr::asBool(VariableHandle* h) {
	void* data;
	if (dataSlots[h->index].type == DT_REF)
		data = dataSlots[*static_cast<int*>(dataSlots[h->index].data)].data;
	else
		data = dataSlots[h->index].data;

	return *static_cast<bool*>(data);
}

std::string& VariableMgr::asString(VariableHandle* h) {
	void* data;
	if (dataSlots[h->index].type == DT_REF)
		data = dataSlots[*static_cast<int*>(dataSlots[h->index].data)].data;
	else 
		data = dataSlots[h->index].data;

	return *static_cast<std::string*>(data);
}
