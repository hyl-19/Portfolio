 // 第07組 11027212 黃建閎 11027222 黃彥霖
// DS 3

# include <iostream>
# include <cstring>
# include <string>
# include <cstdlib>
# include <vector>
# include <math.h>
# include <algorithm>

using namespace std ;

struct Node {  //stack 
	
	string data ;  //存資料 
	Node * next ;
	
};

bool isEmpty( Node * list ) {
// 查看stack是否為空的	
	if ( list == NULL ) 
		return true ;
	return false ;
	
} // isEmpty

Node * Push( string data, Node * list ) { 
// 丟進去stack的最上面 
	
	Node * newNode = new Node ;
	
	newNode->data = data ;
	newNode->next = list ;
	list = newNode ;
	
	return list ;
	
} // Push
	
Node * Pop( Node * list ) {
// 刪除最上面stack的node 
	
	Node * temp = NULL ;
	
	if ( isEmpty( list ) ) 
		return list ;
		
	temp = list ;
	list = list->next ;
	delete temp ; // 釋放記憶體
		
	return list ; 
	
} // Pop

Node * Clear( Node * list ) {
// 清光stack 
	
	Node * temp = NULL ;
	
	while ( list != NULL ) {
		
		temp = list ;
		list = list->next ;
		delete temp ; // 釋放記憶體
			
	} // while
		
	return list ;
	
} // Clear
		
void Print( Node * list ) {
// 印出全部stack 
			
	if ( isEmpty( list ) ) return ;
			
	Node * printNode = list ;
			
	while ( printNode != NULL ) {
				
		cout << printNode->data ;
		if ( printNode->next != NULL ) cout << ", " ;
			
		printNode = printNode->next ;
				
	} // while
			
	cout << endl ;
			
} // Print
	
string GetTopData( Node * list ) {
// 取出最上層的Data 

	return list->data ;
			
} // GetTopData
		
struct Error {
// 記錄錯誤資訊 
	
	int type[3] = {0, 0, 0} ; // 第幾個錯誤 
	vector<char> ch ; // 存錯誤的字元 
	int par = 0 ; // 存括弧 
	int oper = 0 ; // 存運算子 
	
};

bool ErrorOfChar( string in, vector<char> & ch ) {
// 第一個Error 檢查是否為正確的字元 
	
	bool find = false ;
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( !(in[i] >= '0' && in[i] <= '9') ) { // 是否為數字 
			if ( in[i] != '+' && in[i] != '-' && in[i] != '*' && in[i] != '/' &&
			     in[i] != '(' && in[i] != ')' ) { // 是否為合理的運算子 
				find = true ;
				ch.push_back(in[i]) ; // 存入錯誤的運算子 
			} // if
		} // if
		
	} // for
	
	return find ;
	
} // ErrorOfChar

bool ErrorOfParentheses( string in, int & par ) {
// 第二的Error 檢查括弧有沒有對稱 
	
	bool find = false ;
	
	int leftPar = 0 ; // 紀錄'(' 
	int rightPar = 0 ; // 紀錄')'
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( in[i] == '(' ) leftPar++ ;
		else if ( in[i] == ')' ) rightPar++ ; 
		
	} // for
	
	if ( leftPar != rightPar ) { // 右括弧必須等於左括號 
		
		find = true ;
		par = leftPar - rightPar ;
		// 若par為負->右括弧有多
		// 若par為正->左括弧有多 
		
	} // if
	
	return find ;
	
} // ErrorOfParentheses

bool ErrorOfOperator( string in, int & oper ) {
// 第三個Error 檢查有沒有多餘的運算子 
	
	bool find = false ;
	int num = 0 ; // 紀錄有幾個數字
	int value = 0 ; // 紀錄有幾個運算子
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( in[i] >= '0' && in[i] <= '9' ) {
			if ( in[i+1] == '+' || in[i+1] == '-' || in[i+1] == '*' || in[i+1] == '/' || 
			     in[i+1] == ')' || i == in.size() - 1 )
				num++ ;
		} // if
		else if ( in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' ) value++ ;
		
	} // for
	
	if ( num != value + 1 ) { // 數字為運算子+1 
		
		find = true ;
		oper = num - value - 1 ;
		// oper為負->有多運算子
		// oper為正->有少運算子 

	} // if
	
	return find ;
	
} // ErrorOfOperator

