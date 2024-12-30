#pragma once 

#include <string>
#include <stdexcept>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    ASSIGN,
    SCOPE_OPEN,
    SCOPE_CLOSE,
    PRINT,
    NEWLINE,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};

class InvalidCharacterException : public std::runtime_error {
public:
    InvalidCharacterException(const char c) 
        : std::runtime_error("Invalid character: " + c) {}
};

class InvalidTokenException : public std::runtime_error {
public:
    InvalidTokenException(const std::string &token) 
        : std::runtime_error("Invalid token: " + token) {}
};

class Lexer {
private:
    std::string input;
    size_t position;

    void skip_whitespace();
    std::string read_identifier();
    std::string read_number();

public:
    Lexer(const std::string &input) 
        : input(input + "\n"), position(0) {}

    Token next_token();
};



