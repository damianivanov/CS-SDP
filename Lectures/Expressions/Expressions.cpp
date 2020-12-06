// Expressions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "doctest.h"
#include "tokenizer.h" 

#include <cassert>
int apply(char oper, int left, int right)
{
    switch (oper)
    {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return left / right;
    default:
        assert(false); return -1;
    }

}

int evaluate(Tokenizer& tokenizer)
{
    Tokenizer::Token token = tokenizer.nextToken();

    if (token.type == Tokenizer::Token::number)
    {
        return token.numval;
    }


    assert(token.type == Tokenizer::Token::open_par);

    int left = evaluate(tokenizer);

    token = tokenizer.nextToken();
    char oper = token.c;
    assert(token.type == Tokenizer::Token::oper);

    int right = evaluate(tokenizer);
    token = tokenizer.nextToken();

    assert(token.type == Tokenizer::Token::close_par);

    return apply(oper, left, right);

}


int main()
{
    Tokenizer tokenizer(std::cin);

    std::cout << "Expression result = " << evaluate(tokenizer) << std::endl;
}