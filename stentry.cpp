#include "stentry.h"

STEntry::STEntry()
{}
        
STEntry::STEntry(Token* tok, string lex)
{
    token = tok;
    lexeme = lex;
    reserved = false;
    
}

STEntry::STEntry(Token* tok, string lex, bool res)
{
    token = tok;
    lexeme = lex;
    reserved = res;
}