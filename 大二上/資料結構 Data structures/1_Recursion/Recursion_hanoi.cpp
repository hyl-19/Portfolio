# include <stdio.h>
# include <iostream>
# include <string>
# include <time.h> 
# include <cstdlib>
# include <cstring>
# include <stdlib.h>  
# include <string.h>  

using namespace std;
int gcount = 1 ; // �ΨӼư��X���ƦC 

void Change( int &a, int &b) {  // �洫int����� 
	int temp = a ;	
	a = b ;
	b = temp ;
}

void Generate_permutations( int *data, int point, int n ) {
/*
���T�w�Ĥ@�ӼƵM��洫�M�Ỽ�j����Mn�ۦP�Nprint�X�ӡA�̫�b�洫�^�h��
�ĤG�ӼƦr��Ĥ@�Ӱ�n���ۦP�Ʊ��C 
*/
	if ( n == point  ) {
		cout << "[" << gcount++ << "] " ;
		for ( int i = 0 ; i < n ; i++ ) 
			cout << data[i] << " "; 
		
		cout << endl ;
	}	
	else {
		for ( int i = point ; i < n ; i++ ) {
			Change( data[point], data[i] ) ;
			Generate_permutations( data , point + 1, n ) ;
			Change( data[i], data[point] ) ;
		}
	} 
	
}

void Permutations_Limit( int *data, int point, int n ) {
//�M�W�����t�O�N�Oi<9��9�ӼƩ�ƦC�N��9�� 
	if ( n == point  ) {
		cout << "[" << gcount++ << "] " ;
		for ( int i = 0 ; i < n ; i++ ) 
			cout << data[i] << " "; 
		
		cout << endl ;
	}	
	else {
		for ( int i = point ; i < 9 ; i++ ) {
			Change( data[point], data[i] ) ;
			Permutations_Limit( data , point + 1, n ) ;
			Change( data[i], data[point] ) ;
		}
	} 	
}

void Permutations_Challenge( int *data, int point, int m, int n ) {
//�M�W�����t�O�N�Oi<9��9�ӼƩ�ƦC�N��9�� 
	if ( m == point  ) {
		cout << "[" << gcount++ << "] " ;
		for ( int i = 0 ; i < m ; i++ ) 
			cout << data[i] << " "; 
		
		cout << endl ;
	}	
	else {
		for ( int i = point ; i < n ; i++ ) {
			Change( data[point], data[i] ) ;
			Permutations_Challenge( data , point + 1, m , n) ;
			Change( data[i], data[point] ) ;
		}
	} 	
}

bool Isdigit( const char* str ) { // �P�_�Ʀr�O���Oint 
	int temp = 0 ;
	if ( str[0] == '+' ) {   // +X�]��int���@�ءA�Ѯv��code�i�H 
		for ( int i = 1 ; i < strlen( str ) ; i++) {
		
        	int temp = str[i] - '0' ;
        	if ( temp >= 0 && temp <= 9 ) 
        	    continue ;
        	else
            	return false;
    	} 	
	}
	else
		for ( int i = 0 ; i < strlen( str ) ; i++) {
		
        	int temp = str[i] - '0' ;
        	if ( temp >= 0 && temp <= 9 ) 
        	    continue ;
        	else
       	    	return false;
    	} 
    
    return true;	
}

bool Checksame( int *data, int n, int temp ){     // �ˬd�}�C�����ۦP�Ʀr 
	for( int i = 0 ; i <= n ; i++ ) {       	  // n�O��e�s��ĴX�ӡAtemp�O�n�Q�ˬd���s�Ʀr 
		if ( data[i] == temp )
		return false ;
	}
	
	return true ;
}

void test1 ( ) { //��mission��function 
	char input[100] ;
	int n = 0 ;
	while ( true ) {
		cout << "��J�@�ӥ����N:" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {   //�P�_�O���Oint�O���ܧ�string�୼int 
			n = atoi( input ) ;      //���O���ܴNŪ��Oint���� 
			if ( n > 0 )
				break ;
		}
	}
		
	int data[ n ] ;
	for ( int i = 0 ; i < n ; i++ )
		data[i] = i + 1 ;
	
	Generate_permutations( data , 0, n ) ;		
	gcount-- ;
	cout << "Mission 1: " << gcount << " permutations" << endl ;
	cout << "L = " << n << endl ;
	
}

