#include "Parser.h"

int g_scope = 0;

bool g_upscope_test = false;
bool g_upscope = false;


struct scopevar{
	string mScope;
	int mVal;
};

vector<scopevar> g_varname;

using namespace std;

ParserClass::ParserClass(ScannerClass *scanner, SymbolTableClass *symbolT)
:mScanner(scanner), mSymbolTable(symbolT) {
    MSG("Parser constructor");
}

StartNode * ParserClass::Start() {
    ProgramNode *pn = Program();
    Match(EOF_TOKEN);
    StartNode *sn = new StartNode(pn);
    return sn;
}

// Verify that the next token in the input file is of the same type
// that the parser expects.
TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mScanner->GetNextToken();
	if(currentToken.GetTokenType() != expectedType)
	{
		cerr << "Error in ParserClass::Match. " << endl;
		cerr << "Expected token type " << currentToken.GetTokenTypeName() << endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " <<
	currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
	currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}

ProgramNode * ParserClass::Program() {
    
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode *bn = Block();
    ProgramNode *pn = new ProgramNode(bn);
    return pn;
}

BlockNode * ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroupNode *sgn = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode *bn = new BlockNode(sgn);
    return bn;
}

StatementGroupNode* ParserClass::StatementGroup() {
    StatementGroupNode *sgn = new StatementGroupNode();
    while (true) {
        StatementNode *statement = Statement();
        if (statement == NULL) {
            return sgn;
        } else {
            sgn->AddStatement(statement);
        }
    }
}

StatementNode * ParserClass::Statement() {
    TokenClass nextToken = mScanner->PeekNextToken();
    TokenType tt = nextToken.GetTokenType();
    if (tt == INT_TOKEN) {
        return DeclarationStatement();
    }
    else if (tt == IDENTIFIER_TOKEN) {
        return AssignmentStatement();
    }
    else if (tt == COUT_TOKEN) {
        return CoutStatement();
    }
    else if (tt == LCURLY_TOKEN) {
        return Block();
    }
    else if (tt == IF_TOKEN) {
        return IfStatement();
    }
	else if (tt == WHILE_TOKEN) {
        return WhileStatement();
    }
	else if (tt == DO_TOKEN) {
        return DoWhile();
    }
    return NULL;
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
	if(g_upscope_test)
		g_upscope = true;
    Match(INT_TOKEN);
    IdentifierNode *identifier = Identifier();
    Match(SEMICOLIN_TOKEN);
    DeclarationStatementNode* dsn = new DeclarationStatementNode(identifier);
	if(g_upscope_test)
		g_upscope = false;
    return dsn;
}


AssignmentStatementNode * ParserClass::AssignmentStatement()
{
	IdentifierNode * idna = Identifier();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	AssignmentStatementNode * assign = NULL;
	if(tt == ASSIGNMENT_TOKEN){
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode * exp = Expression();
		assign = new AssignmentStatementNode(idna, exp);
	}
	else if(tt == PEQUAL_TOKEN){
		Match(tt);
		ExpressionNode * exp = Expression();
		for(int i=0; i<g_varname.size(); i++){
			if(idna->GetLexeme() == g_varname.at(i).mScope){
				g_scope = g_varname.at(i).mVal;
			}
		}
		IdentifierNode * idna2 = new IdentifierNode(idna->GetLexeme(), mSymbolTable, g_scope);
		g_scope = 0;
		PlusNode * pn = new PlusNode(idna,exp);
		assign = new AssignmentStatementNode(idna2, pn);
	}
	else if(tt == MEQUAL_TOKEN){
		Match(tt);
		ExpressionNode * exp = Expression();
		for(int i=0; i<g_varname.size(); i++){
			if(idna->GetLexeme() == g_varname.at(i).mScope){
				g_scope = g_varname.at(i).mVal;
			}
		}
		IdentifierNode * idna2 = new IdentifierNode(idna->GetLexeme(), mSymbolTable, g_scope);
		g_scope = 0;
		MinusNode * mn = new MinusNode(idna, exp);
		assign = new AssignmentStatementNode(idna2, mn);
	} 
	else if(tt == TEQUAL_TOKEN){
		Match(tt);
		ExpressionNode * exp = Expression();
		for(int i=0; i<g_varname.size(); i++){
			if(idna->GetLexeme() == g_varname.at(i).mScope){
				g_scope = g_varname.at(i).mVal;
			}
		}
		IdentifierNode * idna2 = new IdentifierNode(idna->GetLexeme(), mSymbolTable, g_scope);
		g_scope = 0;
		TimesNode * mn = new TimesNode(idna, exp);
		assign = new AssignmentStatementNode(idna2, mn);
	} 
	/*else if(tt == EQUAL_TOKEN){
		Match(EQUAL_TOKEN);
		ExpressionNode * exp = Expression();
		assign = new AssignmentStatementNode(idna, exp);
	} */
	
	Match(SEMICOLIN_TOKEN);

	//MSG("Creating a AssignmentStatementNode.");
	return assign;
}

