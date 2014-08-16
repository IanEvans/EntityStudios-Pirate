#include <iostream>
#include <fstream>
#include <string>
#include "defense.h"

using namespace std;

int GetData(string, string);
void WriteData(string, string[], int[], int);

int main()
{
	int value = GetData("DefenseStats.txt", "NODE");
	std::cout << "VALUE: " << value << std::endl;
	int value2 = GetData("DefenseStats.txt", "HEALTH");
	std::cout << "VALUE2: " << value2 << std::endl;
	int value3 = GetData("DefenseStats.txt", "DEFENSE");
	std::cout << "VALUE3: " << value3 << std::endl;
	int value4 = GetData("DefenseStats.txt", "TYPE");
	std::cout << "VALUE4: " << value4 << std::endl;
	int value5 = GetData("DefenseStats.txt", "XPOS");
	std::cout << "VALUE5: " << value5 << std::endl;
	int value6 = GetData("DefenseStats.txt", "YPOS");
	std::cout << "VALUE6: " << value6 << std::endl;

	Defense test = Defense(value2, value5, value6, value, value4);
	cout << test;
	string headers[] = {"DEFENSE=", "HEALTH=", "NODE=", 
					    "TYPE=", "XPOS=", "YPOS="};
	int values[] = {value, value2, value3, value4, value5, value6};


	WriteData("Output.txt", headers, values, 6);

	system("PAUSE");
	return 0;
}

int GetData(string file, string search)
{
	std::ifstream stream;
	stream.open(file);

	if(!stream.is_open())
	{
		std::cout << "Error. Does not exist." << std::endl;
		return 1;
	}

	std::string str;
	while(std::getline(stream,str))
	{
		if(!str.compare(0, search.length(),search))
		{
			//std::cout << "WORD: " << found << std::endl;
			//std::cout << str << std::endl;
			int equalAt = str.find('=');
			int value = atoi(str.substr(equalAt+1, string::npos).c_str());

			stream.close();
			return value;
		}
	}

	stream.close();
	return -1;
}

void WriteData(string path, string headers[], int values[], int size)
{
	ofstream stream;
	stream.open(path);
	cout << "Writing " << size << "values  to " << path << endl;
	for(int i = 0; i < size; ++i)
	{
		stream << headers[i] << values[i] << endl;
	}
	stream.close();
}