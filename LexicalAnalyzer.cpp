#include <iomanip>
#include <vector>
#include <cstdlib>
#include <fstream>
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

LexicalAnalyzer::~LexicalAnalyzer()
{
	// This function will complete the execution of the lexical analyzer class


}

token_type LexicalAnalyzer::GetToken()
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
  SetToken();

  /* somewhere in here we'll take the lexeme we found and process it to determine the
     type of token that it is, its string name, etc */
  
  return token; // not returning anything at the moment...
}

string LexicalAnalyzer::GetTokenName(token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.
	return "";
}

string LexicalAnalyzer::GetLexeme() const
{
	// This function will return the lexeme found by the most recent call to
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError(const string &msg)
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

  // original set of if/else statements
  /*
  else if (currentChar == 'c')
    charColumn = 1;
  else if (currentChar == 'a')
    charColumn = 2;
  else if (currentChar == 'd')
    charColumn = 3;
  else if (currentChar == 'r')
    charColumn = 4;
  else if (currentChar == '_')
    charColumn = 5;
  else if (isdigit(currentChar))
    charColumn = 6;
  else if (currentChar == '.')
    charColumn = 7;
  else if (currentChar == '+')
    charColumn = 8;
  else if (currentChar == '-')
    charColumn = 9;
  else if (currentChar == '/')
    charColumn = 10;
  else if (currentChar == '*')
    charColumn = 11;
  else if (currentChar == '>')
    charColumn = 12;
  else if (currentChar == '=')
    charColumn = 13;
  else if (currentChar == '<')
    charColumn = 14;
  else if (currentChar == '(')
    charColumn = 15;
  else if (currentChar == ')')
    charColumn = 16;
  else if (currentChar == '\'')
    charColumn = 17;
  else if (currentChar == '"')
    charColumn = 18;
  else if (currentChar == ' ')
    charColumn = 19;
  else if (currentChar =='?')
    charColumn = 20;
  else if (currentChar == '\0')
    return BU;
  else
    return ER;
  */

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

// also from class activities...
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

void LexicalAnalyzer::SetToken()
{
 	int LexLength = lexeme.length(); 
	if(token == IDKEY)
	{
		if(lexeme[LexLength -1] == '?')
		{
			Predicates();
		}
		else
		{

	 	FindKeyWord();
		}
	}

}

void LexicalAnalyzer::FindKeyWord()
{
	if(lexeme == "cons")
	{
		token = CONS;
	}
	else if(lexeme == "if")
	{
		token = IF;
	}
	else if(lexeme == "cond")
	{
		token  = COND;
	}
	else if(lexeme == "else")
	{
		token = ELSE;
	}
	else if(lexeme == "display")
	{
		token = DISPLAY;
	}
	else if(lexeme == "newline")
	{
		token = NEWLINE;
	}
	else if(lexeme == "and")
	{
		token  = AND;
	
	}
	else if (lexeme == "or")
	{
		token = OR;
	}
	else if(lexeme == "not")
	{
		token = NOT;
	}
	else if(lexeme == "define")
	{
		token = DEFINE;
	}
	else if (lexeme == "modulo")
	{
		token = MODULO; 
	}
	else if(lexeme = "Round")
	{
		token = ROUND; 
	}
	else 
		token = ER; 
	return token; 
}

