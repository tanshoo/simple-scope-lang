#include "interpreter.h"
#include <iostream>

Interpreter::Interpreter(const std::string &input) : lexer(input) {
    current_token = lexer.next_token();
    scopes.push({});
}

void Interpreter::consume(TokenType type) {
    if (current_token.type != type) {
        throw UnexpectedTokenException(current_token.value);
    }
    current_token = lexer.next_token();
}

int Interpreter::interpret_expression() {
    if (current_token.type == TokenType::IDENTIFIER) {
        std::string identifier = current_token.value;
        consume(TokenType::IDENTIFIER);
        if (variables.contains(identifier)) {
            return variables[identifier].top();
        }
        throw InvalidIdentifierException(identifier);
    } else if (current_token.type == TokenType::NUMBER) {
        int value = std::stoi(current_token.value);
        consume(TokenType::NUMBER);
        return value;
    } else {
        throw UnexpectedTokenException(current_token.value);
    }
}

void Interpreter::interpret_statement() {
    if (current_token.type == TokenType::IDENTIFIER) {
        std::string identifier = current_token.value;
        consume(TokenType::IDENTIFIER);
        consume(TokenType::ASSIGN);
        int value = interpret_expression();
        if (!variables.contains(identifier)) {
            variables[identifier] = {};
            scopes.top().insert(identifier);
        } else {
            if (scopes.top().contains(identifier)) {
                variables[identifier].pop();
            } else {
                scopes.top().insert(identifier);
            }
        }
        variables[identifier].push(value);
    } else if (current_token.type == TokenType::PRINT) {
        consume(TokenType::PRINT);
        try {
            int value = interpret_expression();
            std::cout << value << "\n";
        } catch (const InvalidIdentifierException &e) {
            std::cout << "null\n";
        }
    } else if (current_token.type == TokenType::SCOPE_OPEN) {
        consume(TokenType::SCOPE_OPEN);
        scopes.push({});
        while (current_token.type != TokenType::SCOPE_CLOSE) {
            interpret_statement();
        }
        consume(TokenType::SCOPE_CLOSE);
        for (const std::string &identifier : scopes.top()) {
            variables[identifier].pop();
            if (variables[identifier].empty()) {
                variables.erase(identifier);
            }
        }
        scopes.pop();
    } else if (current_token.type != TokenType::NEWLINE) {
        throw UnexpectedTokenException(current_token.value);
    }

    consume(TokenType::NEWLINE);
    while (current_token.type == TokenType::NEWLINE) {
        consume(TokenType::NEWLINE);
    }
}

void Interpreter::run() {
    while (current_token.type != TokenType::END_OF_FILE) {
        interpret_statement();
    }
}


int main() {
    std::string input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input += line + "\n";
    }

    Interpreter interpreter(input);
    interpreter.run();

    return 0;
}
