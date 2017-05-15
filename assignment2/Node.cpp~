#include "Node.h"
#include <iostream>
#include <math.h>
#include "Debug.h"

using namespace std;

/**** Node ****/
Node::~Node()
{
	//deconstrutor
	//MSG("delete Node");
}

/**** Start Node ****/
StartNode::StartNode(ProgramNode* pn_in)
{
	//MSG("STARTNODE");
	pn = pn_in;

}

StartNode::~StartNode()
{
	//MSG("deleting");
	//MSG(pn);
	delete pn;

}

void StartNode::Interpret()
{
	pn->Interpret();
}

void StartNode::Code(InstructionsClass &machineCode){
	pn->Code(machineCode);
}

/**** Program Node ****/
ProgramNode::ProgramNode(BlockNode* bn_in)
{
	//MSG("PROGRAMNODE");
	bn = bn_in;

}

ProgramNode::~ProgramNode()
{
	//MSG("deleting");
	//MSG(bn);
	delete bn;

}

void ProgramNode::Interpret()
{
	bn->Interpret();
}

void ProgramNode::Code(InstructionsClass &machineCode){
	bn->Code(machineCode);
}

/**** Block Node ****/
BlockNode::BlockNode(StatementGroupNode* sgn_in)
{
	//MSG("BLOCKNODE");
	sgn = sgn_in;
}

BlockNode::~BlockNode()
{
	//MSG("deleting");
	//MSG(sgn);
	delete sgn;
}

void BlockNode::Interpret()
{
	sgn->Interpret();
}

void BlockNode::Code(InstructionsClass &machineCode){
	sgn->Code(machineCode);
}

/**** Statement Group Node ****/
StatementGroupNode::StatementGroupNode()
{
	//constructor
	//MSG("STATEMENTGROUPNODE");
}

StatementGroupNode::~StatementGroupNode()
{
	//MSG("deleteing all statement groupnodes");
	while(!sn.empty())
	{
		delete sn.back();
		sn.pop_back();	
	}
	
}

void StatementGroupNode::Interpret()
{
	for(unsigned int i=0; i<sn.size(); i++)
	{
		sn.at(i)->Interpret();
	}
}


void StatementGroupNode::Code(InstructionsClass &machineCode){
	for(unsigned int i=0; i<sn.size(); i++){
		sn.at(i)->Code(machineCode);
	}
}

/**** AddStatementGroup ****/
void StatementGroupNode::AddStatement(StatementNode* sn_in)
{
	//MSG("ADDSTATEMENTGROUPNODE");
	sn.push_back(sn_in);
}

/**** Statement Node ****/
StatementNode::~StatementNode()
{
	//deconstructor
	//MSG("delete statement");
}

void StatementNode::Interpret(){

}

void StatementNode::Code(InstructionsClass &machineCode){

}

/**** Declaration Statment Node ****/
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* idn_in)
{
	//MSG("DECLARATIONSTATEMENTNODE");
	idn = idn_in;
}

DeclarationStatementNode::~DeclarationStatementNode()
{
	//MSG("deleting");
	//MSG(idn);
	delete idn;
	
}

void DeclarationStatementNode::Interpret()
{
	idn->DeclareValue();
}

void DeclarationStatementNode::Code(InstructionsClass &machineCode){
	idn->DeclareValue();
}

/**** Assignment Statement Node ****/
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* idn_in, ExpressionNode* esn_in)
{
	//MSG("ASSIGNMENTSTATEMENTNODE");
	idn = idn_in;
	esn = esn_in;
}

AssignmentStatementNode::~AssignmentStatementNode()
{
	//MSG("deleting");
	//MSG(idn);
	//MSG(esn);
	delete idn;
	delete esn;
	
}

void AssignmentStatementNode::Interpret()
{
		int temp = esn->Evaluate();
		idn->SetValue(temp);
}

void AssignmentStatementNode::Code(InstructionsClass &machineCode){
		esn->CodeEvaluate(machineCode);
		int index = idn->GetIndex();
		machineCode.PopAndStore(index);
}

/**** Cout Statement Node ****/
CoutStatementNode::CoutStatementNode()
{
	//MSG("COUTSTATEMENTNODE");
	eln = new EndlNode();
}

