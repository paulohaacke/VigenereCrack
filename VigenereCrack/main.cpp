#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ctype.h>
#include <cstdio>

#define MAXIMUM_KEY_LENGTH 13
const int asciiSymbols = (int)pow(2, 8);

double CalculateSquareSum(int keyLength, std::string cipherText)
{
	if (keyLength == 0)
	{
		return 0;
	}
	else if (keyLength > (int)cipherText.length())
	{
		return 0;
	}
	std::vector<double> cipherTextCharCount(asciiSymbols);
	int elementsSum = 0;
	for (int i = 0; i < (int)cipherText.length(); i+=keyLength)
	{
		cipherTextCharCount[(unsigned char)cipherText[i]]++;
		elementsSum++;
	}
	double squareSum = 0;
	for (int i = 0; i < (int)cipherTextCharCount.size(); i++)
	{
		double cipherTextFrequency = cipherTextCharCount[i] / elementsSum;
		squareSum += pow(cipherTextFrequency, 2);
	}
	return squareSum;
}

double CalculateQiPiSum(unsigned char key, int startKeyIndex, int keyLength, std::string cipherText, std::vector<double> enFrequencies, std::string &xoredString, int &alphabetCount)
{
	if (keyLength == 0)
	{
		return 0;
	}
	else if (keyLength > (int)cipherText.length())
	{
		return 0;
	}

	//Apply XOR on cipher text to get plain text candidate
	std::string pTextCandidate("");
	for (int i = startKeyIndex; i < (int)cipherText.length(); i += keyLength)
	{
		unsigned char pChar = cipherText[i] ^ key;
		if (pChar == '@' || pChar == '&' || pChar == '>' || pChar == '<' || pChar == '_' || pChar == '#' || pChar == '*' || pChar == '%')
			return 0;
		else if (pChar >= 32 && pChar < 127)
			pTextCandidate.push_back(pChar);
		else
			return 0;
	}
	xoredString = pTextCandidate;

	//Transform plain text candidate to lower case letters
	std::string pTextCandidateLowerCase(pTextCandidate);
	std::transform(pTextCandidateLowerCase.begin(), pTextCandidateLowerCase.end(), pTextCandidateLowerCase.begin(), ::tolower);

	//Count characters in plain text candidate
	std::vector<double> pTextCandidateCharCount(asciiSymbols);
	int elementsSum = 0;
	for (int i = 0; i < (int)pTextCandidateLowerCase.length(); i++)
	{
		if (pTextCandidateLowerCase[i] >= (unsigned char)'a' && pTextCandidateLowerCase[i] <= (unsigned char)'z')
		{
			pTextCandidateCharCount[pTextCandidateLowerCase[i]]++;
			elementsSum++;
			alphabetCount++;
		}
		else if (pTextCandidateLowerCase[i] == ' ')
		{
			alphabetCount++;
		}
	}

	//Calculate SUM(qi*pi), where qi is the plain text candidate letter frequencies found, and pi is the english text letters frequency
	double qipiSum = 0;
	for (int i = 0; i < (int)pTextCandidateCharCount.size(); i++)
	{
		if (i >= 'a' && i <= 'z')
		{
			double qi = pTextCandidateCharCount[i] / elementsSum;
			double pi = enFrequencies[i];
			qipiSum += (pi / 100)*qi;
		}
	}
	return qipiSum;
}

