#ifndef VARIABLE_MGR
#define VARIABLE_MGR

#include <string>
#include <vector>
#include <stack>

enum DataType {
	DT_NULL,
	DT_PINF,
	DT_NINF,
	DT_INT,
	DT_FLOAT,
	DT_BOOL,
	DT_STRING,
	//DT_ARRAY
};

struct VariableData {
	DataType type = DT_NULL;
	unsigned refCount = 0;
	void* data = nullptr;
};

class VariableHandle;

class VariableMgr {
	friend class VariableHandle;
	
public:
	VariableMgr() = default;
	VariableMgr(const VariableMgr& rhs) = delete;
	VariableMgr(VariableMgr&& rhs) = delete;
	VariableMgr& operator=(const VariableMgr& rhs) = delete;
	VariableMgr& operator=(VariableMgr&& rhs) = delete;
	
	VariableHandle createNull();
	VariableHandle createPInf();
	VariableHandle createNInf();
	VariableHandle createInt(int i);
	VariableHandle createFloat(float f);
	VariableHandle createBool(bool b);
	VariableHandle createString(const std::string& s);
	VariableHandle createString(std::string&& s);
	/*VariableHandle createArray(const std::vector<VariableHandle>& a);
	VariableHandle createArray(std::vector<VariableHandle>&& a);*/
	
private:
	VariableHandle create();
	void increaseRef(int index);
	void decreaseRef(int index);
	
	std::vector<VariableData> dataSlots;
	std::stack<unsigned> freeSlots;
};

#endif
