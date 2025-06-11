# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <string.h>
# include <string>
# include <cstdio>
# include <vector>
# include <stack>

// # include <algorithm>

using namespace std ;

vector<string> ge ;
vector<int> gerror ; // her -> 1/2/3
bool gfinish = true ; // 因為outofindex的true無法分辨是否文法結束，當return true&&gfinish == true 才eval
bool gIsS = false ;
bool gIsD = false ;
int gline = 1 ;
string gtype ;
vector<string> gtempnext ;

struct Information {
  string name ;
  string type ;
  string info ;
  string size ;
  int index ;
  int scope ;  // 0 -> global / 1 -> local ;
  vector <string> buffer ;
} ;

vector<Information> gvar ;
vector<Information> gfun ;
vector<Information> glocalvar ;


int Atoi( string& str ) {
  int num = 0 ;
  int sign = 1 ; // �P�_���t
  int i = 0 ;

  if ( str[ i ] == '-' || str[ i ] == '+' )
    sign = ( str[ i++ ] == '-' ) ? -1 : 1 ;

  while ( '0' <= str[ i ] && str[ i ] <= '9' ) {
    num = num * 10 + ( str[ i++ ] - '0' ) ;
  } // while

  return num * sign ;
} // Atoi()

class Data {
  bool misdone ;
  
  bool misdef ;
  int mfundef ;

  bool misstate ;
  int miscompound ; 


  bool Isdigit( char ch ) {
    if ( 48 <= ch && ch <= 57 )
      return true ;

    return false ;
  } // Isdigit()

  bool Isletter( char ch ) {
    if ( 65 <= ch && ch <= 90 )
      return true ;

    if ( 97 <= ch && ch <= 122 )
      return true ;

    return false ;
  } // Isletter()

  bool Iswhitespace( char ch ) {
    if ( ch == ' ' || ch == '\t' || ch == '\n' ) {
      if ( ch == '\n' ) 
        gline++ ;
        // cout << "in fun skipW    : " << gline << endl ;
      return true ;
    }
    // if

    return false ;
  } // Iswhitespace()

  bool Isident( string str ) {
    if ( Isletter( str[ 0 ] ) == false )
      return false ;

    for ( int i = 1 ; i < str.size() ; i++ ) {
      if ( Isletter( str[ i ] ) == false && Isdigit( str[ i ] ) == false && str[ i ] != '_' )
        return false ;
    } // for 

    return true ;
  } // Isident()

  bool Isnum( string str ) {
    int countdot = 0 ;
    int i = 0 ;

    if ( i == 0 && i + 1 == str.size() )     // num can onlt have one sign
      if ( str[ i ] == '-' || str[ i ] == '+' )
        return false ;

    for ( int i = 0 ; i < str.size() ; i++ ) {
      if ( i != 0 && ( str[ i ] == '+' || str[ i ] == '-' ) )
        return false ;

      // if
      if ( Isdigit( str[ i ] ) == false && str[ i ] != '.' && str[ i ] != '-' && str[ i ] != '+' )
        return false ;

      // if
      if ( str[ i ] == '.' ) {
        countdot++ ;
        if ( countdot > 1 )
          return false ;
      } // if
    }   // for

    return true ;
  } // Isnum()

  bool Sametype( char c1, char c2 ) { // a little werid
    if ( Isdigit( c1 ) && Isdigit( c2 ) )
      return true ;

    if ( Isletter( c1 ) && Isletter( c2 ) )
      return true ;

    if ( c1 == '-' && Isdigit( c2 ) )
      return true ;

    return false ;
  } // Sametype()

  bool Isothertype( char ch ) {
    if ( ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
         ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' ||
         ch == '<' || ch == '>' || ch == '&' || ch == '|' || ch == '=' || ch == '!' ||
         ch == ';' || ch == ',' || ch == '?' || ch == ':' || ch == '\'' || ch == '"' || ch == '.' )
      return true ;

    return false ;
  } // Isothertype()

  bool Isboolop( string op ) {
    if ( op == "=" || op == "<>" || op == ">" || op == "<" || op == ">=" || op == "<=" )
      return true ;

    return false ;
  } // Isboolop()

  string Check_next_token() {
    if ( mindex < mtemp.size() - 1 ) {
      mindex++ ;
      return mtemp[ mindex ] ;
    } // if

    return "outofindex" ;
  } // Check_next_token()

  //   ==================================grammar start===============================================

  int mindex ;
  vector<string> mtemp ;

  bool Isidentifier( string str ) { // 變數，不要關鍵字
    // cout << "Isidentifier    " << str << endl ;
    if ( Isconstant( str ) )
      return false ;

    if ( Isident( str ) == true && str != "int" && str != "float" && str != "char" && str != "bool" &&
         str != "string" && str != "void" && str != "if" && str != "else" && str != "while" &&
         str != "do" && str != "return" )
      return true ;

    return false ;
  } // Isidentifier()

  bool Isconstant( string str ) {
    if ( Isnum( str ) || str[ 0 ] == '"' || str[ 0 ] == '\'' || str == "true" || str == "false" )
      return true ;

    return false ;
  } // Isconstant()

  vector<Information> mnewcome ;

  void Newdeftemp( string str, int scope ) {
    // cout << "str " << str << "   my scope    " << scope << endl ;
    for ( int i = 0 ; i < mnewcome.size() ; i++ ) {
      // cout << mnewcome[i].name << "    " << mnewcome[i].scope << endl ;
      if ( mindex == mnewcome[i].index && str == mnewcome[i].name ) {
        return ;
      } // if
    } // for
    // cout << endl;

    Information data ;
    data.name = str ;
    data.index = mindex ;
   
    data.type = gtype ; // ???????????
   
    
    data.scope = scope ;
    // cout << data.type << endl;
    mnewcome.push_back( data ) ;
    // cout << data.name << " " << data.type << " " << data.scope << endl ;
  } // Newdeftemp();

  bool User_input( vector<string> v ) {
    // abc cout << "User_input    " << v[ 0 ] << endl ;
    // cout << "init: " << gerror << endl ;
    mtemp = v ;
    mindex = 0 ;
    string str = mtemp[ mindex ] ; // get ident

    // Done 0 1
    if ( Definition( str ) ) {
      misdef = true ;
      return true ;
    } // if
      
    mindex = 0 ;
    if ( Statement( str ) ) {
      misstate = true ;
      return true ;
    } // if

    if ( gerror.empty() == false && gerror[0] == 3 ) 
      return false ;
      

    gerror.push_back( 2 ) ;
    ge.push_back( str ) ;
    return false ;
  } // User_input()