bool CheckParentheses( string in ) {
// 第三個Error 檢查括號內是否為infix 
	
	bool start = false ;
	int num = 0 ; // 紀錄數字 
	int value = 0 ; // 紀錄運算子 
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( in[i] == '(' ) {
			start = true ; // 遇到左括弧開始記錄 
			num = 0 ;
	 		value = 0 ;
		} // if
		else if ( in[i] == ')' ) {
			start = false ; // 遇到右括弧結束紀錄 
			if ( num != value + 1 )		
				return true ;
		} // else if
		else if ( start ) {	
			if ( in[i] >= '0' && in[i] <= '9' ) {
				if ( in[i+1] == '+' || in[i+1] == '-' || in[i+1] == '*' || in[i+1] == '/' || 
			     	in[i+1] == ')' || i == in.size() - 1 )
					num++ ;
			} // if
			else if ( in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' ) value++ ;
		} // else if
		
	} // for
		
	return false ;
	
} // CheckParentheses

bool FindError( string in, int type[3], vector<char> & ch, int & par, int & oper ) {
// 尋找有沒有Error 
	
	bool find = false ;
	
	if ( ErrorOfChar(in, ch) ) { // Error 1
		type[0] = 1 ;
		find = true ;
	} // if
	
	if ( ErrorOfParentheses(in, par) ) { // Error 2 
		type[1] = 1 ;
		find = true ;
	} // if
	
	if ( ErrorOfOperator(in, oper) ) { // Error 3
		type[2] = 1 ;
		find = true ;
	} // if
	
	if ( CheckParentheses(in) ) { // Error 3
		type[2] = 2 ;
		find = true ;
	} //CheckParentheses
	
	return find ;
	
} // FindError

void PrintError( int type[3], vector<char> ch, int par, int oper ) {
// 印出Error 
	
	if ( type[0] == 1 ) { // error 1
		
		cout << "Error 1: " ;
		
		for ( int i = 0 ; i < ch.size() ; i++ ) {
			
			cout << ch.at(i) ;
			if ( i != ch.size() - 1 ) cout << ", " ;
			 
		} // for
		
		if ( ch.size() == 1 ) cout << " is NOT a legitimate character." << endl ;
		else cout << " are NOT legitimate characters." << endl ; 
		
	} // if
	
	if ( type[1] == 1 ) { // error 2
		
		cout << "Error 2: there " ;
		
		if ( par > 0 ) { // left > right -> "open"
		
			if ( par == 1 ) cout << "is 1 extra open parenthesis." << endl ;
			else cout << "are " << par << " extra open parenthesis." << endl ;
		
		} // if
		else if ( par < 0 ) { // left < right -> "close"
		
			if ( par == -1 ) cout << "is 1 extra close parenthesis." << endl ;
			else cout << "are " << -par << " extra close parenthesis." << endl ;
			
		} // else if
		
	} // if
	
	if ( type[2] == 2 ) cout << "Error 3: It is NOT infix in the parentheses." << endl ;
	else if ( type[2] == 1 ) { // error 3
	
		cout << "Error 3: there " ;
		
		if ( oper > 0 ) { // 少了運算子 
		
			if ( oper == 1 ) cout << "is 1 extra operand." << endl ;
			else cout << "are " << oper << " extra operands." << endl ;
		
		} // if
		else if ( oper < 0 ) { // 多了運算子
		
			if ( oper == -1 ) cout << "is 1 extra operator." << endl ;
			else cout << "are " << -oper << " extra operators." << endl ;
			
		} // else if
	
	} // else if
	
} // PrintError

int OperPriority( string op ) {
// 紀錄運算子的優先順序 
	
	if ( op == "(" ) return 1 ; // 括弧內先做 
	else if ( op == "+" || op == "-" ) return 2 ; // 後加減 
	else if ( op == "*" || op == "/" ) return 3 ; // 先乘除 
	else return 0 ;
	
} // OperPriority

