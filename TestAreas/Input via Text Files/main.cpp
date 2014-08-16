#include <iostream>
#include <fstream>
#include <string>
#include "defense.h"

using namespace std;

int GetData(string, string);

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
	cout << test.health << endl;
	cout << test;

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
		std::string found;
		for(int j = 0; j < search.length(); ++j)
		{
			if(str[j] == search[j])
			{
				found.push_back(str[j]);
			}
		}

		if(search.length() == found.length())
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