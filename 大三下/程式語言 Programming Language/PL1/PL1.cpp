# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <string.h> 
# include <string>
# include <cstdio>
# include <vector>
# include <stack>
# include <sstream>
# include <math.h>
# include <iomanip>
 
using namespace std ;

int gerror = 0 ; // her -> 1/2/3
vector<string> ge ;

struct Info {
  string name ; 
  string info ;
};

vector<Info> gvar ; // store variable

int Atoi( string& str ) {
  int num = 0;
  int sign = 1; // �P�_���t 
  int i = 0;
  
  if ( str[i] == '-' || str[i] == '+' ) {
    sign = ( str[i++] == '-' ) ? -1 : 1;
  } // if
  
  while ( '0' <= str[i] && str[i] <= '9' ) {
    num = num * 10 + ( str[i++] - '0' );
  } // while

  return num * sign ;
} // Atoi()

class Data {
  
  bool misquit ;
  
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
  
  bool Isothertype( char ch ) {
    if ( ch == '=' || ch == '>' || ch == '<' || ch == ';' || ch == '(' || ch == ')' ||
         ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ) {  
      return true ;
    } // if
    
    return false ;
  } // Isothertype()
  
  bool Isfloat( string str ) {
    for ( int i = 0 ; i < str.size() ; i++ ) {
      if ( str[i] == '.' ) {
        return true ;
      } // if
    } // for 
    
    return false ;
  } // Isfloat()
  
  bool Isop( string op ) {
    if ( op == "+" || op == "-" || op == "/" || op == "*" ) 
      return true ;
      
    return false ;
  } // Isop()
  
  bool Iswhitespace( char ch ) {
    if ( ch == ' ' || ch == '\t' || ch == '\n' ) {
      return true ;
    } // if
    
    return false ;
  } // Iswhitespace()
  
  bool Sametype( char c1, char c2 ) { // a little werid
    if ( Isdigit( c1 ) && Isdigit( c2 ) ) 
      return true ;
    if ( Isletter( c1 ) && Isletter( c2 ) ) 
      return true ;
    if ( Isothertype( c1 ) && Isothertype( c2 ) ) 
      return true ;
      
    return false ;
  } // Sametype()
  
  int Precendence( string op ) {
    // cout << op ;
    if ( op == "+" || op == "-" ) {
      return 1 ;
    } // if 
    else if ( op == "*" || op == "/" ) {
      return 2 ;
    } // else if 
    
    return 0 ;
  } // Precendence()
  
  bool Isboolop( string op ) {
    if ( op == "=" || op == "<>" || op == ">" || op == "<" || op == ">=" || op == "<=" ) {
      return true ;
    } // if
    
    return false ;
  } // Isboolop() 
  
  bool BoolexpF( float left, float right, string op ) {
    float threshold = 0.0001 ;
    if ( fabs( left - right ) == 0 ) {
      if ( op == "=" ) 
        return ( left == right ) ;
      if ( op == ">=" ) 
        return ( left >= right ) ;
      if ( op == "<=" ) 
        return ( left <= right ) ;
    } // if
    else if ( fabs( left - right ) <= threshold )  {
      if ( op == "=" ) 
        return true ;
      if ( op == "<>" ) 
        return false ;
      if ( op == ">" ) 
        return false ;
      if ( op == "<" ) 
        return false ;
      if ( op == ">=" ) 
        return ( left >= true ) ;
      if ( op == "<=" ) 
        return ( left <= true ) ;
    } // else if
    else {
      if ( op == "=" ) 
        return ( left == right ) ;
      if ( op == "<>" ) 
        return ( left != right ) ;
      if ( op == ">" ) 
        return ( left > right ) ;
      if ( op == "<" ) 
        return ( left < right ) ;
      if ( op == ">=" ) 
        return ( left >= right ) ;
      if ( op == "<=" ) 
        return ( left <= right ) ;
    } // else

    return false ;
  } // BoolexpF()
  
