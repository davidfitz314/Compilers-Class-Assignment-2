#include <iostream>
#include "StateMachine.h"
#include "Debug.h"

using namespace std;

StateMachineClass::StateMachineClass()
{
	//MSG("Initializing Statemachine Class");
	for(int i=0; i<LAST_STATE; i++)
	{
		for(int j=0; j<LAST_STATE; j++)
		{
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}
	for(int i=0; i<LAST_STATE; i++)
	{
		mLegalMoves[COMMENT_STATE][i] = COMMENT_STATE;
		mLegalMoves[LINECOMMENT_STATE][i] = LINECOMMENT_STATE;
	}

	//NotState
	//mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
	
	//integer state
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][ENDLINE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE;
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE; 

	//identifer state
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
/////////////
	//mLegalMoves[IDENTIFIER_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
/////////////
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;

	//lessthan state
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;

	//greaterthan state
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
	mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;

	mLegalMoves[START_STATE][AND_CHAR] = PAND_STATE;
	mLegalMoves[PAND_STATE][AND_CHAR] = AND_STATE;
	//math states
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PEQUAL_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MEQUAL_STATE;
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = COMMENT_STATE;
	
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[TIMES_STATE][EQUAL_CHAR] = TEQUAL_STATE;

	//and or states
	mLegalMoves[START_STATE][OR_CHAR] = POR_STATE;
	mLegalMoves[POR_STATE][OR_CHAR] = OR_STATE;
	mLegalMoves[TIMES_STATE][TIMES_CHAR] = EXPONENT_STATE;
	
	//comment states
	
	mLegalMoves[COMMENT_STATE][TIMES_CHAR] = NCOMMENT_STATE;
	mLegalMoves[NCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][ENDLINE_CHAR] = START_STATE;
	

	//paren and curly states
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
	mLegalMoves[START_STATE][SEMICOLIN_CHAR] = SEMICOLIN_STATE;
	mLegalMoves[START_STATE][COLIN_CHAR] = COLIN_STATE;
	mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;

//mCorrespondingtypes machineState intialized to their end token
	for(int i=0; i<LAST_STATE; i++)
	{
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[SEMICOLIN_STATE] = SEMICOLIN_TOKEN; 
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[EOF_STATE] = EOF_TOKEN;
	mCorrespondingTokenTypes[COLIN_STATE] = COLIN_TOKEN;
	mCorrespondingTokenTypes[COMMENT_STATE] = COMMENT_TOKEN;
	mCorrespondingTokenTypes[UNCOMMENT_STATE] = UNCOMMENT_TOKEN;
	mCorrespondingTokenTypes[LINECOMMENT_STATE] = LINECOMMENT_TOKEN;
	mCorrespondingTokenTypes[NCOMMENT_STATE] = NCOMMENT_TOKEN;
	mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
	mCorrespondingTokenTypes[EXPONENT_STATE] = EXPONENT_TOKEN;
	mCorrespondingTokenTypes[PEQUAL_STATE] = PEQUAL_TOKEN;
	mCorrespondingTokenTypes[MEQUAL_STATE] = MEQUAL_TOKEN;
	mCorrespondingTokenTypes[TEQUAL_STATE] = TEQUAL_TOKEN;	

	mCorrespondingTokenTypes[ENDLINE_STATE] = ENDLINE_TOKEN;

	//mCorrespondingTokenTypes[NOT_STATE] = NOT_TOKEN;

	mCorrespondingTokenTypes[LAST_STATE] = LAST_TOKEN;

	
	
	
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType)
{
	CharacterType ct;
	bool skip = false;

	if(isdigit(currentCharacter)){
		ct = DIGIT_CHAR;
		skip = true;
	}
	if(isalpha(currentCharacter)){
		ct = LETTER_CHAR;
		skip = true;
	}
	if(isspace(currentCharacter)){
		ct = WHITESPACE_CHAR;
		skip = true;
	}
	if(currentCharacter == '+'){
		ct = PLUS_CHAR;
		skip = true;
	}
	if(currentCharacter == EOF){
		ct = EOF_CHAR;
		skip = true;
	}
	if(currentCharacter == '('){
		ct = LPAREN_CHAR;
		skip = true;
	}
	if(currentCharacter == ')'){
		ct = RPAREN_CHAR;
		skip = true;
	}
	if(currentCharacter == '{'){
		ct = LCURLY_CHAR;
		skip = true;
	}
	if(currentCharacter == '}'){
		ct = RCURLY_CHAR;	
		skip = true;
	}
	if(currentCharacter == ';'){
		ct = SEMICOLIN_CHAR;	
		skip = true;
	}
	if(currentCharacter == ':'){
		ct = COLIN_CHAR;	
		skip = true;
	}
	if(currentCharacter == '<'){
		ct = LESS_CHAR;	
		skip = true;
	}
	if(currentCharacter == '>'){
		ct = GREATER_CHAR;	
		skip = true;
	}
	if(currentCharacter == '='){
		ct = EQUAL_CHAR;
		skip = true;
	}
	if(currentCharacter == '-'){
		ct = MINUS_CHAR;
		skip = true;
	}
	if(currentCharacter == '*'){
		ct = TIMES_CHAR;
		skip = true;
	}
	if(currentCharacter == '/'){
		ct = DIVIDE_CHAR;
		skip = true;
	}
	if(currentCharacter == '\n'){
		ct = ENDLINE_CHAR;
		skip = true;
	}
	if(currentCharacter == '&'){
		ct = AND_CHAR;
		skip = true;
	}
	if(currentCharacter == '|'){
		ct = OR_CHAR;
		skip = true;
	}
	//if(currentCharacter == '!'){
	//	ct = NOT_CHAR;
	//	skip = true;
	//}
	if(!skip){
		std::cout << currentCharacter << std::endl;
		ct = BAD_CHAR;
	}


	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];

	mCurrentState = mLegalMoves[mCurrentState][ct];

	return mCurrentState;
}

void StateMachineClass::PrintMlegalMoves()
{
	cout << "\nState,Char{mLegalMoves}\n" << endl;
	for (int i=0; i<LAST_STATE; i++)
	{
		
		for (int j=0; j<LAST_CHAR; j++)
		{
			cout << i << "," << j << "{" << mLegalMoves[i][j] << "}";
			if (j == 9){
				cout << endl;
			}		
		}
	cout << "\n"<< endl;
	}
}

void StateMachineClass::ResetCurrentState()
{
	this->mCurrentState = START_STATE;
}


