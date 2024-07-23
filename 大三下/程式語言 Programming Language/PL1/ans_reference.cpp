# include <stdio.h>
# include <string>
# include <string.h>
# include <vector>
# include <math.h>
using namespace std;

struct ID_Table {
  string identifier ;
  int interger ;
  float num_float ;
  int type ;
};

struct Token_inf {
  string token ;
  int type ;
};

bool gEND = false ;
int gcommand_type = -1 ;
int gerror_type = -1 ;
string gerror_token = "" ;
vector < Token_inf > gtoken_string ;
vector < ID_Table > gidentifier_table ;

class Scanner_
{
  friend class Paser; // it means Paser can ues Scanner_'s value or functions
  private:
  string mlast_token ; // we can peek this token
  int mlast_token_type ;
  char mlast_char ;
  
  bool IsLegalChar( char ch ){
    if ( IsIdentifier( ch ) || IsDot( ch ) || IsNumber( ch ) || IsSeparator( ch ) )
      return true ;
    return false ;
  } // IsLegalChar()
  
  bool IsIdentifier( char ch ){
    if ( ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90 || ch == 95 ) return true ;
    else return false ; 
  } // IsIdentifier()
  
  bool IsDot( char ch ){
    if ( ch == 46 ) return true ;
    else return false ;
  } // IsDot()
  
  bool IsNumber( char ch ){
    if ( ch >= 48 && ch <= 57 ) return true ;
    else return false ; 
  } // IsNumber()
  
  bool IsSingleSeparator( char ch ){
    if ( ch == ';' || ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '(' || ch == ')' )
      return true ;
    else return false ; 
  } // IsSingleSeparator()
  
  bool IsSeparator( char ch ){
    if ( ch == ';' || ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
         ch == '<' || ch == '>' || ch == ':' || ch == '(' || ch == ')' || IsWhiteSpace( ch ) )
      return true ;
    else return false ; 
  } // IsSeparator()
  
  bool IsWhiteSpace( char ch ){
    if ( ch == ' ' || ch == '\n' || ch == '\t' ) return true ;
    else return false ; 
  } // IsWhiteSpace()
  
  void Reset(){
    mlast_token.clear() ;
    mlast_token_type = -1 ;
  } // Reset()

  public:
  Scanner_(){
    Reset() ;
  } // Scanner_()
        
  ~Scanner_(){
    Reset() ;
  } // ~Scanner_()
  
  void ClearThisLine(){
    Reset() ;
    char ch ;
    if ( mlast_char != '\0' ){
      ch = mlast_char ;
      mlast_char = '\0' ;
    } // if 
    else scanf( "%c", &ch ) ;

    while ( ch != '\n' ) scanf( "%c", &ch ) ;
  } // ClearThisLine()
  
  bool PeekToken( string &token, int &type ) {
    if ( ! mlast_token.empty() ){
      token = mlast_token ;
      type = mlast_token_type ;
      return true ;
    } // if
    
    if ( GetToken( token, type ) ){
      mlast_token = token ;
      mlast_token_type = type ;
      return true ;
    } // if 
    else return false ;
  } // PeekToken()
  
