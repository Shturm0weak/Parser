#pragma once

#include <vector> 
#include <iostream>

struct Node {
public:

	std::string m_Name;
	std::string m_Value;
	std::vector<Node*> m_Childs;
	Node* m_Parent = nullptr;
	uint64_t m_Id = 0;
	
	~Node();

	static void PrintNode(const Node& node, std::string tabs = "");
private:

	Node();

	static void SaveInFile(std::ofstream& out, const Node& node, std::string tabs = "");

	friend class Parser;	
};