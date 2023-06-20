#include "scanner.h"
#include "stdio.h"

class Parser
{
private:
	Scanner* scanner;
	Token* lToken;
	SymbolTable* globalST;
	SymbolTable* currentST;

	void advance();
	void match(int);
	bool isType(Token*);
	void isList(Token* tok);
	void error(string);
	void initSimbolTable();

	void program(); 
	void classList(); 
	void classDecl(); 
	void classBody(); 
	void varDeclListOpt(); 
	void varDeclList(); 
	void varDeclListComma();
	void varDecl();
	void varDeclOpt(); 
	void type();
	void constructDeclListOpt(); 
	void constructDeclList(); 
	void constructDeclListComma(); 
	void constructDecl(); 
	void methodDeclListOpt(); 
	void methodDeclList(); 
	void methodDeclListComma(); 
	void methodDecl(); 
	void methodBody(); 
	void paramListOpt(); 
	void paramList(); 
	void paramListComma();
	void param();
	void statementsOpt(); 
	void statements(); 
	void statementsComma();
	void statement(); 
	void atribStat(); 
	void printStat(); 
	void readStat();
	void returnStat(); 
	void superStat(); 
	void ifStat(); 
	void forStat(); 
	void atribStatOpt(); 
	void expressionOpt(); 
	void lValue(); 
	void lValueComp();
	void expression(); 
	void allocExpression(); 
	void numExpression(); 
	void term();
	void unaryExpression(); 
	void factor(); 
	void argListOpt(); 
	void argList(); 
	void argListComma();  

public:
	Parser(string);
	void run();
};