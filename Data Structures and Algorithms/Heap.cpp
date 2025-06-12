//11027222黃彥霖
//DS0
 
# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>
# include<iomanip>
# include<math.h>

using namespace std ;

struct InputFile {
	int num ;
	int value ;
	
	string line ;   // 存一行資料 
}; // InputFile

class File {
	
	vector<InputFile> list ;  // 存讀入的data 
	string ID ;               // 存檔案代碼
	string title ;            // 標頭 
	
	
	void GetLineOfData( string line, InputFile & list ) {
    	// 去存line裡面的資訊 
    	string data = "/0" ;
		
		GetString(line, 9, data) ;
		FixNum(data) ;
		list.value = atoi(data.c_str()) ;
		
	} // GetLineOfData
	
	
	public :
		void GetString(string line, int index, string & str) {
     		// 分割line的資訊
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
			// 修學生數數字的特殊input "XXX"
			
			int n = num.size() ;
			if ( num[0] == '\"' && num[n-1] == '\"' ) {
				num = num.erase(n-1, n) ; // 消除後面的雙引號 
				num = num.erase(0, 1) ;   // 消除前面的雙引號 
				num = num.erase(1, 1) ;   // 消除中間的逗號 
			} // if
				
		} // FixNum 
		
		bool ReadFile( string name ) {
		// 存取 file 裡的 data
		
			InputFile data ;
			ifstream in ;
			string file ;  
			int count = 0 ;
				
    		cout << endl << "Input a file number [0: quit] : " ;
    		cin >> ID ; // 讀入檔案代碼 
			
			if ( ID == "0" )
				return false ;

    		file = name + ID + ".txt" ;  // 建立檔案完整名稱 
    			
    		in.open(file.c_str(), ios::in) ; // 在讀入模式下開啟in檔案
    	
    		if ( !in.is_open() ) { // 找不到此檔案輸出error 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				for ( int i = 0 ; i < 3 ; i++) {
					getline(in, title) ;  // 讀前三行不要的data
				}

				while( getline(in, data.line) ) {   // 逐行存資料   
					GetLineOfData(data.line, data) ;
					list.push_back(data) ;
					list.at(count).num = count + 1 ;    
					count++ ;
				} // while
						
			} // else
			
			in.close() ; // 關檔 
			
			return true ;
		
		} // ReadFile
		
		void clearFile() {
			// 把全部的資料刪除 
			
			list.clear() ;
			
		} // clearFile

		vector<InputFile> GetList() {
			// 取得資料 
			
			return list ;
			
		} // GetList()
		
		~File() {
			
			list.clear() ;
			ID = "/0" ;
			
		} // destructor
		
}; // File

class minHeap : public File {
	vector<InputFile> minheap ;  // minheap的資料
	
	void swapup(int i) {    
		i-- ;  // i = 當時的.size()所以要減一才會是當前node的number 
        while (i > 0) {
            int parent = (i - 1) / 2 ;  // 找到該節點parent的位置 
            if ( minheap.at(i).value < minheap.at(parent).value ) {    //父節點>子節點，兩者做交換 
                swap( minheap.at(i), minheap.at(parent) ) ;			   //持續比較到維持min heap的條件為止 
                i = parent ;
            } else {
                break ;
            }
        }
        
    }
    
    int findleftmostindex() {  // 找到整個heap最左下的node的index 
   		int j = 0 ;
		while ( 1 ) {
			if ( pow(2,j) <= minheap.size() && pow(2,j+1)-1 >= minheap.size() ) {   //可以算出最多到第j層                                     //lestmostnode的index = 2 ^ j - 1
				j = pow(2,j) - 1 ;
    			return j ;   //回傳index 
    			
			}
			j++ ;
		}
		
	}
	
	
	public :
		void push( vector<InputFile> list, int i ) {  // 把data丟進heap裡 
			
			minheap.push_back(list.at(i)) ;
			swapup(minheap.size()) ;      // 把這資料丟進heap並判斷是否要往上交換 
			
		}
		
		void print() {
			
    		cout << "<min heap>" << endl ;
    		printf("root: [%d] %d\n", minheap.at(0).num, minheap.at(0).value) ;
    		printf("bottom: [%d] %d\n", minheap.at(minheap.size()-1).num, minheap.at(minheap.size()-1).value) ;
    		int index = 0 ;
    		index = findleftmostindex() ;
    		printf("leftmost node: [%d] %d\n", minheap.at(index).num, minheap.at(index).value) ;
    		
		}
		
		void clean() {  //清除資料 
			minheap.clear() ;
		}
		 
}; // minheap

class minmaxHeap : public File {
	vector<InputFile> min_maxheap ;  
	
