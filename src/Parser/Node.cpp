#include "Node.h"
#include "Parser.h"

Node::Node()
{
	m_Id = Parser::GetInstance().s_NodeId;
	Parser::GetInstance().s_NodeId++;
}

void Node::SaveInFile(std::ofstream& out, const Node& node, std::string tabs)
{
	out << tabs << node.m_Id << " ";
	if(node.m_Parent != nullptr) out << node.m_Parent->m_Id << " ";
	else out << "-1" << " ";
	out << node.m_Name;
	out << " = ";
	uint64_t childsSize = node.m_Childs.size();
	if (childsSize > 0) 
	{
		out << "{\n";
		tabs.append("  ");
		for (uint64_t i = 0; i < childsSize; i++)
		{
			SaveInFile(out, *node.m_Childs[i], tabs);
		}
		tabs.erase(tabs.begin() + tabs.size() - 1);
		tabs.erase(tabs.begin() + tabs.size() - 1);
		out << tabs << "}\n";
	}
	else
		out << node.m_Value << std::endl;
}

void Node::PrintNode(const Node& node, std::string tabs)
{
	std::cout << tabs << node.m_Name << " = ";
	uint64_t childsSize = node.m_Childs.size();
	if (childsSize > 0) 
	{
		std::cout << "{\n";
		tabs.append("  ");
		for (uint64_t i = 0; i < childsSize; i++)
		{
			PrintNode(*node.m_Childs[i], tabs);
		}
		tabs.erase(tabs.begin() + tabs.size() - 1);
		tabs.erase(tabs.begin() + tabs.size() - 1);
		std::cout << tabs << "}\n";
	}
	else
		std::cout << node.m_Value << std::endl;
}

Node::~Node() 
{
	for (uint64_t i = 0; i < m_Childs.size(); i++)
	{
		delete m_Childs[i];
	}
#ifdef _DEBUG
	std::cout << "Node <" << m_Name << "> has been destroyed\n";
#endif
}