CoutStatementNode::~CoutStatementNode()
{
	for(unsigned int i=0; i<esn.size(); i++)
	{
		delete esn.back();
		esn.pop_back();
	}
	//MSG("deleting");
	//MSG(eln);
	delete eln;
}

void CoutStatementNode::Interpret()
{
	for(unsigned int i=0; i<esn.size(); i++)
	{
		if(esn.at(i) == NULL)
		{
			eln->Evaluate();
		}
		else
		{
			int temp = esn.at(i)->Evaluate();
			cout << temp;
		}
	}
}

void CoutStatementNode::AddExpression(ExpressionNode * cn)
{
	esn.push_back(cn);
}

void CoutStatementNode::Code(InstructionsClass &machineCode){
	for(unsigned int i=0; i<esn.size(); i++){
		if(esn.at(i) == NULL){
			eln->Code(machineCode);
			
		}
		else{
			esn.at(i)->CodeEvaluate(machineCode);
			machineCode.PopAndWrite();
		}
	}
}

/**** IfStatementNode ****/
IfStatementNode::IfStatementNode(ExpressionNode* esn_in, StatementNode* sgn_in, StatementNode* sgne_in)
{
	//MSG("IFSTATEMENTNODE");
	esn = esn_in;
	sgn = sgn_in;
	sgne = sgne_in;
}

IfStatementNode::~IfStatementNode()
{
	//MSG("deleting");
	//MSG(esn);
	//MSG(sgn);
	//MSG(sgne);
	delete esn;
	delete sgn;
	delete sgne;
}

void IfStatementNode::Interpret()
{
	if(esn->Evaluate())
	{
		sgn->Interpret();
	}
	else if(sgne != NULL)
	{
		sgne->Interpret();
	}
}

void IfStatementNode::Code(InstructionsClass &machineCode){
	esn->CodeEvaluate(machineCode);
	unsigned char * addressValue = machineCode.SkipIfZeroStack();
	unsigned char * address1 = machineCode.GetAddress();
	sgn->Code(machineCode);
	unsigned char * jmp = machineCode.Jump();
	unsigned char * address2 = machineCode.GetAddress();
	machineCode.SetOffset(addressValue, address2 - address1);
	if(sgne != NULL){
		unsigned char * address3 = machineCode.GetAddress();
		sgne->Code(machineCode);
		unsigned char * address4 = machineCode.GetAddress();
		machineCode.SetOffset(jmp, address4 - address3);
	}
}

/**** WhileStatement Node ****/
WhileStatementNode::WhileStatementNode(ExpressionNode* esn_in, StatementNode * sgn_in)
{
	//MSG("WHILESTATEMENTNODE");
	esn = esn_in;
	sgn = sgn_in;
}

WhileStatementNode::~WhileStatementNode()
{	
	//MSG("deleting");
	//MSG(esn);
	//MSG(sgn);
	delete esn;
	delete sgn;
}

void WhileStatementNode::Interpret()
{
	while(esn->Evaluate() != 0)
	{
		sgn->Interpret();
	}
}

void WhileStatementNode::Code(InstructionsClass &machineCode){
	unsigned char * addressEx = machineCode.GetAddress();
	esn->CodeEvaluate(machineCode);
	unsigned char * addressValue = machineCode.SkipIfZeroStack();
	unsigned char * address1 = machineCode.GetAddress();
	sgn->Code(machineCode);
	unsigned char * jmp = machineCode.Jump();
	unsigned char * address2 = machineCode.GetAddress();
	machineCode.SetOffset(addressValue, address2 - address1);
	machineCode.SetOffset(jmp, addressEx - address2);
}

/**** DoWhileNode ****/
DoWhileNode::DoWhileNode(ExpressionNode *en, StatementNode *sn, StatementGroupNode *sgn)
: mExpressionNode(en), mStatementNode(sn), mStatementGroupNode(sgn)
{
	//MSG("DOSTATEMENTNODE");	
}


DoWhileNode::~DoWhileNode() {
	//MSG("DOWHILE Deconstructor");
    delete mExpressionNode;
    delete mStatementNode;
    delete mStatementGroupNode;
}

