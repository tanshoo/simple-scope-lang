#include "lexer.h"

void Lexer::skip_whitespace() {
    while (position < input.size() && 
          (input[position] == ' ' || input[position] == '\t')) {
        ++position;
    }
}

std::string Lexer::read_identifier() {
    size_t start = position;
    while (position < input.size() && std::isalnum(input[position])) {
        ++position;
    }
    return input.substr(start, position - start);
}

std::string Lexer::read_number() {
    size_t start = position;
    while (position < input.size() && std::isdigit(input[position])) {
        ++position;
    }
    return input.substr(start, position - start);
}

Token Lexer::next_token() {
    skip_whitespace();

    if (position >= input.size()) {
        return {TokenType::END_OF_FILE, ""};
    }

    char current = input[position];

    if (std::isalpha(current)) {
        std::string identifier = read_identifier();
        if (identifier == "scope") {
            skip_whitespace();
            if (position < input.size() && input[position] == '{') {
                ++position;
                return {TokenType::SCOPE_OPEN, "scope {"};
            }
            throw InvalidTokenException(identifier);
        } else if (identifier == "print") {
            return {TokenType::PRINT, "print"};
        } else {
            return {TokenType::IDENTIFIER, identifier};
        }
    } else if (std::isdigit(current)) {
        return {TokenType::NUMBER, read_number()};
    } else if (current == '=') {
        ++position;
        return {TokenType::ASSIGN, "="};
    } else if (current == '}') {
        ++position;
        return {TokenType::SCOPE_CLOSE, "}"};
    } else if (current == '\n') {
        ++position;
        return {TokenType::NEWLINE, "\\n"};
    } else {
        throw InvalidCharacterException(current);
    }
}