	int findlevel(int i) {
		int j = 0 ;
		while ( 1 ) {
			if ( pow(2,j) <= i && pow(2,j+1)-1 >= i ) {   //index start at 1, the each level node will
    			return j ;                                //between 2^k ~ 2^(k+1)-1, and return level
    			
			}
			j++ ;
		}
	}
	
	void minswap(int i) {  //minheap
		
        while (i > 0) {
            int parent = (i - 1) / 2;
            int grandparent = (parent - 1) / 2 ;
            if ( min_maxheap.at(i).value < min_maxheap.at(grandparent).value ) {  //node.value < grandparent.value
                swap( min_maxheap.at(i), min_maxheap.at(grandparent) );
                i = grandparent;
                
            } else {
                break;
            }
        }
    }
    
    void maxswap(int i) {  // maxheap
		
        while (i > 0) {
            int parent = (i - 1) / 2;
            int grandparent = (parent - 1) / 2;
            int level = findlevel(i+1) ;
            if ( level <= 1  ) {  // the node need to change level can't be 1 because in min-max heap 
            	return ;		  // level = 1 is the top of the max heap level 
			}
            else if ( min_maxheap.at(i).value > min_maxheap.at(grandparent).value ) { // node.value > grandparent.value
                swap( min_maxheap.at(i), min_maxheap.at(grandparent) );
                i = grandparent;
                
            } else {
                break;
            }
            
            
        }   
    }
	
	void swapup(int i) {
		i-- ;
		int parent = (i - 1) / 2 ; 
        
        	int level = findlevel(parent+1) ;
        	//cout << "plevel=" << level << endl ;
            if ( level % 2 == 0 ) {  //parent is in min heap level 
            	if ( min_maxheap.at(i).value < min_maxheap.at(parent).value ) { // node,value < parent.value
                	swap( min_maxheap.at(i), min_maxheap.at(parent) );
                	i = parent ;
                	minswap(i) ;
        		}
        		else {
        			maxswap(i) ;    // ensure max heap (in max heap level)
				}
			}
			else if ( level % 2 == 1 ) {  //parent is in max heap level 
				if ( min_maxheap.at(i).value > min_maxheap.at(parent).value ) {  // node,value > parent.value
                	swap( min_maxheap.at(i), min_maxheap.at(parent) );
                	i = parent;	
                	maxswap(i) ;
				}
				else {
					minswap(i) ;  // ensure min heap (in min heap level)
				}
			}
			
		           
    }
    
    int findleftmostindex() {  // 找到整個heap最左下的node的index 
   		int j = 0 ;
		while ( 1 ) {
			if ( pow(2,j) <= min_maxheap.size() && pow(2,j+1)-1 >= min_maxheap.size() ) {   //可以算出最多到第j層                                     //lestmostnode的index = 2 ^ j - 1
				j = pow(2,j) - 1 ;
    			return j ;   //回傳index 
    			
			}
			j++ ;
		}
		
	}
        

	public :
		void push( vector<InputFile> list, int i ) {
			
			min_maxheap.push_back(list.at(i)) ;
			swapup(min_maxheap.size()) ;
			
		}
		
		void print() {
			
    		cout << "<min-max heap>" << endl ;
    		printf("root: [%d] %d\n", min_maxheap.at(0).num, min_maxheap.at(0).value) ;
    		printf("bottom: [%d] %d\n", min_maxheap.at(min_maxheap.size()-1).num, min_maxheap.at(min_maxheap.size()-1).value) ;
    		int index = 0 ;
    		index = findleftmostindex() ;
    		printf("leftmost node: [%d] %d\n", min_maxheap.at(index).num, min_maxheap.at(index).value) ;
    		
		}
		
		void printdelete() {
			string data ;
			cout << "[" << min_maxheap.at(0).num << "] " ;
			GetString( min_maxheap.at(0).line, 2, data ) ;
			cout << data ;
			GetString( min_maxheap.at(0).line, 4, data ) ;
			cout << data << ", " ;
			GetString( min_maxheap.at(0).line, 5, data ) ;
			FixNum(data) ;
			cout << data << ", " ;
			GetString( min_maxheap.at(0).line, 6, data ) ;
			FixNum(data) ;
			cout << data << ", " ;
			cout << min_maxheap.at(0).value << endl ;
			
		}
		