int main()
{
	

	std::string hexText("F96DE8C227A259C87EE1DA2AED57C93FE5DA36ED4EC87EF2C63AAE5B9A7EFFD673BE4ACF7BE8923CAB1ECE7AF2DA3DA44FCF7AE29235A24C963FF0DF3CA3599A70E5DA36BF1ECE77F8DC34BE129A6CF4D126BF5B9A7CFEDF3EB850D37CF0C63AA2509A76FF9227A55B9A6FE3D720A850D97AB1DD35ED5FCE6BF0D138A84CC931B1F121B44ECE70F6C032BD56C33FF9D320ED5CDF7AFF9226BE5BDE3FF7DD21ED56CF71F5C036A94D963FF8D473A351CE3FE5DA3CB84DDB71F5C17FED51DC3FE8D732BF4D963FF3C727ED4AC87EF5DB27A451D47EFD9230BF47CA6BFEC12ABE4ADF72E29224A84CDF3FF5D720A459D47AF59232A35A9A7AE7D33FB85FCE7AF5923AA31EDB3FF7D33ABF52C33FF0D673A551D93FFCD33DA35BC831B1F43CBF1EDF67F0DF23A15B963FE5DA36ED68D378F4DC36BF5B9A7AFFD121B44ECE76FEDC73BE5DD27AFCD773BA5FC93FE5DA3CB859D26BB1C63CED5CDF3FE2D730B84CDF3FF7DD21ED5ADF7CF0D636BE1EDB79E5D721ED57CE3FE6D320ED57D469F4DC27A85A963FF3C727ED49DF3FFFDD24ED55D470E69E73AC50DE3FE5DA3ABE1EDF67F4C030A44DDF3FF5D73EA250C96BE3D327A84D963FE5DA32B91ED36BB1D132A31ED87AB1D021A255DF71B1C436BF479A7AF0C13AA14794");

	int len = hexText.length();
	std::string cText;
	for (int i = 0; i< len; i += 2)
	{
		std::string byte = hexText.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		cText.push_back(chr);
	}

	fprintf(stdout, "The cypher text is: \n%s\n", cText.c_str());

	std::vector<double> enTextFrequencies(asciiSymbols);
	enTextFrequencies['a'] = 8.167;
	enTextFrequencies['b'] = 1.492;
	enTextFrequencies['c'] = 2.782;
	enTextFrequencies['d'] = 4.253;
	enTextFrequencies['e'] = 12.702;
	enTextFrequencies['f'] = 2.228;
	enTextFrequencies['g'] = 2.015;
	enTextFrequencies['h'] = 6.094;
	enTextFrequencies['i'] = 6.966;
	enTextFrequencies['j'] = 0.153;
	enTextFrequencies['k'] = 0.772;
	enTextFrequencies['l'] = 4.025;
	enTextFrequencies['m'] = 2.406;
	enTextFrequencies['n'] = 6.749;
	enTextFrequencies['o'] = 7.507;
	enTextFrequencies['p'] = 1.929;
	enTextFrequencies['q'] = 0.095;
	enTextFrequencies['r'] = 5.987;
	enTextFrequencies['s'] = 6.327;
	enTextFrequencies['t'] = 9.056;
	enTextFrequencies['u'] = 2.758;
	enTextFrequencies['v'] = 0.978;
	enTextFrequencies['w'] = 2.361;
	enTextFrequencies['x'] = 0.150;
	enTextFrequencies['y'] = 1.974;
	enTextFrequencies['z'] = 0.074;

	//Calculate square sum of frequencies
	std::vector<double> squareSum(MAXIMUM_KEY_LENGTH);
	for (int i = 0; i < (int)squareSum.size(); i++)
	{
		squareSum[i] = CalculateSquareSum(i + 1, cText);
	}
	int keyLength = &(*std::max_element(squareSum.begin(), squareSum.end())) - &(*squareSum.begin()) + 1;

	std::vector<std::vector<double> > qipiSum(keyLength);
	std::vector<std::vector<std::string> > xorStrs(keyLength);
	std::vector<unsigned char> foundKey(keyLength);
	std::vector<std::vector<int> > alphCountComplete(keyLength);
	for (int iKeyChar = 0; iKeyChar < keyLength; iKeyChar++)
	{
		std::vector<double> tmpSum(asciiSymbols);
		std::vector<std::string> myXorStrs(asciiSymbols);
		std::vector<int> alphCount(asciiSymbols);
		for (int kChar = 0; kChar < 256; kChar++)
		{
			tmpSum[kChar] = CalculateQiPiSum(kChar, iKeyChar, keyLength, cText, enTextFrequencies, myXorStrs[kChar], alphCount[kChar]);
		}
		alphCountComplete[iKeyChar] = alphCount;
		xorStrs[iKeyChar] = myXorStrs;
		qipiSum[iKeyChar] = tmpSum;
		unsigned char foundChar = &(*std::max_element(qipiSum[iKeyChar].begin(), qipiSum[iKeyChar].end())) - &(*qipiSum[iKeyChar].begin());
		foundKey[iKeyChar] = foundChar;
	}

	std::vector<unsigned char> pTextFound(cText.length());
	std::string pTextFoundStr("");
	for (int ch = 0; ch < (int)cText.length(); ch++)
	{
		pTextFound[ch] = cText[ch] ^ foundKey[ch%keyLength];
		pTextFoundStr.push_back(pTextFound[ch]);
	}

	fprintf(stdout, "Possible key is:\n");
	for (int i = 0; i < keyLength; i++)
	{
		fprintf(stdout, "%x ", foundKey[i]);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "Possible plain text is:\n%s\n", pTextFoundStr.c_str());

	return 0;
}
