/*
Course: CS 460 -- Programming Languages 
Assignment: Project 1 -- Part 1
Date: September 24, 2018
*/

#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"IDENT_T", "NUMLIT_T", "STRLIT_T", "LISTOP_T", "CONS_T", "IF_T", "COND_T","ELSE_T","DISPLAY_T","NEWLINE_T","AND_T","OR_T", "NOT_T","DEFINE_T","NUMBERP_T","LISTP_T","ZEROP_T","NULLP_T", "STRINGP_T","PLUS_T","MINUS_T","DIV_T","MULT_T","MODULO_T", "ROUND_T","EQUALTO_T","GT_T","LT_T","GTE_T","LTE_T","LPAREN_T", "RPAREN_T","SQUOTE_T","ERROR_T","EOF_T" };

static string input_lookup[] = { "+", "-", "/", "*", "=", "<", ">", "(", ")", "'", "c", "a", "d", "r", "#", "_", ".", "?", "alpha", "other" };

//static string table [] = {}; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // This function will initialize the lexical analyzer class

  DEBUG = true;
  pos = 0;
  linenum = 0;
  lexeme = "";
  errors = 0;
  currentPosition = 0;
  startPosition = 0;

  input.open(filename);
  if (!input)
    {
      cout << "File not found!" << endl;
      return;
    }
  /*
  if (input.fail())
    {
      cerr << "File: " << filename << " not found.\n";
      exit (2);
      }*/
  debugFile.open("debug.dbg", std::ofstream::out | std::ofstream::trunc);

}

LexicalAnalyzer::~LexicalAnalyzer ()
{
  // This function will complete the execution of the lexical analyzer class

  input.close();
  //Close listing file
  listingFile.close();
  
  //Close token file
  tokenFile.close();
  
  //Close debug file
  debugFile.close();
}

token_type LexicalAnalyzer::GetToken ()
{
  // This function will find the next lexeme int the input file and return
  // the token_type value associated with that lexeme
  return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
  // The GetTokenName function returns a string containing the name of the
  // token passed to it. 
  //return "";

  return token_names[token];
}

string LexicalAnalyzer::GetLexeme () const
{
  // This function will return the lexeme found by the most recent call to 
  // the get_token function

  //Probably a good spot for the DFA??
  
  // return "";
  
  // return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
  // This function will be called to write an error message to a file
  if (msg != " ")
    cout << "Error: Cannot find character" << endl;
  //Not quite done with the message statement
  return;
}

/*
token_type LexicalAnalyzer::Predicates ()
{ //token_type taken from SyntacticalAnalyzer.cpp file
  
  //This function handles the 5 predicates 
  
  if ("number?" == lexeme)
    return NUMBERP_T;
  if ("list?" == lexeme)
    return LISTP_T;
  if ("zero?" == lexeme)
    return ZEROP_T;
  if ("null?" == lexeme)
    return NULLP_T;
  if ("string?" == lexeme)
    return STRINGP_T;
  return IDENT_T;
}
*/
