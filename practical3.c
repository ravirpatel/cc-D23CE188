#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

class LexicalAnalyzer {
private:
    // List of C Keywords
    std::unordered_set<std::string> c_keywords = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "inline", "int", "long", "register", "restrict", "return",
        "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while", "_Alignas",
        "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
        "_Noreturn", "_Static_assert", "_Thread_local"
    };

    // List of Special Symbols in C
    std::unordered_set<std::string> c_special_symbols = {
        "{", "}", "[", "]", "(", ")", "#", "##", ";", ":", "?", ".", "->",
        ",", "...", "@"
    };

    // List of C Operators
    std::unordered_set<std::string> c_operators = {
        "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=",
        "%=", "&=", "|=", "^=", "<<=", ">>=", "==", "!=", ">", "<", ">=",
        "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "?", ":",
        "."
    };

    // Function to check if a character is valid for identifier
    bool isValidIdentifierChar(char c) {
        return std::isalnum(c) || c == '_';
    }

    // Function to check if a word is a valid identifier
    bool isValidIdentifier(const std::string& identifier) {
        if (identifier.empty()) {
            return false;
        }

        if (!std::isalpha(identifier[0]) && identifier[0] != '_') {
            return false;
        }

        return std::all_of(identifier.begin() + 1, identifier.end(),
            [this](char c) { return isValidIdentifierChar(c); });
    }

    // Function to split string into words
    std::vector<std::string> splitLine(const std::string& line) {
        std::vector<std::string> words;
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            words.push_back(word);
        }

        return words;
    }

public:
    void processFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string line;
        int line_number = 1;

        while (std::getline(file, line)) {
            std::vector<std::string> words = splitLine(line);

            for (const auto& word : words) {
                if (c_keywords.find(word) != c_keywords.end()) {
                    std::cout << "Line " << line_number << ": " << word << " : Keyword" << std::endl;
                }
                else if (c_special_symbols.find(word) != c_special_symbols.end()) {
                    std::cout << "Line " << line_number << ": " << word << " : Punctuation" << std::endl;
                }
                else if (c_operators.find(word) != c_operators.end()) {
                    std::cout << "Line " << line_number << ": " << word << " : Operator" << std::endl;
                }
                else if (isValidIdentifier(word)) {
                    std::cout << "Line " << line_number << ": " << word << " : Identifier" << std::endl;
                }
                else {
                    std::cout << "Line " << line_number << ": " << word << " : Unknown or Invalid" << std::endl;
                }
            }

            line_number++;
        }

        file.close();
        std::cout << "Processing complete." << std::endl;
    }
};

int main() {
    LexicalAnalyzer analyzer;
    std::string filename;

    std::cout << "Enter the name of the C source file: ";
    std::cin >> filename;

    analyzer.processFile(filename);

    return 0;
}
