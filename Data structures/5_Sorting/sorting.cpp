# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>
# include<ctime>
# include <queue>
# include <math.h>

using namespace std ;
// DS 2
// 11027212 ���ض� 11027222 �����M 
struct Type {		 
        string rowData ;     // row data 
        int numOfGrad ;      // number of graduates
	
}; // Type

class Data {
	vector<Type> sortlist ; 
        
    public:
    	string ID ;
     	int datanum = 0 ;
     	
     	void GetString(string line, int index, string & str) {
     		// ��Function�O���F���Xline�̪���T
			// ��X�ĴX��tab�e����T
			 
			int pos = 0 ;	// �����}�l��m			
			for(int i = 0 ; i < index - 1 ; ++i) {
				pos = line.find('\t', pos) ; // �qpos�}�l�M��U�@��TAB 
				pos++ ;			
			} // for
	
			int ntab = line.find('\t', pos) ; // ��ĴX��TAB�e���r��	
			if (ntab != string::npos) // ���TAB 
				str = line.substr(pos, ntab - pos) ;
			else 
				str = line.substr(pos, line.size() - 1 - pos) ;
		} // GetString
		
		void FixNum( string & num ) {
			// �h�׾ǥͼƪ��Ʀr�A"1,038" 
			
			int n = num.size() ;
			if ( num[0] == '\"' && num[n-1] == '\"' ) {
				num = num.erase(n-1, n) ; // �����᭱�����޸� 
				num = num.erase(0, 1) ;   // �����e�������޸� 
				num = num.erase(1, 1) ;   // �����������r�� 
			} // if
				
		} // FixNum
		
    	void GetLineOfData( string str, int& numOfGrad ) {
    		// �h�sline�̭�����T 
    		string data = "/0" ;		   		
			GetString(str, 9, data) ;
			FixNum(data) ;
			numOfGrad = atoi(data.c_str()) ;
			
		} // GetLineOfData
		
				
		string FileName( string str ) { 
		// �^�ǧ��㪺 file name
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// �s�� file �̪� data
		
			Type type ;
			ifstream in ;
			string file ; // �ɮצW�� 
				
    		cout << endl << "Input a file number (e.g. 501, 502, 503, ... ) :" ;
    		cin >> ID ; // Ū�J�ɮץN�X 
			
    		file = FileName(name) ; // �ɮק���W�� 
    			
    		in.open(file.c_str(), ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    		if ( !in.is_open() ) { // �䤣�즹�ɮ� 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				while(getline(in, type.rowData)) { // �s��� 
					sortlist.push_back(type) ;			
				} // while
						
			} // else
			
			in.close() ; // ���� 
			for (int i = 0; i < 3 ; i++){
				sortlist.erase(sortlist.begin());
			}
			//cout << sortlist.size() << endl ;
			for (int i = 0 ; i < sortlist.size() ; i++ ) {
				GetLineOfData(sortlist.at(i).rowData, sortlist.at(i).numOfGrad ) ;
				//cout << sortlist.at(i).schoolNum << " " << sortlist.at(i).depNum << " " << sortlist.at(i).numOfGrad << endl ;
			}
			datanum = sortlist.size() ;
			return true ;
		
		} // ReadFile
		
		bool ReadFile( string name, string num ) {
		// �s�� file �̪� data
		
			Type type ;   
			ifstream in ;
			string file ; // �ɮצW�� 
			ID = num ;
    		file = FileName(name) ; // �ɮק���W�� 
    			
    		in.open(file.c_str(), ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    		if ( !in.is_open() ) { // �䤣�즹�ɮ� 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				while(getline(in, type.rowData)) { // �s��� 
					sortlist.push_back(type) ;			
				} // while
						
			} // else
			
			in.close() ; // ���� 
			for (int i = 0; i < 3 ; i++){
				sortlist.erase(sortlist.begin());
			}
			
			for (int i = 0 ; i < sortlist.size() ; i++ ) {
				GetLineOfData(sortlist.at(i).rowData, sortlist.at(i).numOfGrad ) ;
			}
			datanum = sortlist.size() ;
			return true ;
		
		} // ReadFile
		
		
		void WriteFile( string name ) {
			// �g�ɮ� str ���ɮצW�� 
			
			string file ;
			
			file = FileName(name) ; // �ɮק���W��
			 
			ofstream out(file.c_str()) ; // �إ��ɮ� 
			
			
			for ( int i = 0 ; i < sortlist.size() ; i++ ) {
				// �g�J��� 
				
				out << sortlist.at(i).rowData << endl ;
				
			} // for
			
			out.close() ; // ���� 
			
		} // WriteFile
		
