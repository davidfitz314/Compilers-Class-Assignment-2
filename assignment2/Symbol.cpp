#include "Debug.h"
#include "Symbol.h"
using namespace std;

SymbolTableClass::SymbolTableClass()
{
	//MSG("Initializing Symbol Class");
//constructor
}

bool SymbolTableClass::Exists(std::string s, int scope)
{
	
// returns true if <s> is already in the symbol table.
	for (unsigned int i=0; i<SymTable.size(); i++)
	{
		if(s == SymTable[i].mLabel && SymTable[i].scope == scope)
			//MSG("scope test.........................................");			
			//MSG(scope);
			return true;
	}
	return false;
}

void SymbolTableClass::AddEntry(std::string s, int scope)
{
	
	bool sin = Exists(s, scope);
	if(sin == false)
	{
		Variable symbol;
		symbol.mLabel = s;
		symbol.mValue = 0;
		symbol.scope = scope;
		SymTable.push_back(symbol);
		MSG("\n" << symbol.mLabel << "\t" << symbol.mValue << "\n");
	}
	else 
		std::cout << "AddEntry failed!!! string already exists\n";
// adds <s> to the symbol table,
// or quits if it was already there
}

int SymbolTableClass::GetValue(std::string s, int scope)
{
	if(!Exists(s, scope)) {
        cout << "Variable " << s << " does not exists." << endl;
        exit(1);
    }
	return SymTable[GetIndex(s, scope)].mValue;
// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
}

void SymbolTableClass::SetValue(std::string s, int v, int scope)
{
	if(!Exists(s, scope)) {
		cout << "Variable " << s << " does not exists." << endl;
        exit(1);
    }
	SymTable[GetIndex(s, scope)].mValue = v;

// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
}

int SymbolTableClass::GetIndex(std::string s, int scope)
{
	for(unsigned int i = 0; i<SymTable.size();i++)
	{
		if(s == SymTable[i].mLabel && SymTable[i].scope == scope)
			return i;
	}
// returns the index of where variable <s> is.
// returns -1 if variable <s> is not there.
	return -1;
}
/*
int SymbolTableClass::GetCount()
{
// returns the current number of variables in the symbol
// table.
	return (int)SymTable.size();
}*/
