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
// 11027212 黃建閎 11027222 黃彥霖 
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
     		// 此Function是為了取出line裡的資訊
			// 找出第幾個tab前的資訊
			 
			int pos = 0 ;	// 紀錄開始位置			
			for(int i = 0 ; i < index - 1 ; ++i) {
				pos = line.find('\t', pos) ; // 從pos開始尋找下一個TAB 
				pos++ ;			
			} // for
	
			int ntab = line.find('\t', pos) ; // 找第幾個TAB前的字串	
			if (ntab != string::npos) // 找到TAB 
				str = line.substr(pos, ntab - pos) ;
			else 
				str = line.substr(pos, line.size() - 1 - pos) ;
		} // GetString
		
		void FixNum( string & num ) {
			// 去修學生數的數字，"1,038" 
			
			int n = num.size() ;
			if ( num[0] == '\"' && num[n-1] == '\"' ) {
				num = num.erase(n-1, n) ; // 消除後面的雙引號 
				num = num.erase(0, 1) ;   // 消除前面的雙引號 
				num = num.erase(1, 1) ;   // 消除中間的逗號 
			} // if
				
		} // FixNum
		
    	void GetLineOfData( string str, int& numOfGrad ) {
    		// 去存line裡面的資訊 
    		string data = "/0" ;		   		
			GetString(str, 9, data) ;
			FixNum(data) ;
			numOfGrad = atoi(data.c_str()) ;
			
		} // GetLineOfData
		
				
		string FileName( string str ) { 
		// 回傳完整的 file name
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// 存取 file 裡的 data
		
			Type type ;
			ifstream in ;
			string file ; // 檔案名稱 
				
    		cout << endl << "Input a file number (e.g. 501, 502, 503, ... ) :" ;
    		cin >> ID ; // 讀入檔案代碼 
			
    		file = FileName(name) ; // 檔案完整名稱 
    			
    		in.open(file.c_str(), ios::in) ; // 在讀入模式下開啟in檔案
    	
    		if ( !in.is_open() ) { // 找不到此檔案 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				while(getline(in, type.rowData)) { // 存資料 
					sortlist.push_back(type) ;			
				} // while
						
			} // else
			
			in.close() ; // 關檔 
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
		// 存取 file 裡的 data
		
			Type type ;   
			ifstream in ;
			string file ; // 檔案名稱 
			ID = num ;
    		file = FileName(name) ; // 檔案完整名稱 
    			
    		in.open(file.c_str(), ios::in) ; // 在讀入模式下開啟in檔案
    	
    		if ( !in.is_open() ) { // 找不到此檔案 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				while(getline(in, type.rowData)) { // 存資料 
					sortlist.push_back(type) ;			
				} // while
						
			} // else
			
			in.close() ; // 關檔 
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
			// 寫檔案 str 為檔案名稱 
			
			string file ;
			
			file = FileName(name) ; // 檔案完整名稱
			 
			ofstream out(file.c_str()) ; // 建立檔案 
			
			
			for ( int i = 0 ; i < sortlist.size() ; i++ ) {
				// 寫入資料 
				
				out << sortlist.at(i).rowData << endl ;
				
			} // for
			
			out.close() ; // 關檔 
			
		} // WriteFile
		
		void WriteFile( clock_t s, clock_t b,clock_t m, clock_t q,clock_t r ) {
			Type type ;
			ifstream in ;
			string file = "sort_time.txt" ;
			in.open(file.c_str(), ios::in) ;
			if ( !in.is_open() ) {
				ofstream out(file.c_str()) ;
				out << "檔案編號\t選擇排序\t氣泡排序\t合併排序\t快速排序\t基數排序" << endl ;
				out << ID << "\t" << s << "\t"<< b << "\t"<< m<< "\t"<< q << "\t"<< r << endl ;
			}
			else {
				ofstream out(file.c_str(), ios::app) ;
				out << ID << "\t" << s << "\t"<< b << "\t"<< m<< "\t"<< q << "\t"<< r << endl ;
			}
			in.close() ;
		
			
		}
		
		void bubble_sort() {
			for ( int i = 0 ; i < datanum -1 ; i++ ) {  //做0~N-1 
				for ( int j = 0 ; j < datanum-i-1 ; j++ ) { //把小的丟後面 
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
		
		int indexofmin(int num) { // 找最大的numOfGrad 
			int index = 0 ;
			for(int i = 0 ; i < num ; i++) {
				if( sortlist.at(index).numOfGrad > sortlist.at(i).numOfGrad) {  //看numOfGrad大小 
					index = i ; //有比較小把index設為i 
				}
			}
		
			return index ;
		}
		
		void select_sort() {  		
			for ( int i = datanum - 1 ; i > 0 ; --i ) {   //從最後開始找 
				int index = indexofmin(i+1);        //找到numofgrad最小的index 
				if ( index != i )
					swap( sortlist.at(index),sortlist.at(i)) ; // 交換 
			}
		}
		
		void Mergearr(int first, int mid, int last) {
			int first1 = first ;  //左邊的第一位 
			int last1 = mid ;     //左邊的最後一位 
			int first2 = mid+1 ;  //右邊的第一位
			int last2 = last ;    //右邊的最後一位  
			int index = first ;    
			vector<Type> temp(datanum) ; //暫時存放的vector 
		
			for ( ; (first1 <= last1 ) && (first2 <= last2 ) ; ++index ) {
				
				if (sortlist.at(first1).numOfGrad >= sortlist.at(first2).numOfGrad ) {  
					temp.at(index) = sortlist.at(first1) ;  //大的放前面 
					++first1 ;
				}
				else {
					temp.at(index) = sortlist.at(first2) ;  //小的放後面  
					++first2 ;
				}
			}
			
			for ( ; first1 <= last1 ; ++first1, ++index) { // 做完左邊 
				temp.at(index) = sortlist.at(first1) ;
			}
			
			for ( ; first2 <= last2 ; ++first2, ++index) { // 做完右邊 
				temp.at(index) = sortlist.at(first2) ;
			}  
			
			for (index = first; index <= last; ++index) { // 複製結果 
				sortlist.at(index) = temp.at(index);
				
			}	
		}
		
		void merge_sort( int start, int back ) {   
			int mid = 0 ;
			if ( start < back ) {
				mid = ( start +  back ) / 2 ; // 切兩個vector範圍 
				merge_sort( start, mid ) ;    // 分割 vector 的前段 
				merge_sort( mid + 1, back ) ; // 分割 vector 的後段 
				Mergearr(start, mid, back) ;  // 比較並合併vector 
			}	
		}
		
		int Partition(int first, int back) { //右邊>=p，左邊<p 

			int pivot = sortlist.at(first).numOfGrad ;  
			int last = first ;
			int unknow = first + 1 ;
			while ( unknow <= back ) {
				if( sortlist.at(unknow).numOfGrad >= pivot ) {  //左邊位置 
					++last ;
					swap(sortlist.at(last), sortlist.at(unknow)) ;
				}
				++unknow ;
				
			}
			swap(sortlist.at(last), sortlist.at(first)) ; //把pivot換到他的位置上 
			return last ; // 回傳pivot位置 
		}
		
		void quick_sort( int start, int back ) { 
		int p = 0 ;
			if( start < back ) {
				p = Partition(start, back) ; // 找pivot 
				quick_sort(start, p-1) ;  //排左邊 
				quick_sort(p+1, back) ;   //排右邊 
			}
		}
		
		void radix_sort() { 
			int max = 0 ; //存最大的數 
			for ( int i = 0 ; i < datanum ; i++ ) {  //找到最大的numofgrad 
				if ( max < sortlist.at(i).numOfGrad ) {
					max = sortlist.at(i).numOfGrad ;
				}
			}
			
			int num = 0 ;  //數numofgrad的最大位數 
			int temp = max ;  
			while ( temp > 0 ) { 
				temp /= 10 ;
				num++ ;
			}
			
			queue<Type> qtemp[10] ;  //存0~9餘數的queue 
			int divide = 1 ;         //除數先設1 

			for ( int i = 0 ; i < num ; i++) { //用幾位數設定要跑的次數 
				
				for ( int j = 0 ; j < datanum; j++ ) { //分類他在第幾位數的餘數是多少 
					qtemp[( sortlist.at(j).numOfGrad / divide ) % 10].push(sortlist.at(j)) ; //從他的位數決定他要丟到幾號queue 
				}
				
				int k = 0 ;
				for ( int j = 9 ; j >= 0 ; j-- ) {  //從9號queue開始倒出來 
					while ( qtemp[j].empty() == false ) {
						swap(sortlist.at(k), qtemp[j].front() ) ;	//從queue開頭存入sortlist，用k數數量 
						k++ ;		
						qtemp[j].pop() ;
					}
				}
				
				divide *= 10 ;		//除數每次*10 
			}	
		} 	
}; // class

bool isDigit( string str ) {
// 判斷是否為數字 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

void mission1() {  // bb 301 // sc 20
	clock_t bbt ;    //計時bubblesort 
	clock_t st ;	 //計時selectionsort 
	
	Data bubble ; 
	if( bubble.ReadFile("input") ) {
		bbt = clock() ;  //開始計時 
		bubble.bubble_sort() ;
		bbt = clock() - bbt ; //結束計時  
		bubble.WriteFile("bubble_sort") ;  
	}

	Data select ;
	// strcpy(select.ID,bubble.ID) ;
	if( select.ReadFile("input", bubble.ID) ) {
		st = clock() ; //開始計時 
		select.select_sort() ;
		st = clock() - st ; //結束計時  
		bubble.WriteFile("Select_sort") ;
	}
	
	cout << "\nSelect sort: " << st << " ms." << endl ;
	cout << "\nBubble sort: " << bbt << " ms." << endl ;
	
}

void mission2() {  // bb 301 // sc 20
	clock_t ms ;    //計時mergesort 
	clock_t qs ;	//計時quicksort 
	
	Data merge ;
	if( merge.ReadFile("input") ) {
		ms = clock() ; //開始計時 
		int start = 0 ;
		int back = merge.datanum ;  //取得vector的size 
		merge.merge_sort( start, back -1 ) ;
		ms = clock() - ms ; //結束計時  
		merge.WriteFile("Merge_sort") ;
		cout << "\nMerge sort: " << ms << " ms." << endl ;
	}

	
	Data quick ;
	if( quick.ReadFile("input", merge.ID) ) {
		qs = clock() ; //開始計時 
		quick.quick_sort(0,quick.datanum-1) ;
		qs = clock() - qs ; //結束計時  
		quick.WriteFile("Quick_sort") ;
		cout << "\nQuick sort: " << qs << " ms." << endl ;
	}
	
}

void mission3() {
	clock_t rs ;    
	
	Data radix ;
	if( radix.ReadFile("input") ) {
		rs = clock() ; //開始計時 
		radix.radix_sort( ) ;
		rs = clock() - rs ; //結束計時 
		radix.WriteFile("Radix_sort") ;
		cout << "\nRadix sort: " << rs << " ms." << endl ;
	}
}

//==========================================================================
void mission1(string ID, clock_t &bbt, clock_t &st) {  // bb 301 // sc 20
	Data bubble ; 
	if( bubble.ReadFile("input", ID) ) {
		bbt = clock() ;  //開始計時 
		bubble.bubble_sort() ;
		bbt = clock() - bbt ; //結束計時  
		bubble.WriteFile("bubble_sort") ;  
	}

	Data select ;
	// strcpy(select.ID,bubble.ID) ;
	if( select.ReadFile("input",ID) ) {
		st = clock() ; //開始計時 
		select.select_sort() ;
		st = clock() - st ; //結束計時  
		bubble.WriteFile("Select_sort") ;
	}
	
	cout << "\nSelect sort: " << st << " ms." << endl ;
	cout << "\nBubble sort: " << bbt << " ms." << endl ;
	
}

void mission2(string ID, clock_t &qs, clock_t &ms) {  // bb 301 // sc 20
	
	Data merge ;
	if( merge.ReadFile("input",ID) ) {
		ms = clock() ; //開始計時 
		int start = 0 ;
		int back = merge.datanum ;  //取得vector的size 
		merge.merge_sort( start, back -1 ) ;
		ms = clock() - ms ; //結束計時  
		merge.WriteFile("Merge_sort") ;
		cout << "\nMerge sort: " << ms << " ms." << endl ;
	}

	
	Data quick ;
	if( quick.ReadFile("input", ID) ) {
		qs = clock() ; //開始計時 
		quick.quick_sort(0,quick.datanum-1) ;
		qs = clock() - qs ; //結束計時  
		quick.WriteFile("Quick_sort") ;
		cout << "\nQuick sort: " << qs << " ms." << endl ;
	}
	
}

void mission3(string ID, clock_t &rs) {

	Data radix ;
	if( radix.ReadFile("input", ID) ) {
		rs = clock() ; //開始計時 
		radix.radix_sort( ) ;
		rs = clock() - rs ; //結束計時 
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

	string command = "/0" ; // 讀取指令 
	int cd = -1 ;           // int的指令 
	
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
		
		if ( isDigit(command) ) // 是否為int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) mission1() ; // 進入任務一 
		else if ( cd == 2 ) mission2() ; // 進入任務二 
		else if ( cd == 3 ) mission3() ; // 進入任務三 
		else if ( cd == 4 ) mission4() ;
		else cout << endl << "Command is NOT exist !!" << endl ; // 無此指令 
		
	} while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