void DoWhileNode::Interpret() {
    while (mExpressionNode->Evaluate()) {
        if (mStatementGroupNode == NULL) {
            mStatementNode->Interpret();
        }
        else {
            mStatementGroupNode->Interpret();
        }
    }
}
/*
void DoWhileNode::Code(InstructionsClass &machineCode){
	unsigned char * addressEx = machineCode.GetAddress();
	esn->CodeEvaluate(machineCode);
	unsigned char * addressValue = machineCode.SkipIfZeroStack();
	unsigned char * address1 = machineCode.GetAddress();
	sgn->Code(machineCode);
	unsigned char * jmp = machineCode.Jump();
	unsigned char * address2 = machineCode.GetAddress();
	machineCode.SetOffset(addressValue, address2 - address1);
	machineCode.SetOffset(jmp, addressEx - address2);
}
*/
/**** Expression Node ****/
ExpressionNode::~ExpressionNode()
{
	//MSG("EXPRESSIONNODE Deconstructor");
}

void ExpressionNode::CodeEvaluate(InstructionsClass &machineCode)
{
}

/**** Integer Node ****/
IntegerNode::IntegerNode(int i_in)
{
	//MSG("INTEGERNODE");
	i = i_in;
}

int IntegerNode::Evaluate()
{

	return i;
}

void IntegerNode::CodeEvaluate(InstructionsClass &machineCode){
	machineCode.PushValue(this->i);
}

/*
IdentifierNode::IdentifierNode(string ident_in, Symbol * sym_in)
{
	ident = ident_in;
	sym = sym_in;
}
void IdentifierNode::DeclareValue()
{
	sym->AddEntry(ident, scope);
}
void IdentifierNode::SetValue(int v)
{
	sym->SetValue(ident, v);
}
int IdentifierNode::GetIndex(){
	int err = sym->GetIndex(ident);
	return err;
}
string IdentifierNode::GetLexeme()
{
	return ident;
}
int IdentifierNode::Evaluate()
{
	return sym->GetValue(ident);
}
*/
/**** Identifier Node ****/
IdentifierNode::IdentifierNode(string ident_in, SymbolTableClass * sym_in, int scope_in)
{
	scope = scope_in;
	ident = ident_in;
	sym = sym_in;
	//MSG("IDENTIFIERNODE");
}

void IdentifierNode::DeclareValue()
{
	sym->AddEntry(ident, scope);
}

void IdentifierNode::SetValue(int v)
{
	sym->SetValue(ident, v, scope);
}

int IdentifierNode::GetIndex(){
	int err = sym->GetIndex(ident, scope);
	return err;
}
string IdentifierNode::GetLexeme()
{
	return ident;
}

int IdentifierNode::Evaluate()
{
	return sym->GetValue(ident, scope);
}

void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode){
	machineCode.PushVariable(this->GetIndex());
}

/**** Binary Operator Node ****/
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* len_in, ExpressionNode* ren_in)
{
	//MSG("BINARYOPERATORNODE");
	len = len_in;
	ren = ren_in;	
}

BinaryOperatorNode::~BinaryOperatorNode()
{
///////////////////////////////////////////////////////////////////
	//MSG("deleting");
	//MSG(len);
	//MSG(ren);
	delete len;
	delete ren;
}


void BinaryOperatorNode::CodeEvaluate(InstructionsClass &machineCode)
{
}

/**** Plus Node ****/
PlusNode::PlusNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("PLUSNODE");
}

int PlusNode::Evaluate()
{
	return len->Evaluate() + ren->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}

/**** Minus Node ****/
MinusNode::MinusNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("MINUSNODE");
}

int MinusNode::Evaluate()
{
	return len->Evaluate() - ren->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}

/**** Times Node ****/
TimesNode::TimesNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("TIMESNODE");
}

int TimesNode::Evaluate()
{
	return len->Evaluate() * ren->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

/**** Divide Node ****/
DivideNode::DivideNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("DIVIDENODE");
}

int DivideNode::Evaluate()
{
	return len->Evaluate() / ren->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
}

/**** Less Node ****/
LessNode::LessNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("LESSNODE");
}

int LessNode::Evaluate()
{
	if(len->Evaluate() < ren->Evaluate())
		return 1;
	else
		return 0;
}

void LessNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopLessPush();
}

/**** Less Equal Node ****/
LessEqualNode::LessEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("LESSEQUALNODE");
}

