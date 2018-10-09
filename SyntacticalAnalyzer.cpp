#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;

	while ((t = lex->GetToken()) != EOF_T)
	{
	  // set variables to be printed
	  int lineNum = lex->getLineNum();
	  string line = lex->getLine();
	  string lexeme = lex->GetLexeme();
	  string tokenName = lex->GetTokenName(t);
	  string errorMsg = lex->getErrorString();

	  // if this is the start of a newly read in line, print the line w/line number
	  if (lex->readNewLine())
	    lex->printToListingFile(lineNum, line);
	  if (errorMsg != "")
	    lex->ReportError(errorMsg);
	  if (t != NONE)
	    lex->printToTokenFile(lexeme, tokenName);
	  t = EOF_T;
	}
	lex->printToTokenFile("EOF_T", "EOF_T");
	lex->printToListingFile(-1, "Done");

}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