/*
AssignmentStatementNode * ParserClass::AssignmentStatement() {
    IdentifierNode *identifier = Identifier();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    AssignmentStatementNode *asn = NULL;
    if (tt == ASSIGNMENT_TOKEN) {
        Match(ASSIGNMENT_TOKEN);
        ExpressionNode *expression = Expression();
        asn = new AssignmentStatementNode(identifier, expression);
    }
    Match(SEMICOLIN_TOKEN);
    return asn;
}
*/

CoutStatementNode * ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    CoutStatementNode *csn = new CoutStatementNode();
    ExpressionNode *expression = Expression();
    csn->AddExpression(expression);
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == INSERTION_TOKEN) {
            Match(INSERTION_TOKEN);
            TokenClass next = mScanner->PeekNextToken();
            if (next.GetTokenType() == ENDL_TOKEN) {
                Match(ENDL_TOKEN);
                csn->AddExpression(NULL);
            }
            else {
                ExpressionNode *nextExpression = Expression();
                csn->AddExpression(nextExpression);
            }
        }
        else {
            if (tt == ENDL_TOKEN) {
                Match(ENDL_TOKEN);
                csn->AddExpression(NULL);
            }
            Match(SEMICOLIN_TOKEN);
            break;
        }
    }
    return csn;
}

/////////////////////////////////////////////////////////
IfStatementNode* ParserClass::IfStatement() {
	g_upscope_test = true;
    StatementNode* S2 = NULL;
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * e = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * S1 = Statement();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == ELSE_TOKEN) {
        Match(ELSE_TOKEN);
        S2 = Statement();
    }
    IfStatementNode* in = new IfStatementNode(e,S1,S2);
	g_upscope_test = false;
	g_varname.clear();
    return in;
}
///////////////////////////////////////////////////////////

/*
Token tt = Match(IDENTIFIER_TOKEN);
	IdentifierNode * idn = new IdentifierNode(tt.GetLexeme(), sym);
	return idn;
*/
IdentifierNode * ParserClass::Identifier() {
    TokenClass token = Match(IDENTIFIER_TOKEN);
	for(unsigned int i=0; i<g_varname.size(); i++)
	{
		if(token.GetLexeme() == g_varname.at(i).mScope)
		{
			g_scope = g_varname.at(i).mVal;
		}
	} 
	if(g_upscope)
	{
		g_scope++;
		scopevar s;
		s.mScope = token.GetLexeme();
		s.mVal = g_scope;
		g_varname.push_back(s);
	}

    IdentifierNode *in = new IdentifierNode(token.GetLexeme(), mSymbolTable, g_scope/*scope in goes here*/);
	g_scope = 0;
    return in;
}

ExpressionNode * ParserClass::Expression() {
    ExpressionNode *expNode = Or();
    return expNode;
}