		void WriteFile( clock_t s, clock_t b,clock_t m, clock_t q,clock_t r ) {
			Type type ;
			ifstream in ;
			string file = "sort_time.txt" ;
			in.open(file.c_str(), ios::in) ;
			if ( !in.is_open() ) {
				ofstream out(file.c_str()) ;
				out << "�ɮ׽s��\t��ܱƧ�\t��w�Ƨ�\t�X�ֱƧ�\t�ֳt�Ƨ�\t��ƱƧ�" << endl ;
				out << ID << "\t" << s << "\t"<< b << "\t"<< m<< "\t"<< q << "\t"<< r << endl ;
			}
			else {
				ofstream out(file.c_str(), ios::app) ;
				out << ID << "\t" << s << "\t"<< b << "\t"<< m<< "\t"<< q << "\t"<< r << endl ;
			}
			in.close() ;
		
			
		}
		
		void bubble_sort() {
			for ( int i = 0 ; i < datanum -1 ; i++ ) {  //��0~N-1 
				for ( int j = 0 ; j < datanum-i-1 ; j++ ) { //��p����᭱ 
					if(sortlist.at(j+1).numOfGrad > sortlist.at(j).numOfGrad)   {
						swap(sortlist.at(j+1), sortlist.at(j)) ;
					}				
				}		
			}		
		}
		void P() {
			for ( int i = 0 ; i < datanum ; i++) {
				cout << sortlist.at(i).rowData << endl ;
			}
			cout << endl << endl ;
		}
		
		int indexofmin(int num) { // ��̤j��numOfGrad 
			int index = 0 ;
			for(int i = 0 ; i < num ; i++) {
				if( sortlist.at(index).numOfGrad > sortlist.at(i).numOfGrad) {  //��numOfGrad�j�p 
					index = i ; //������p��index�]��i 
				}
			}
		
			return index ;
		}
		
		void select_sort() {  		
			for ( int i = datanum - 1 ; i > 0 ; --i ) {   //�q�̫�}�l�� 
				int index = indexofmin(i+1);        //���numofgrad�̤p��index 
				if ( index != i )
					swap( sortlist.at(index),sortlist.at(i)) ; // �洫 
			}
		}
		
		void Mergearr(int first, int mid, int last) {
			int first1 = first ;  //���䪺�Ĥ@�� 
			int last1 = mid ;     //���䪺�̫�@�� 
			int first2 = mid+1 ;  //�k�䪺�Ĥ@��
			int last2 = last ;    //�k�䪺�̫�@��  
			int index = first ;    
			vector<Type> temp(datanum) ; //�Ȯɦs��vector 
		
			for ( ; (first1 <= last1 ) && (first2 <= last2 ) ; ++index ) {
				
				if (sortlist.at(first1).numOfGrad >= sortlist.at(first2).numOfGrad ) {  
					temp.at(index) = sortlist.at(first1) ;  //�j����e�� 
					++first1 ;
				}
				else {
					temp.at(index) = sortlist.at(first2) ;  //�p����᭱  
					++first2 ;
				}
			}
			
			for ( ; first1 <= last1 ; ++first1, ++index) { // �������� 
				temp.at(index) = sortlist.at(first1) ;
			}
			
			for ( ; first2 <= last2 ; ++first2, ++index) { // �����k�� 
				temp.at(index) = sortlist.at(first2) ;
			}  
			
			for (index = first; index <= last; ++index) { // �ƻs���G 
				sortlist.at(index) = temp.at(index);
				
			}	
		}
		
		void merge_sort( int start, int back ) {   
			int mid = 0 ;
			if ( start < back ) {
				mid = ( start +  back ) / 2 ; // �����vector�d�� 
				merge_sort( start, mid ) ;    // ���� vector ���e�q 
				merge_sort( mid + 1, back ) ; // ���� vector ����q 
				Mergearr(start, mid, back) ;  // ����æX��vector 
			}	
		}
		
