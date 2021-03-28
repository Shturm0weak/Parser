#include "Parser.h"
#include <iostream>

Node* Parser::Parse(const char* inFile)
{
	std::ifstream in(inFile);
	std::string token;
	Parser::GetInstance().s_NodeId = 0;
	Node* mainNode = nullptr;
	if (!in.fail()) 
	{
		while (!(in.eof() || in.fail()))
		{
			mainNode = ParseNode(in, token, nullptr);
			break;
		}
	}
	else {
		std::cout << "Ошибка: Невозможно открыть файл <" << inFile << ">\n";
	}
	in.close();
	return mainNode;
}

Parser& Parser::GetInstance()
{
	static Parser instance;
	return instance;
}

Node* Parser::ParseNode(std::ifstream& in, std::string& token, Node* parent)
{
	Parser& parser = Parser::GetInstance();
	if (parser.s_IsParseListClosed == false) in >> token;
	else parser.s_IsParseListClosed = true;

	if (token == "}") return nullptr;

	Node* node = new Node();
	node->m_Name = (std::string&&)token;

	in >> token;
	if (token != "=")
	{
		std::cout << "Ошибка: Неверный формат данных\n";
		exit(INVALID_DATA_FORMAT);
	}
	in >> token;
	
	if (token == "{")
		ParseList(in, token, node);
	else if (token[0] == '\"' && token.back() == '\"')
	{
		token.pop_back();
		token.erase(token.begin());
		node->m_Value = (std::string&&)token;
	}
	else
	{
		std::cout << "Ошибка: Неверный формат данных\n";
		exit(INVALID_DATA_FORMAT);
	}

	if (parent != nullptr)
	{
		parent->m_Childs.push_back(node);
		parent->m_Childs.back()->m_Parent = parent;
	}
	return node;
}

bool Parser::SaveInFile(const char* outFile, Node& node)
{
	if (&node == nullptr)
	{
		std::cout << "Ошибка: Узел пуст\n";
		return false;
	}
	std::ofstream out(outFile);
	Node::SaveInFile(out, node);
	out.close();
	std::cout << "Данные успешно сохранены в <" << outFile << ">\n";
	return true;
}

void Parser::ParseList(std::ifstream& in, std::string& token, Node* parent)
{
	Parser& parser = Parser::GetInstance();
	parser.s_IsParseListClosed = false;
	while (token != "}")
	{
		ParseNode(in, token, parent);
	}
	parser.s_IsParseListClosed = true;

	in >> token;
}
