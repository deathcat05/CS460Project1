#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

<<<<<<< HEAD
enum token_type {NONE = -1, IDKEY = 100, NUMLIT, STRLIT, LISTOP, CONS, IF,
                 COND, ELSE, DISPLAY, NEWLINE, AND, OR, NOT, DEFINE,
		 NUMBERP, LISTP, ZEROP, NULLP, STRINGP, PLUS, MINUS, DIV,
		 MULT, MODULO, ROUND, EQUALTO, GT, LT, GTE, LTE, LPAREN,
                 RPAREN, QUOTE, BU, GD, ER, EOF_T, NUM_TOKENS};
=======
enum token_type
{
	NONE = -1,
	EOF_T,
	NUM_TOKENS
};
>>>>>>> ddcb7d1a9973d963796dd3c13f0252d64dd6e5c4

class LexicalAnalyzer
{
<<<<<<< HEAD
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
=======
  public:
	LexicalAnalyzer(char *filename);
	~LexicalAnalyzer();
	token_type GetToken();
	string GetTokenName(token_type t) const;
	string GetLexeme() const;
	void GetInputFile(char *filename); //Reading in the file for manipulation
	void ReportError(const string &msg);

	//Getters
	ifstream &getInput() { return input; }
	ofstream &getListingFile() { return listingFile; }
	ofstream &getTokenFile() { return tokenFile; }
	ofstream &getDebugFile() { return debugFile; }
	//token_type getToken() {return token_type;}
	string getString() { return line; }
	int getLinenum() { return linenum; }
	string getLexeme() { return lexeme; }
	int getErrors() { return errors; }

	//Setters
	void setInput(ifstream &_input) { input = _input; }
	void setListingFile(ofstream &_listingFile) { listingFile = _listingFile; }
	void setTokenFile(ofstream &_tokenFile) { this->tokenFile = _tokenFile; }
	void setToken(token_type token) { this->token = token; }
	void setString(string line) { this->line = line; }
	void setLinenum(int linenum) { this->linenum = linenum; }
	void setLexeme(string lexeme) { this->lexeme = lexeme; }
	void setErrors(int errors) { this->errors = errors; }

  private:
>>>>>>> ddcb7d1a9973d963796dd3c13f0252d64dd6e5c4
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
