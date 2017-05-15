#include <iostream>
using namespace std;
#include "Token.h"
#include "Debug.h"

TokenClass::TokenClass()
{
	//MSG("Blank constructor for TokenClass initialized")
}

TokenClass::TokenClass(TokenType type, const string & lexeme)
{
	
	//MSG("dont push the start button, the start button, the start button... ps token class initializer with passed in arguments");
	this->mType = type;
	this->mLexeme = lexeme;
}

TokenType TokenClass::GetTokenType() const 
{ 
	return this->mType; 
}

const string & TokenClass::GetTokenTypeName() const 
{ 
	return gTokenTypeNames[this->mType]; 
}

string TokenClass::GetLexeme() const 
{ 
	return this->mLexeme; 
}

void TokenClass::CheckReserved()
{
	//Tests if token is of correct type or if it was instead a reserved word token.
	if(mLexeme == "void")
		mType = VOID_TOKEN;
	if(mLexeme == "main")
		mType = MAIN_TOKEN;
	if(mLexeme == "int")
		mType = INT_TOKEN;
	if(mLexeme == "cout")
		mType = COUT_TOKEN;
	if(mLexeme == "eof")
		mType = EOF_TOKEN;
	if(mLexeme == "bad")
		mType = BAD_TOKEN;
	if(mLexeme == "return")
		mType = RETURN_TOKEN;
	if(mLexeme == "if")
		mType = IF_TOKEN;
	if(mLexeme == "else")
		mType = ELSE_TOKEN;
	if(mLexeme == "while")
		mType = WHILE_TOKEN;
	if(mLexeme == "do")
		mType = DO_TOKEN;
	if(mLexeme == "begin")
		mType = LCURLY_TOKEN;
	if(mLexeme == "and")
		mType = AND_TOKEN;
	if(mLexeme == "or")
		mType = OR_TOKEN;
	if(mLexeme == "endl")
		mType = ENDL_TOKEN;
	if(mLexeme == "end")
		mType = RCURLY_TOKEN;
	

}

void TokenClass::PrintTokenError(string c, int line)
{
	cout << "Error at line: " << line << '\n' << "Symbol: '" << c << "' cannot be read by the compiler \n" << endl;

}

ostream &operator<<(ostream & out, const TokenClass & tc)
{
	out << tc.GetTokenType() << " ";
	out << tc.GetTokenTypeName() << " ";
	out << tc.GetLexeme();
	return out;
}


