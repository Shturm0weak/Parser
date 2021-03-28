#include <iostream>
#include "Parser/Parser.h"

void ParseAndLoad() 
{
	std::string inFile, outFile;
	std::cout << "Загрузить из\n";
	std::cin >> inFile;
	std::cout << "Загрузить в\n";
	std::cin >> outFile;
	Node* node = Parser::GetInstance().Parse(inFile.c_str());
	Parser::GetInstance().SaveInFile(outFile.c_str(), *node);
	delete node;
}

int main()
{
	setlocale(LC_ALL, "ru");
	ParseAndLoad();
}