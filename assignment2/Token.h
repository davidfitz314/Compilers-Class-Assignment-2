#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <iostream>
#include <string>

enum TokenType {
/*
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	EQUAL_TOKEN, 
	NOT_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
	TIMES_TOKEN, DIVIDE_TOKEN, OUTSTREAM_TOKEN, COMMENT_TOKEN, BLOCKCOMMENT_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
	RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, EXCLAMATION_TOKEN,
	BAD_TOKEN, ENDFILE_TOKEN
*/
	START_TOKEN, IDENTIFIER_TOKEN, INTEGER_TOKEN, CANTMOVE_TOKEN, LESSEQUAL_TOKEN, 
	LESS_TOKEN, INSERTION_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, SEMICOLIN_TOKEN, 
	PLUS_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, 
	EQUAL_TOKEN, ASSIGNMENT_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, 
	COLIN_TOKEN, EOF_TOKEN, /*NOTEQUAL_TOKEN,*/ COMMENT_TOKEN, 
	UNCOMMENT_TOKEN, LINECOMMENT_TOKEN, NCOMMENT_TOKEN, ENDLINE_TOKEN, VOID_TOKEN, 
	COUT_TOKEN, MAIN_TOKEN, INT_TOKEN, RETURN_TOKEN, IF_TOKEN, EXPONENT_TOKEN, 
	DO_TOKEN, ELSE_TOKEN, PEQUAL_TOKEN, MEQUAL_TOKEN, TEQUAL_TOKEN,/*NOT_TOKEN,*/
	ENDL_TOKEN, WHILE_TOKEN, AND_TOKEN, OR_TOKEN, BAD_TOKEN, LAST_TOKEN,
};

const std::string gTokenTypeNames[] = {
/*
	"VOID", "MAIN", "INT", "COUT",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL",
	"NOT",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE", "OUTSTREAM", "COMMENT", "BLOCKCOMMENT",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IDENTIFIER", "INTEGER", "EXCLAMATION"
	"BAD", "EOF"
*/
	"START", "IDENTIFIER", "INTEGER", "CANTMOVE", "LESSEQUAL", 
	"LESS", "INSERTION", "LPAREN", "RPAREN", "SEMICOLIN", 
	"PLUS", "LCURLY", "RCURLY", "GREATER", "GREATEREQUAL", 
	"EQUAL", "ASSIGNMENT", "MINUS", "TIMES", "DIVIDE", 
	"COLIN", "EOF", /*"NOTEQUAL",*/ "COMMENT", 
	"UNCOMMENT", "LINECOMMENT", "NCOMMENT", "ENDLINE", "VOID", 
	"COUT", "MAIN", "INT ", "RETURN", "IF", "EXPONENT",
	"DO", "ELSE", "PLUSEQUAL", "MINUSEQUAL", "TIMESEQUAL",/*"NOT_TOKEN",*/
	"ENDL", "WHILE", "AND", "OR", "BAD", "LAST"
};

class TokenClass
{
	private:
		TokenType mType;
		std::string mLexeme;
	public:
		TokenClass();
		TokenClass(TokenType type, const std::string & lexeme);
		TokenType GetTokenType() const;
		const std::string & GetTokenTypeName() const;
		std::string GetLexeme() const;
		void CheckReserved();
		void PrintTokenError(std::string c, int line);

};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);

#endif // TOKEN