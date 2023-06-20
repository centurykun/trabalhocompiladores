#include "scanner.h"  
#include "ctype.h"
#include "stdio.h"
#include <iostream>


Scanner::Scanner(string input, SymbolTable* table)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;
    pos = 0;
    line = 1;

    st = table;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    cout << this->input;

}

int Scanner::getLine()
{
    return line;
}

Token*
Scanner::nextToken()
{
    Token* tok;
    string lexeme;
    int state = 1;

    while (true)
    {
        while (isspace(input[pos]))
            pos++;
        switch (state)
        {
        case 1:
            if (input[pos] == '<')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, LESS_OR_EQUAL);
                }
                else {
                    tok = new Token(OP, LESS_THAN);
                }
            }
            else if (input[pos] == '=')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, EQUAL);
                }
                else {
                    tok = new Token(OP, ASSIGNMENT);
                }
            }
            else if (input[pos] == '>')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, GREATER_OR_EQUAL);
                }
                else {
                    tok = new Token(OP, GREATER_THAN);
                }
            }
            
            else if (input[pos] == '!')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, NOT_EQUAL);
                }
                else {
                    lexicalError("Expected = after !");
                }
            }
            else if (input[pos] == '+')
            {
                pos++;
                tok = new Token(OP, ADDITION);
            }
            else if (input[pos] == '-')
            {
                pos++;
                tok = new Token(OP, SUBTRACTION);
            }
            else if (input[pos] == '*')
            {
                pos++;
                tok = new Token(OP, ASTERISK);
            }
            else if (input[pos] == '/')
            {
                pos++;

                if (input[pos] == '/') {
                    while (input[pos] != '\n')
                        pos++;
                    state = 1;

                }

                else if (input[pos] == '*') {
                    state = 2;
                }
                else {
                    tok = new Token(OP, BAR);
                }
            }
            else if (input[pos] == '%')
            {
                pos++;
                tok = new Token(OP, MODULAR);
            }
            else if (input[pos] == ';') {
                pos++;
                tok = new Token(SEP, SEMICOLON);
            }
            else if (input[pos] == '(') {
                pos++;
                tok = new Token(SEP, LEFT_PARENTHESE);
            }
            else if (input[pos] == ')') {
                pos++;
                tok = new Token(SEP, RIGHT_PARENTHESE);
            }
            else if (input[pos] == '{') {
                pos++;
                tok = new Token(SEP, LEFT_BRACE);
            }
            else if (input[pos] == '}') {
                pos++;
                tok = new Token(SEP, RIGHT_BRACE);
            }
            else if (input[pos] == ']') {
                pos++;
                tok = new Token(SEP, RIGHT_BRACE);
            }
            else if (input[pos] == '[') {
                pos++;
                tok = new Token(SEP, LEFT_BRACKET);
            }
            else if (input[pos] == ',') {
                pos++;
                tok = new Token(SEP, COMMA_LITERAL);
            }
            else if (input[pos] == ':') {
                pos++;
                tok = new Token(SEP, COLON);
            }
            else if (input[pos] == '.') {
                pos++;
                tok = new Token(SEP, DOT);
            }
            else if (isdigit(input[pos])) {
                pos++;
                while (isdigit(input[pos]))
                    pos++;
                tok = new Token(INTEGER_LITERAL);
            }
            else if (isalpha(input[pos]) || input[pos] == '_') {
                pos++;
                while (isalpha(input[pos]) || isdigit(input[pos]) || input[pos] == '_')
                    pos++;

                STEntry* obj = st->get(lexeme);
                if (!obj) {
                    tok = new Token(ID);
                    STEntry* IDreserved;
                    IDreserved = new STEntry(tok, lexeme, true);
                    add(IDreserved);
                }
                else
                    tok = new Token(obj->token->name);
            }
            else if (input[pos] == '"') {
                pos++;
                while(input[pos++] != '"')
                    pos++;
                tok = new Token(STRING_LITERAL);
            }
            else if (input[pos] == '\0')
                tok = new Token(END_OF_FILE);
            return tok;
        case 2:

            while (input[pos] != '*')
                pos++;

            state = 3;
        case 3:

            if (input[pos] == '/') {
                pos++;

                state = 1;
            }
            else 
                state = 2;
        }
    }
}
    void Scanner::lexicalError(string msg)
    {
        cout << "Linha " << line << ": " << msg << endl;

        exit(EXIT_FAILURE);
    }