int LessEqualNode::Evaluate()
{
	if(len->Evaluate() <= ren->Evaluate())
		return 1;
	else
		return 0;
}

void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

/**** Greater Node ****/
GreaterNode::GreaterNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("GREATERNODE");
}

int GreaterNode::Evaluate()
{
	if(len->Evaluate() > ren->Evaluate())
		return 1;
	else
		return 0;
}

void GreaterNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterPush();
}

/**** Greater Equal Node ****/
GreaterEqualNode::GreaterEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("GREATEREQUALNODE");
}

int GreaterEqualNode::Evaluate()
{
	if(len->Evaluate() >= ren->Evaluate())
		return 1;
	else
		return 0;
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterEqualPush();
}

/**** Equal Node ****/
EqualNode::EqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("EQUALNODE");
}
int EqualNode::Evaluate()
{
	if(len->Evaluate() == ren->Evaluate())
		return 1;
	else
		return 0;
}

void EqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopEqualPush();
}

/**** Not Equal Node ****/
NotEqualNode::NotEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
	:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("NOTEQUALNODE");
}
int NotEqualNode::Evaluate()
{
	if(len->Evaluate() != ren->Evaluate())
		return 1;
	else
		return 0;
}

void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopNotEqualPush();
}

/**** AndNode ****/
AndNode::AndNode(ExpressionNode* len_in, ExpressionNode* ren_in)
:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("ANDNODE");
}

int AndNode::Evaluate()
{
	if(len->Evaluate() && ren->Evaluate())
		return 1;
	else
		return 0;
}

void AndNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopAndPush();
}

/**** OrNode ****/
OrNode::OrNode(ExpressionNode* len_in, ExpressionNode* ren_in)
:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("ORNODE");
}

int OrNode::Evaluate()
{
	if(len->Evaluate() || ren->Evaluate())
		return 1;
	else
		return 0;
}

void OrNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopOrPush();
}

/**** PlusEqualNode ****/
PlusEqualNode::PlusEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
:BinaryOperatorNode(len_in, ren_in)
{
	MSG("\t\t\t\tPlus equal here");
}
int PlusEqualNode::Evaluate(){
	return len->Evaluate() + ren->Evaluate();
}
void PlusEqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}

/**** MinusEqualNode ****/
MinusEqualNode::MinusEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
:BinaryOperatorNode(len_in, ren_in)
{
	MSG("\t\t\t\tMinus equal here");
}
int MinusEqualNode::Evaluate(){
	return len->Evaluate() - ren->Evaluate();
}
void MinusEqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}

/**** TimesEqualNode ****/
TimesEqualNode::TimesEqualNode(ExpressionNode* len_in, ExpressionNode* ren_in)
:BinaryOperatorNode(len_in, ren_in)
{
	MSG("\t\t\t\tTimes equal here");
}
int TimesEqualNode::Evaluate(){
	return len->Evaluate() * ren->Evaluate();
}
void TimesEqualNode::CodeEvaluate(InstructionsClass &machineCode){
	len->CodeEvaluate(machineCode);
	ren->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

/**** ExponentNode ****/
ExponentNode::ExponentNode(ExpressionNode* len_in, ExpressionNode* ren_in)
:BinaryOperatorNode(len_in, ren_in)
{
	//MSG("EXPONENTNODE");
}

int ExponentNode::Evaluate()
{
	int ren_out = ren->Evaluate();
	int len_out = len->Evaluate();
	double total = pow((double)len_out, (double)ren_out);
	return (int)total;
}


/**** EndlNode ****/
EndlNode::EndlNode()
{
	//MSG("ENDLNODE");
}
EndlNode::~EndlNode()
{	
	//MSG("deleting endlnode");
}
void EndlNode::Evaluate()
{
	cout << endl;
}

void EndlNode::Code(InstructionsClass &machineCode){
	machineCode.WriteEndl();
}

/**** NotNode ****/
/*NotNode::NotNode(ExpressionNode* en)
: mExpressionNode(en)
{
	MSG("NOTNODE");
	
}
NotNode::~NotNode()
{
	MSG("Deconstructor");
}
int NotNode::Evaluate()
{
	
	return !mExpressionNode->Evaluate();
}*/
