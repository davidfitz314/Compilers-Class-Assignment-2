#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;
#include "Scanner.h"
#include "StateMachine.h"
#include "Token.h"
#include "Debug.h"



ScannerClass::ScannerClass(string fileIn)
{
	
	//MSG("Initializing Scanner Class Object");
	
	this->mFin.open(fileIn.c_str());
	this->line = 1;
	if (!this->mFin.is_open())
	{
		cout << "error in opening file " << fileIn << endl;
		exit(EXIT_FAILURE);
	}
}

ScannerClass::~ScannerClass()
{
	//MSG("Deconstructor for Scanner Class");
	this->mFin.close();
}

TokenClass ScannerClass::GetNextToken()
{
	TokenType currentToken; 
	StateMachineClass statey;
	statey.ResetCurrentState();
	MachineState currentState = START_STATE;
	bool endOfFile = false;
	string stringLexeme;
	do {
		//read characters from mFin 
				
		char c = this->mFin.get();
		
		stringLexeme += c;
		currentState = statey.UpdateState(c, currentToken);
		//and pass to state machine UpdateState
		//MSG("CURRENT STATE IS ");
		//MSG(currentState);
		if (currentState == START_STATE)
		{
			stringLexeme = "";
			if (c == '\n')
			{
				this->line += 1;
			}
		}
		if (currentState == CANTMOVE_STATE)
		{
			endOfFile = true;
		}
	}
	while (!endOfFile);

	if (currentToken == BAD_TOKEN)
	{
		TokenClass badToke;
		badToke.PrintTokenError(stringLexeme, line);
		exit(1);
	}
	
	mFin.unget();
	stringLexeme.resize(stringLexeme.size() - 1);

	TokenClass finalToke(currentToken, stringLexeme);
	finalToke.CheckReserved();
	
	//then create tokenclass object initalized to corresponding tokenType parameter
	//call check reserved on new token class object
	//if bad_token print message saying so and exit

	//mFin.unget() may be used to put an unprocessed character back into the input stream
	return finalToke;
}		

TokenClass ScannerClass::PeekNextToken()
{
	std::streamoff filepos = mFin.tellg();
	int linenumber = this->line;

	TokenClass tc = GetNextToken();

	if(mFin.eof())
		mFin.clear();

	mFin.seekg(filepos);
	this->line = linenumber;

	return tc;
}

int ScannerClass::GetLine(){
	return this->line;
}