  // ==================================��k's part=====================
  
  int mindex ;
  vector<string> mtemp ;
  
  bool Isident( string str ) {
    if ( Isletter( str[0] ) == false )
      return false;

    for ( int i = 1; i < str.size() ; i++ ) {
      if ( Isletter( str[i] ) == false && Isdigit( str[i] ) == false && str[i] != '_' ) {
        return false;
      } // if
    } // for

    return true;
  } // Isident()

  bool Isnum( string str ) {
    int countdot = 0;
    int i = 0 ;
    if ( i == 0 && i + 1 == str.size() ) {   // num can onlt have one sign
      if ( str[i] == '-' || str[i] == '+' )
        return false ;
    } // if

    for ( int i = 0; i < str.size() ; i++ ) {
      if ( i != 0 && ( str[i] == '+' || str[i] == '-' ) ) {
        return false;
      } // if
      if ( Isdigit( str[i] ) == false && str[i] != '.' && str[i] != '-' && str[i] != '+' ) {
        return false;
      } // if
      if ( str[i] == '.' ) {
        countdot++;
        if ( countdot > 1 ) {
          return false;
        } // if
      } // if
    } // for

    return true;
  } // Isnum()
  
  string Gettok() {
    if ( mindex < mtemp.size() - 1 ) {
      mindex++ ;
      return mtemp[mindex] ;
    } // if
    
    return "outofindex" ;
  } // Gettok()

