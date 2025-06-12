 // ��07�� 11027212 ���ض� 11027222 �����M
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
	
	string data ;  //�s��� 
	Node * next ;
	
};

bool isEmpty( Node * list ) {
// �d��stack�O�_���Ū�	
	if ( list == NULL ) 
		return true ;
	return false ;
	
} // isEmpty

Node * Push( string data, Node * list ) { 
// ��i�hstack���̤W�� 
	
	Node * newNode = new Node ;
	
	newNode->data = data ;
	newNode->next = list ;
	list = newNode ;
	
	return list ;
	
} // Push
	
Node * Pop( Node * list ) {
// �R���̤W��stack��node 
	
	Node * temp = NULL ;
	
	if ( isEmpty( list ) ) 
		return list ;
		
	temp = list ;
	list = list->next ;
	delete temp ; // ����O����
		
	return list ; 
	
} // Pop

Node * Clear( Node * list ) {
// �M��stack 
	
	Node * temp = NULL ;
	
	while ( list != NULL ) {
		
		temp = list ;
		list = list->next ;
		delete temp ; // ����O����
			
	} // while
		
	return list ;
	
} // Clear
		
void Print( Node * list ) {
// �L�X����stack 
			
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
// ���X�̤W�h��Data 

	return list->data ;
			
} // GetTopData
		
struct Error {
// �O�����~��T 
	
	int type[3] = {0, 0, 0} ; // �ĴX�ӿ��~ 
	vector<char> ch ; // �s���~���r�� 
	int par = 0 ; // �s�A�� 
	int oper = 0 ; // �s�B��l 
	
};

bool ErrorOfChar( string in, vector<char> & ch ) {
// �Ĥ@��Error �ˬd�O�_�����T���r�� 
	
	bool find = false ;
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( !(in[i] >= '0' && in[i] <= '9') ) { // �O�_���Ʀr 
			if ( in[i] != '+' && in[i] != '-' && in[i] != '*' && in[i] != '/' &&
			     in[i] != '(' && in[i] != ')' ) { // �O�_���X�z���B��l 
				find = true ;
				ch.push_back(in[i]) ; // �s�J���~���B��l 
			} // if
		} // if
		
	} // for
	
	return find ;
	
} // ErrorOfChar

bool ErrorOfParentheses( string in, int & par ) {
// �ĤG��Error �ˬd�A�����S����� 
	
	bool find = false ;
	
	int leftPar = 0 ; // ����'(' 
	int rightPar = 0 ; // ����')'
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( in[i] == '(' ) leftPar++ ;
		else if ( in[i] == ')' ) rightPar++ ; 
		
	} // for
	
	if ( leftPar != rightPar ) { // �k�A���������󥪬A�� 
		
		find = true ;
		par = leftPar - rightPar ;
		// �Ypar���t->�k�A�����h
		// �Ypar����->���A�����h 
		
	} // if
	
	return find ;
	
} // ErrorOfParentheses

bool ErrorOfOperator( string in, int & oper ) {
// �ĤT��Error �ˬd���S���h�l���B��l 
	
	bool find = false ;
	int num = 0 ; // �������X�ӼƦr
	int value = 0 ; // �������X�ӹB��l
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( in[i] >= '0' && in[i] <= '9' ) {
			if ( in[i+1] == '+' || in[i+1] == '-' || in[i+1] == '*' || in[i+1] == '/' || 
			     in[i+1] == ')' || i == in.size() - 1 )
				num++ ;
		} // if
		else if ( in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' ) value++ ;
		
	} // for
	
	if ( num != value + 1 ) { // �Ʀr���B��l+1 
		
		find = true ;
		oper = num - value - 1 ;
		// oper���t->���h�B��l
		// oper����->���ֹB��l 

	} // if
	
	return find ;
	
} // ErrorOfOperator

