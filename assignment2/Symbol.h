#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
//add in scopes to everything
class SymbolTableClass
{
	private:
		struct Variable 
		{
			std::string mLabel;
			int mValue;
			int scope;
		};
		std::vector <Variable> SymTable;

	public:
		SymbolTableClass();
		//constructor
		bool Exists(std::string s, int scope);
		// returns true if <s> is already in the symbol table.
		void AddEntry(std::string s, int scope);
		// adds <s> to the symbol table,
		// or quits if it was already there
		int GetValue(std::string s, int scope);
		// returns the current value of variable <s>, when
		// interpreting. Meaningless for Coding and Executing.
		// Prints a message and quits if variable s does not exist.
		void SetValue(std::string s, int v, int scope);
		// sets variable <s> to the given value, when interpreting.
		// Meaningless for Coding and Executing.
		// Prints a message and quits if variable s does not exist.
		int GetIndex(std::string s, int scope);
		// returns the index of where variable <s> is.
		// returns -1 if variable <s> is not there.
		//int GetCount();
		// returns the current number of variables in the symbol
		// table.
	

};

#endif 