  bool GetToken( string &token, int &type ){
    if ( ! mlast_token.empty() ){
      token = mlast_token ;
      mlast_token.clear() ;
      return true ;
    } // if
    // //////////////////////////////////////////////////////////////// Get The First Char
    char ch = '\0' ;
    if ( mlast_char != '\0' ){
      ch = mlast_char ;
      mlast_char = '\0' ;
    } // if
    else scanf( "%c", &ch ) ;

    if ( ! IsLegalChar( ch ) ){
      gerror_type = 0 ;
      gerror_token = ch ;
      return false;
    } // if
    // //////////////////////////////////////////////////////////////// Skip White Space
    while ( IsWhiteSpace( ch ) ) scanf( "%c", &ch ) ;
    if ( ! IsLegalChar( ch ) ){
      gerror_type = 0 ;
      gerror_token = ch ;
      return false;
    } // if

    if ( IsSingleSeparator( ch ) ){
      token = ch ;
      type = 0 ;
      return true ;
    } // if
    else if ( IsSeparator( ch ) ){
      if ( ch == ':' ){
        char peek_char ;
        scanf( "%c", &peek_char ) ;
        if ( peek_char == '=' ){
          token = ch ;
          token = token + peek_char ;
          type = 0 ;
          return true ;
        } // if
        else{
          mlast_char = peek_char ; // 下回合用的 
          gerror_type = 0 ;
          gerror_token = ch ;
          return false;
        } // else
      } // if
      else if ( ch == '/' ){
        char peek_char ;
        scanf( "%c", &peek_char ) ;
        
        if ( ! IsLegalChar( peek_char ) ){
          gerror_type = 0 ;
          gerror_token = peek_char ;
          return false;
        } // if
        
        if ( peek_char == '/' ){
          ClearThisLine() ;
          return GetToken( token, type ) ;
        } // if
        else{
          mlast_char = peek_char ;
          token = ch ;
          type = 0 ;
          return true ;
        } // else
      } // else if
      else if ( ch == '>' ){
        char peek_char ;
        scanf( "%c", &peek_char ) ;
        if ( ! IsLegalChar( peek_char ) ){
          gerror_type = 0 ;
          gerror_token = peek_char ;
          return false;
        } // if
        
        if ( peek_char == '=' ){
          token = ch ;
          token = token + peek_char ;
          type = 0 ;
          return true ;
        } // if
        else{
          mlast_char = peek_char ;
          token = ch ;
          type = 0 ;
          return true ;
        } // else
      } // else if
      else if ( ch == '<' ){
        char peek_char ;
        scanf( "%c", &peek_char ) ;
        
        if ( ! IsLegalChar( peek_char ) ){
          gerror_type = 0 ;
          gerror_token = peek_char ;
          return false;
        } // if
      
        if ( peek_char == '>' || peek_char == '=' ){
          token = ch ;
          token = token + peek_char ;
          type = 0 ;
          return true ;
        } // if
        else{
          mlast_char = peek_char ;
          token = ch ;
          type = 0 ;
          return true ;
        } // else
      } // else if
    } // else if 
    else{
      if ( IsIdentifier( ch ) ){
        type = 1 ;
        token = ch ;
        scanf( "%c", &ch ) ;
        
        if ( ! IsLegalChar( ch ) ){
          gerror_type = 0 ;
          gerror_token = ch ;
          return false;
        } // if
        
        while ( ! IsSeparator( ch ) && ! IsDot( ch ) ){
          if ( ! IsLegalChar( ch ) ){
            gerror_type = 0 ;
            gerror_token = ch ;
            return false;
          } // if

          token = token + ch ;
          scanf( "%c", &ch ) ;
        } // while
     
        mlast_char = ch ;
        return true ;
      } // if
      else if ( IsNumber( ch ) || IsDot( ch ) ){
        int dot = 0 ;
        if ( IsDot( ch ) ) dot++ ;
        token = ch ;
        scanf( "%c", &ch ) ;
        if ( IsDot( ch ) ) dot++ ;
        if ( ! IsLegalChar( ch ) ){
          gerror_type = 0 ;
          gerror_token = ch ;
          return false;
        } // if
        
        while ( ! IsSeparator( ch ) && dot <= 1 && ! IsIdentifier( ch ) ){
          token = token + ch ;
          if ( ! IsLegalChar( ch ) ){
            gerror_type = 0 ;
            gerror_token = ch ;
            return false;
          } // if

          scanf( "%c", &ch ) ;
          if ( IsDot( ch ) ) dot++ ;
        } // while
    
        if ( dot > 0 ) type = 3 ;
        else type = 2 ;
        // 來到這的 ch 一定是 Separator !!!!!!!!!
        
        mlast_char = ch ; // 下次再來
        return true ;
      } // else if
    } // else
    
    return false ;
  } // GetToken()
  
};

Scanner_ *gscanner = new Scanner_() ;

int CharToNumberOrDot( char ch ){
  if ( ch == '0' ) return 0 ;
  else if ( ch == '1' ) return 1 ;
  else if ( ch == '2' ) return 2 ;
  else if ( ch == '3' ) return 3 ;
  else if ( ch == '4' ) return 4 ;
  else if ( ch == '5' ) return 5 ;
  else if ( ch == '6' ) return 6 ;
  else if ( ch == '7' ) return 7 ;
  else if ( ch == '8' ) return 8 ;
  else if ( ch == '9' ) return 9 ;
  else return -1 ;
} // CharToNumberOrDot()
  
int TokenToInterger( string token ){
  int sum = 0 ;
  for ( int n = token.size() - 1, timer = 1 ; n > -1 ; n--, timer = timer * 10 )
    sum = sum + ( CharToNumberOrDot( token[ n ] ) ) * timer ;
  return sum ;
} // TokenToInterger()
  
float TokenToFloat( string token ){
  float sum = 0 ;
  int dot ;
  bool found = false ;
  for ( dot = 0 ; dot < token.size() && ! found ; dot++ ){
    if ( token[dot] == '.' ){
      found = true ;
      dot-- ;
    } // if
  } // for
  
  if ( token.size() == 1 ) return 0 ;
  else if ( dot == 0 ){
    float timer = 0.1 ;
    for ( int n = dot + 1 ; n < token.size() ; n++, timer = timer / 10 )
      sum = sum + ( CharToNumberOrDot( token[ n ] ) ) * timer ;
    return sum ;
  } // else if
  else if ( dot == token.size() - 1 ){
    string temp ;
    for ( int n = 0 ; n < dot ; n++ )
      temp = temp + token[ n ] ;
    float sum = TokenToInterger( temp ) ;
    return sum ;
  } // else if
  else{
    string temp ;
    for ( int n = 0 ; n < dot ; n++ )
      temp = temp + token[ n ] ;
    float sum = TokenToInterger( temp ) ;
    float timer = 0.1 ;
    for ( int n = dot + 1 ; n < token.size() ; n++, timer = timer / 10 )
      sum = sum + ( CharToNumberOrDot( token[ n ] ) ) * timer ;
    return sum ;
  } // else
} // TokenToFloat()

