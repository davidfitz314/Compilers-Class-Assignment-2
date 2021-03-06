#ifndef _NODE_H
#define _NODE_H

#include <string>
#include "Symbol.h"
#include "Instructions.h"


using namespace std;

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class IfStatementNode;
class WhileStatementNode;
class DoStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;
class AndNode;
class OrNode;
class PlusEqualNode;
class MinusEqualNode;
class TimesEqualNode;
class ExponentNode;
class EndlNode;
class NotNode;

//node
class Node
{
private:

public:
	virtual ~Node();
	virtual void Interpret() = 0;
	virtual void Code(InstructionsClass &machineCode) = 0;

};


//startnode
class StartNode:public Node
{
private:
	ProgramNode* pn;

public:
	StartNode(ProgramNode* pn_in);
	~StartNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);

};

//programnode
class ProgramNode:public Node
{
private:
	BlockNode* bn;

public:
	ProgramNode(BlockNode* bn_in);
	~ProgramNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);

};

//statementgroupnode
class StatementGroupNode:public Node
{
public:
	vector <StatementNode*> sn;

	StatementGroupNode();
	~StatementGroupNode();
	void AddStatement(StatementNode * sn_in);
	void Interpret();
	void Code(InstructionsClass &machineCode);

};

//statementnode
class StatementNode:public Node
{
private:

public:
	~StatementNode();
	virtual void Interpret() = 0;
	void Code(InstructionsClass &machineCode);

};

/////////////////////////////////////////
//blocknode
class BlockNode:public StatementNode
{
private:
	StatementGroupNode* sgn;

public:
	BlockNode(StatementGroupNode* sgn_in);
	~BlockNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);

};
//////////////////////////////////////////

//declarationstatementnode
class DeclarationStatementNode:public StatementNode
{
private:
	IdentifierNode* idn;

public:
	DeclarationStatementNode(IdentifierNode* idn_in);
	~DeclarationStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);
};

//assignmentstatementnode
class AssignmentStatementNode:public StatementNode
{
private:
	IdentifierNode* idn;
	ExpressionNode* esn;
public:
	AssignmentStatementNode(IdentifierNode* idn_in, ExpressionNode* esn_in);
	~AssignmentStatementNode(); 
	void Interpret();
	void Code(InstructionsClass &machineCode);

};

//coutstatementnode
class CoutStatementNode:public StatementNode
{
private:
	vector<ExpressionNode*> esn;
	EndlNode * eln;
public:
	
	CoutStatementNode();
	~CoutStatementNode();
	void Interpret();
	void AddExpression(ExpressionNode * cn);
	void Code(InstructionsClass &machineCode);
};

//ifstatementnode
class IfStatementNode:public StatementNode
{
private:
	ExpressionNode* esn;
	StatementNode* sgn;
	StatementNode* sgne;
public:
	IfStatementNode(ExpressionNode* esn_in, StatementNode* sgn_in, StatementNode* sgne_in);
	~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);


};

//whilestatementnode
class WhileStatementNode:public StatementNode
{
private:
	ExpressionNode* esn;
	StatementNode* sgn;
public:
	WhileStatementNode(ExpressionNode* esn_in, StatementNode * sgn_in);
	~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass &machineCode);


};

//DoWhileNode
class DoWhileNode: public StatementNode {
public:
    DoWhileNode(ExpressionNode *en, StatementNode *sn, StatementGroupNode *statementGroupNode);
    ~DoWhileNode();
    void Interpret();
    //void Code(InstructionsClass &machineCode);
private:
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;
    StatementGroupNode *mStatementGroupNode;
};

//expressionnode
class ExpressionNode
{
private:
		
public:
	virtual ~ExpressionNode();
	virtual int Evaluate() = 0;
	virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;

};

//integernode
class IntegerNode:public ExpressionNode
{
private:
	int i;

public:
	IntegerNode(int i_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//identifiernode
class IdentifierNode:public ExpressionNode
{
private:
	string ident;
	SymbolTableClass* sym;
	int scope;
public:
	IdentifierNode(string ident_in, SymbolTableClass * sym_in, int scope_in);
//	IdentifierNode(string ident_in, SymbolTableClass * sym_in);
	void DeclareValue();
	void SetValue(int v);
	int GetIndex();
	string GetLexeme();
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//binaryoperatornode
class BinaryOperatorNode:public ExpressionNode
{
public:
	ExpressionNode* len;
	ExpressionNode* ren;

	BinaryOperatorNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	~BinaryOperatorNode();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//plusnode
class PlusNode:public BinaryOperatorNode
{
private:

public:
	PlusNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//minusnode
class MinusNode:public BinaryOperatorNode
{
private:

public:
	MinusNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//timesnode
class TimesNode:public BinaryOperatorNode
{
private:

public:
	TimesNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//dividenode
class DivideNode:public BinaryOperatorNode
{
private:

public:
	DivideNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//lessnode
class LessNode:public BinaryOperatorNode
{
private:

public:
	LessNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//lessequalnode
class LessEqualNode:public BinaryOperatorNode
{
private:

public:
	LessEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//greaternode
class GreaterNode:public BinaryOperatorNode
{
private:

public:
	GreaterNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//greaterequalnode
class GreaterEqualNode:public BinaryOperatorNode
{
private:

public:
	GreaterEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//equalnode
class EqualNode:public BinaryOperatorNode
{
private:

public:
	EqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//notequalnode
class NotEqualNode:public BinaryOperatorNode
{
private:

public:
	NotEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//andnode
class AndNode:public BinaryOperatorNode
{
private:

public:
	AndNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//ornode
class OrNode:public BinaryOperatorNode
{
private:

public:
	OrNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);

};

//plusEqualNode
class PlusEqualNode:public BinaryOperatorNode
{
private:
public:
	PlusEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);
};

//minusEqualNode
class MinusEqualNode:public BinaryOperatorNode
{
private:
public:
	MinusEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);
};

//TimesEqualNode
class TimesEqualNode:public BinaryOperatorNode
{
private:
public:
	TimesEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machineCode);
};

//exponentnode
class ExponentNode:public BinaryOperatorNode
{
private:

public:
	ExponentNode(ExpressionNode* len_in, ExpressionNode* ren_in);
	int Evaluate();
};

//endlnode
class EndlNode
{
private:

public:
	EndlNode();
	~EndlNode();
	void Evaluate();
	void Code(InstructionsClass &machineCode);

};

//notNode
/*
class NotNode: public ExpressionNode
{
private:
	ExpressionNode *mExpressionNode;
public:
	NotNode(ExpressionNode* en);
	~NotNode();
	int Evaluate();
};*/
#endif
