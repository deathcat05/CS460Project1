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

	int count = 0; // temporary...to limit the while loop

	while ((t = lex->GetToken()) != EOF_T)
	{
	  if (count == 35) // limiting to 35 calls of GetToken for now
	    break;
		//Create a p1 file & open for input
		//ofstream p1File;
		//p1File.open("P1-0.p1");

		// get a token
		// write its name to the .p1 file
		// write the corresponding lexeme to the .p1 file
	  t = EOF_T;
	  count++;
	}

}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