class Paser
{
  private:
  string mtoken ;
  int mtype ;
  // command type == 0 == Quit
  // command type == 1 == AssignmentExp
  // command type == 2 == ArithmeticExp
  // command type == 3 == BooleanExp
  // type == 0 == separator
  // type == 1 == identifier
  // type == 2 == interger
  // type == 3 == num_float
  bool ArithExp(){
    if ( Factor() ){
      if ( ! gscanner->PeekToken( mtoken, mtype ) ) return false ;
      
      while ( mtoken == "+" || mtoken == "-" || mtoken == "*" || mtoken == "/" ){
        if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
        else{
          Token_inf temp ;
          temp.token = mtoken ;
          temp.type = mtype ;
          gtoken_string.push_back( temp ) ;
        } // else

        if ( Factor() ){
          if ( ! gscanner->PeekToken( mtoken, mtype ) ){
            gerror_type = 0 ;
            gerror_token = mtoken ;
            return false ;
          } // if
        } // if
        else return false ;
      } // while

      return true ;
    } // if

    else return false ;
  } // ArithExp()
  
  bool Factor(){
    if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
    else{
      Token_inf temp ;
      temp.token = mtoken ;
      temp.type = mtype ;
      gtoken_string.push_back( temp ) ;
    } // else
    
    if ( mtype == 1 ){
      bool found = false ;
      for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ ){
        if ( mtoken == gidentifier_table[n].identifier ) found = true ;
      } // for
        
      if ( ! found ){
        gerror_type = 2 ;
        gerror_token =  mtoken ;
        return false ;
      } // if

      if ( gtoken_string.size() > 2 ){
        bool found = false ;
        for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ ){
          if ( gidentifier_table[n].identifier == mtoken ){
            if ( gidentifier_table[n].type == 2 ){
              int maybezero = gidentifier_table[n].interger ;
              if ( maybezero == 0 && gtoken_string[ gtoken_string.size() - 2 ].token == "/" ){
                gerror_type = 3 ; 
                return false ;
              } // if
            } // if
            else if ( gidentifier_table[n].type == 2 ){
              float maybezero = gidentifier_table[n].num_float ;
              if ( maybezero == 0 && gtoken_string[ gtoken_string.size() - 2 ].token == "/" ){
                gerror_type = 3 ; 
                return false ;
              } // if
            } // if
          } // if
        } // for
      } // if

