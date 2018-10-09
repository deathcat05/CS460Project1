#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer(char *filename)
{
	lex = new LexicalAnalyzer(filename);
	token_type t;
	bool startOfFile = true;
	ofstream tokenFile, listFile;
	string tokenFileName, listFileName;

	while ((t = lex->GetToken()) != EOF_T)
	{
		// set variables to be printed
		int lineNum = lex->getLineNum();
		string line = lex->getLine();
		string lexeme = lex->GetLexeme();
		string tokenName = lex->GetTokenName(t);
		//string errorToReport = lex->GetError();


		// get and set the file names for our token and list files
		if (startOfFile)
		{
			for (int i = 0; filename[i] != '.'; i++)
			{
				tokenFileName += filename[i];
				listFileName += filename[i];
			}
			tokenFileName += ".p1";
			listFileName += ".lst";

			// open files for writing
			tokenFile.open(tokenFileName, ios::app);
			listFile.open(listFileName, ios::app);

			// print heading of list file
			listFile << "Input file: " << filename << endl;
			startOfFile = false;
		}
		// if this is the start of a newly read in line, print the line w/line number
		if (lex->readNewLine())
			listFile << "   " << lineNum << ": " << line << endl; 

		tokenFile << left << setw(15) << tokenName << lexeme << endl;

		t = EOF_T;
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer()
{
	delete lex;
}
