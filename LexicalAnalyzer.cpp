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

bool testing = false;

LexicalAnalyzer::LexicalAnalyzer (char * filename): input(filename)
{
  // This function will initialize the lexical analyzer class

  
  pos = 0;
  lineNum = 0;
  /*
  lexeme = "";
  errors = 0;
  currentState = 0;
  */
  //startState = 0;

  /*
  input.open(filename);
  if (!input)
    {
      cout << "File not found!" << endl;
      return;
    }
  */
  
  if (input.fail())
    {
      cerr << "File: " << filename << " not found.\n";
      exit (2);
      }
  //debugFile.open("debug.dbg", std::ofstream::out | std::ofstream::trunc);

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

   if (line.empty() || pos >= line.length()-1)
    {
      getline (input, line);
      pos = 0;
      // everytime we get a new line, we need to reset our pos variable to 0
      lineNum++;
      // also, increment our lineNum variable (which starts at 0 initially)
      cout << lineNum << ".) " << line << endl;
      // output the line number and contents
    }

  /* Here is where we start parsing the line.  parseInput() wil return the lexeme it
     finds as a string, which we then assign to our private variable lexeme */
  lexeme = parseInput();

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
  
  return "";
  
  // return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
  // This function will be called to write an error message to a file
  if (msg != "")
    cout << msg << endl;
  listingFile << "Error was found at line" << lineNum << pos
	      << ": Invalid character was found: " << lexeme << endl;
  debugFile << "Error was found at line" << lineNum << pos
	    << ": Invalid character was found: " << lexeme << endl;
  errors++;
//return;
}

string LexicalAnalyzer::getLine ()
{
  return line;
}

int LexicalAnalyzer::getLineNum()
{
  return lineNum;
}

string LexicalAnalyzer::parseInput ()
{
  string temp;
  string code = getLine();
   while (pos < code.length())
    {
      int state = 0;
      // read in characters one at a time, add to temp, evaluate new state
      while (state > -1 && state < 100)
        {
	  if (testing)
	    cout << ">> Current position: " << pos << endl;
          temp += code[pos];
          if (testing)
            cout << ">> CURRENT STATE: " << state << ", looking at " << code[pos] << endl;
          state = nextState(state, code[pos]);
          if (testing)
            cout << ">> TRANSITIONED TO STATE: " << state << endl;
          pos++;
        }
      if (testing)
        cout << ">> END STATE: " << state << endl;
      // if we need to back up...
      if (state < -1 || state == BU)
        {
          temp.erase(temp.length()-1, 1); // erase the last character
          pos--; // decrement position
        }
      // check that temp isn't empty or just whitespace, then print
      if (temp != "" && temp != " ")
	{
	  cout << '\t' << temp << endl; //<< '\t' << category(state) << endl;
	  break;
	}
    }
   return temp;
}

