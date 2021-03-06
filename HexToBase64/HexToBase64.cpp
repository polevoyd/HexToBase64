#include "stdafx.h"
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>

std::string hexToBase64(std::string str);
void askToExit(bool &b);
int main()
{
	bool to_exit{ false };
	while (!to_exit)
	{
		std::cout << "Enter a text to encode or \"exit\" to leave: " << "\n";
		std::string text{};
		std::getline(std::cin, text);
		if (text == "exit")
		{
			to_exit = true;
		}
		else
		{
			std::cout << hexToBase64(text) << "\n";
		}
	}
	return 0;
}

std::string hexToBase64(std::string str)
{
	std::string s{};

	// Converting ASCII string to numerical binary
	for (char &i : str)
		s += (std::bitset<8>(i).to_string());

	//Pad at the end as necessary with zeros (to divide by 6)
	while (s.size() % 6 != 0)
		s += '0';

	//Divide binary string into words of 6 bits
	std::vector<std::string> vs{};
	for (int i = 0; i < s.size(); i += 6)
	{
		std::string temp(s, i, 6);
		vs.push_back(temp);
	}

	//Convert 6 - bit words to decimal then decimal to ASCII
	std::vector<int> vi{};
	for (std::string &i : vs)
	{
		std::bitset<6> tmp{ i };
		vi.push_back(tmp.to_ulong());
	}

	const std::vector<char> base64_c{
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
		'W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','0','p','q','r',
		's','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/' };

	std::string rt{};

	for (int &i : vi)
		rt += base64_c[i];

	// Pad the string with "=" as necessary
	while (rt.size() % 4 != 0)
		rt += '=';

	return rt;
}
void askToExit(bool &b)
{
	std::cout << "Close application? y/n" << "\t";
	char a{};
	std::cin >> a;
	if (a == 'y')
	{
		b = true;
	} 
	else
	{
		b = false;
		std::cout << system("cls");
	}
}