		int Partition(int first, int back) { //�k��>=p�A����<p 

			int pivot = sortlist.at(first).numOfGrad ;  
			int last = first ;
			int unknow = first + 1 ;
			while ( unknow <= back ) {
				if( sortlist.at(unknow).numOfGrad >= pivot ) {  //�����m 
					++last ;
					swap(sortlist.at(last), sortlist.at(unknow)) ;
				}
				++unknow ;
				
			}
			swap(sortlist.at(last), sortlist.at(first)) ; //��pivot����L����m�W 
			return last ; // �^��pivot��m 
		}
		
		void quick_sort( int start, int back ) { 
		int p = 0 ;
			if( start < back ) {
				p = Partition(start, back) ; // ��pivot 
				quick_sort(start, p-1) ;  //�ƥ��� 
				quick_sort(p+1, back) ;   //�ƥk�� 
			}
		}
		
		void radix_sort() { 
			int max = 0 ; //�s�̤j���� 
			for ( int i = 0 ; i < datanum ; i++ ) {  //���̤j��numofgrad 
				if ( max < sortlist.at(i).numOfGrad ) {
					max = sortlist.at(i).numOfGrad ;
				}
			}
			
			int num = 0 ;  //��numofgrad���̤j��� 
			int temp = max ;  
			while ( temp > 0 ) { 
				temp /= 10 ;
				num++ ;
			}
			
			queue<Type> qtemp[10] ;  //�s0~9�l�ƪ�queue 
			int divide = 1 ;         //���ƥ��]1 

			for ( int i = 0 ; i < num ; i++) { //�δX��Ƴ]�w�n�]������ 
				
				for ( int j = 0 ; j < datanum; j++ ) { //�����L�b�ĴX��ƪ��l�ƬO�h�� 
					qtemp[( sortlist.at(j).numOfGrad / divide ) % 10].push(sortlist.at(j)) ; //�q�L����ƨM�w�L�n���X��queue 
				}
				
				int k = 0 ;
				for ( int j = 9 ; j >= 0 ; j-- ) {  //�q9��queue�}�l�˥X�� 
					while ( qtemp[j].empty() == false ) {
						swap(sortlist.at(k), qtemp[j].front() ) ;	//�qqueue�}�Y�s�Jsortlist�A��k�Ƽƶq 
						k++ ;		
						qtemp[j].pop() ;
					}
				}
				
				divide *= 10 ;		//���ƨC��*10 
			}	
		} 	
}; // class