void test2 ( ) {   // can't same 
	char input[100] ;
	int n = 0 ;
	double start, end ;
	while ( true ) {
		cout << "��JM�ӥ����(2~9):" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {
			n = atoi( input ) ;
			if ( n >= 2 && n <= 9 ) {
				break ;
			}
			else
				cout << "M not in [ 2~9 ]" << endl ;
		}
	}
	
	int *data = ( int * ) malloc( n * sizeof( int ) ) ;
	int temp ;
	for ( int i = 0 ; i < n ; i++ ) {
		while ( true ) {
			cout << "��J��" << i + 1 << "�ӼƦr:" ; 
			cin >> input ;
			cout << endl ;
			if ( Isdigit ( input ) ) {
				temp = atoi( input ) ;
				if ( Checksame( data, i, temp ) ) { 
					data[i] = temp ;
					break ;	
				}
				else 
					cout << "Wrong! there have the same numbers.\n" << endl ;
			}
		}
	}
    start = clock() ;
	Generate_permutations( data, 0, n ) ;
	gcount-- ;
	cout << "Mission 2: " << gcount << " permutations" << endl ;
	end = clock() ;
	cout <<  "T = " << end - start << " ms" << endl;
	free( data ) ;
}

void test3 ( ) {
	char input[100] ;
	int n = 0 ;
	double start, end ;
	while ( true ) {
		cout << "��JM�ӥ����(1~9):" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {
			n = atoi( input ) ;
			if ( n >= 1 && n <= 9 ) {
				break ;
			}
			else
				cout << "M not in [ 1~9 ]" << endl ;
		}
	}
	

	start = clock() ;
	int data[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
	Permutations_Limit( data, 0, n ) ;
	gcount-- ;
	cout << "Mission 3: " << gcount << " permutations" << endl ;
	end = clock() ;
	cout <<  "T = " << end - start << " ms" << endl;
	
}

void Challenge() {
	char input[100] ;
	int n = 0 ;
	int m = 0 ;
	double start, end ;
	while ( true ) {
		cout << "��J�����N:" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {
			n = atoi( input ) ;
			if ( n >= 1 ) {
				break ;
			}
			else
				cout << "N is not �����" << endl ;
		}
	}
	
	while ( true ) {
		cout << "��J�����M:" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {
			m = atoi( input ) ;
			if ( m >= 1 && m <= n ) {
				break ;
			}
			else
				cout << "M is not in [1," << m << "]" << endl ;
		}
	}
	int i = 0 ;
	int data[n] ;
	for ( int j = 0 ; j < n ; j++ ) {
		data[j] = j + 1 ;
	}
	start = clock() ;
	Permutations_Challenge( data, 0, m, n ) ;
	gcount-- ;
	cout << "Mission 4: " << gcount << " permutations" << endl ;
	end = clock() ;
	cout <<  "T = " << end - start << " ms" << endl;
	
}

int main() {
	int command = 0 ;
	int n = 0 ;
	char input[100] ;
	do {
		cout << "\n** Permutation Generator **" << endl ;
		cout << "* 0. Quit                 *" << endl ;
		cout << "* 1. N numbers from 1...N *" << endl ;
		cout << "* 2. M numbers from input *" << endl ;
		cout << "* 3. M numbers from 1...9 *" << endl ;
		cout << "* 4. M numbers form N(�D��)" << endl ; 
		cout << "***************************" << endl ;
		cout << "Input a choice(0,1,2,3,4):" ;
		cin >> input ;
		if ( Isdigit ( input ) ) {
			command = atoi( input ) ;
		}
		else {
			return 0 ;
		}
		
		gcount = 1 ;
		if ( command == 0 ) 
			break ;
		else if ( command == 1 ) 
			test1() ;	
		else if ( command == 2 ) 
			test2() ;
		else if ( command == 3 ) 
			test3() ;
		else if ( command == 4 )
			Challenge() ;
		else {
			cout << "\nCommand doesn't exist!" << endl ; // bug : input ex : "www" will stop 
		}
		
		cout << endl ;
	} while ( command != 0 ) ;
	
	system( "PAUSE" ) ;
	return 0 ;
}