      return true ;
    } // if 
    else if ( mtype == 0 ){
      if ( mtoken == "+" || mtoken == "-" ){
        if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
        else{
          Token_inf temp ;
          temp.token = mtoken ;
          temp.type = mtype ;
          gtoken_string.push_back( temp ) ;
        } // else

        if ( mtype == 2 || mtype == 3 ){
          if ( gtoken_string.size() > 2 ){
            if ( mtype == 2 ){
              int maybezero = TokenToInterger( mtoken ) ;
              if ( maybezero == 0 && gtoken_string[ gtoken_string.size() - 3 ].token == "/" ){
                gerror_type = 3 ; 
                return false ;
              } // if
            } // if
            else if ( mtype == 3 ){
              int maybezero = TokenToFloat( mtoken ) ;
              if ( maybezero == 0 && gtoken_string[ gtoken_string.size() - 3 ].token == "/" ){
                gerror_type = 3 ; 
                return false ;
              } // if
            } // else if
          } // if

          return true ;
        } // if
        else{
          gerror_type = 1 ;
          gerror_token = mtoken ;
          return false ;
        } // else
      } // if
      else if ( mtoken == "(" ){
        if ( ArithExp() ){
          if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
          else{
            Token_inf temp ;
            temp.token = mtoken ;
            temp.type = mtype ;
            gtoken_string.push_back( temp ) ;
          } // else
          
          if ( mtoken == ")" ) return true ;
          else{
            gerror_type = 1 ;
            gerror_token = mtoken ;
            return false ;
          } // else
        } // if
        else return false ;
      } // else if
      else{
        gerror_type = 1 ;
        gerror_token = mtoken ;
        return false ;
      } // else
    } // else if
    else if ( mtype == 2 || mtype == 3 ){
      if ( gtoken_string.size() > 2 ){
        if ( mtype == 2 ){
          int maybezero = TokenToInterger( mtoken ) ;
          if ( maybezero == 0 && gtoken_string[ gtoken_string.size() - 2 ].token == "/" ){
            gerror_type = 3 ; 
            return false ;
          } // if
        } // if
        else if ( mtype == 3 ){
          int maybezero = TokenToFloat( mtoken ) ;
          if ( maybezero == 0 && gtoken_string[ gtoken_string.size() - 2 ].token == "/" ){
            gerror_type = 3 ; 
            return false ;
          } // if
        } // else if
      } // if

      return true ;
    } // else if 
    
    return false ;
  } // Factor()

  bool IDStartExp(){
    if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
    else{
      Token_inf temp ;
      temp.token = mtoken ;
      temp.type = mtype ;
      gtoken_string.push_back( temp ) ;
    } // else

    string peektoken ;
    if ( ! gscanner->PeekToken( peektoken, mtype ) ) return false ;

    if ( peektoken == ":=" ) {
      if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
      else{
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
      } // else

      if ( ArithExp() ){
        if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
        else{
          Token_inf temp ;
          temp.token = mtoken ;
          temp.type = mtype ;
          gtoken_string.push_back( temp ) ;
        } // else
          
        if ( mtoken == ";" ){
          gcommand_type = 1 ; 
          return true ;
        } // if
        else{
          gerror_type = 1 ;
          gerror_token = mtoken ;
          return false ;
        } // else
      } // if
      else return false ;
    } // if
    else if ( peektoken == "+" || peektoken == "-" || peektoken == "*" || peektoken == "/" ){
      bool found = false ;
      for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ )
        if ( mtoken == gidentifier_table[n].identifier ) found = true ;
        
      if ( ! found ){
        gerror_type = 2 ;
        gerror_token =  mtoken ;
        return false ;
      } // if

      if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
      else{
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
      } // else

      if ( ArithExp() ){
        if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
        else{
          Token_inf temp ;
          temp.token = mtoken ;
          temp.type = mtype ;
          gtoken_string.push_back( temp ) ;
        } // else
            
        if ( mtoken == "=" || mtoken == "<>" || 
             mtoken == ">" || mtoken == "<" || 
             mtoken == ">=" || mtoken == "<=" ){
          if ( ArithExp() ){
            if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
            else{
              Token_inf temp ;
              temp.token = mtoken ;
              temp.type = mtype ;
              gtoken_string.push_back( temp ) ;
            } // else
                
            if ( mtoken == ";" ){
              gcommand_type = 3 ; 
              return true ;
            } // if
            else{
              gerror_type = 1 ;
              gerror_token = mtoken ;
              return false ;
            } // else
          } // if
          else return false ;
        } // if
        else if ( mtoken == ";" ){
          gcommand_type = 2 ; 
          return true ;
        } // else if
        else{
          gerror_type = 1 ;
          gerror_token = mtoken ;
          return false ;
        } // else
      } // if
      else return false ;
    } // else if 
    else if ( peektoken == "=" || peektoken == "<>" || 
              peektoken == ">" || peektoken == "<" || 
              peektoken == ">=" || peektoken == "<=" ){
      bool found = false ;
      for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ )
        if ( mtoken == gidentifier_table[n].identifier ) found = true ;
        
      if ( ! found ){
        gerror_type = 2 ;
        gerror_token =  mtoken ;
        return false ;
      } // if

      if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
      else{
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
      } // else

      if ( ArithExp() ){
        if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
        else{
          Token_inf temp ;
          temp.token = mtoken ;
          temp.type = mtype ;
          gtoken_string.push_back( temp ) ;
        } // else
    
        if ( mtoken == ";" ){
          gcommand_type = 3 ;
          return true ;
        } // if
        else{
          gerror_type = 1 ;
          gerror_token = mtoken ;
          return false ;
        } // else
      } // if
      else return false ;
    } // else if
    else if ( peektoken == ";" ){
      bool found = false ;
      for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ )
        if ( mtoken == gidentifier_table[n].identifier ) found = true ;
      
      if ( ! found ){
        gerror_type = 2 ;
        gerror_token =  mtoken ;
        return false ;
      } // if

      if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
      else{
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
      } // else

      gcommand_type = 2 ;
      return true ;
    }
    // else if
    else{
      if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
      else{
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
      } // else

      gerror_type = 1 ;
      gerror_token = mtoken ;
      return false ;
    } // else
  } // IDStartExp()

  bool NotIDStartExp(){
    if ( ArithExp() ){
      if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
      else{
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
      } // else
      
      if ( mtoken == "=" || mtoken == "<>" || 
           mtoken == ">" || mtoken == "<" || 
           mtoken == ">=" || mtoken == "<=" ){
        if ( ArithExp() ){
          if ( ! gscanner->GetToken( mtoken, mtype ) ) return false ;
          else{
            Token_inf temp ;
            temp.token = mtoken ;
            temp.type = mtype ;
            gtoken_string.push_back( temp ) ;
          } // else
                
          if ( mtoken == ";" ){
            gcommand_type = 3 ;
            return true ;
          } // if
          else{
            gerror_type = 1 ;
            gerror_token = mtoken ;
            return false ;
          } // else
        } // if
        else return false ;
      } // if
      else if ( mtoken == ";" ){
        gcommand_type = 2 ;
        return true ;
      } // else if
      else{
        gerror_type = 1 ;
        gerror_token = mtoken ;
        return false ;
      } // else
    } // if
    else return false ;
  } // NotIDStartExp()

  void Reset(){
    mtype = -1 ;
    mtoken.clear() ;
  } // Reset()
  
  public:
  Paser(){
    Reset() ;
  } // Paser()
  
  ~Paser(){
    Reset() ;
  } // ~Paser()

  bool Command(){
    if ( ! gscanner->PeekToken( mtoken, mtype ) ){
      if ( mtoken == "quit" ){
        gEND = true ;
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        gtoken_string.push_back( temp ) ;
        return true ;
        // 記錄情況 quit@$#%  
      } // if

      return false ;
    } // if
    
    
    if ( mtoken == "quit" ){
      if ( ! gscanner->GetToken( mtoken, mtype ) ) {
        printf("%s\n", mtoken.c_str()) ;
        return false ;
      }
      else
      {
        Token_inf temp ;
        temp.token = mtoken ;
        temp.type = mtype ;
        
        gtoken_string.push_back( temp ) ;
      } // else
      
      gcommand_type = 0 ; 
      gEND = true ; 
      return true ;
    } // if
    else if ( mtype == 1 ){
      if ( IDStartExp() ) return true ;
      else return false ;
    } // else if
    else
    {
      if ( NotIDStartExp() ) return true ;
      else return false ;
    } // else
  } // Command()
};

class Eval
{
  private:
  struct Token_string{
    string separator;
    string identifier;
    int interger;
    float num_float;
    int type ;
    Token_string *next ;
  };

  Token_string *mtoken_ptr ;
  