  bool Definition( string str ) {
    // abc cout << "Definition     " << str << endl ;
    if ( str == "void" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Isidentifier( str ) ) {
        Newdeftemp( str, mfundef ) ;
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Function_definition_without_ID( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if
    else if ( Type_specifier( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Isidentifier( str ) ) {
        Newdeftemp( str, mfundef ) ;
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        // cout << "aaaaaaaaaaaaaaaaaaaaaaa  gerror  :  " << gerror << endl ;
        if ( Function_definition_or_declarators( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if

    return false ;
  } // Definition()

  bool Type_specifier( string str ) {
    // abc cout << "Type_specifier     " << str << endl ;
    if ( str == "int" ) {
      gtype = "int" ;
      return true ;
    } // if
    else if ( str == "char" ) {
      gtype = "char" ;
      return true ;
    } // else if
    else if ( str == "float" ) {
      gtype = "float" ;
      return true ;
    } // else if
    else if ( str == "string" ) {
      gtype = "string" ;
      return true ;
    } // else if
    else if ( str == "bool" ) {
      gtype = "bool" ;
      return true ;
    } // else if

    return false ;
  } // Type_specifier()

  bool Function_definition_or_declarators( string str ) {
    // abc cout << "Function_definition_or_declarators     " << str << endl ;
    if ( Function_definition_without_ID( str ) )
      return true ;
    else if ( Rest_of_declarators( str ) )
      return true ;

    return false ;
  } // Function_definition_or_declarators()

  bool Rest_of_declarators( string str ) {
    // cout << "Rest_of_declarators     " << str  << "     " << gerror << endl ;
    if ( str == "[" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Isconstant( str ) ) { // I need to chech what is constant
        for ( int i = 0 ; i < mnewcome.size() ; i++ ) {
          if ( mnewcome[i].name == mtemp[mindex-2] && mnewcome[i].index && mindex-2 ) {
            mnewcome[i].size = str ;
          } // if
        } // for
        
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == "]" ) { // if is ], read next, ";" is required
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else { // [] 進來要確定是constant
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    while ( str == "," ) {
      // cout << "i am here \n" ;
      str = Check_next_token() ;
      // cout << str << "     " << gerror  <<endl ;
      if ( str == "outofindex" ) return true ;

      if ( Isidentifier( str ) ) {
        // cout << "i am here too   " << str << "      " << mindex << endl  ;
        Newdeftemp( str, mfundef ) ;
        str = Check_next_token() ;
        // cout << "i need ; ->>>>>   " << str << "      " << mindex << endl  ;
        if ( str == "outofindex" ) return true ;

        // cout << "is ;     ->>>>    " << str << endl ;


        if ( str == "[" ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( Isconstant( str ) ) {
            for ( int i = 0 ; i < mnewcome.size() ; i++ ) {
              if ( mnewcome[i].name == mtemp[mindex-2] && mnewcome[i].index && mindex-2 ) {
                mnewcome[i].size = str ;
              } // if
            } // for

            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( str == "]" ) {  // get next is "," or ";"
              str = Check_next_token() ;
              if ( str == "outofindex" ) return true ;
            } // if
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        // cout << "i am not in \n" ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else

      // cout << "exiet while     " << str << endl ;
    } // while


    if ( str == ";" ) {
      gfinish = true ;
      return true ;
    } // if

    return false ;
  } // Rest_of_declarators()

  bool Function_definition_without_ID( string str ) {
    // abc cout << "Function_definition_without_ID     " << str << "     gerror    " << gerror << endl ;
    bool havein = false ;

    if ( str == "(" ) {
      mfundef = true ;
      str = Check_next_token() ;
      // cout << "i have got : " << str << endl ;
      if ( str == "outofindex" ) return true ;

      if ( str == "void" )
        havein = true ;
      else if ( Formal_parameter_list( str ) )
        havein = true ;

      if ( havein == true ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if

      // cout << str << "ssssssss       " << gerror << "       wwwwwwwwwwwwwwwwww\n" ;

      if ( str == ")" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Compound_statement( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    return false ;
  } // Function_definition_without_ID()

  bool Formal_parameter_list( string str ) {
    // cout << "Formal_parameter_list     " << str << "     " << gerror << endl ;
    bool havein = false ;

    if ( Type_specifier( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == "&" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if

      if ( Isidentifier( str ) ) {
        Newdeftemp( str, mfundef ) ;
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        havein = true ; // 紀錄一下他有進去 type + ident

        if ( str == "[" ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( Isconstant( str ) ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( str == "]" ) {
              str = Check_next_token() ;
              if ( str == "outofindex" ) return true ;
            } // if
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    while ( str == "," ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Type_specifier( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if

      if ( str == "&" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if

      if ( Isidentifier( str ) ) {
        Newdeftemp( str, mfundef ) ;
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == "[" ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( Isconstant( str ) ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( str == "]" ) {
              str = Check_next_token() ;
              if ( str == "outofindex" ) return true ;
            } // if
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
      } // if
    } // while

    if ( havein == true ) { // 判斷到[ 不是的話看"," ,都不是但是確定上排對，偷看的要退回去
      mindex-- ;
      return true ;
    } // if

    return false ;
  } // Formal_parameter_list()

  vector<int> mupindex ; // using for compound statedment
  vector<int> mlowindex ;

  void Checkupper() {
    for ( int i = 0 ; i < mupindex.size() ; i++ ) {
      if ( mindex == mupindex[i] ) {
        // cout << "i am repeat :     " << mindex << "       num:  " << miscompound << endl;
        return ;
      } // if
    } // for

    miscompound++ ;
    mupindex.push_back( mindex ) ;
  } // Checkupper()

  void Checklow() {
    for ( int i = 0 ; i < mlowindex.size() ; i++ ) {
      if ( mindex == mlowindex[i] ) {
        // cout << "i am repeat ~~~~~~~~~ :     " << mindex << "       num:  " << miscompound << endl;
        return ;
      } // if
    } // for

    miscompound-- ;
    mlowindex.push_back( mindex ) ;
  } // Checklow()



  bool Compound_statement( string str ) {
    // cout << "Compound_statement    " << str << "        num -> " << miscompound << endl ;
    bool havein = false ;

    if ( str == "{" ) {
      Checkupper() ;

      str = Check_next_token() ;
      if ( str == "outofindex" ) {
        return true ;
      } // if
      
      while ( Declaration( str ) || Statement( str ) ) {
        str = Check_next_token() ;
        // cout << "ssssssssssssssssssssssssssssssssssssssss         " << str<< miscompound <<endl;
        if ( str == "outofindex" ) return true ;
      } // while
      

      // cout << miscompound << "   sMC   " << mMc << "       in   " << mindex << "str   "  << str << endl ;
      if ( str == "}" ) {
        // cout << "i have been here !!!!!!!!!!\n" ;
        Checklow() ;
        if ( miscompound == 0 ) {
          gfinish = true ;
        } // if

        return true ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    return false ;
  } // Compound_statement()

  bool Declaration( string str ) {
     // cout << "Declaration    " << str << endl ;

    if ( Type_specifier( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Isidentifier( str ) ) {
        Newdeftemp( str, mfundef ) ;
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Rest_of_declarators( str ) )
          return true ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    return false ;
  } // Declaration()

  bool Statement( string str ) {
    // cout << "Statement       " << str << endl ;
    if ( str == ";" ) { // the null statement
      gfinish = true ;
      return true ;
    } // if

    if ( Expression( str ) ) {
      // cout << gerror  << endl;
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == ";" ) {
        // cout << "Ohhhhhhhhhhhhhhhhhhhh" << endl ;
        gfinish = true ;
        return true ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    if ( str == "return" ) {

      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Expression( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == ";" ) {
          gfinish = true ;
          return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if                  // because -> [expression] can appear 0 ~ 1,
      else if ( str == ";" ) { // and next str is ";", dont need to index--
        gfinish = true ;
        return true ;
      } // else if
      else { // not a expression or ";" -> it must be wrong
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    if ( Compound_statement( str ) )
      return true ;

    if ( str == "if" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == "(" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == ")" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( Statement( str ) ) {

              gfinish = false ;
              str = Check_next_token() ;
              if ( str == "outofindex" ) return true ;

              if ( str == "else" ) {
                str = Check_next_token() ;
                if ( str == "outofindex" ) return true ;
                
                // cout << "wewewew  str  :  " << str << endl;
                if ( Statement( str ) )
                  return true ;
                else {
                  gerror.push_back( 2 ) ;
                  ge.push_back( str ) ;
                  return false ;
                } // else
              } // if
              else { // 他不是else ->[else] -> index-- and true
                if ( miscompound == 0 ) {
                  gfinish = true ;
                  gtempnext.push_back( str ) ;
                  return true ;
                } // if

                mindex-- ; // weird;
                gfinish = true ; // 我不知道這樣可不可以，但就試試看 maybe here have some ERROR
                return true ;
              } // else
            } // if -> statement
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if -> )
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if -> expression
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if -> (
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if ->str

    if ( str == "while" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == "(" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == ")" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( Statement( str ) )
              return true ;
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    if ( str == "do" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Statement( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == "while" ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == "(" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( Expression( str ) ) {
              str = Check_next_token() ;
              if ( str == "outofindex" ) return true ;

              if ( str == ")" ) {
                str = Check_next_token() ;
                if ( str == "outofindex" ) return true ;

                if ( str == ";" ) {
                  gfinish = true ;
                  return true ;
                } // if
                else {
                  gerror.push_back( 2 ) ;
                  ge.push_back( str ) ;
                  return false ;
                } // else
              } // if
              else {
                gerror.push_back( 2 ) ;
                ge.push_back( str ) ;
                return false ;
              } // else
            } // if
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    return false ;
  } // Statement()

  bool Expression( string str ) {
    // abc cout << "Expression       " << str << endl ;
    bool havein = false ;

    if ( Basic_expression( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      havein = true ;
    } // if

    while ( str == "," ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Basic_expression( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // while

    if ( str != "," && havein == true ) {
      mindex-- ;
      return true ;
    } // if

    return false ;
  } // Expression()

  bool Basic_expression( string str ) { // wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    // abc cout << "Basic_expression       " << str << endl ;
    if ( Isidentifier( str ) ) {
      if ( Checkexistvar( str ) == false && Isdeffun( str ) == false && 
           Checkisfunlocal( str ) == false && Checkexistfun( str ) == false ) {
        gerror.push_back( 3 ) ;
        ge.push_back( str ) ;
        return false ;
      } // if

      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Rest_of_Identifier_started_basic_exp( str ) )
        return true ;
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if
    else if ( str == "++" || str == "--" ) { // PP or MM
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Isidentifier( str ) ) {
        if ( Checkexistvar( str ) == false && Isdeffun( str ) == false && 
             Checkisfunlocal( str ) == false && Checkexistfun( str ) == false ) {
          gerror.push_back( 3 ) ;
          ge.push_back( str ) ;
          return false ;
        } // if

        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Rest_of_PPMM_Identifier_started_basic_exp( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if
    else if ( Sign( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( Sign( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // while

      if ( Signed_unary_exp( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Romce_and_romloe( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if
    else if ( Isconstant( str ) || str == "(" ) {
      if ( Isconstant( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Romce_and_romloe( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        }   // else
      } // if
      else if ( str == "(" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == ")" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( Romce_and_romloe( str ) )
              return true ;
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // else if
    } // else if

    return false ;
  } // Basic_expression()

  bool Rest_of_Identifier_started_basic_exp( string str ) {
    // abc cout << "Rest_of_Identifier_started_basic_exp      " << str << endl ;

    bool havein = false ;
    int temp = mindex ;

    if ( str == "(" && havein == false ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Actual_parameter_list( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      }   // if

      if ( str == ")" ) {
        // cout << "i am here" << endl ;
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        // cout << "OMG:  " << str << endl ;
        if ( Romce_and_romloe( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        }   // else
      }   // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if
    else {
      if ( str == "[" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == "]" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            havein = true ;
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if

      temp = mindex ;
      // cout << "2restofISBE:    " << str << endl ;
      if ( Assignment_operator( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Basic_expression( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        }   // else
      }   // if
      else
        mindex = temp ;

      if ( ( str == "++" || str == "--" ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Romce_and_romloe( str ) )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        }   // else
      }   // if
      else
        mindex = temp ;

      if ( Romce_and_romloe( str ) )
        // cout << "g: " << gerror << endl ;
        return true ;
      else
        mindex = temp ;  // ??????????????????????????????? // mindex--; choose one
    } // else

    return false ;
  } // Rest_of_Identifier_started_basic_exp()

  bool Rest_of_PPMM_Identifier_started_basic_exp( string str ) {
    // abc cout << "Rest_of_PPMM_Identifier_started_basic_exp    " << str << endl ;
    if ( str == "[" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Expression( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == "]" ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    if ( Romce_and_romloe( str ) )
      return true ;

    return false ;
  } // Rest_of_PPMM_Identifier_started_basic_exp()

  bool Sign( string str ) {
    // abc cout << "Sign    " << str << endl ;
    if ( str == "+" || str == "-" || str == "!" )
      return true ;

    return false ;
  } // Sign()

  bool Actual_parameter_list( string str ) {
    // abc cout << "Actual_parameter_list    " << str << endl ;
    bool havein = false ;

    if ( Basic_expression( str ) ) {
      havein = true ;
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;
    }

    while ( str == "," ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Basic_expression( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // while

    if ( str != "," && havein == true ) {
      mindex-- ;
      return true ;
    } // if

    return false ;
  } // Actual_parameter_list()

  bool Assignment_operator( string str ) {
    // abc cout << "Assignment_operator    " << str << endl ;
    if ( str == "=" || str == "*=" || str == "/=" || str == "%=" || str == "+=" || str == "-=" )
      return true ;

    return false ;
  } // Assignment_operator()

  bool Romce_and_romloe( string str ) {
    // abc cout << "Romce_and_romloe     " << str << endl ;
    if ( Rest_of_maybe_logical_OR_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == "?" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Basic_expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == ":" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( Basic_expression( str ) )
              return true ;
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        mindex-- ;
        return true ;
      } // else
    } // if

    return false ;
  } // Romce_and_romloe()

  bool Rest_of_maybe_logical_OR_exp( string str ) {
    // abc cout << "Rest_of_maybe_logical_OR_exp     " << str << endl ;
    if ( Rest_of_maybe_logical_AND_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "||" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_logical_AND_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "||" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_logical_OR_exp()

  bool Maybe_logical_AND_exp( string str ) {
    // abc cout << "Maybe_logical_AND_exp    " << str << endl ;
    if ( Maybe_bit_OR_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "&&" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_bit_OR_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "&&" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_logical_AND_exp()

  bool Rest_of_maybe_logical_AND_exp( string str ) {
    // abc cout << "Rest_of_maybe_logical_AND_exp     " << str << endl ;
    if ( Rest_of_maybe_bit_OR_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "&&" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_bit_OR_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "&&" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_logical_AND_exp()

  bool Maybe_bit_OR_exp( string str ) {
    // abc cout << "Maybe_bit_OR_exp   " << str << endl ;
    if ( Maybe_bit_ex_OR_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "|" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_bit_ex_OR_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "|" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_bit_OR_exp()

  // --------------------------------------------------------------------
  bool Rest_of_maybe_bit_OR_exp( string str ) {
    // abc cout << "Rest_of_maybe_bit_OR_exp     " << str << endl ;
    if ( Rest_of_maybe_bit_ex_OR_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "|" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_bit_ex_OR_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "|" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_bit_OR_exp()

  bool Maybe_bit_ex_OR_exp( string str ) {
    // abc cout << "Maybe_bit_ex_OR_exp   " << str << endl ;
    if ( Maybe_bit_AND_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "^" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_bit_AND_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "^" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_bit_ex_OR_exp()

  bool Rest_of_maybe_bit_ex_OR_exp( string str ) {
    // abc cout << "Rest_of_maybe_bit_ex_OR_exp     " << str << endl ;
    if ( Rest_of_maybe_bit_AND_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "^" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_bit_AND_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "^" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_bit_ex_OR_exp()

  bool Maybe_bit_AND_exp( string str ) {
    // abc cout << "Maybe_bit_AND_exp   " << str << endl ;
    if ( Maybe_equality_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "&" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_equality_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "&" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_bit_AND_exp()

  bool Rest_of_maybe_bit_AND_exp( string str ) {
    // abc cout << "Rest_of_maybe_bit_AND_exp     " << str << endl ;
    if ( Rest_of_maybe_equality_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "&" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_equality_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "&" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_bit_AND_exp()

  bool Maybe_equality_exp( string str ) {
    // abc cout << "Maybe_equality_exp   " << str << endl ;
    if ( Maybe_relational_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "==" || str == "!=" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_relational_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "==" || str != "!=" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_equality_exp()

  bool Rest_of_maybe_equality_exp( string str ) {
    // abc cout << "Rest_of_maybe_equality_exp    " << str << endl ;
    if ( Rest_of_maybe_relational_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "==" || str == "!=" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_relational_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "==" || str != "!=" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_equality_exp()

  bool Maybe_relational_exp( string str ) {
    // abc cout << "Maybe_relational_exp   " << str << endl ;
    if ( Maybe_shift_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "<" || str == ">" || str == ">=" || str == "<=" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_shift_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "<" || str != ">" || str != ">=" || str != "<=" ) {
        mindex-- ;
        return true ;
      } // if
    } // if


    return false ;
  } // Maybe_relational_exp()

  bool Rest_of_maybe_relational_exp( string str ) {
    // abc cout << "Rest_of_maybe_relational_exp    " << str << endl ;
    if ( Rest_of_maybe_shift_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "<" || str == ">" || str == ">=" || str == "<=" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_shift_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "<" || str != ">" || str != ">=" || str != "<=" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_relational_exp()

  bool Maybe_shift_exp( string str ) {
    if ( Maybe_additive_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "<<" || str == ">>" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_additive_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "<<" || str != ">>" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_shift_exp()

  bool Rest_of_maybe_shift_exp( string str ) {
    // abc cout << "Rest_of_maybe_shift_exp    " << str << endl ;
    if ( Rest_of_maybe_additive_exp( str ) ) {
      str = Check_next_token() ;
      // cout << "i am here      :    " << str << endl ;
      if ( str == "outofindex" ) return true ;

      while ( str == "<<" || str == ">>" ) {
        str = Check_next_token() ;

        if ( str == "outofindex" ) return true ;

        // cout << "aaaaaaaa ccccccccccc :    " << str << endl ;

        if ( Maybe_additive_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "<<" || str != ">>" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_shift_exp()

  bool Maybe_additive_exp( string str ) {
    if ( Maybe_mult_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "+" || str == "-" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_mult_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "+" || str != "-" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Maybe_additive_exp()

  bool Rest_of_maybe_additive_exp( string str ) {
    // abc cout << "Rest_of_maybe_additive_exp    " << str << endl ;
    if ( Rest_of_maybe_mult_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( str == "+" || str == "-" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Maybe_mult_exp( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while

      if ( str != "+" || str != "-" ) {
        mindex-- ;
        return true ;
      } // if
    } // if

    return false ;
  } // Rest_of_maybe_additive_exp()

  bool Maybe_mult_exp( string str ) {
    if ( Unary_exp( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Rest_of_maybe_mult_exp( str ) )
        return true ;
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if

    return false ;
  } // Maybe_mult_exp()

  bool Rest_of_maybe_mult_exp( string str ) {
    // abc cout << "Rest_of_maybe_mult_exp    " << str << endl ;
    bool havein = false ;

    while ( str == "*" || str == "/" || str == "%" ) {
      havein = true ;
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Unary_exp( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // while


    mindex-- ;
    // cout << mtemp[ mindex ] << "!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" ;
    return true ;
  } // Rest_of_maybe_mult_exp()

  bool Unary_exp( string str ) {
    if ( Sign( str ) ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      while ( Sign( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;
      } // while

      if ( Signed_unary_exp( str ) )
        return true ;
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // if
    else if ( Unsigned_unary_exp( str ) )
      return true ;
    else if ( str == "++" || str == "--" ) { // PP | MM
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Isidentifier( str ) ) {
        if ( Checkexistvar( str ) == false && Isdeffun( str ) == false && 
             Checkisfunlocal( str ) == false && Checkexistfun( str ) == false ) {
          gerror.push_back( 3 ) ;
          ge.push_back( str ) ;
          return false ;
        } // if

        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == "[" ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( Expression( str ) ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( str == "]" )
              return true ;
            else {
              gerror.push_back( 2 ) ;
              ge.push_back( str ) ;
              return false ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          mindex-- ;
          return true ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if

    return false ;
  } // Unary_exp()

  bool Signed_unary_exp( string str ) {
    if ( Isidentifier( str ) ) {
      if ( Checkexistvar( str ) == false && Isdeffun( str ) == false && 
           Checkisfunlocal( str ) == false && Checkexistfun( str ) == false ) {
        gerror.push_back( 3 ) ;
        ge.push_back( str ) ;
        return false ;
      } // if

      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == "(" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Actual_parameter_list( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == ")" )
            return true ;
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else if ( str == ")" )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else if ( str == "[" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == "]" )
            return true ;
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // else if
      else {
        mindex-- ;  // ( , [ 不一定要有
        return true ;
      } // else
    } // if
    else if ( Isconstant( str ) )
      return true ;
    else if ( str == "(" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Expression( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == ")" )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if

    return false ;
  } // Signed_unary_exp()

  bool Unsigned_unary_exp( string str ) {
    if ( Isidentifier( str ) ) {
      if ( Checkexistvar( str ) == false && Isdeffun( str ) == false && 
           Checkisfunlocal( str ) == false && Checkexistfun( str ) == false ) {
        gerror.push_back( 3 ) ;
        ge.push_back( str ) ;
        return false ;
      } // if

      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( str == "(" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Actual_parameter_list( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == ")" )
            return true ;
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else if ( str == ")" )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else if ( str == "[" ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( Expression( str ) ) {
          str = Check_next_token() ;
          if ( str == "outofindex" ) return true ;

          if ( str == "]" ) {
            str = Check_next_token() ;
            if ( str == "outofindex" ) return true ;

            if ( str == "++" || str == "--" )
              return true ;
            else {
              mindex-- ;
              return true ;
            } // else
          } // if
          else {
            gerror.push_back( 2 ) ;
            ge.push_back( str ) ;
            return false ;
          } // else
        } // if
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // else if
      else if ( str == "++" || str == "--" )
        return true ;
      else {
        mindex-- ;  // ( , [ 不一定要有
        return true ;
      } // else
    } // if
    else if ( Isconstant( str ) )
      return true ;
    else if ( str == "(" ) {
      str = Check_next_token() ;
      if ( str == "outofindex" ) return true ;

      if ( Expression( str ) ) {
        str = Check_next_token() ;
        if ( str == "outofindex" ) return true ;

        if ( str == ")" )
          return true ;
        else {
          gerror.push_back( 2 ) ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // if
      else {
        gerror.push_back( 2 ) ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if

    return false ;
  } // Unsigned_unary_exp()

  // ==================================grammar end=================================================

  bool Isdeffun( string str ) {
    if ( str == "ListAllVariables" || str == "ListVariable" || str == "ListAllFunctions" ||
         str == "ListFunction" || str == "Done" || str == "cin" || str == "cout" ) 
      return true ;

    return false ;
  } // Isdeffun()

  bool Checkexistfun( string str ) {
    // cout << "in str    " << str << endl ;
    
    for ( int i = 0 ; i < gfun.size() ; i++ ) {
      // cout << "incheck     " << gfun[i].name << endl ;
      if ( str == gfun[i].name )
        return true ;
    } // for 

    return false ;
  } // Checkexistfun()

  bool Checkisfunlocal( string str ) {
    
    for ( int i = 0 ; i < mnewcome.size() ; i++ ) {
      // cout << "mnewcome     " << mnewcome[i].name << endl ;
      if ( str == mnewcome[i].name && mnewcome[i].scope == 1 )
        return true ;
    } // for 

    return false ;
  } // Checkisfunlocal()

  bool Checkexistvar( string str ) {
    for ( int i = 0 ; i < gvar.size() ; i++ ) {
      if ( str == gvar[i].name )
        return true ;
    } // for

    return false ;
  } // Checkexistvar()

  void Printspace( int n ) {
    while ( n > 0 ) {
      cout << " " ;
      n-- ;
    } // while
  } // Printspace()

  void Printallfun() {
    for ( int i = 1; i < gfun.size() ; i++ ) {
      Information key = gfun[i];
      int j = i - 1;

      while ( j >= 0 && gfun[j].name > key.name ) {
        gfun[j + 1] = gfun[j];
        j = j - 1;
      } // while

      gfun[j + 1] = key;
    } // for
    
    cout << "> " ;
    for ( int i = 0 ; i < gfun.size() ; i++ ) { // .append( "()" )
      cout << gfun[i].name << "()" << endl ; 
    } // for
  } // Printallfun()

  void Printallvar() {
    for ( int i = 1; i < gvar.size() ; i++ ) {
      Information key = gvar[i];
      int j = i - 1;

      while ( j >= 0 && gvar[j].name > key.name ) {
        gvar[j + 1] = gvar[j];
        j = j - 1;
      } // while

      gvar[j + 1] = key;
    } // for
    
    cout << "> " ;
    for ( int i = 0 ; i < gvar.size() ; i++ ) 
      cout << gvar[i].name << endl ;
  } // Printallvar()

  void Printvar( string str ) { // ListVariable("x");
    string temp ;
    Information data ;
    for ( int i = 1 ; i < str.size() - 1 ; i++ ) // 削掉""
      temp += str[i] ;

    for ( int i = 0 ; i < gvar.size() ; i++ ) {
      if ( gvar[i].name == temp ) {
        data = gvar[i] ;
      } // if
    } // for 

    if ( data.size.empty() == true )
      cout << "> " << data.type << " " << data.name << " ;" << endl ;
    else 
      cout << "> " << data.type << " " << data.name << "[ " << data.size << " ]" << " ;" << endl ;

  } // Printvar()

  void Printfun( string str ) { 
    string funname ;
    vector<string> temp ;

    for ( int i = 1 ; i < str.size() - 1 ; i++ ) // 削掉""
      funname += str[i] ;

    str = funname ;  

    for ( int i = 0 ; i < gfun.size() ; i++ ) {
      // cout << "gfun name :    " << gfun[i].name << endl; 
      if ( gfun[i].name == funname ) {
        for ( int j = 0 ; j < gfun[i].buffer.size() ; j++ ) {
          // cout << gfun[i].buffer[j] << "   " ;
          temp = gfun[i].buffer ;
        } // for
      } // if

      // cout << endl ;
    } // for 

    // cout << "fffff   " << str << endl ;
    int space = 0 ;
    bool isifwhile = false ;
    bool isnewline = true ;
    bool issinglestate = false ;
    int bracket = 0 ;

    cout << "> " ;
    for ( int i = 0 ; i < temp.size() ; i++ ) {
      if ( isnewline == true ) {
        if ( temp[i] == "}" ) 
          space -= 2 ;
        Printspace( space ) ;
        isnewline = false ;
      } // if
      
      cout << temp[i] ;

      if ( temp[i] == "if" || temp[i] == "while" ) {
        isifwhile = true ;
      } // if

      if ( isifwhile == true ) {
        if ( temp[i] == "(" )
          bracket++ ;
        if ( temp[i] == ")" )
          bracket-- ;

        // cout << bracket << endl ;
        if ( i + 1 < temp.size() && bracket == 0 && temp[i] == ")" && temp[i+1] != "{" ) {
          cout << "\n";
          space += 2;
          isnewline = true ;
          issinglestate = true ;
          isifwhile = false ;
        } // if
        else {
          isifwhile = false ;
        } // else
      } // if
        
      if ( temp[i] == "{" ) {
        cout << "\n";
        space += 2;
        isnewline = true ;
      } // if
      else if ( temp[i] == ";" ) {
        if ( issinglestate == true ) {
          cout << "\n";
          isnewline = true ;
          space -= 2 ;
          issinglestate = false ;
        } // if
        else {
          cout << "\n";
          isnewline = true ;
        } // else
      } // else if
      else if ( temp[i] == "}" ) {
        if ( Checkdo_while( i, temp ) ) { // check do-while
          Printspace( 1 ) ; 
        } // if
        else { // not do-while, just next line
          cout << "\n";
          isnewline = true ;
        } // else
      } // else if
      else if ( i + 1 < temp.size() && ( temp[i+1] == "," || temp[i+1] == "[" ) ) { // a[2], int x, z
        i++ ;
        cout << temp[i] ;
        Printspace( 1 ) ;
      } // if
      else if ( i + 1 < temp.size() && ( temp[i+1] == "++" || temp[i+1] == "--" ) ) {  // a++, a--
        i++ ;
        cout << temp[i] ;
        Printspace( 1 ) ;
      } // else if
      else if ( temp[i] == "++" || temp[i] == "--" ) {  // a++, a--
        i++ ;
        cout << temp[i] ;
        Printspace( 1 ) ;
      } // else if
      else if ( temp[i] == str || Checkexistfun( temp[i] ) == true )  { // function int a()
        if ( i + 1 < temp.size() && temp[i+1] == "(" ) { // to certain is function, ex: int a
          i++ ;
          cout << temp[i] ;
          Printspace( 1 ) ;
        } // if
        else {
          Printspace( 1 ) ;
        } // else
      } // else if
      else {
        Printspace( 1 ) ;
      } // else
    } // for

  } // Printfun()

  bool Checkdo_while( int i, vector<string> temp ) { // i == } , trace back to find "do"
  
    int index = i - 1 ; // trace back 
    int num = -1 ; // temp[i] == "}" -> num be initialized -1
    // cout << "1   " << num << "   " << index << "    " << temp[i+1]<< endl ;
    while ( index > 0 ) {
      if ( temp[index] == "{" )
        num++ ;
      if ( temp[index] == "}" )
        num-- ;
      
      if ( num == 0 && temp[index-1] == "do" && temp[i+1] == "while" ) {
        // cout << "aaa\n" ;
        return true ;
      } // if

      index-- ;
      // cout << "\ny   " << num << "   " << temp[index] << "    " << temp[i+1]<< endl ;
    } // while

    return false ;
  } // Checkdo_while()
  
  void Eval( vector<string> exp ) {  // mnewcome<Information>會有新進來的ident

    if ( misdef ) {
      if ( mfundef ) {
        cout << "> " ;
        for ( int i = 0 ; i < gfun.size() ; i++ ) {
          if ( gfun[i].name == exp[1] ) {
            const char* TEMP = exp[1].c_str() ;
            printf( "New definition of %s() entered ...\n", TEMP ) ;
            gfun[i].buffer = mtemp ;
            return ;
          } // if
        } // for

        const char* TEMP = exp[1].c_str() ;
        printf( "Definition of %s() entered ...\n", TEMP ) ;
        // exp[1] += "()" ;
        Information data ;
        data.name = exp[1] ;
        data.buffer = mtemp ;
        // cout << "data name    " << data.name << endl ;
        gfun.push_back( data ) ;
        return ;
      } // if
      else { // 單純宣告變數

        cout << "> " ;
        for ( int i = 0 ; i < mnewcome.size() ; i++ ) { // 檢查剛剛被新定義的var
          if ( Checkexistvar( mnewcome[i].name ) ) {
            const char* TEMP = mnewcome[i].name.c_str() ;
            printf( "New definition of %s entered ...\n", TEMP ) ;

            for ( int j = 0 ; j < gvar.size() ; j++ ) {
              if ( gvar[j].name == mnewcome[i].name ) {
                gvar[j] = mnewcome[i] ;
              } // if
            } // for
          } // if
          else {
            const char* TEMP = mnewcome[i].name.c_str() ;
            printf( "Definition of %s entered ...\n", TEMP ) ;
            gvar.push_back( mnewcome[i] ) ;
          } // else
        } // for 



        return ;
      } // else

    } // if --------------------------- statement ----------------------------
    else if ( misstate ) {
      if ( Isdeffun( exp[ 0 ] ) ) {
        if ( exp[ 0 ] == "Done" ) {
          cout << "> Our-C exited ..." << endl ;
          misdone = true ;
          return ;
        } // if
        else if ( exp[0] == "ListAllVariables" && exp.size() == 4 ) {
          Printallvar() ;
          cout << "Statement executed ..." << endl ;
        } // else if 
        else if ( exp[0] == "ListAllFunctions" && exp.size() == 4 ) {
          Printallfun() ;
          cout << "Statement executed ..." << endl ;
        } // else if 
        else if ( exp[0] == "ListVariable" ) {
          Printvar( exp[2] ) ;
          cout << "Statement executed ..." << endl ;
        } // else if 
        else if ( exp[0] == "ListFunction" ) {
          Printfun( exp[2] ) ;
          cout << "Statement executed ..." << endl ;
        } // else if 
        else if ( exp[0] == "cin" || "cout" ) {
          cout << "> Statement executed ..." << endl ;
        } // else if
      } // if
      else
        cout << "> Statement executed ..." << endl ;
    } // else if
  } // Eval()

  string Gettoken() { // 判斷token並回傳, main function is "determine"
    char ch ;
    scanf( "%c", &ch ) ;

    while ( Iswhitespace( ch ) ) {
      scanf( "%c", &ch ) ;
    } // while

    char next = cin.peek() ;
    char now = ch ;
    string str ;
    int dotnum = 0 ;     //
    char first = ch ;     // can't be '_'
    bool isnum = false ;
    bool isident = false ;
    bool isother = false ;

    if ( first == '_' || ( first == '.' && Isdigit( next ) == false ) ) { // _ 開頭 -> wrong
      gerror.push_back( 1 ) ;
      str += now ;
      return str ;
    } // if    // 三種都不是 -> wrong
    else if ( Isletter( now ) == false && Isdigit( now ) == false && Isothertype( now ) == false ) {
      gerror.push_back( 1 ) ;
      str += now ;
      return str ;
    } // else if

    str += ch ;
    char temp[ 200 ] ;
    if ( Isdigit( now ) || first == '.' ) {
      if ( first == '.' )
        dotnum++ ;

      isnum = true ;
    } // if
    else if ( Isletter( now ) )
      isident = true ;
    else
      isother = true ;

    // cout << isnum << "   " << isident << "   " << isother << endl ;

    while ( isnum || isident || isother ) {
      // cout << "1 " << now << "   2 " << next << "  g: " << gerror << endl ;
      // cout << "now: " << now << "   next: " << next << endl ;
      if ( isnum && ( ( Isdigit( now ) && Isdigit( next ) ) || next == '.' ||
                      ( now == '.' && Isdigit( next ) ) ) ) { // ===================num==========
        if ( next == '.' )
          dotnum++ ;
        // if
        if ( dotnum <= 1 )
          str += next ;
        // if
        else
          return str ;
        // else
      } // if
      else if ( isident &&
                ( ( now == '_' && next == '_' ) ||
                  ( Isletter( now ) && Isletter( next ) ) || ( now == '_' && Isletter( next ) ) ||
                  ( Isletter( now ) && Isdigit( next ) ) || ( Isletter( now ) && next == '_' ) ||
                  ( Isdigit( now ) && Isletter( next ) ) || ( now == '_' && Isdigit( next ) ) ||
                  ( Isdigit( now ) && Isdigit( next ) ) || ( Isdigit( now ) && next == '_' ) ) )     // ident
        str += next ;
      // else if
      else {  // ====================================othrtpart=======================
        // cout << "3now letter is  :   " << now << "  total str  :    " << str << endl ;
        if ( now == '<' && ( next == '=' || next == '<'  ) ) {
          str += next ;
          if (  str == "<=" || str == "<<" ) {
            scanf( "%c", &now ) ;
            return str ;
          } // if
        }  // else if
        else if ( now == '>' && ( next == '=' || next == '>'  ) ) {
          str += next ;
          if ( str == ">=" || str == ">>" ) {
            scanf( "%c", &now ) ;
            return str ;
          } // if
        }  // else if
        else if ( now == '/' ) {
          if ( next == '/' ) {
            cin.getline( temp, 200 ) ;
            gline++ ;
            now = cin.peek() ;
            str = now ;
            while ( Iswhitespace( now ) ) {
              scanf( "%c", &now ) ;
              now = cin.peek() ;
              str = now ;
              // cout << "///str : " << str ;
            } // while

            if ( Isdigit( now ) || first == '.' ) {
              if ( first == '.' )
                dotnum++ ;
              // if

              isnum = true ;
            } // if
            else if ( Isletter( now ) )
              isident = true ;
            // else if
            else
              isother = true ;
            // else
          } // if
          else
            return str ;
          // else
        } // else if
        else if ( now == '"' ) {
          while ( next != '"' ) {
            str += next ;
            scanf( "%c", &now ) ;
            next = cin.peek() ;
          } // while

          str += next ;
          scanf( "%c", &now ) ; // 讀掉 ""
          return str ;
        } // else if
        else if ( ( now == '!' && next == '=' ) || ( now == '|' && next == '|' ) ||
                  ( now == '&' && next == '&' ) || ( now == '+' && next == '=' ) ||
                  ( now == '+' && next == '+' ) || ( now == '-' && next == '=' ) ||
                  ( now == '-' && next == '-' ) || ( now == '*' && next == '=' ) ||
                  ( now == '%' && next == '=' ) || ( now == '/' && next == '=' ) ||
                  ( now == '=' && next == '=' ) ) {
          str += next ;
          scanf( "%c", &now ) ;
          return str ;
        } // else if
        else if ( now == '\'' ) {
          str += next ;
          scanf( "%c", &now ) ;
          next = cin.peek() ;
          if ( next == '\'' ) {
            str += next ;
            scanf( "%c", &now ) ;
            return str ;
          } // if
          else {
            gerror.push_back( 1 ) ;
            return "\'" ;
          } // else 

        } // else if
        else
          return str ;

        // else
      } // else

      scanf( "%c", &ch ) ;
      now = ch ;
      next = cin.peek() ;
    } // while

    return str ;
  } // Gettoken()

public:
  Data() {
    misdone = false ;
    misdef = false ;
    misstate = false ;
    miscompound = 0 ;
    mfundef = false ;
  } // Data()

  void Reset() {
    gfinish = false ;

    misdef = false ;
    misstate = false ;

    gerror.clear() ;
    ge.clear() ;

    miscompound = 0 ;
    mupindex.clear() ;
    mlowindex.clear() ;

    mnewcome.clear() ;
    mfundef = false ;
    gline = 1 ;

    char next = cin.peek() ;
    char now ;
    char temp[200] ;
    while ( next == ' ' || next == '\t' || next == '\n' ) { // 結束and後面都空Scantillcline()格且換行
      if ( next == '\n' ) {
        scanf( "%c", &next ) ;
        gline = 1 ;
        return ;
      } // if

      scanf( "%c", &now ) ;
      if ( cin.peek() == '/' ) {  // 後面是} 但後面有註解//，這裡也不能留，重設gline
        scanf( "%c", &now ) ;
        if ( cin.peek() == '/' ) { 
          cin.getline( temp, 200 ) ; 
          // cout << " i have read the // " << endl ;
          gline = 1 ;
          return ;
        } // if
      } // if

      next = cin.peek() ;
    } // while
  } // Reset()

  void Scantillcline() { // 因為reset會把正確一行後面讀完，對ERROR一樣不要讀到'\n'，給reset統一處理
    char ch ;
    while ( cin.peek() != '\n' ) {
      scanf( "%c", &ch ) ;
    } // while
  } // Scantillcline()

  void Scanner() { // use Gettoken() to get token and store into a vector, a whole command till ";".
    char ch ;
    string str ;
    vector<string> expression ;
    char temp[ 200 ] ;

    gfinish = false ;

    while ( misdone == false ) {
      
      // cout << "line ->>>>    " << gline << endl ;
      if ( miscompound == 0 && gtempnext.empty() == false ) {
        str = gtempnext[0] ;
        gtempnext.clear() ;
      } // if
      else {
        str = Gettoken() ;
      } // else
      // cout << "str: " << str << "    1gerror : " << gerror << endl ;
      // cout << "str: " << str << "    gline    :  " << gline << "      \n" ;
      // cout << "str: " << str << "    is ->    :  " << mfundef << "      \n" ;
      if ( gerror.empty() == false && gerror[0] == 1 ) {
        const char* TEMP = str.c_str() ;
        printf( "> Line %d : unrecognized token with first char : '%s'\n", gline, TEMP ) ;
        Scantillcline() ;  // 還不確定她錯誤處理
        // cin.getline( temp, 200 ) ;
        expression.clear() ;
        Reset() ;
      } // if
      else {    // 沒有unrecognized token
        expression.push_back( str ) ;
        // cout << "par: " << User_input( expression ) << endl ;
        User_input( expression ) ;
        // cout << "end? " << gfinish << " Error: " << gerror << endl ;
        // cout << expression.size() << "zzzzzzzzzzzzzzzzzzzz" << endl ;
        if ( gerror.empty() == false && gerror[0] == 3 ) {
          const char* TEMP = ge[ 0 ].c_str() ;
          printf( "> Line %d : undefined identifier : '%s'\n", gline, TEMP ) ;
          Scantillcline() ; // 還不確定她錯誤處理
          // cin.getline( temp, 200 ) ;
          expression.clear() ;
          Reset() ;
        } // if
        
        if ( gerror.empty() == false && gerror[0] == 2  ) {
          const char* TEMP = ge[ 0 ].c_str() ;
          printf( "> Line %d : unexpected token : '%s'\n", gline, TEMP ) ;
          Scantillcline() ; // 還不確定她錯誤處理
          // cin.getline( temp, 200 ) ;
          expression.clear() ;
          Reset() ;
        } // if

        if ( gfinish == true && miscompound == 0 ) {
          // cout << "str :   " << str << "    " << "determine  :  DEF ->  "
          // << misdef << "      STATE  ->   " << misstate << endl ;
          Eval( expression ) ;
          expression.clear() ;
          Reset() ;
        } // if
      } // else

    } // while
  } // Scanner()

  bool Quit() {
    return misdone ;
  } // Quit()
} ; // Data()

int main() {
  int utestnum ;
  Data data ;

  cin >> utestnum ;
  char ch = cin.peek() ;
  while ( ch == ' ' || ch == '\t' || ch == '\n' ) {
    if ( ch == '\n' ) {
      scanf( "%c", &ch ) ;
      ch = 'q' ;
    } // if
    else {
      scanf( "%c", &ch ) ;
      ch = cin.peek() ;
    } // else
  } // while

  cout << "Our-C running ..." << endl ;
  do {
    data.Scanner() ;
  } while ( data.Quit() != true ) ;

  return 0 ;
} // main()