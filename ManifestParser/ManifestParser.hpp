#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

inline void skipWhitespace(std::istringstream& input) {
    while (isspace(input.peek())) {
        input.get();
    }
}

inline std::string parseString(std::istringstream& input) {
    char c;
    std::string value;
    input.get(); // Consume the opening double quote

    while (input.get(c)) {
        if (c == '"') {
            break;
        }
        value += c;
    }

    return value;
}

inline json parseObject(std::istringstream& input) {
    json obj;
    std::string key;

    while (input.peek() != '}') {
        skipWhitespace(input);
        key = parseString(input); // Extract the key value
        skipWhitespace(input);

        if (input.peek() == '{') {
            input.get(); // Consume the opening curly brace
            obj[key] = parseObject(input);
            skipWhitespace(input);
        }
        else if (input.peek() == '"') {
            obj[key] = parseString(input);
            skipWhitespace(input);
        }

        if (input.peek() == '}') {
            input.get(); // Consume the closing curly brace
            break;
        }
    }
    return obj;
}

inline json parseJson(std::istringstream& input) {
    // Skip first line
    std::string line;
    std::getline(input, line);

    // Consume the opening curly brace
    while (input.peek() != '{') {
        input.get();
    } input.get();

    json data;
    data = parseObject(input);

    return data;
}

#endif // JSON_PARSER_HPP