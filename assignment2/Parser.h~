#ifndef _PARSER_H_
#define _PARSER_H_
#include <stdio.h>
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Token.h"
#include "Debug.h"

class ParserClass {
public:
    ParserClass(ScannerClass *scanner, SymbolTableClass *symbolTableClass);
    StartNode * Start();
    
private:
    ScannerClass *mScanner;
    SymbolTableClass *mSymbolTable;
	TokenClass Match(TokenType expectedType);
    ProgramNode * Program();
    BlockNode * Block();
    StatementGroupNode * StatementGroup();
    StatementNode * Statement();
    DeclarationStatementNode * DeclarationStatement();
    AssignmentStatementNode * AssignmentStatement();
    CoutStatementNode * CoutStatement();
    IfStatementNode * IfStatement();
    WhileStatementNode * WhileStatement();
	DoWhileNode * DoWhile();
    IdentifierNode * Identifier();
    ExpressionNode * Expression();
    ExpressionNode * Relational();
    ExpressionNode * Side();
    ExpressionNode * Term();
	//ExpressionNode * Not();
    ExpressionNode * Factor();
    IntegerNode * Integer();
    ExpressionNode * Exponent();
    ExpressionNode * Or();
    ExpressionNode * And();
    
};

#endif