  // ========================================================Parsercommand
  bool Parsercommand( vector<string> v ) {   // - / 22 / - / 33  OR  // a / := / 4 /
    mtemp = v ;
    mindex = 0 ;
    string str = mtemp[mindex];     // get ident
    if ( Isident( str ) ) {   // IDENT   
      str = Gettok() ;
      if ( str == "outofindex" ) {
        return true ;
      } // if
      
      if ( str  == ":=" ) {    // Ū�U�@�ӧP�_ := || IDless 
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( ArithExp( str ) ) {
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
          if ( str == ";" ) 
            return true ;
        } // if
      } // if
      else {
        if ( str == ";" ) {   // a; ?????????????????????????????????????
          if ( Findvar( v[0] ) == "cannotfindthisword" ) {  
            gerror = 3 ;
            ge.push_back( v[0] ) ;
            return false ;
          } // if
          
          return true ;
        } // if
        
        if ( IDlessArithExpOrBexp( str ) ) {    // idless {+,a}[Bexp, Arith]
          if ( Findvar( v[0] ) == "cannotfindthisword" ) {   // a + b c// a need to be defined
            gerror = 3 ;
            ge.push_back( v[0] ) ;
          } // if
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
          if ( str == ";" ) 
            return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // else  
    } // if
    else if ( NOT_ID_StartArithExpOrBexp( str ) ) {
      str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( str == ";" ) 
        return true ;
    } // else if 
    else if ( str == "quit" ) {
      return true ;
    } // else if
    
    gerror = 2 ;
    ge.push_back( str ) ;
    return false ; 
  } // Parsercommand()
  // ========================================================IDlessArithExpOrBexp()
  bool IDlessArithExpOrBexp( string str ) {  // 
    bool havein = false ;
    while ( str == "+" || str == "-" || str == "*" || str == "/" ) {
      havein = true ;
      // cout << havein << endl ;
      if ( str == "+" || str == "-" ) {
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( Term( str ) ) {
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;  
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ; 
        } // else
      } // if
      else if ( str == "*" || str == "/" ) {
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        
        if ( Factor( str ) ) {
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ; 
        } // else
      } // else if
    } // while
    
    if ( BooleanOperator( str ) ) {
      str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( ArithExp( str ) ) {
        return true ;
      } // if
      else {
        gerror = 2 ;
        ge.push_back( str ) ;
        return false ; 
      } // else
    } // if
    else {
      if ( havein == false ) { // no in +_*/ && not bool
        gerror = 2 ;
        ge.push_back( str ) ;  
        return false ;
      } // if
      else {
        mindex--;
      } // else
    } // else
  
    return true ;
   
  } // IDlessArithExpOrBexp()
  // ========================================================
  bool BooleanOperator( string str ) {
    if ( str == "=" || str == "<>" || str == ">" || 
         str == "<" || str == ">=" || str == "<=" ) {
      return true ;       
    } // if

    return false ;
  } // BooleanOperator()
  // ========================================================
  bool NOT_ID_StartArithExpOrBexp( string str ) {
    if ( NOT_ID_StartArithExp( str ) ) {
      string str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( BooleanOperator( str ) ) {
        string str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( ArithExp( str ) ) {
          return true ;
        } // if
        else {  // is bool not arith -> wrong
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else 
      } // if
      else {
        mindex-- ;
      } // else
      
      return true ;
    } // if
    else {
      gerror = 2 ;
      ge.push_back( str ) ;
      return false ;
    } // else
    
    return true ;
  } // NOT_ID_StartArithExpOrBexp()
  
  // ========================================================
  bool NOT_ID_StartArithExp( string str ) {
    if ( NOT_ID_StartTerm( str ) ) {
      str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      while ( str == "+" || str == "-" ) {
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        
        // cout << "isT" << str << endl ;
        if ( Term( str ) ) {   // �ݦ��S������ 
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while
      
      if ( ( str == "+" || str == "-" ) == false ) {
        mindex-- ;
        return true ; // because can appear 0 ~ infinite
      } // if
      
      return true ;
    } // if
    
    gerror = 2 ;
    ge.push_back( str ) ;
    return false ;
  } // NOT_ID_StartArithExp()
  // ========================================================
  bool NOT_ID_StartTerm( string str ) {
    if ( NOT_ID_StartFactor( str ) ) {
      str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      
      while ( str == "*" || str == "/" ) {
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        
        if ( Factor( str ) ) {   // �ݦ��S������ 
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else
      } // while
      if ( ( str == "*" || str == "/" ) == false ) {
        mindex-- ;
        return true ; // because can appear 0 ~ infinite
      } // if
      
      return true ;
    } // if
    
    gerror = 2 ;
    ge.push_back( str ) ;
    return false ;
  } // NOT_ID_StartTerm()
  // ========================================================
  bool NOT_ID_StartFactor( string str ) {
    if ( str == "+" || str == "-" ) {   // [SIGN]
      string str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( Isnum( str ) ) {
        return true ;
      } // if
      else {
        gerror = 2 ;
        ge.push_back( str ) ;
        return false ;
      } // else 
    } // if
    else if ( Isnum( str ) ) {
      return true ;
    } // else if
    else if ( str == "(" ) {
      string str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( ArithExp( str ) ) {
        string str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( str == ")" ) {
          return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else 
      } // if
      else {
        gerror = 2 ;
        ge.push_back( str ) ;
        return false ;
      } // else
    } // else if
    
    gerror = 2 ;
    ge.push_back( str ) ;
    return false ;
  } // NOT_ID_StartFactor()

  // ========================================================
  bool ArithExp( string str ) {
    // cout << "ArithExp   " ; 
    if ( Term( str ) ) {
      str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      while ( str == "+" || str == "-" ) {
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( Term( str ) ) {   // �ݦ��S������ 
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else 
      } // while
      
      if ( ( str == "+" || str == "-" ) == false ) {
        mindex-- ;
        return true ; // because can appear 0 ~ infinite
      } // if
      
      return true ;
    } // if

    gerror = 2 ;
    ge.push_back( str ) ;
    return false ;
  } // ArithExp()
  // ========================================================term
  bool Term( string str ) {
    if ( Factor( str ) ) {
      str = Gettok() ;
      if ( str == "outofindex" ) return true ;   
      while ( str == "*" || str == "/" ) {
        str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( Factor( str ) ) {   // �ݦ��S������ 
          str = Gettok() ;
          if ( str == "outofindex" ) return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          return false ;
        } // else 
      } // while
      
      if ( ( str == "*" || str == "/" ) == false ) {
        mindex-- ;
        return true ; // because can appear 0 ~ infinite
      } // if
      
      return true ;
    } // if

    gerror = 2 ;
    ge.push_back( str ) ;
    return false ;
  } // Term()
  // ========================================================Factor 
  bool Factor( string str ) {
    if ( Isident( str ) ) {
      if ( Findvar( str ) == "cannotfindthisword" ) {
        gerror = 3 ;
        ge.push_back( str ) ;
      } // if
      
      return true ;
    } // if
    else if ( str == "+" || str == "-" ) {   // [SIGN]
      string str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( Isnum( str ) ) {
        return true ;
      } // if
      else {
        mindex-- ;
        gerror = 2 ;
        ge.push_back( str ) ;
        return false ;
      } // else 
    } // else if
    else if ( Isnum( str ) ) {
      return true ;
    } // else if
    else if ( str == "(" ) {
      string str = Gettok() ;
      if ( str == "outofindex" ) return true ;
      if ( ArithExp( str ) ) {
        string str = Gettok() ;
        if ( str == "outofindex" ) return true ;
        if ( str == ")" ) {
          return true ;
        } // if
        else {
          gerror = 2 ;
          ge.push_back( str ) ;
          mindex-- ;
          return false ;
        } // else
      } // if
      else {
        mindex-- ;
        gerror = 2 ;
        ge.push_back( str ) ;
        return false ;
      } // else 
    } // else if
    
    gerror = 2 ;
    ge.push_back( str ) ;
    return false ;
  } // Factor()
  
  // =======================================��k����==============================
  void Fixexp( vector<string> & expression ) { // a:=-16-9-(+3--4);
    if ( expression.size() >= 2 ) {
      if ( ( expression[0] == "+" || expression[0] == "-" ) && Isnum( expression[1] ) ) {
        expression[1] = expression[0] + expression[1] ;
        expression.erase( expression.begin() ) ;
      } // if
    } // if
    
    for ( int i = 0 ; i < expression.size() - 2 && expression.size() > 2 ; i++ ) {
      if ( ( Isop( expression[i] ) || expression[i] == "(" ) && Isnum( expression[i+2] ) &&
           ( expression[i+1] == "+" || expression[i+1] == "-" )  ) {
        expression[i+2] = expression[i+1] + expression[i+2] ;
        expression.erase( expression.begin() + i + 1 ) ;    
      } // if
    } // for
    
  } // Fixexp()
  
  float CalculateF( vector<string> expression ) {
    vector<string> out ;
    stack<string> op ;
    Fixexp( expression ) ;
    for ( int i = 0 ; i < expression.size() ; i++ ) {
      if ( expression[i] == "(" ) {     // ( ��Jop 
        op.push( expression[i] ) ;
      } // if
      else if ( expression[i] == ")" ) {   // ) �bop���(���� 
        while ( op.top() != "(" ) {
          string str = op.top() ;
          op.pop() ;
          out.push_back( str ) ;
        } // while
        
        op.pop() ; // pop out "("
      } // else if
      else if ( expression[i] == "+" || expression[i] == "-" ||
                expression[i] == "*" ||  expression[i] == "/" ) {  // �u������ 
           
        if ( op.empty() == true || Precendence( expression[i] ) > Precendence( op.top() ) ) {
          op.push( expression[i] ) ;
        } // if 
        else {
          while ( op.empty() == false && Precendence( expression[i] ) <= Precendence( op.top() ) ) {
            string str = op.top() ;
            out.push_back( str ) ;
            op.pop() ;
          } // while 
          
          op.push( expression[i] ) ;
        } // else
      } // else if 
      else {  // number
        out.push_back( expression[i] ) ;
      } // else
      
    } // for
    
    while ( op.empty() == false ) {
      string str = op.top() ;
      op.pop() ;
      out.push_back( str ) ;
    } // while
    
    stack<string> temp ;
    float t1, t2 ;
    char buffer[32];
    float ans ;
        
    for ( int i = 0 ; i < out.size() ; i++ ) {
      if ( out[i] != "+" && out[i] != "-" && out[i] != "*" &&  out[i] != "/" ) {
        temp.push( out[i] ) ;
      } // if
      else {
        t2 = atof( temp.top().c_str() ) ;
        temp.pop() ;
        t1 = atof( temp.top().c_str() ) ;
        temp.pop() ;
        
        if ( out[i] == "+" ) {
          ans = t1 + t2 ;
        } // if
        else if ( out[i] == "-" ) {
          ans = t1 - t2 ;
        } // else if
        else if ( out[i] == "*" ) {
          ans = t1 * t2 ;
        } // else if
        else if ( out[i] == "/" ) {
          ans = t1 / t2 ;
        } // else if
        
        sprintf( buffer, "%f", ans );
        string a( buffer ) ;
        temp.push( a ) ;
      } // else
    } // for
    
    return atof( temp.top().c_str() ) ;
    
  } // CalculateF()
  
  int Calculate( vector<string> expression ) {
    vector<string> out ;
    stack<string> op ;
    Fixexp( expression ) ;
    for ( int i = 0 ; i < expression.size() ; i++ ) {
      // cout << "e : " << expression[i] << endl ;
      if ( expression[i] == "(" ) {     // ( ��Jop 
        op.push( expression[i] ) ;
      } // if
      else if ( expression[i] == ")" ) {   // ) �bop���(���� 
        while ( op.top() != "(" ) {
          string str = op.top() ;
          op.pop() ;
          out.push_back( str ) ;
        } // while
        
        op.pop() ; // pop out "("
      } // else if
      else if ( expression[i] == "+" || expression[i] == "-" ||
                expression[i] == "*" ||  expression[i] == "/" ) {  // �u������ 
        if ( op.empty() == true || Precendence( expression[i] ) > Precendence( op.top() ) ) {
          op.push( expression[i] ) ;
        } // if 
        else {
          while ( op.empty() == false && Precendence( expression[i] ) <= Precendence( op.top() ) ) {
            string str = op.top() ;
            out.push_back( str ) ;
            op.pop() ;
          } // while 
          
          op.push( expression[i] ) ;
        } // else
      } // else if 
      else {  // number
        out.push_back( expression[i] ) ;
      } // else
    } // for
    
    while ( op.empty() == false ) {
      string str = op.top() ;
      op.pop() ;
      out.push_back( str ) ;
    } // while
    
    stack<string> temp ;
    int t1, t2 ;
    char buffer[32];
    int ans ;
        
    for ( int i = 0 ; i < out.size() ; i++ ) {
      if ( out[i] != "+" && out[i] != "-" && out[i] != "*" &&  out[i] != "/" ) {
        temp.push( out[i] ) ;
      } // if
      else {
        t2 = Atoi( temp.top() ) ;
        temp.pop() ;
        t1 = Atoi( temp.top() ) ;
        temp.pop() ;
        
        if ( out[i] == "+" ) {
          ans = t1 + t2 ;
        } // if
        else if ( out[i] == "-" ) {
          ans = t1 - t2 ;
        } // else if
        else if ( out[i] == "*" ) {
          ans = t1 * t2 ;
        } // else if
        else if ( out[i] == "/" ) {
          ans = t1 / t2 ;
        } // else if
        
        sprintf( buffer, "%d", ans );
        string a( buffer ) ;
        temp.push( a ) ;
      } // else
    } // for
    
    return atoi( temp.top().c_str() ) ;
    
  } // Calculate()
  
  string Findvar( string str ) {
    for ( int i = 0 ; i < gvar.size() ; i++ ) {
      if ( gvar[i].name == str ) {
        return gvar[i].info ;
      } // if
    } // for
    
    return "cannotfindthisword" ;
  } // Findvar()

  void Eval( vector<string> expression ) { // In theory, it's supposed to detect grammer
    bool isboolexp = false ;
    bool isassign = false ;
    bool havefloat = false ;
    int ans = 0 ;
    float fans = 0.0 ;
    vector<string> exp1, exp2 ;
    
    string getval ;
    bool findas = false ;
    for ( int i = 0 ; i < expression.size() ; i++ ) { // �ˬdassign �ᦳident����exist ,��g�ȶi�J 
      if ( expression[i] == ":=" ) {
        findas = true ;
        i++ ;
      } // if
      
      if ( Isident( expression[i] ) && findas ) {
        getval = Findvar( expression[i] ) ;
        if ( getval == "cannotfindthisword" ) {
          const char* CSTR = expression[i].c_str() ;
          printf( "> Undefined identifier : '%s'\n", CSTR ) ;
          return ;
        } // if
        else {
          expression[i] = getval ;
        } // else
      } // if
    } // for
    
    for ( int i = 0 ; i < expression.size() ; i++ ) {  // have float num
      if ( Isfloat( expression[i] ) ) {
        havefloat = true ;
      } // if
    } // for
    
    // ===========================pre-process================================================
    string tass ; // store :=
    string str ;
    for ( int j = 0 ; j < expression.size() ; j++ ) {  // determine is assigner 
      if ( expression[j] == ":=" ) {
        tass = expression[j] ;
        isassign = true ;
        j++ ;
      } // if
      if ( isassign == false && Isident( expression[j] ) ) {  // a := 3, �b:=�e��ident�s�Jassign 
        str = expression[j] ;
      } // if
      else if ( isassign == true ) {
        exp2.push_back( expression[j] ) ;
      } // else if
    } // for
    
    if ( isassign == true ) {
      char buffer[100] ;
      Info temp ;
      if ( havefloat == true ) {
        fans = CalculateF( exp2 ) ;
        printf( "> %1.3f\n", fans ) ;
        stringstream ss ;
        ss << fixed << setprecision( 4 ) << fans;
        string a( ss.str() );
        temp.info = a ;
      } // if
      else {
        ans = Calculate( exp2 ) ;
        printf( "> %d\n", ans ) ;
        stringstream ss ;
        ss << ans;
        string a( ss.str() );
        temp.info = a ;
      } // else
      
      bool same = false ;
      int index = -1 ;
      for ( int i = 0 ; i < gvar.size() ; i++ ) {
        if ( str == gvar[i].name ) {  // is var have same in buffer, need to update
          same = true ;
          index = i ;
        } // if
      } // for
    
      if ( same ) {
        gvar[index].info = temp.info ;
      } // if
      else {
        temp.name = str ;
        gvar.push_back( temp ) ;
      } // else

      return ;
    } // if
    
    // ===================================expression's part==========================
    for ( int i = 0 ; i < expression.size() ; i++ ) {
      if ( Isident( expression[i] ) ) {
        getval = Findvar( expression[i] ) ;
        if ( getval == "cannotfindthisword" ) {
          const char* CSTR = expression[i].c_str() ;
          printf( "> Undefined identifier : '%s'\n", CSTR ) ;
          return ;
        } // if
        else {
          expression[i] = getval ;
        } // else
      } // if
    } // for
    
    havefloat = false ;
    for ( int i = 0 ; i < expression.size() ; i++ ) {  // have float num -> 
      if ( Isfloat( expression[i] ) ) {
        havefloat = true ;
      } // if
    } // for
    
    for ( int i = 0 ; i < expression.size() - 1 && expression.size() != 1 ; i++ ) {  //  x/0
      if ( expression[ i ] == "/" && atof( expression[i+1].c_str() ) == 0 && Isnum( expression[i+1] ) ) {
        cout << "e:" << expression[i+1] ;
        cout << "ERROR" << endl ;
        return ;
      } // if
    } // for

    string optemp ;
    for ( int j = 0 ; j < expression.size() ; j++ ) { // �ݬO���Obool exp 
      if ( Isboolop( expression[j] ) ) {
        optemp = expression[j] ;
        isboolexp = true ;
        j++ ;
      } // if
      if ( isboolexp == false ) {
        exp1.push_back( expression[j] ) ;
      } // if
      else if ( isboolexp == true ) {
        exp2.push_back( expression[j] ) ;
      } // else if
    } // for
    
    if ( isboolexp == false && havefloat == true ) {   // exp and f
      fans = CalculateF( expression ) ;
      printf( "> %1.3f\n", fans ) ;
    } // if
    else if ( isboolexp == true ) {  // bo and f -> use float 
      if ( BoolexpF( CalculateF( exp1 ), CalculateF( exp2 ), optemp ) )
        cout << "> true" << endl;
      else 
        cout << "> false" << endl;
    } // else if
    
    if ( isboolexp == false && havefloat == false ) { // exp and int
      ans = Calculate( expression ) ;
      cout << "> " << ans << endl;
    } // if
  } // Eval()
  
  string Gettoken( char ch ) {    // �P�_token�æ^��, main function is "determine" 
    char next = cin.peek() ;
    char now = ch ;
    string str ;
    int dotnum = 0 ;  // 
    char first = ch ; // can't be '_'
    bool isnum = false ;
    bool isident = false ;
    bool isother = false ;
    if ( now == ':' && next == '=' ) {
      str += now ;
      scanf( "%c", &now ) ;
      next = cin.peek() ;
      str += now ;
      return str ;
    } // if
    else if ( first == '_' || ( first == '.' && Isdigit( next ) == false ) ) {
      gerror = 1 ;
      str += now ;
      return str ;
    } // else if
    else if ( Isletter( now ) == false && Isdigit( now ) == false && Isothertype( now ) == false ) {
      gerror = 1 ;
      str += now ;
      return str ;
    } // else if

    str += ch ;
    char temp[200] ;
    if ( Isdigit( now ) || first == '.' ) {
      if ( first == '.' ) {
        dotnum++ ;
      } // if
      
      isnum = true ;
    } // if
    else if ( Isletter( now ) ) {
      isident = true ;
    } // else if
    else {
      isother = true ;
    } // else
    
    while ( isnum || isident || isother ) {
      // cout << "now: " << now << "   next: " << next << endl ;
      if ( isnum && ( ( Isdigit( now ) && Isdigit( next ) ) || next == '.' ||  
                      ( now == '.' && Isdigit( next ) ) ) ) { // ===================num==========
        if ( next == '.' ) {
          dotnum++ ;
        } // if
        if ( dotnum <= 1 ) {
          str += next ;
        } // if
        else {
          return str ;
        } // else 
      }  // if 
      else if ( isident && 
                ( ( now == '_' && next == '_' ) ||
                  ( Isletter( now ) && Isletter( next ) ) || ( now == '_' && Isletter( next ) ) || 
                  ( Isletter( now ) && Isdigit( next ) ) || ( Isletter( now ) && next == '_' ) || 
                  ( Isdigit( now ) && Isletter( next ) ) || ( now == '_' && Isdigit( next ) ) ||
                  ( Isdigit( now ) && Isdigit( next ) )  || ( Isdigit( now ) && next == '_' ) ) ) {  // ident
        str += next ;
      } // else if
      else { // ====================================othrtpart=======================
        if ( now == '<' && ( next == '>' || next == '=' ) ) {
          str += next ;
          if ( str == "<>" || str == "<=" ) {
            scanf( "%c", &now ) ;
            return str ;
          } // if
        } // else if
        else if ( now == '>' && next == '=' ) {
          str += next ;
          if ( str == ">=" ) {
            scanf( "%c", &now ) ;
            return str ;
          } // if
        } // else if
        else if ( now == '/' ) {
          if ( next == '/' ) {
            
            cin.getline( temp, 200 ) ;
            now = cin.peek() ;
            str = now ;
            while ( Iswhitespace( now ) ) {
              scanf( "%c", &now ) ;
              now = cin.peek() ;
              str = now ;
              // cout << "///str : " << str ;
            } // while
            
            if ( Isdigit( now ) || first == '.' ) {
              if ( first == '.' ) {
                dotnum++ ;
              } // if
              
              isnum = true ;
            } // if
            else if ( Isletter( now ) ) {
              isident = true ;
            } // else if
            else {
              isother = true ;
            } // else
          } // if
          else {
            return str ;
          } // else
        } // else if
        else {
          return str ;
        } // else  
      } // else 

      scanf( "%c", &ch ) ;
      now = ch ;
      next = cin.peek() ;
    } // while

    return str ;
  } // Gettoken()
  
public :

  Data() {
    misquit = false ;
  } // Data()

  void Scanner() {     // use Gettoken() to get token and store into a vector, a whole command till ";".
    char ch ;
    string str ;
    vector <string> expression ;
    char temp[200] ;
    scanf( "%c", &ch ) ;
    while ( 1 ) {
      if ( Iswhitespace( ch ) ) {  // " ", "\t", "\n"
      } // if
      else {
        str = Gettoken( ch ) ;
        if ( gerror == 1 ) {
          const char* CSTR = str.c_str() ;
          printf( "> Unrecognized token with first char : '%s'\n", CSTR ) ; 
          cin.getline( temp, 200 ) ;
          expression.clear() ;
          gerror = 0 ;
        } // if 
        else {
          expression.push_back( str ) ;
          if ( expression[0] == "quit" ) {
            cout << "> Program exits..." << endl ;
            misquit = true ;
            return ;
          } // if
          Parsercommand( expression ) ; // parser check
          if ( gerror == 2 ) {
            const char* CSTR = ge[0].c_str() ;
            printf( "> Unexpected token : '%s'\n", CSTR ) ;
            cin.getline( temp, 200 ) ;
            expression.clear() ;
            gerror = 0 ;
            ge.clear() ;
          } // if
          else if ( gerror == 3 ) {
            const char* CSTR = ge[0].c_str() ;
            printf( "> Undefined identifier : '%s'\n", CSTR ) ;
            cin.getline( temp, 200 ) ;
            expression.clear() ;
            gerror = 0 ;
            ge.clear() ;
          } // else if
          else {
            if ( str == ";" ) {
              expression.pop_back() ;
              Eval( expression ) ;
              expression.clear() ;
            } // if
          } // else 
        } // else
      } // else
      
      scanf( "%c", &ch ) ;   
    } // while
  } // Scanner()

  bool Quit() {
    return misquit ;
  } // Quit()

};

int main() {
  int utestnum ;
  Data data ;
  cin >> utestnum ;
  cout << "Program starts..." << endl;
  do {
    data.Scanner() ;
  } while ( data.Quit() != true ) ;
  
  return 0 ;

} // main()

/* 
hidden data ;

1.(1,2)����// (�i��) 

2.(3,4)float�B��

3. (3,4) a/0 -> Error

4.(7)<0.0001 -> 
( 1 / 100000 ) = ( 1/10000000 ) ;  // difference is within 0.0001
( 1 / 100000 ) > ( 1/10000000 ) ;
( 1 / 100 ) = ( 1/1000000 ) ;  // difference is more than 0.0001
( 1 / 100 ) > ( 1/1000000 ) ;

5.(9) a:=1 ; a*1:=4 ; error-> :=
*/