  void BuildTokenString(){
    Token_string *curr_ptr ;
    for ( int n = 0 ; n < gtoken_string.size() ; n++ ){ 
      Token_string *node = new Token_string ;
      if ( gtoken_string[n].type == 0 ){
        node->separator = gtoken_string[n].token ;
        node->identifier = "" ;
        node->interger = -99999 ;
        node->num_float = -99999 ;
        node->type = gtoken_string[n].type ;
        node->next = NULL ;
      } // if
      else if ( gtoken_string[n].type == 1 ){
        node->separator = "" ;
        node->identifier = gtoken_string[n].token ;
        node->interger = -99999 ;
        node->num_float = -99999 ;
        node->type = gtoken_string[n].type ;
        node->next = NULL ;
      } // else if
      else if ( gtoken_string[n].type == 2 ){
        node->separator = "" ;
        node->identifier = "" ;
        node->interger = TokenToInterger( gtoken_string[n].token ) ;
        node->num_float = -99999 ;
        node->type = gtoken_string[n].type ;
        node->next = NULL ;
      } // else if
      else if ( gtoken_string[n].type == 3 ){
        node->separator = "" ;
        node->identifier = "" ;
        node->interger = -99999 ;
        node->num_float = TokenToFloat( gtoken_string[n].token ) ;
        node->type = gtoken_string[n].type ;
        node->next = NULL ;
      } // else if

      if ( mtoken_ptr == NULL ){
        mtoken_ptr = node ;
        curr_ptr = mtoken_ptr ;
      } // if
      else{
        curr_ptr->next = node ;
        curr_ptr = curr_ptr->next ;
      } // else
    } // for
  } // BuildTokenString()

  void DelSign(){
    Token_string *curr_ptr = mtoken_ptr ;  
    if ( curr_ptr != NULL ){
      if  ( curr_ptr->separator == "+" ){
        if ( curr_ptr->next != NULL ){
          if ( curr_ptr->next->type == 2 || curr_ptr->next->type == 3 ){
            curr_ptr = curr_ptr->next ;
            mtoken_ptr = curr_ptr ;
          } // if 
        } // if
      } // if
      else if ( curr_ptr->separator == "-" ){
        if ( curr_ptr->next != NULL ){
          if ( curr_ptr->next->type == 2 ){
            curr_ptr = curr_ptr->next ;
            mtoken_ptr = curr_ptr ;
            curr_ptr->interger = curr_ptr->interger * -1 ;
          } // if
          else if ( curr_ptr->next->type == 3 ){
            curr_ptr = curr_ptr->next ;
            mtoken_ptr = curr_ptr ;
            curr_ptr->num_float = curr_ptr->num_float * -1 ;
          } // else if
        } // if          
      } // else if
    } // if
      
    while ( curr_ptr != NULL ){
      if ( curr_ptr->separator != ")" &&  curr_ptr->type == 0 ){
        if ( curr_ptr->next != NULL ){
          if ( curr_ptr->next->separator == "+"  ){
            if ( curr_ptr->next->next != NULL ){
              if ( curr_ptr->next->next->type == 2 ){
                curr_ptr->next->type = 2 ;
                curr_ptr->next->separator = "" ;
                curr_ptr->next->interger = curr_ptr->next->next->interger ;
                curr_ptr->next->next = curr_ptr->next->next->next ;
              } // if
              else if ( curr_ptr->next->next->type == 3  ){
                curr_ptr->next->type = 3 ;
                curr_ptr->next->separator = "" ;
                curr_ptr->next->num_float = curr_ptr->next->next->num_float ;
                curr_ptr->next->next = curr_ptr->next->next->next ;                    
              } // else if 
            } // if
          } // if
          else if ( curr_ptr->next->separator == "-" ){
            if ( curr_ptr->next->next != NULL ){
              if ( curr_ptr->next->next->type == 2 ){
                curr_ptr->next->type = 2 ;
                curr_ptr->next->separator = "" ;
                curr_ptr->next->interger = curr_ptr->next->next->interger * -1 ;
                curr_ptr->next->next = curr_ptr->next->next->next ;
              } // if
              else if ( curr_ptr->next->next->type == 3  ){
                curr_ptr->next->type = 3 ;
                curr_ptr->next->separator = "" ;
                curr_ptr->next->num_float = curr_ptr->next->next->num_float * -1 ;
                curr_ptr->next->next = curr_ptr->next->next->next ;                    
              } // else if 
            } // if
          } // else if
        } // if
      } // if

      curr_ptr = curr_ptr->next ;
    } // while
  } // DelSign()
  