bool CheckParentheses( string in ) {
// �ĤT��Error �ˬd�A�����O�_��infix 
	
	bool start = false ;
	int num = 0 ; // �����Ʀr 
	int value = 0 ; // �����B��l 
	
	for ( int i = 0 ; i < in.size() ; i++ ) {
		
		if ( in[i] == '(' ) {
			start = true ; // �J�쥪�A���}�l�O�� 
			num = 0 ;
	 		value = 0 ;
		} // if
		else if ( in[i] == ')' ) {
			start = false ; // �J��k�A���������� 
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
// �M�䦳�S��Error 
	
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
// �L�XError 
	
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
		
		if ( oper > 0 ) { // �֤F�B��l 
		
			if ( oper == 1 ) cout << "is 1 extra operand." << endl ;
			else cout << "are " << oper << " extra operands." << endl ;
		
		} // if
		else if ( oper < 0 ) { // �h�F�B��l
		
			if ( oper == -1 ) cout << "is 1 extra operator." << endl ;
			else cout << "are " << -oper << " extra operators." << endl ;
			
		} // else if
	
	} // else if
	
} // PrintError

int OperPriority( string op ) {
// �����B��l���u������ 
	
	if ( op == "(" ) return 1 ; // �A�������� 
	else if ( op == "+" || op == "-" ) return 2 ; // ��[�� 
	else if ( op == "*" || op == "/" ) return 3 ; // ������ 
	else return 0 ;
	
} // OperPriority

string SetOper( char op ) {
// �r����r�� 
	
	if ( op == '+' ) return "+" ;
	else if ( op == '-' ) return "-" ;
	else if ( op == '*' ) return "*" ;
	else if ( op == '/' ) return "/" ;
	else if ( op == '(' ) return "(" ;
	else if ( op == ')' ) return ")" ;
	
} // SetOper

Node * ToPostFix( string in ) {
	
	Node * oper = NULL ;    // �s�B��l 
	Node * number = NULL ;  // �s���骺��T(�Ʀr) 
	char value[100] = {0} ; // �s�Ʀr�ϥΪ� 
	string str ;            // �s�Ʀr�ϥΪ�  
	int index = 0 ;         // ����value����m  
	
	for ( int i = 0 ; i < in.size() ; i++ ) { // ���r��̪��r���@�Ӥ@�Ӥ�� 
		
		if ( '0' <= in[i] && in[i] <= '9' ) {    
				value[index] = in[i] ;
				index++ ;
			if ( !('0' <= in[i+1] && in[i+1] <= '9') || i == in.size()-1 ) {  // �Ʀr�U�@�ӬO�B��l 
				str = value ;   // �r���}�C��r�� 
				number = Push(value, number) ;   // �s�Jstack 
				memset(value, 0, 100) ;  // �M��value 
				index = 0 ;  //��l�� 
			} // if
		} // if
		else if ( in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '(' || in[i] == ')') {
		// �O�B��l	 
			if ( in[i] == '(' ) oper = Push("(", oper) ;  // �k�A�����s�J 
			else if ( in[i] == ')' ) {  // �A�������� 
				while( GetTopData(oper) != "(" ) {  // �J�쥪�A���e����Jnumber�� 
					number = Push(GetTopData(oper), number) ;
					oper = Pop(oper) ;
				} // while
				
				oper = Pop(oper );  // �R���w�s�J���B��l  
			} // else if
			else { // ��������[��
				str = SetOper(in[i]) ; // �ഫ���O  
				if ( isEmpty(oper) || OperPriority(str) > OperPriority(GetTopData(oper)) )
				//�s�j���� ��᭱ �A�Ystack���Ū��ιB��l���u�����Ǥp��stack of top data�A 
					oper = Push(str, oper) ; // �s�Jnumber
				else { 
				// �Y���O�Ū��ιB��l���u�����Ǥj��stack of top data
					while ( !isEmpty(oper) && OperPriority(str) <= OperPriority(GetTopData(oper)) ) {
						number = Push(GetTopData(oper), number) ; // �s�Jnumber
						oper = Pop(oper) ; // �R���w�[�Joutput���B��l
					} // while
					
					oper = Push(str, oper); // �s�Jnumber
				} // else
			} // else
		} // else if
		
	} // for
	
	//�N�ѤU��operator��inumber��
	while ( oper != NULL ) {
		number = Push(GetTopData(oper), number) ;
		oper = Pop(oper) ;
	} // while
	
	//�˹L�Ӹ˶i�h�L�X�� 
	Node * result = NULL;
	
	while ( !isEmpty(number) ) {
		result = Push(GetTopData(number), result) ;
		number = Pop(number) ;
	} // while

	return result;
		
} // ToPostFix

bool isDigit( string str ) {
// �O�_���Ʀr 	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( str[i] >= '0' && str[i] <= '9' ) continue ;
		else return false ;
		
	} // for
	
	return true ;
	
} // isDigit

