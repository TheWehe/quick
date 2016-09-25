#ifndef VARIABLE_MGR_HPP
#define VARIABLE_MGR_HPP

#include <vector>
#include <stack>
#include <list>

enum DataType {
	DT_NULL,
	DT_INT,
	DT_REF
};

class VariableHandle;

struct VariableData {
	DataType type = DT_NULL;
	void* data = nullptr;
	VariableHandle* originalRef;
	std::list<VariableHandle*> refs;
};

class VariableMgr {
	friend class VariableHandle;
	
public:
	VariableMgr() = default;
	VariableMgr(const VariableMgr& rhs) = delete;
	VariableMgr& operator=(const VariableMgr& rhs) = delete;
	VariableMgr(VariableMgr&& rhs) = delete;
	VariableMgr& operator=(VariableMgr&& rhs) = delete;
	~VariableMgr();
	
	VariableHandle* createNull();
	VariableHandle* createInt(int i);
	VariableHandle* createCopy(VariableHandle* target);
	VariableHandle* createRef(VariableHandle* target);
	void destroy(VariableHandle* h);
	
private:
	VariableHandle* create();
	void addRef(VariableHandle* target, VariableHandle* ref);
	void destroyRef(VariableHandle* target, VariableHandle* ref, bool deleteHandle = true);
	void assign(VariableHandle* target, VariableHandle* toCopy);
	DataType getType(VariableHandle* h);
	int& asInt(VariableHandle* h);

	std::vector<VariableData> dataSlots;
	std::stack<unsigned> freeSlots;
};

#endif
