# include <stdio.h>
# include <iostream>
# include <string>
# include <time.h> 
# include <cstdlib>
# include <cstring>
# include <stdlib.h>  
# include <string.h>  

using namespace std;
int gcount = 1 ; // 用來數做幾次排列 

void Change( int &a, int &b) {  // 交換int的資料 
	int temp = a ;	
	a = b ;
	b = temp ;
}

void Generate_permutations( int *data, int point, int n ) {
/*
先固定第一個數然後交換然後遞迴直到和n相同就print出來，最後在交換回去把
第二個數字丟第一個做n次相同事情。 
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
//和上面的差別就是i<9有9個數抽排列就做9次 
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
//和上面的差別就是i<9有9個數抽排列就做9次 
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

bool Isdigit( const char* str ) { // 判斷數字是不是int 
	int temp = 0 ;
	if ( str[0] == '+' ) {   // +X也算int的一種，老師的code可以 
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

bool Checksame( int *data, int n, int temp ){     // 檢查陣列內有相同數字 
	for( int i = 0 ; i <= n ; i++ ) {       	  // n是當前存到第幾個，temp是要被檢查的新數字 
		if ( data[i] == temp )
		return false ;
	}
	
	return true ;
}

void test1 ( ) { //做mission的function 
	char input[100] ;
	int n = 0 ;
	while ( true ) {
		cout << "輸入一個正整數N:" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {   //判斷是不是int是的話把string轉乘int 
			n = atoi( input ) ;      //不是的話就讀到是int為止 
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
		cout << "輸入M個正整數(2~9):" ;
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
			cout << "輸入第" << i + 1 << "個數字:" ; 
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
		cout << "輸入M個正整數(1~9):" ;
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
		cout << "輸入正整數N:" ;
		cin >> input ;
		cout << endl ;
		if ( Isdigit ( input ) ) {
			n = atoi( input ) ;
			if ( n >= 1 ) {
				break ;
			}
			else
				cout << "N is not 正整數" << endl ;
		}
	}
	
	while ( true ) {
		cout << "輸入正整數M:" ;
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
		cout << "* 4. M numbers form N(挑戰)" << endl ; 
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