  void DelID(){
    Token_string *curr_ptr = mtoken_ptr ;
    if ( curr_ptr != NULL ){
      if  ( curr_ptr->type == 1 ){
        if ( curr_ptr->next != NULL ){
          if ( curr_ptr->next->type == 0 && curr_ptr->next->separator == ":=" )
            curr_ptr = curr_ptr->next->next ;
        } // if
      } // if
    } // if
    
    while ( curr_ptr != NULL ){
      if ( curr_ptr->type == 1 ){
        bool found = false ;
        for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ ){
          if ( curr_ptr->identifier == gidentifier_table[n].identifier ){
            if ( gidentifier_table[n].type == 2 ){
              curr_ptr->type = 2 ;
              curr_ptr->identifier = "" ;
              curr_ptr->interger = gidentifier_table[n].interger ;
              found = true ;
            } // if
            else if ( gidentifier_table[n].type == 3 ){
              curr_ptr->type = 3 ;
              curr_ptr->identifier = "" ;
              curr_ptr->num_float = gidentifier_table[n].num_float ;
              found = true ;
            } // else if
          } // if 
        } // for
      } // if
 
      curr_ptr = curr_ptr->next ;
    } // while
    

  } // DelID()
  
  void DelParen(){
    Token_string *curr_ptr = mtoken_ptr ;
    while ( curr_ptr != NULL ){
      if ( curr_ptr->type == 0 && curr_ptr->separator == "(" )
        MergeParen( curr_ptr ) ;

      curr_ptr = curr_ptr->next ;
    } // while
  } // DelParen()
  
  void MergeParen( Token_string *curr_ptr )
  {
    Token_string *leftparen = curr_ptr ;
    curr_ptr = curr_ptr->next ;
    while ( curr_ptr->separator != ")" ){
      if ( curr_ptr->type == 0 && curr_ptr->separator == "(" )
        MergeParen( curr_ptr ) ;

      curr_ptr = curr_ptr->next ;
    } // while
    
    MultiOrDivForParen( leftparen->next ) ;
    AddOrSubForParen( leftparen->next ) ;
    if ( leftparen->next->type == 2 ){
      leftparen->type = 2 ;
      leftparen->separator = "" ;
      leftparen->interger = leftparen->next->interger ;
      leftparen->next = leftparen->next->next->next ;
    } // if
    else if ( leftparen->next->type == 3 ){
      leftparen->type = 3 ;
      leftparen->separator = "" ;
      leftparen->num_float = leftparen->next->num_float ;
      leftparen->next = leftparen->next->next->next ;
    } // else if
  } // MergeParen()
  
  void AddOrSubForParen( Token_string *curr_ptr ){
    while ( curr_ptr->type != 0 && curr_ptr->separator != ")" ){
      while ( ( curr_ptr->type == 2 || curr_ptr->type == 3 ) && curr_ptr->next->type == 0 && 
              ( curr_ptr->next->separator == "+" || curr_ptr->next->separator == "-" ) )
      {
        if ( curr_ptr->type == 2 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "+" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger + curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger + curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "-" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger - curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger - curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // else if
          } // if
        } // if
        else if ( curr_ptr->type == 3 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "+" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float + curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float + curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "-" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float - curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float - curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // else if
          } // if
        } // else if
      } // while
      
      curr_ptr = curr_ptr->next ;
    } // while
  } // AddOrSubForParen()
  
  void AddOrSub(){
    Token_string *curr_ptr = mtoken_ptr ;
    while ( curr_ptr != NULL ){
      while ( ( curr_ptr->type == 2 || curr_ptr->type == 3 ) && curr_ptr->next->type == 0 && 
              ( curr_ptr->next->separator == "+" || curr_ptr->next->separator == "-" ) ){
        if ( curr_ptr->type == 2 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "+" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger + curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger + curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "-" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger - curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger - curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // else if
          } // if
        } // if
        else if ( curr_ptr->type == 3 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "+" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float + curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float + curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "-" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float - curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float - curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // else if
          } // if
        } // else if
      } // while
      
      curr_ptr = curr_ptr->next ;
    } // while
  } // AddOrSub()

  void MultiOrDivForParen( Token_string *curr_ptr ){
    while ( curr_ptr->separator != ")" ){
      while ( ( curr_ptr->type == 2 || curr_ptr->type == 3 ) && curr_ptr->next->type == 0 && 
              ( curr_ptr->next->separator == "*" || curr_ptr->next->separator == "/" ) ){
        if ( curr_ptr->type == 2 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "*" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger * curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger * curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "/" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger / curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger / curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // else if
          } // if
        } // if
        else if ( curr_ptr->type == 3 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "*" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float * curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float * curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "/" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float / curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float / curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // else if
          } // if
        } // else if
      } // while
      
      curr_ptr = curr_ptr->next ;
    } // while
  } // MultiOrDivForParen()

  bool MultiOrDiv(){
    Token_string *curr_ptr = mtoken_ptr ;
    while ( curr_ptr != NULL ){
      while ( ( curr_ptr->type == 2 || curr_ptr->type == 3 ) && curr_ptr->next->type == 0 && 
              ( curr_ptr->next->separator == "*" || curr_ptr->next->separator == "/" ) ){
        if ( curr_ptr->type == 2 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "*" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->interger = curr_ptr->interger * curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->interger * curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "/" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  if ( curr_ptr->next->next->interger == 0 ) return false ;
                  curr_ptr->interger = curr_ptr->interger / curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  if ( curr_ptr->next->next->num_float == 0 ) return false ;
                  curr_ptr->num_float = curr_ptr->interger / curr_ptr->next->next->num_float ;
                  curr_ptr->type = 3 ;
                  curr_ptr->interger = -99999 ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if 
              } // if
            } // else if
          } // if
        } // if
        else if ( curr_ptr->type == 3 ){
          if ( curr_ptr->next != NULL ){
            if ( curr_ptr->next->separator == "*" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  curr_ptr->num_float = curr_ptr->num_float * curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  curr_ptr->num_float = curr_ptr->num_float * curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // if
            else if ( curr_ptr->next->separator == "/" && curr_ptr->next->type == 0 ){
              if ( curr_ptr->next->next != NULL ){
                if ( curr_ptr->next->next->type == 2 ){
                  if ( curr_ptr->next->next->interger == 0 ) return false ;
                  curr_ptr->num_float = curr_ptr->num_float / curr_ptr->next->next->interger ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // if
                else if ( curr_ptr->next->next->type == 3 ){
                  if ( curr_ptr->next->next->num_float == 0 ) return false ;
                  curr_ptr->num_float = curr_ptr->num_float / curr_ptr->next->next->num_float ;
                  curr_ptr->next = curr_ptr->next->next->next ;
                } // else if 
              } // if
            } // else if
          } // if
        } // else if
      } // while
      
      curr_ptr = curr_ptr->next ;
    } // while
    
    return true ;
  } // MultiOrDiv()

  void PrettyPrint(){
    Token_string *curr_ptr = mtoken_ptr ;
    while ( curr_ptr != NULL ){
      if ( curr_ptr->type == 0 )
        printf( "[%s][%d]\n", curr_ptr->separator.c_str(), curr_ptr->type ) ;
      else if ( curr_ptr->type == 1 )
        printf( "[%s][%d]\n", curr_ptr->identifier.c_str(), curr_ptr->type ) ;
      else if ( curr_ptr->type == 2 )
        printf( "[%d][%d]\n", curr_ptr->interger, curr_ptr->type ) ;
      else if ( curr_ptr->type == 3 )
        printf( "[%f][%d]\n", curr_ptr->num_float, curr_ptr->type ) ;
      curr_ptr = curr_ptr->next ;
    } // while
  } // PrettyPrint()
  
  void AssignmentExp(){
    ID_Table id_talbe ;
    if ( mtoken_ptr->next->next->type == 2 ){
      id_talbe.identifier = mtoken_ptr->identifier ;
      id_talbe.interger = mtoken_ptr->next->next->interger ;
      id_talbe.type = 2 ;
      bool found = false ;
      for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ ){
        if ( gidentifier_table[n].identifier == id_talbe.identifier ){
          found = true ;
          gidentifier_table[n].interger = id_talbe.interger ;
          gidentifier_table[n].type = 2 ;
        } // if
      } // for

      if ( ! found ) gidentifier_table.push_back( id_talbe ) ;
    } // if
    else if ( mtoken_ptr->next->next->type == 3 ){
      id_talbe.identifier = mtoken_ptr->identifier ;
      id_talbe.num_float = mtoken_ptr->next->next->num_float ;
      id_talbe.type = 3 ;
      bool found = false ;
      for ( int n = 0 ; n < gidentifier_table.size() && ! found ; n++ ){
        if ( gidentifier_table[n].identifier == id_talbe.identifier ){
          found = true ;
          gidentifier_table[n].num_float = id_talbe.num_float ;
          gidentifier_table[n].type = 3 ;
        } // if
      } // for
      
      if ( ! found ) gidentifier_table.push_back( id_talbe ) ;
    } // else if
    
    mtoken_ptr = mtoken_ptr->next->next ;
    ArithmeticExp() ;
  } // AssignmentExp()

  void ArithmeticExp(){
    if ( mtoken_ptr->type == 2 )
      printf( "%d\n", mtoken_ptr->interger ) ;
    else if ( mtoken_ptr->type == 3 ){
      char buffer [50];
      sprintf( buffer, "%.4f", mtoken_ptr->num_float ) ;    
      if ( buffer[ strlen( buffer ) - 1 ] >= 53 && buffer[ strlen( buffer ) - 1 ] <= 57 ){
        float x = mtoken_ptr->num_float + 0.0005 ;
        sprintf( buffer, "%.3f", x ) ;         
        printf( "%s\n", buffer ) ;
      } // if
      else{
        sprintf( buffer, "%.3f", mtoken_ptr->num_float ) ;
        printf( "%s\n", buffer ) ;
      } // else
    } // else if
  } // ArithmeticExp()

  void BooleanExp(){
    Token_string *bool_operator = mtoken_ptr->next ;
    if ( bool_operator->separator == "=" ){
      if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "true\n" ) ;
        else 
          printf( "false\n" ) ;
      } // if
      else if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 2 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->interger  ) <= 0.0001 )
          printf( "true\n" ) ;
        else 
          printf( "false\n" ) ;
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->interger - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "true\n" ) ;
        else 
          printf( "false\n" ) ;
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 2 ){
        if ( mtoken_ptr->interger == mtoken_ptr->next->next->interger )
          printf( "true\n" ) ;
        else
          printf( "false\n" ) ;
      } // else if
    } // if
    else if ( bool_operator->separator == "<>" ){
      if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->num_float  ) > 0.0001 )
          printf( "true\n" ) ;
        else 
          printf( "false\n" ) ;
      } // if
      else if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 2 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->interger  ) > 0.0001 )
          printf( "true\n" ) ;
        else 
          printf( "false\n" ) ;
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->interger - mtoken_ptr->next->next->num_float  ) > 0.0001 )
          printf( "true\n" ) ;
        else 
          printf( "false\n" ) ;
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 2 ){
        if ( mtoken_ptr->interger != mtoken_ptr->next->next->interger )
          printf( "true\n" ) ;
        else
          printf( "false\n" ) ;
      } // else if
    } // else if
    else if ( bool_operator->separator == ">" ){
      if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "false\n" ) ;
        else{
          if ( mtoken_ptr->num_float > mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // if
      else if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 2 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->interger  ) <= 0.0001 )
          printf( "false\n" ) ;
        else
        {
          if ( mtoken_ptr->num_float > mtoken_ptr->next->next->interger )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->interger - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "false\n" ) ;
        else
        {
          if ( mtoken_ptr->interger > mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 2 ){
        if ( mtoken_ptr->interger > mtoken_ptr->next->next->interger )
          printf( "true\n" ) ;
        else
          printf( "false\n" ) ;
      } // else if
    } // else if
    else if ( bool_operator->separator == "<" ){
      if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "false\n" ) ;
        else{
          if ( mtoken_ptr->num_float < mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // if
      else if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 2 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->interger  ) <= 0.0001 )
          printf( "false\n" ) ;
        else{
          if ( mtoken_ptr->num_float > mtoken_ptr->next->next->interger )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->interger - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "false\n" ) ;
        else{
          if ( mtoken_ptr->interger > mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 2 ){
        if ( mtoken_ptr->interger < mtoken_ptr->next->next->interger  )
          printf( "true\n" ) ;
        else
          printf( "false\n" ) ;
      } // else if
    } // else if
    else if ( bool_operator->separator == ">=" ){
      if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "true\n" ) ;
        else{
          if ( mtoken_ptr->num_float > mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // if
      else if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 2 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->interger  ) <= 0.0001 )
          printf( "true\n" ) ;
        else{
          if ( mtoken_ptr->num_float > mtoken_ptr->next->next->interger )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->interger - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "true\n" ) ;
        else{
          if ( mtoken_ptr->interger > mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 2 ){
        if ( mtoken_ptr->interger >= mtoken_ptr->next->next->interger )
          printf( "true\n" ) ;
        else
          printf( "false\n" ) ;
      } // else if
    } // else if
    else if ( bool_operator->separator == "<=" ){
      if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "true\n" ) ;
        else{
          if ( mtoken_ptr->num_float < mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // if
      else if ( mtoken_ptr->type == 3 && mtoken_ptr->next->next->type == 2 ){
        if ( fabs( mtoken_ptr->num_float - mtoken_ptr->next->next->interger  ) <= 0.0001 )
          printf( "true\n" ) ;
        else{
          if ( mtoken_ptr->num_float > mtoken_ptr->next->next->interger )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 3 ){
        if ( fabs( mtoken_ptr->interger - mtoken_ptr->next->next->num_float  ) <= 0.0001 )
          printf( "true\n" ) ;
        else{
          if ( mtoken_ptr->interger > mtoken_ptr->next->next->num_float )
            printf( "true\n" ) ;
          else
            printf( "false\n" ) ;
        } // else
      } // else if
      else if ( mtoken_ptr->type == 2 && mtoken_ptr->next->next->type == 2 ){
        if ( mtoken_ptr->interger <= mtoken_ptr->next->next->interger )
          printf( "true\n" ) ;
        else
          printf( "false\n" ) ;
      } // else if
    } // else if
  } // BooleanExp()

  public:
  Eval(){
    mtoken_ptr = NULL ;
  } // Eval()

  ~Eval(){
    mtoken_ptr = NULL ;
  } // ~Eval()
  
  bool StartEval(){
    BuildTokenString() ;
    DelSign() ;
    DelID() ;
    DelParen() ;
    if ( MultiOrDiv() ) AddOrSub() ;
    else{
      gerror_type = 3 ;
      return false ;
    } // else
    
    return true ;
  } // StartEval()
  
  void Print(){
    if ( gcommand_type == 1 ) AssignmentExp() ;
    else if ( gcommand_type == 2 ) ArithmeticExp() ;
    else if ( gcommand_type == 3 ) BooleanExp() ;
  } // Print()
  
};