bool isDigit( string str ) {
// �P�_�O�_���Ʀr 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

void mission1() {  // bb 301 // sc 20
	clock_t bbt ;    //�p��bubblesort 
	clock_t st ;	 //�p��selectionsort 
	
	Data bubble ; 
	if( bubble.ReadFile("input") ) {
		bbt = clock() ;  //�}�l�p�� 
		bubble.bubble_sort() ;
		bbt = clock() - bbt ; //�����p��  
		bubble.WriteFile("bubble_sort") ;  
	}

	Data select ;
	// strcpy(select.ID,bubble.ID) ;
	if( select.ReadFile("input", bubble.ID) ) {
		st = clock() ; //�}�l�p�� 
		select.select_sort() ;
		st = clock() - st ; //�����p��  
		bubble.WriteFile("Select_sort") ;
	}
	
	cout << "\nSelect sort: " << st << " ms." << endl ;
	cout << "\nBubble sort: " << bbt << " ms." << endl ;
	
}

void mission2() {  // bb 301 // sc 20
	clock_t ms ;    //�p��mergesort 
	clock_t qs ;	//�p��quicksort 
	
	Data merge ;
	if( merge.ReadFile("input") ) {
		ms = clock() ; //�}�l�p�� 
		int start = 0 ;
		int back = merge.datanum ;  //���ovector��size 
		merge.merge_sort( start, back -1 ) ;
		ms = clock() - ms ; //�����p��  
		merge.WriteFile("Merge_sort") ;
		cout << "\nMerge sort: " << ms << " ms." << endl ;
	}

	
	Data quick ;
	if( quick.ReadFile("input", merge.ID) ) {
		qs = clock() ; //�}�l�p�� 
		quick.quick_sort(0,quick.datanum-1) ;
		qs = clock() - qs ; //�����p��  
		quick.WriteFile("Quick_sort") ;
		cout << "\nQuick sort: " << qs << " ms." << endl ;
	}
	
}

void mission3() {
	clock_t rs ;    
	
	Data radix ;
	if( radix.ReadFile("input") ) {
		rs = clock() ; //�}�l�p�� 
		radix.radix_sort( ) ;
		rs = clock() - rs ; //�����p�� 
		radix.WriteFile("Radix_sort") ;
		cout << "\nRadix sort: " << rs << " ms." << endl ;
	}
}

//==========================================================================
void mission1(string ID, clock_t &bbt, clock_t &st) {  // bb 301 // sc 20
	Data bubble ; 
	if( bubble.ReadFile("input", ID) ) {
		bbt = clock() ;  //�}�l�p�� 
		bubble.bubble_sort() ;
		bbt = clock() - bbt ; //�����p��  
		bubble.WriteFile("bubble_sort") ;  
	}

	Data select ;
	// strcpy(select.ID,bubble.ID) ;
	if( select.ReadFile("input",ID) ) {
		st = clock() ; //�}�l�p�� 
		select.select_sort() ;
		st = clock() - st ; //�����p��  
		bubble.WriteFile("Select_sort") ;
	}
	
	cout << "\nSelect sort: " << st << " ms." << endl ;
	cout << "\nBubble sort: " << bbt << " ms." << endl ;
	
}

void mission2(string ID, clock_t &qs, clock_t &ms) {  // bb 301 // sc 20
	
	Data merge ;
	if( merge.ReadFile("input",ID) ) {
		ms = clock() ; //�}�l�p�� 
		int start = 0 ;
		int back = merge.datanum ;  //���ovector��size 
		merge.merge_sort( start, back -1 ) ;
		ms = clock() - ms ; //�����p��  
		merge.WriteFile("Merge_sort") ;
		cout << "\nMerge sort: " << ms << " ms." << endl ;
	}

	
	Data quick ;
	if( quick.ReadFile("input", ID) ) {
		qs = clock() ; //�}�l�p�� 
		quick.quick_sort(0,quick.datanum-1) ;
		qs = clock() - qs ; //�����p��  
		quick.WriteFile("Quick_sort") ;
		cout << "\nQuick sort: " << qs << " ms." << endl ;
	}
	
}

void mission3(string ID, clock_t &rs) {

	Data radix ;
	if( radix.ReadFile("input", ID) ) {
		rs = clock() ; //�}�l�p�� 
		radix.radix_sort( ) ;
		rs = clock() - rs ; //�����p�� 
		radix.WriteFile("Radix_sort") ;
		cout << "\nRadix sort: " << rs << " ms." << endl ;
	}
}
//==========================================================================
void mission4() {
	clock_t bbt, st, qt, ms, rs ;
	Data test ;
	if ( test.ReadFile("input") ) {
		mission1(test.ID,bbt,st) ;
		mission2(test.ID,qt,ms) ;
		mission3(test.ID,rs) ;
	}

	test.WriteFile(st, bbt, ms, qt, rs) ;	
	
}



int main() {

	string command = "/0" ; // Ū�����O 
	int cd = -1 ;           // int�����O 
	
	do { 
	
		cout << endl << "******** Sorting Algorithms *********" ;
		cout << endl << "* 0. QUIT                           *" ;
		cout << endl << "* 1. Selection sort vs. Bubble sort *" ;
		cout << endl << "* 2. Merge sort vs. Quick sort      *" ;
		cout << endl << "* 3. Simulate two queues by SQF     *" ;
		cout << endl << "* 3. Radix sort                     *" ;
		cout << endl << "* 4. Comparisons on five methods    *" ;
		cout << endl << "Input a command(0, 1, 2, 3, 4) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) mission1() ; // �i�J���Ȥ@ 
		else if ( cd == 2 ) mission2() ; // �i�J���ȤG 
		else if ( cd == 3 ) mission3() ; // �i�J���ȤT 
		else if ( cd == 4 ) mission4() ;
		else cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		
	} while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