int Calculate( string s1, string s2, string op ) {
// �^�ǹB��᪺�Ʀr �A�i�ӬOstring�ҥH��atoi 

	int num1 = atoi(s1.c_str()) ;
	int num2 = atoi(s2.c_str()) ;
	if ( op == "+" ) return num1 + num2 ;
	else if ( op == "-" ) return num1 - num2 ;
	else if ( op == "*" ) return num1 * num2 ;
	else if ( op == "/" ) return num1 / num2 ;
	return 0 ;
} // Calculate

string Change( int num ) {
//��int�নstring�A�]���sdata���O�Ostring 
    char temp[100]; 
    string str ;
    sprintf( temp, "%d", num );  
    str = temp ;
    return str ;
}


void CalculatePostfix( Node * list , int & num ,int & total ) { 
//�p���Ǧ� 
	string num1 ; //�����Ĥ@�ӼƦr 
	string num2 ; //�O���ĤG�ӼƦr 
	int numt ;    //�ۥ[�@�G�Ʀr�� 
	Node * temp = NULL ; //�]�w�@�ӷs��temp�ΨӦs�n�⪺�F�� 
	string value ;   //value�sstack�� 

	while ( !isEmpty(list) ) {    

		value = GetTopData(list) ;    
		if ( isDigit(value) ) {
			temp = Push( value, temp) ;   //����Ʀr����i�s��stack�̭� 
			// cout << temp -> data ;
		}
		else {  //�I��B��l�N���O���A��k���@�� 
		/***
		�J��B��l�A�qtemp�W�����Ʀr��num2�M��pop���A�b���Ʀr��num1�M��pop�A
		���h�ۥ[�নstring�bpush�^temp�̭� 
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
				if( numt == 0 ) {     // �J��/0�����p�|���A�N�^�� 
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
		
		list = Pop(list) ;   //�̤W���Χ��N�R�� 
	}
	
	value = GetTopData(temp) ;  //�̳ѤU�̫᪺���G�btemp�� 
	total = atoi(value.c_str()) ;
	
	
} // CalculatePostfix

void mission1() {
// ���Ȥ@ 
	
	string input = "/0" ; // �sEvaluator
	Error error ; // ��l��Error struct 
	Node * postfix = NULL ; // ��l�ƫ��� 
	int total = 0 ; // �̫ᵪ�� 
	int errorNum = -1 ; // ���ƬO�_��0
	
	cout << endl << "Input an infix expression: " ;
	getline(cin, input) ; // Ū�J�@�� 
	input.erase(remove(input.begin(), input.end(), ' '), input.end()) ; // �h���ť� 
	
	if ( FindError(input, error.type, error.ch, error.par, error.oper) ) // �M��error 
		PrintError(error.type, error.ch, error.par, error.oper) ;
	else { // �}�l�q��������� 
		postfix = ToPostFix(input) ;
		cout << "It is a legitimate infix expression." << endl ;
		cout << "Postfix expression: " ;
		
		Print(postfix) ; // �L�X���� 
		CalculatePostfix(postfix, errorNum, total ) ; // �p�⵪�� 
		
		if ( errorNum == 0 ) { // ���Ƭ�0 
			cout << "### Error: Divided by ZERO! ###" << endl ;
			cout << "### It cannot be successfully evaluated! ###" << endl ;
			postfix = Clear(postfix) ; // ����O���� 
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