// this is also, for now, unchanged from our class activities
int LexicalAnalyzer::nextState (int currentState, char currentChar)
{
  int charColumn;
  // set col to appropriate value based on transition matrix
  if (isalpha(currentChar) && currentChar != 'c' && currentChar != 'a' && currentChar != 'd' && currentChar != 'r')
    charColumn = 0;
  
  else if (isdigit(currentChar))
    charColumn = 6;

  else
    switch (currentChar)
      {
      case 'c':
	charColumn = 1;
	break;
	
      case 'a':
	charColumn = 2;
	break;
	
      case 'd':
	charColumn = 3;
	break;
	
      case 'r':
	charColumn = 4;
	break;

      case '_':
	charColumn = 5;
	break;
	
      case '.':
	charColumn = 7;
	break;
	
      case '+':
	charColumn = 8;
	break;
	
      case '-':
	charColumn = 9;
	break;
	
      case '/':
	charColumn = 10;
	break;

      case '*':
	charColumn = 11;
	break;
	
      case '>':
	charColumn = 12;
	break;
      
      case '=':
	charColumn = 13;
	break;

      case '<':
	charColumn = 14;
	break;
      
      case '(':
	charColumn = 15;
	break;
	
      case ')':
	charColumn = 16;
	break;
	
      case '\'':
	charColumn = 17;
	break;
	
      case '"':
	charColumn = 18;
	break;
	
      case ' ':
	charColumn = 19;
	break;
      
      case '?':
	charColumn = 20;
	break;

      case '\0':
	return BU;

      default:
	return ER;
      }


int states[11][21] = {
/*      alpha      c        a        d        r        _       #    .       +        -        /        *        >        =         <        (        )        '        "        ws  ?*/
/*       0         1        2        3        4        5       6    7       8        9        10       11       12       13        14       15       16       17       18       19  20*/
/*      ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*0*/ {1,        2,       1,       1,       1,       ER,     5,   6,      4,       7,       DIV,     MULT,    8,       EQUALTO,  9,       LPAREN,  RPAREN,  QUOTE,   10,      GD, ER},
  /*1*/ {1,        1,       1,       1,       1,       1,      1,  -IDKEY, -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,   -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY, IDKEY },
  /*2*/ {1,        1,       3,       3,       1,       1,      1,  -IDKEY, -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,   -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY, IDKEY},
  /*3*/ {1,        1,       1,       3,       LISTOP,  1,      1,  -IDKEY, -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,   -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY,  -IDKEY, IDKEY},
  /*4*/ {-PLUS,   -PLUS,   -PLUS,   -PLUS,   -PLUS,   -PLUS,   5,   6,     -PLUS,   -PLUS,   -PLUS,   -PLUS,   -PLUS,   -PLUS,    -PLUS,   -PLUS,   -PLUS,   -PLUS,   -PLUS,   -PLUS, -PLUS},
  /*5*/ {-NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, 5,   6,     -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT,  -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT},
  /*6*/ {-NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, 6,  -NUMLIT, -NUMLIT, -NUMLIT,-NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT,  -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT, -NUMLIT},
  /*7*/ {-MINUS,  -MINUS,  -MINUS,  -MINUS,  -MINUS,  -MINUS,  5,   6,     -MINUS,  -MINUS,  -MINUS,  -MINUS,  -MINUS,  -MINUS,    MINUS,  -MINUS,  -MINUS,  -MINUS,  -MINUS,  -MINUS, -MINUS},
  /*8*/ {-GT,     -GT,     -GT,     -GT,     -GT,     -GT,    -GT, -GT,    -GT,     -GT,     -GT,     -GT,     -GT,      GTE, -GT,     -GT,     -GT,     -GT,     -GT,     -GT, -GT},
  /*9*/ {-LT,     -LT,     -LT,     -LT,     -LT,     -LT,    -LT, -LT,    -LT,     -LT,     -LT,     -LT,     -LT,      LTE, -LT,     -LT,     -LT,     -LT,     -LT,     -LT, -GT},
  /*10*/{10,       10,      10,      10,      10,      10,     10,  10,     10,      10,      10,      10,      10,      10,       10,      10,      10,      10,      STRLIT,  10, 10}};

//return the transition state table
 return states[currentState][charColumn];
}

string LexicalAnalyzer::category (int catState)
{
  if (catState == PLUS || catState == -PLUS)
    return "PLUS_T";
  else if (catState == MINUS || catState == -MINUS)
    return "MINUS_T";
  else if (catState == MULT || catState == -MULT)
    return "MULT_T";
  else if (catState == DIV || catState == -DIV)
    return "DIV_T";
  else if (catState == EQUALTO || catState == -EQUALTO)
    return "EQUALTO_T";
  else if (catState == GTE || catState == -GTE)
    return "GTE_T";
  else if (catState == LTE || catState == -LTE)
    return "LTE_T";
  else if (catState == GT || catState == -GT)
    return "GT_T";
  else if (catState == LT || catState == -LT)
    return "LT_T";
  else if (catState == LPAREN || catState == -LPAREN)
    return "LPAREN_T";
  else if (catState == RPAREN || catState == -RPAREN)
    return "RPAREN_T";
  else if (catState == QUOTE || catState == -QUOTE)
    return "QUOTE_T";
  else if (catState == LISTOP || catState == -LISTOP)
    return "LISTOP_T";
  else if (catState == IDKEY || catState == -IDKEY)
    return "IDKEY_T";
  else if (catState == NUMLIT || catState == -NUMLIT)
    return "NUMLIT_T";
  else if (catState == STRLIT || catState == -STRLIT)
    return "STRLIT_T";
  else if (catState == ER)
    return "ERROR_T";
}

token_type LexicalAnalyzer::Predicates ()
{
  //token_type taken from SyntacticalAnalyzer.cpp file
  
  /*This function handles the 5 predicates*/ 
  
  //Conditional: if the last character is an ? then check if it's valid 
  if (line.length()-1 == '?')
    {
      if ("number?" == lexeme)
	token = NUMBERP;
      else if ("list?" == lexeme)
	token = LISTP;
      else if ("zero?" == lexeme)
	token = ZEROP;
      else if ("null?" == lexeme)
	token = NULLP;
      else if ("string?" == lexeme)
	token = STRINGP;
      //return IDENT_T;
      //set to an error if none of these options
      else
	return ER;
    }
  //else
  //return;
}