ExpressionNode* ParserClass::Or() {
    ExpressionNode *current = And();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == OR_TOKEN) {
            Match(tt);
            current = new OrNode(current, And());
        }
        else {
            break;
        }
    }
    return current;
}

ExpressionNode* ParserClass::And() {
    ExpressionNode *current = Relational();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == AND_TOKEN) {
            Match(tt);
            current = new AndNode(current, Relational());
        }
        else {
            break;
        }
    }
    return current;
}

ExpressionNode* ParserClass::Relational() {
    ExpressionNode * current = Side();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == LESS_TOKEN || tt == LESSEQUAL_TOKEN ||
        tt == GREATER_TOKEN || tt == GREATEREQUAL_TOKEN ||
        tt == EQUAL_TOKEN ) {
        Match(tt);
        if (tt == LESS_TOKEN)
            current = new LessNode(current, Relational());
        else if(tt == LESSEQUAL_TOKEN)
            current = new LessEqualNode(current, Relational());
        else if(tt == GREATER_TOKEN)
            current = new GreaterNode(current, Relational());
        else if(tt == GREATEREQUAL_TOKEN)
            current = new GreaterEqualNode(current, Relational());
        else if(tt == EQUAL_TOKEN)
            current = new EqualNode(current, Relational());
        }
    return current;
}

ExpressionNode* ParserClass::Side() {
    ExpressionNode *current = Term();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == PLUS_TOKEN) {
            Match(tt);
            current = new PlusNode(current, Term());
        }
        else if(tt == MINUS_TOKEN) {
            Match(tt);
            current = new MinusNode(current, Term());
        }
        else {
            return current;
        }
    }
}

ExpressionNode* ParserClass::Term() {
    ExpressionNode *current = Exponent();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == TIMES_TOKEN) {
            Match(tt);
            current = new TimesNode(current, Exponent());
        }
        else if(tt == DIVIDE_TOKEN) {
            Match(tt);
            current = new DivideNode(current, Exponent());
        }
        else {
            return current;
        }
    }
}



ExpressionNode* ParserClass::Exponent() {
    ExpressionNode *current = Factor();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == EXPONENT_TOKEN) {
            Match(tt);
            current = new ExponentNode(current, Factor());
        }
        else {
            return current;
        }
    }
}

//////////////////////////////////////////////
/*
ExpressionNode *ParserClass::Not() {
	
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == NOT_TOKEN){
			Match(NOT_TOKEN);	
			return new NotNode(Not());
		}
		else {	
			return Factor();
		}
}
*/
ExpressionNode* ParserClass::Factor() {
    ExpressionNode *current = NULL;
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == IDENTIFIER_TOKEN) {
        current = Identifier();
    }
    else if (tt == INTEGER_TOKEN) {
        current = Integer();
    }
	//else if (tt == NOT_TOKEN) {
	//	current = Not();
	//}
    else {
        Match(LPAREN_TOKEN);
        current = Expression();
        Match(RPAREN_TOKEN);
    }
    return current;
}



IntegerNode * ParserClass::Integer() {
    TokenClass tc = Match(INTEGER_TOKEN);
    string s = tc.GetLexeme();
    const char *c = s.c_str();
    IntegerNode *i = new IntegerNode(atoi(c));
    return i;
}

WhileStatementNode* ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *e = Expression();
    Match(RPAREN_TOKEN);

    StatementNode *statement = Statement();

    WhileStatementNode *ws = new WhileStatementNode(e, statement);
    return ws;
}


DoWhileNode* ParserClass::DoWhile() {
    StatementNode *statement = NULL;
    StatementGroupNode *statementgroup = NULL;
    Match(DO_TOKEN);
    statement = Statement();
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode *e = Expression();
    Match(RPAREN_TOKEN);
    Match(SEMICOLIN_TOKEN);
    DoWhileNode *dw = new DoWhileNode(e, statement, statementgroup);
    return dw;
}
