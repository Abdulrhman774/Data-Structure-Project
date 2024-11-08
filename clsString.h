#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;
public:

	clsString()
	{
		_Value = "";
	};

	clsString(string S1value)
	{
		_Value = S1value;
	}

	static enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

	void setstring(string S1value)
	{
		_Value = S1value;
	}

	string getString()
	{
		return _Value;
	}

	__declspec(property(get = getString, put = setstring)) string Value;




	static void PrintFirstLetter(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if ((S1.at(i) != ' ') && IsFirstLetter)
			{
				cout << S1.at(i) << endl;
			}
			IsFirstLetter = (S1.at(i) == ' ' ? true : false);
		}
	}

	void PrintFirstLetter()
	{
		PrintFirstLetter(_Value);
	}


	static string UpperFirstLetterOfEachWord(string Line)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < Line.length(); i++)
		{
			if ((Line.at(i) != ' ') && IsFirstLetter)
			{

				Line.at(i) = tolower(Line.at(i));

			}
			IsFirstLetter = (Line.at(i) == ' ' ? true : false);
		}
		return Line;
	}

	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}


	static string UpperWord(string Line)
	{
		for (int i = 0; i < Line.length(); i++)
		{
			Line.at(i) = toupper(Line.at(i));
		}
		return Line;
	}

	string UpperWord()
	{
		_Value = UpperWord(_Value);
	}


	static string LowerWord(string Line)
	{
		for (int i = 0; i < Line.length(); i++)
		{
			Line.at(i) = tolower(Line.at(i));
		}
		return Line;
	}

	string LowerWord()
	{
		_Value = LowerWord(_Value);
	}


	static char InvertedLetterCase(char Chatacter)
	{
		return isupper(Chatacter) ? tolower(Chatacter) : toupper(Chatacter);
	}

	static string InveringSpecificLetters(string Line)
	{
		for (int i = 0; i < Line.length(); i++)
		{
			Line.at(i) = InvertedLetterCase(Line.at(i));
		}
		return Line;
	}

	string InveringSpecificLetters()
	{
		return InveringSpecificLetters(_Value);
	}


	// Method 1
	static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All) {
		if (WhatToCount == enWhatToCount::All) {
			return S1.length();
		}

		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i])) {
				Counter++;
			}
			if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i])) {
				Counter++;
			}
		}
		return Counter;
	}

	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
	{
		return CountLetters(_Value, WhatToCount);
	}


	// Method 2
	static short CountCapitalLetters(string S1) {
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (isupper(S1[i])) {
				Counter++;
			}
		}
		return Counter;
	}

	static short CountSmallLetters(string S1) {
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (islower(S1[i])) {
				Counter++;
			}
		}
		return Counter;
	}

	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}



	static short CountWords(string S1)
	{

		string delim = " "; // delimiter  
		short Counter = 0;
		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word   
			if (sWord != "")
			{
				Counter++;
			}

			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Counter++; // it counts the last word of the string.
		}

		return Counter;

	}

	short CountWords()
	{
		return CountWords(_Value);
	};



	static short CountCharOfString(string Line, char Character)
	{
		short Counter = 0;

		for (short i = 0; i < Line.length(); i++)
		{
			if (Line.at(i) == Character)
				Counter++;
		}
		return Counter;
	}

	short CountCharOfString(char Character)
	{
		return CountCharOfString(_Value, Character);
	}



	static short CountLetterWithMuchCase(string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}
		return Counter;
	}

	short CountLetterWithMuchCase(char Letter, bool MatchCase = true)
	{
		return CountLetterWithMuchCase(_Value, Letter, MatchCase);
	}



	static bool IsVowel(char Character)
	{
		char charArr[5] = { 'a', 'e', 'o', 'u', 'i' };

		for (int i = 0; i < 5; i++)
		{
			if (tolower(Character) == tolower(charArr[i]))
				return true;
		}
		return false;
	}



	static short CountVowel(string Line)
	{
		short Counter = 0;
		for (short i = 0; i < Line.length(); i++)
		{
			if (IsVowel(Line.at(i)))
				Counter++;
		}
		return Counter;
	}

	short CountVowel()
	{
		return CountVowel(_Value);
	}


	static void CountVowel(string Line, vector<char>& vLetters)
	{
		for (short i = 0; i < Line.length(); i++)
		{
			if (IsVowel(Line.at(i)))
				vLetters.push_back(Line.at(i));
		}
	}

	void CountVowel(vector<char>& vLetters)
	{
		CountVowel(_Value, vLetters);
	}



	static void PrintEachWordOfString(string Line)
	{
		string delim = " "; // Delimeter
		short pos = 0;
		string sWord = "";

		cout << "\n\nYour string words are: \n\n";

		while ((pos = Line.find(delim)) != std::string::npos)
		{
			sWord = Line.substr(0, pos); // strore the word

			if (sWord != "")
				cout << sWord << endl;

			Line.erase(0, pos + delim.length());
		}
		if (Line != "")
			cout << Line << endl;
	}

	void PrintEachWordOfString()
	{
		PrintEachWordOfString(_Value);
	}



	static short NumOfWords(string Line)
	{
		string delim = " ";
		short pos = 0;
		string Word = "";
		short Counter = 0;


		while ((pos = Line.find(delim)) != std::string::npos)
		{
			Word = Line.substr(0, pos);


			if (Word != "")
				Counter++;

			Line.erase(0, pos + delim.length());
		}

		if (Line != "")
			Counter++;

		return Counter;

	}

	short NumOfWords()
	{
		return NumOfWords(_Value);
	}

	static vector <string> Sblit(string Line, string delim)
	{
		vector<string> vString;

		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = Line.find(delim)) != std::string::npos)
		{
			sWord = Line.substr(0, pos); // store the word   
			// if (sWord != "")
			// {
			vString.push_back(sWord);
			//}

			Line.erase(0, pos + delim.length());  /* erase() until positon and move to next word. */
		}

		if (Line != "")
		{
			vString.push_back(Line); // it adds last word of the string.
		}

		return vString;
	}

	vector <string> Sblit(string delim)
	{
		return Sblit(_Value, delim);
	}


	static short NumOfTokens(string Line)
	{
		string delim = " ";
		short pos = 0;
		string Word = "";
		short Counter = 0;


		while ((pos = Line.find(delim)) != std::string::npos)
		{
			Word = Line.substr(0, pos);


			if (Word != "")
				Counter++;

			Line.erase(0, pos + delim.length());
		}

		if (Line != "")
			Counter++;

		return Counter;

	}

	short NumOfTokens()
	{
		return NumOfTokens(_Value);
	}



	static string TrimFromRight(string sWord)
	{
		for (int i = sWord.length() - 1; i >= 0; i--)
		{
			if (sWord[i] != ' ')
			{
				return sWord.substr(0, i + 1);
			}
		}
		return "";
	}

	void TrimFromRight()
	{
		_Value = TrimFromRight(_Value);
	}

	static string TrimFromLeft(string sWord)
	{
		for (int i = 0; i < sWord.length(); i++)
		{
			if (sWord[i] != ' ')
			{
				return sWord.substr(i, sWord.length() - i);
			}
		}
		return "";
	}

	void TrimFromLeft()
	{
		_Value = TrimFromLeft(_Value);
	}

	static string Trim(string sWord)
	{
		return TrimFromLeft(TrimFromRight(sWord));
	}

	string Trim()
	{
		return Trim(_Value);
	}



	static string JoinString(vector <string>& vS1, string Sptr)
	{
		string S1 = "";

		for (string& JoinString : vS1)
		{
			S1 = S1 + JoinString + Sptr;
		}
		return S1.substr(0, (S1.length() - Sptr.length()));

	}

	static string JoinString(string ArrS1[], short Length, string Sptr)
	{
		string S1 = "";

		for (short i = 0; i < Length; i++)
		{
			S1 = S1 + ArrS1[i] + Sptr;
		}
		return S1.substr(0, (S1.length() - Sptr.length()));
	}



	static string ReverseWordsInString(string S1)
	{
		vector<string> vString;
		string S2 = "";
		vString = Sblit(S1, " ");

		// declare iterator
		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;
			S2 += *iter + " ";
		}

		S2 = S2.substr(0, S2.length() - 1); //remove last space.
		return S2;
	}

	string ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}



	static string AllLowerLetters(string Line)
	{
		for (int i = 0; i < Line.length(); i++)
		{
			Line.at(i) = tolower(Line.at(i));
		}
		return Line;
	}

	void AllLowerLetters()
	{
		_Value = AllLowerLetters(_Value);
	}


	static string AllUpperLetters(string Line)
	{
		for (int i = 0; i < Line.length(); i++)
		{
			Line.at(i) = toupper(Line.at(i));
		}
		return Line;
	}

	void AllUpperLetters()
	{
		_Value = AllLowerLetters(_Value);
	}


	static string ReplaceWordInStringUsingBuiltInFunction(string S1, string StringToReplace, string ReplaceTo, bool MuchCase = true)
	{
		string Sptr = " ";
		vector <string> vString = Sblit(S1, Sptr);

		for (string& sString : vString)
		{
			if (MuchCase)
			{
				if (sString == StringToReplace)
				{
					sString = ReplaceTo;
				}
			}
			else
			{
				if (AllLowerLetters(sString) == AllLowerLetters(StringToReplace))
				{
					sString = ReplaceTo;
				}
			}

		}

		return JoinString(vString, Sptr);
	}

	void ReplaceWordInStringUsingBuiltInFunction(string StringToReplace, string ReplaceTo)
	{
		_Value = ReplaceWordInStringUsingBuiltInFunction(_Value, StringToReplace, ReplaceTo);
	}



	static string RemovePunctuationsFromString(string S1)
	{
		string S2 = "";

		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}
		return S2;
	}

	void RemovePunctuationsFromString()
	{
		_Value = RemovePunctuationsFromString(_Value);
	}

};

