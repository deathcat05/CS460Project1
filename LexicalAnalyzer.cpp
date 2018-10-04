#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = { "IDENT_T","NUMLIT_T","STRLIT_T","LISTOP_T","CONS_T","IF_T",
                                "COND_T","ELSE_T","DISPLAY_T","NEWLINE_T","AND_T","OR_T",
                                "NOT_T","DEFINE_T","NUMBERP_T","LISTP_T","ZEROP_T","NULLP_T",
                                "STRINGP_T","PLUS_T","MINUS_T","DIV_T","MULT_T","MODULO_T",
                                "ROUND_T","EQUALTO_T","GT_T","LT_T","GTE_T","LTE_T","LPAREN_T",
                                "RPAREN_T","SQUOTE_T","ERROR_T","EOF_T" };
bool testing = false;

// notice the initializer list style used for input...This is how we
// deal with initializing a private ifstream variable.
LexicalAnalyzer::LexicalAnalyzer (char * filename): input(filename)
{
  // check if input file exists
  if (input.fail())
    {
      cerr << "File: " << filename << " not found.\n";
      exit (2);
    }

  pos = 0; // set pos to 0
  lineNum = 0; // set lineNum to 0

}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class


}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme in the input file and return
	// the token_type value associated with that lexeme

  /* So, this if condition is to determine whether we do or don't need to grab the
     next line and load it into our line variable.
     First, if the line is empty (which only happens with the very first call to
     GetToken() ) then get the first line and load into line variable.
     After that, the only other times we'll be loading up another line again is when
     pos becomes >= the length of the line - 1 (in other words, when we've incremented
     to the end/read all the tokens in our line). */
  if (line.empty() || pos >= line.length()-1)
    {
      getline (input, line);
      pos = 0; // everytime we get a new line, we need to reset our pos variable to 0
      lineNum++; // also, increment our lineNum variable (which starts at 0 initially)
      cout << lineNum << ".) " << line << endl; // output the line number and contents
    }

  /* Here is where we start parsing the line.  parseInput() wil return the lexeme it
     finds as a string, which we then assign to our private variable lexeme */
  lexeme = parseInput();

  /* somewhere in here we'll take the lexeme we found and process it to determine the
     type of token that it is, its string name, etc */
  
  return token; // not returning anything at the moment...
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.

  if (t == PLUS || t == -PLUS)
    return "PLUS_T";
  else if (t == MINUS || t == -MINUS)
    return "MINUS_T";
  else if (t == MULT || t == -MULT)
    return "MULT_T";
  else if (t == DIV || t == -DIV)
    return "DIV_T";
  else if (t == EQUALTO || t == -EQUALTO)
    return "EQUALTO_T";
  else if (t == GTE || t == -GTE)
    return "GTE_T";
  else if (t == LTE || t == -LTE)
    return "LTE_T";
  else if (t == GT || t == -GT)
    return "GT_T";
  else if (t == LT || t == -LT)
    return "LT_T";
  else if (t == LPAREN || t == -LPAREN)
    return "LPAREN_T";
  else if (t == RPAREN || t == -RPAREN)
    return "RPAREN_T";
  else if (t == QUOTE || t == -QUOTE)
    return "QUOTE_T";
  else if (t == LISTOP || t == -LISTOP)
    return "LISTOP_T";
  else if (t == IDKEY || t == -IDKEY)
    return "IDKEY_T";
  else if (t == NUMLIT || t == -NUMLIT)
    return "NUMLIT_T";
  else if (t == STRLIT || t == -STRLIT)
    return "STRLIT_T";
  else if (t == ER)
    return "ERROR_T";

}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}

string LexicalAnalyzer::getLine ()
{
  return line;
}

int LexicalAnalyzer::getLineNum()
{
  return lineNum;
}

/* not documenting this extensively just yet as a lot may change but this is basically
   what was used during our class activities to deal with those input types */
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
 
  // return the transition state value
  return states[currentState][charColumn];
}