string SetOper( char op ) {
// 字元轉字串 
	
	if ( op == '+' ) return "+" ;
	else if ( op == '-' ) return "-" ;
	else if ( op == '*' ) return "*" ;
	else if ( op == '/' ) return "/" ;
	else if ( op == '(' ) return "(" ;
	else if ( op == ')' ) return ")" ;
	
} // SetOper

Node * ToPostFix( string in ) {
	
	Node * oper = NULL ;    // 存運算子 
	Node * number = NULL ;  // 存整體的資訊(數字) 
	char value[100] = {0} ; // 存數字使用的 
	string str ;            // 存數字使用的  
	int index = 0 ;         // 紀錄value的位置  
	
	for ( int i = 0 ; i < in.size() ; i++ ) { // 拿字串裡的字元一個一個比對 
		
		if ( '0' <= in[i] && in[i] <= '9' ) {    
				value[index] = in[i] ;
				index++ ;
			if ( !('0' <= in[i+1] && in[i+1] <= '9') || i == in.size()-1 ) {  // 數字下一個是運算子 
				str = value ;   // 字元陣列轉字串 
				number = Push(value, number) ;   // 存入stack 
				memset(value, 0, 100) ;  // 清空value 
				index = 0 ;  //初始化 
			} // if
		} // if
		else if ( in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '(' || in[i] == ')') {
		// 是運算子	 
			if ( in[i] == '(' ) oper = Push("(", oper) ;  // 右括弧先存入 
			else if ( in[i] == ')' ) {  // 括號內先做 
				while( GetTopData(oper) != "(" ) {  // 遇到左括弧前都丟入number裡 
					number = Push(GetTopData(oper), number) ;
					oper = Pop(oper) ;
				} // while
				
				oper = Pop(oper );  // 刪除已存入的運算子  
			} // else if
			else { // 先乘除後加減
				str = SetOper(in[i]) ; // 轉換型別  
				if ( isEmpty(oper) || OperPriority(str) > OperPriority(GetTopData(oper)) )
				//新大於舊 放後面 ，若stack為空的或運算子的優先順序小於stack of top data， 
					oper = Push(str, oper) ; // 存入number
				else { 
				// 若不是空的或運算子的優先順序大於stack of top data
					while ( !isEmpty(oper) && OperPriority(str) <= OperPriority(GetTopData(oper)) ) {
						number = Push(GetTopData(oper), number) ; // 存入number
						oper = Pop(oper) ; // 刪除已加入output的運算子
					} // while
					
					oper = Push(str, oper); // 存入number
				} // else
			} // else
		} // else if
		
	} // for
	
	//將剩下的operator丟進number裡
	while ( oper != NULL ) {
		number = Push(GetTopData(oper), number) ;
		oper = Pop(oper) ;
	} // while
	
	//倒過來裝進去印出來 
	Node * result = NULL;
	
	while ( !isEmpty(number) ) {
		result = Push(GetTopData(number), result) ;
		number = Pop(number) ;
	} // while

	return result;
		
} // ToPostFix

bool isDigit( string str ) {
// 是否為數字 	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( str[i] >= '0' && str[i] <= '9' ) continue ;
		else return false ;
		
	} // for
	
	return true ;
	
} // isDigit

int Calculate( string s1, string s2, string op ) {
// 回傳運算後的數字 ，進來是string所以用atoi 

	int num1 = atoi(s1.c_str()) ;
	int num2 = atoi(s2.c_str()) ;
	if ( op == "+" ) return num1 + num2 ;
	else if ( op == "-" ) return num1 - num2 ;
	else if ( op == "*" ) return num1 * num2 ;
	else if ( op == "/" ) return num1 / num2 ;
	return 0 ;
} // Calculate

string Change( int num ) {
//把int轉成string，因為存data型別是string 
    char temp[100]; 
    string str ;
    sprintf( temp, "%d", num );  
    str = temp ;
    return str ;
}


