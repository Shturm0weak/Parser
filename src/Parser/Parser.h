#pragma once

#include "Node.h"
#include <fstream>

#define INVALID_DATA_FORMAT -10

class Parser {
public:

    static Parser& GetInstance();
    static Node* Parse(const char* inFile);
    static bool SaveInFile(const char* outFile, Node& node);
private:

    uint64_t s_NodeId = 0;
    bool s_IsParseListClosed = false;

    Parser& operator=(const Parser& rhs) { return *this; }

    Parser(const Parser&) = delete;
    Parser() {}

    static Node* ParseNode(std::ifstream& in, std::string& token, Node* parent);
    static void ParseList(std::ifstream& in, std::string& token, Node* parent);

    friend class Node;
};