//11027222�����M
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
	
	string line ;   // �s�@���� 
}; // InputFile

class File {
	
	vector<InputFile> list ;  // �sŪ�J��data 
	string ID ;               // �s�ɮץN�X
	string title ;            // ���Y 
	
	
	void GetLineOfData( string line, InputFile & list ) {
    	// �h�sline�̭�����T 
    	string data = "/0" ;
		
		GetString(line, 9, data) ;
		FixNum(data) ;
		list.value = atoi(data.c_str()) ;
		
	} // GetLineOfData
	
	
	public :
		void GetString(string line, int index, string & str) {
     		// ����line����T
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
			// �׾ǥͼƼƦr���S��input "XXX"
			
			int n = num.size() ;
			if ( num[0] == '\"' && num[n-1] == '\"' ) {
				num = num.erase(n-1, n) ; // �����᭱�����޸� 
				num = num.erase(0, 1) ;   // �����e�������޸� 
				num = num.erase(1, 1) ;   // �����������r�� 
			} // if
				
		} // FixNum 
		
		bool ReadFile( string name ) {
		// �s�� file �̪� data
		
			InputFile data ;
			ifstream in ;
			string file ;  
			int count = 0 ;
				
    		cout << endl << "Input a file number [0: quit] : " ;
    		cin >> ID ; // Ū�J�ɮץN�X 
			
			if ( ID == "0" )
				return false ;

    		file = name + ID + ".txt" ;  // �إ��ɮק���W�� 
    			
    		in.open(file.c_str(), ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    		if ( !in.is_open() ) { // �䤣�즹�ɮ׿�Xerror 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				for ( int i = 0 ; i < 3 ; i++) {
					getline(in, title) ;  // Ū�e�T�椣�n��data
				}

				while( getline(in, data.line) ) {   // �v��s���   
					GetLineOfData(data.line, data) ;
					list.push_back(data) ;
					list.at(count).num = count + 1 ;    
					count++ ;
				} // while
						
			} // else
			
			in.close() ; // ���� 
			
			return true ;
		
		} // ReadFile
		
		void clearFile() {
			// ���������ƧR�� 
			
			list.clear() ;
			
		} // clearFile

		vector<InputFile> GetList() {
			// ���o��� 
			
			return list ;
			
		} // GetList()
		
		~File() {
			
			list.clear() ;
			ID = "/0" ;
			
		} // destructor
		
}; // File

class minHeap : public File {
	vector<InputFile> minheap ;  // minheap�����
	
	void swapup(int i) {    
		i-- ;  // i = ��ɪ�.size()�ҥH�n��@�~�|�O��enode��number 
        while (i > 0) {
            int parent = (i - 1) / 2 ;  // ���Ӹ`�Iparent����m 
            if ( minheap.at(i).value < minheap.at(parent).value ) {    //���`�I>�l�`�I�A��̰��洫 
                swap( minheap.at(i), minheap.at(parent) ) ;			   //�����������min heap�����󬰤� 
                i = parent ;
            } else {
                break ;
            }
        }
        
    }
    
    int findleftmostindex() {  // �����heap�̥��U��node��index 
   		int j = 0 ;
		while ( 1 ) {
			if ( pow(2,j) <= minheap.size() && pow(2,j+1)-1 >= minheap.size() ) {   //�i�H��X�̦h���j�h                                     //lestmostnode��index = 2 ^ j - 1
				j = pow(2,j) - 1 ;
    			return j ;   //�^��index 
    			
			}
			j++ ;
		}
		
	}
	
	
	public :
		void push( vector<InputFile> list, int i ) {  // ��data��iheap�� 
			
			minheap.push_back(list.at(i)) ;
			swapup(minheap.size()) ;      // ��o��ƥ�iheap�çP�_�O�_�n���W�洫 
			
		}
		
		void print() {
			
    		cout << "<min heap>" << endl ;
    		printf("root: [%d] %d\n", minheap.at(0).num, minheap.at(0).value) ;
    		printf("bottom: [%d] %d\n", minheap.at(minheap.size()-1).num, minheap.at(minheap.size()-1).value) ;
    		int index = 0 ;
    		index = findleftmostindex() ;
    		printf("leftmost node: [%d] %d\n", minheap.at(index).num, minheap.at(index).value) ;
    		
		}
		
		void clean() {  //�M����� 
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
    
    int findleftmostindex() {  // �����heap�̥��U��node��index 
   		int j = 0 ;
		while ( 1 ) {
			if ( pow(2,j) <= min_maxheap.size() && pow(2,j+1)-1 >= min_maxheap.size() ) {   //�i�H��X�̦h���j�h                                     //lestmostnode��index = 2 ^ j - 1
				j = pow(2,j) - 1 ;
    			return j ;   //�^��index 
    			
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
// �P�_�O�_���Ʀr 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

void mission1( minHeap & minheap ) {
	
	vector<InputFile> list ;
	
	if ( minheap.ReadFile("input") ) { // �Y��Ū���ơA�i�J 
		
		list = minheap.GetList() ;     // ���XŪ�쪺��� 
		for ( int i = 0 ; i < list.size() ; i++ ) {
			minheap.push(list, i) ;    // ��list�����F��@�@�إߨ�heap�� 
		}
		
		minheap.print() ;              //�L�Xheap���ݭn��data 
	
	} // if
	
	minheap.clearFile() ;
	minheap.clean() ;                  // �M��heap 

} // mission1

void mission2( minmaxHeap & min_maxheap ) {
	
	min_maxheap.clearFile() ;
	min_maxheap.clean() ;                  // �M��heap 
	
	vector<InputFile> list ;  
	
	if ( min_maxheap.ReadFile("input") ) { // �Y��Ū���ơA�i�J 
		
		list = min_maxheap.GetList() ;     // ���XŪ�쪺��� 
		for ( int i = 0 ; i < list.size() ; i++ ) {
			min_maxheap.push(list, i) ;    // ��list�����F��@�@�إߨ�heap�� 
		}
		
		min_maxheap.print() ;              //�L�Xheap���ݭn��data 
	
	} // if
	

} // mission2

void mission3( minmaxHeap & min_maxheap, int count ) {
	
	for ( int i = 0 ; i < count ; i++ ) {
		cout << "TOP  " << setw(2) << i+1 << ":" ;
		min_maxheap.deletemin() ;
	}
	
}


int main() {
	
	string command = "/0" ; // Ū�����O 
	int cd = -1 ;           // int�����O
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
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			mission1(minheap) ; // �i�J���Ȥ@ 
		}
		else if ( cd == 2 ){
			mission2(min_maxheap) ; // �i�J���ȤG 
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
			cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		}
	}while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
