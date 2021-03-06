#include <iostream>
#include <cstdlib>
#include "Token.h"
#include "StateMachine.h"
#include "Symbol.h"
#include "Scanner.h"
#include "Debug.h"
#include "Node.h"
#include "Parser.h"
#include "Instructions.h"

using namespace std;

void Interpret(string InputFile)
{
	ScannerClass scan(InputFile);
	SymbolTableClass sym;
	
	ParserClass parser(&scan, &sym);
	StartNode *test = parser.Start();
	cout << "finished building the parse tree. \n";
	test->Interpret();
	delete test;
}

void CodeAndExecute(string InputFile)
{
	ScannerClass testfile(InputFile);
	SymbolTableClass sym;
	
	ParserClass parser(&testfile, &sym);
	StartNode *test = parser.Start();
	cout << "\n\tparse tree built\n";

		
	InstructionsClass machineCode;
	test->Code(machineCode);
	machineCode.Finish();
	machineCode.Execute();

	cout << "\ttesting complete" << endl;
	
	
	
	delete test;
}


int main() {
/*
	cout << "\nTesting file in and out" << endl;
	ScannerClass testfile("example.txt");
	SymbolTableClass sym;
	
	IdentifierNode * identifier = new IdentifierNode("sum", &sym);
	//cout << identifier->Evaluate() << endl;
	IntegerNode * integer1 = new IntegerNode(8);
	IntegerNode * integer2 = new IntegerNode(4);
//plus check
	PlusNode * plus = new PlusNode(integer1, integer2);
	cout << "\t" << plus->Evaluate() << endl;
//minus check
	MinusNode * minus = new MinusNode(integer1, integer2);
	cout << "\t" << minus->Evaluate() << endl;
//times check
	TimesNode * times = new TimesNode(integer1, integer2);
	cout << "\t" << times->Evaluate() << endl;
//divide check
	DivideNode * divide = new DivideNode(integer1, integer2);
	cout << "\t" << divide->Evaluate() << endl;
//less check
	LessNode * less = new LessNode(integer1, integer2);
	cout << "\t" << less->Evaluate() << endl;
//less equal check
	LessEqualNode * lessEqual = new LessEqualNode(integer1, integer2);
	cout << "\t" << lessEqual->Evaluate() << endl;
//greater check
	GreaterNode * greater = new GreaterNode(integer1, integer2);
	cout << "\t" << greater->Evaluate() << endl;
//greater equal check
	GreaterEqualNode * greaterEqual = new GreaterEqualNode(integer1, integer2);
	cout << "\t" << greaterEqual->Evaluate() << endl;
//equal check
	EqualNode * equal = new EqualNode(integer1, integer2);
	cout << "\t" << equal->Evaluate() << endl;
//not equal check
	NotEqualNode * neq = new NotEqualNode(integer1, integer2);
	cout << "\t" << neq->Evaluate() << endl;
	cout << endl;
	cout << endl;
	cout << "testing delete \n";
//	delete plus;
//	delete equal;
//	delete greater;
//	delete divide;
//	delete identifier;
	cout << "i think it worked?" << endl;;
*/
	string inputFile = "example.txt";
	cout << "code and execute section \n\n";
	//CodeAndExecute(inputFile);
	cout << "Interpret section \n\n";
	Interpret(inputFile);
	cout << "\nEverything is complete \n";
/*
to add in the not operator to the machinecode section 
viud encode(instructionsclass &ic)
{
mpexpression->encode(ic)
ic.logicalnot()
}

void instructionsclass::logicalNot()
{
encode(immediate_to_eax)
encode(0)
encode(push_eax)
poppopequalpush()
//if it was zero it becomes 1, all other numbers become 0;
}
*/
	return 0;
}