void CalculatePostfix( Node * list , int & num ,int & total ) { 
//計算後序式 
	string num1 ; //紀錄第一個數字 
	string num2 ; //記錄第二個數字 
	int numt ;    //相加一二數字用 
	Node * temp = NULL ; //設定一個新的temp用來存要算的東西 
	string value ;   //value存stack用 

	while ( !isEmpty(list) ) {    

		value = GetTopData(list) ;    
		if ( isDigit(value) ) {
			temp = Push( value, temp) ;   //拿到數字先丟進新的stack裡面 
			// cout << temp -> data ;
		}
		else {  //碰到運算子就分別做，方法都一樣 
		/***
		遇到運算子，從temp上面取數字到num2然後pop掉，在取數字到num1然後pop，
		拿去相加轉成string在push回temp裡面 
		***/
			if ( value == "+" ) {
				num2 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				num1 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				numt = Calculate( num1, num2, value) ;
				value = Change( numt ) ;
				temp = Push(value,temp) ;
			} 
			else if (value == "-" ) {
				num2 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				num1 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				numt = Calculate( num1, num2, value) ;
				value = Change( numt ) ;
				temp = Push(value,temp) ;
			}
			else if (value == "*" ) {
				num2 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				num1 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				numt = Calculate( num1, num2, value) ;
				value = Change( numt ) ;
				temp = Push(value,temp) ;
			}
			else if (value == "/" ) {
				num2 = GetTopData(temp) ;
				numt = atoi(num2.c_str()) ;
				if( numt == 0 ) {     // 遇到/0的狀況會錯，就回報 
					num = 0 ;
					break ;
				}
				temp = Pop( temp ) ;
				num1 = GetTopData(temp) ;
				temp = Pop( temp ) ;
				numt = Calculate( num1, num2, value) ;
				value = Change( numt ) ;
				temp = Push(value,temp) ;
			}
		}
		
		list = Pop(list) ;   //最上面用完就刪掉 
	}
	
	value = GetTopData(temp) ;  //最剩下最後的結果在temp裡 
	total = atoi(value.c_str()) ;
	
	
} // CalculatePostfix

void mission1() {
// 任務一 
	
	string input = "/0" ; // 存Evaluator
	Error error ; // 初始化Error struct 
	Node * postfix = NULL ; // 初始化指標 
	int total = 0 ; // 最後答案 
	int errorNum = -1 ; // 除數是否為0
	
	cout << endl << "Input an infix expression: " ;
	getline(cin, input) ; // 讀入一行 
	input.erase(remove(input.begin(), input.end(), ' '), input.end()) ; // 去除空白 
	
	if ( FindError(input, error.type, error.ch, error.par, error.oper) ) // 尋找error 
		PrintError(error.type, error.ch, error.par, error.oper) ;
	else { // 開始從中序轉後續 
		postfix = ToPostFix(input) ;
		cout << "It is a legitimate infix expression." << endl ;
		cout << "Postfix expression: " ;
		
		Print(postfix) ; // 印出後續 
		CalculatePostfix(postfix, errorNum, total ) ; // 計算答案 
		
		if ( errorNum == 0 ) { // 除數為0 
			cout << "### Error: Divided by ZERO! ###" << endl ;
			cout << "### It cannot be successfully evaluated! ###" << endl ;
			postfix = Clear(postfix) ; // 釋放記憶體 
		} // if
		else cout << "Answer: " << total << endl ;
	} // else
	
} // mission1

int main() {
	
	string command ;
	int cd = 0 ;
	
	do {
		
		cout << endl << "* Arithmetic Expression Evaluator *" ;
		cout << endl << "* 0. QUIT                         *" ;
		cout << endl << "* 1. Infix2postfix Evaluation     *" ;
		cout << endl << "***********************************" ;
		cout << endl << "Input a choice(0, 1): " ;
		getline(cin, command) ;
		
		if ( !isDigit(command) ) return 0 ;
		else cd = atoi(command.c_str()) ;
		
		if ( cd == 0 ) return 0 ;
		else if ( cd == 1 ) mission1() ;
		else cout << endl << "Command does NOT exsit!" << endl ;
		
	} while( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
