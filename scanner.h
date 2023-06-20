#include "symboltable.h"
#include <fstream>

class Scanner
{
private:
    string input; 
    int pos;
    int line;
    SymbolTable* st;

public:
    Scanner(string input, SymbolTable* st);

    int getLine();

    Token* nextToken();

    void lexicalError(string);

};