#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {NONE = -1, IDKEY = 100, NUMLIT, STRLIT, LISTOP, CONS, IF,
                 COND, ELSE, DISPLAY, NEWLINE, AND, OR, NOT, DEFINE,
		 NUMBERP, LISTP, ZEROP, NULLP, STRINGP, PLUS, MINUS, DIV,
		 MULT, MODULO, ROUND, EQUALTO, GT, LT, GTE, LTE, LPAREN,
                 RPAREN, QUOTE, BU, GD, ER, EOF_T, NUM_TOKENS};

class LexicalAnalyzer
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
	void SetToken();
	token_type FindKeyWord(string lexeme);
	//void ValidateIdentifier(string token);

	// functions I added
	string parseInput();
	string getLine ();
	int getLineNum ();
	int nextState (int currentState, char currentChar);
	string category (int catState);
    
    private:
	ifstream input;
	ofstream listingFile;
	ofstream tokenFile;
	ofstream debugFile;
	token_type token;
	string line;
	int lineNum;
	int pos;
	string lexeme;
	int errors;

};

#endif
