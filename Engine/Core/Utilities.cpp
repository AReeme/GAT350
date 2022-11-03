#include "Utilities.h" 
#include <string>
#include <cctype>
#include <algorithm> 

namespace neu
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		// convert string characters to lower case 
		std::transform(lower.begin(), lower.end(), lower.begin(),[](unsigned char c) { return std::tolower(c); });

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		// convert string characters to upper case 
		std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) { return std::toupper(c); });

		return upper;
	}

	bool CompareIgnoreCase(std::string& str1, std::string& str2)
	{
		// if string lengths don't match return false 
		// returns false if string characters aren't equal
		if (str1.length() != str2.length())
		{
			return false;
		}
		
		return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](char& c1, char& c2) {
			return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
			}));

	}
}