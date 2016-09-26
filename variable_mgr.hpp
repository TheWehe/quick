#ifndef VARIABLE_MGR_HPP
#define VARIABLE_MGR_HPP

#include <vector>
#include <stack>
#include <list>
#include <string>

enum DataType {
	DT_NULL,
	DT_INT,
	DT_FLOAT,
	DT_PINF,
	DT_NINF,
	DT_BOOL,
	DT_STRING,
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
	VariableHandle* createFloat(float f);
	VariableHandle* createPInf();
	VariableHandle* createNInf();
	VariableHandle* createBool(bool b);
	VariableHandle* createString(const std::string& s);
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
	float& asFloat(VariableHandle* h);
	bool& asBool(VariableHandle* h);
	std::string& asString(VariableHandle* h);

	std::vector<VariableData> dataSlots;
	std::stack<unsigned> freeSlots;
};

#endif
