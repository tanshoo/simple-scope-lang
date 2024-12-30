#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include "lexer.h"

class UnexpectedTokenException : public std::runtime_error {
public:
    UnexpectedTokenException(const std::string &token) 
        : std::runtime_error("Unexpected token: " + token) {}
};

class InvalidIdentifierException : public std::runtime_error {
public:
    InvalidIdentifierException(const std::string  &identifier) 
        : std::runtime_error("Invalid identifier: " + identifier) {}
};

class Interpreter {
private:
    std::unordered_map<std::string, std::stack<int>> variables;
    std::stack<std::unordered_set<std::string>> scopes;
    Lexer lexer;
    Token current_token;

    void consume(TokenType type);
    void interpret_statement();
    int interpret_expression();

public:
    Interpreter(const std::string &input);
    void run();
};