int main() {
  Paser *paser = NULL ;
  Eval *eval = NULL;
  char ch ;
  scanf( "%c", &ch ) ; // 讀走題號 真正使用時要註解掉 
  scanf( "%c", &ch ) ; // 讀走題號 真正使用時要註解掉
  printf( "Program starts...\n" ) ;

  while ( ! gEND ){
    printf( "> " ) ;
    paser = new Paser() ;
    if ( paser->Command() ){
      if ( ! gEND ){
        eval = new Eval() ;
        if ( eval->StartEval() ) eval->Print() ;
        else{
          if ( gerror_type == 3 ) {
            gscanner->ClearThisLine() ;
            printf( "Error\n" ) ;
          } // if
        } // else
      } // if      
    } // if
    else{
      if ( gerror_type == 0 ){
        gscanner->ClearThisLine() ;
        printf( "Unrecognized token with first char : '%s'\n", gerror_token.c_str() ) ;
      } // if
      else if ( gerror_type == 1 ){
        gscanner->ClearThisLine() ;
        printf( "Unexpected token : '%s'\n", gerror_token.c_str() ) ;
      } // else if
      else if ( gerror_type == 2 ){
        gscanner->ClearThisLine() ;
        printf( "Undefined identifier : '%s'\n", gerror_token.c_str() ) ;
      } // else if 
    } // else
    
    delete paser ;
    paser = NULL ;
    delete eval ;
    eval = NULL ;
    gcommand_type = -1 ;
    gerror_type = -1 ;
    gerror_token = "" ;
    gtoken_string.clear() ;
  } // while
  
  printf( "Program exits..." ) ;
  return 0;
} // main()