		void deletemin() {
			printdelete() ;
			//cout << min_maxheap.at(0).value << endl ;
			if ( min_maxheap.size() > 0 ) {
				swap(min_maxheap.at(0), min_maxheap.at(min_maxheap.size()-1)) ;
			}
			
			//cout << min_maxheap.at(min_maxheap.size()-1).line ;
			
			min_maxheap.pop_back() ;
			if(min_maxheap.size()== 0 ) {
				return ;
			}
			
			int index = 0 ;
			int cL = 2*index+1 ;
			int cR = 2*index+2 ;

			if ( cL < min_maxheap.size() && min_maxheap.at(cL).value < min_maxheap.at(index).value ) {
				swap(min_maxheap.at(index), min_maxheap.at(cL) );
			}
			else if ( cR < min_maxheap.size() && min_maxheap.at(cR).value < min_maxheap.at(index).value ) {
				swap(min_maxheap.at(index), min_maxheap.at(cR)) ;
			}
			
			int checkchild = 2 * cL + 1 ;
			int min = min_maxheap.at(index).value ;
			int tempindex = 0 ;
			
			while ( 1 ) {
				for ( int i = 0 ; i < 4 && (checkchild + i) < min_maxheap.size() ; i++ ) {
					
					if ( min_maxheap.at(checkchild+i).value < min ) {
						min = min_maxheap.at(checkchild+i).value ;
						tempindex = checkchild+i ;
					}
				}
				if ( min == min_maxheap.at(index).value ) {
					break ;
				}
				else {
					swap(min_maxheap.at(index), min_maxheap.at(tempindex) );
					index = tempindex ;
				}
				
				min = min_maxheap.at(index).value ;
				tempindex = 0 ;
				checkchild = 2 * index + 1 ;
				cL = checkchild ;
				cR = 2*index+2 ;
				if ( cL < min_maxheap.size() && min_maxheap.at(cL).value < min_maxheap.at(index).value ) {
					swap(min_maxheap.at(index), min_maxheap.at(cL) );
					}
				else if ( cR < min_maxheap.size() && min_maxheap.at(cR).value < min_maxheap.at(index).value ) {
					swap(min_maxheap.at(index), min_maxheap.at(cR)) ;
				}
				
				checkchild = 2 * checkchild + 1 ;
			}
			
		}
		
		void clean() {
			min_maxheap.clear() ; // clean the vector 
		}
		
		int getsize() {
			return min_maxheap.size() ;
		}
		
}; // minmaxheap



bool isDigit( string str ) {
// 判斷是否為數字 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

void mission1( minHeap & minheap ) {
	
	vector<InputFile> list ;
	
	if ( minheap.ReadFile("input") ) { // 若有讀到資料，進入 
		
		list = minheap.GetList() ;     // 取出讀到的資料 
		for ( int i = 0 ; i < list.size() ; i++ ) {
			minheap.push(list, i) ;    // 把list內的東西一一建立到heap裡 
		}
		
		minheap.print() ;              //印出heap面需要的data 
	
	} // if
	
	minheap.clearFile() ;
	minheap.clean() ;                  // 清除heap 

} // mission1

void mission2( minmaxHeap & min_maxheap ) {
	
	min_maxheap.clearFile() ;
	min_maxheap.clean() ;                  // 清除heap 
	
	vector<InputFile> list ;  
	
	if ( min_maxheap.ReadFile("input") ) { // 若有讀到資料，進入 
		
		list = min_maxheap.GetList() ;     // 取出讀到的資料 
		for ( int i = 0 ; i < list.size() ; i++ ) {
			min_maxheap.push(list, i) ;    // 把list內的東西一一建立到heap裡 
		}
		
		min_maxheap.print() ;              //印出heap面需要的data 
	
	} // if
	

} // mission2

void mission3( minmaxHeap & min_maxheap, int count ) {
	
	for ( int i = 0 ; i < count ; i++ ) {
		cout << "TOP  " << setw(2) << i+1 << ":" ;
		min_maxheap.deletemin() ;
	}
	
}


int main() {
	
	string command = "/0" ; // 讀取指令 
	int cd = -1 ;           // int的指令
	minHeap minheap ;              // class of BST 
	minmaxHeap min_maxheap ;
	
	do { 
	
		cout << endl << "********** Heap Construction **********" ;
		cout << endl << "* 0. QUIT                             *" ;
		cout << endl << "* 1. Build a min heap                 *" ;
		cout << endl << "* 2. Build a min-max heap             *" ;
		cout << endl << "* 3: Top-K minimums from min-max heap *" ;
		cout << endl << "***************************************" ;
		cout << endl << "Input a command(0, 1, 2, 3) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // 是否為int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			mission1(minheap) ; // 進入任務一 
		}
		else if ( cd == 2 ){
			mission2(min_maxheap) ; // 進入任務二 
		}
		else if ( cd == 3 ) {
			int count = 0 ;
			cout << "Enter the value of K in [1," << min_maxheap.getsize()  <<"]:" ;
			cin >> count ;
			if ( count > 0 && count < min_maxheap.getsize() + 1 ) {
				mission3(min_maxheap, count) ;
			}
		} 
		else {
			cout << endl << "Command is NOT exist !!" << endl ; // 無此指令 
		}
	}while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
