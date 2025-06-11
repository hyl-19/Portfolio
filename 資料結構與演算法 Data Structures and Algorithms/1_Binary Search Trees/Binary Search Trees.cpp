//11027222黃彥霖
//DS0
 
# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>
# include<ctime>
# include<iomanip>
# include<stack>

using namespace std ;

struct InputFile {
	
	string line ;   // 存一行資料 
	string schoolname ;
	string depname ;
	string course ;
	string level ;
	int stunum ;
	int tecnum ;
	int grad ;
	
}; // InputFile

struct Node {
	vector<InputFile> data ;
	Node * right ;
	Node * left ;
		
}; // Node

class File {
	
	vector<InputFile> list ;  // 存清單
	string ID ;               // 檔案代碼
	string title ;            // 標頭 
	
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
	
	void GetLineOfData( string line, InputFile & list ) {
    	// 去存line裡面的資訊 
    	string data = "/0" ;
    	
		GetString(line, 2, list.schoolname) ;
			
		GetString(line, 4, list.depname) ;
			
		GetString(line, 5, list.course) ;
		  		
		GetString(line, 6, list.level) ;
		
		GetString(line, 7, data) ;
		FixNum(data) ;
		list.stunum = atoi(data.c_str()) ;
		
		GetString(line, 8, data) ;
		FixNum(data) ;
		list.tecnum = atoi(data.c_str()) ;
		
		GetString(line, 9, data) ;
		FixNum(data) ;
		list.grad = atoi(data.c_str()) ;
		
	} // GetLineOfData
		
	void FixNum( string & num ) {
		//  去修學生數的數字，"1,038"
			
		int n = num.size() ;
		if ( num[0] == '\"' && num[n-1] == '\"' ) {
			num = num.erase(n-1, n) ; // 消除後面的雙引號 
			num = num.erase(0, 1) ; // 消除前面的雙引號 
			num = num.erase(1, 1) ; // 消除中間的逗號 
		} // if
				
	} // FixNum 
	
	public :

		string FileName( string str ) { 
		// 回傳完整的 file name
		
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// 存取 file 裡的 data
		
			InputFile data ;
			ifstream in ;
			string file ; // 檔案名稱
				
    		cout << endl << "Input a file number [0: quit] : " ;
    		cin >> ID ; // 讀入檔案代碼 
			
			if ( ID == "0" )
				return false ;

    		file = FileName(name) ; // 檔案完整名稱 
    			
    		in.open(file.c_str(), ios::in) ; // 在讀入模式下開啟in檔案
    	
    		if ( !in.is_open() ) { // 找不到此檔案 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				for ( int i = 0 ; i < 3 ; i++) {
					getline(in, title) ;  // 讀標頭
				}

				while( getline(in, data.line) ) { // 存資料
					GetLineOfData(data.line, data) ;
					list.push_back(data) ;
				} // while
						
			} // else
			
			in.close() ; // 關檔 
			
			return true ;
		
		} // ReadFile
		
		void WriteFile( string name ) {
			// 寫檔案 str 為檔案名稱 
			
			string file ;
			
			file = FileName(name) ; // 檔案完整名稱
			 
			ofstream out(file.c_str()) ; // 建立檔案 
			
			for ( int i = 0 ; i < list.size() ; i++ ) // 寫入資料 
				out << list.at(i).line << endl ;
			
			out.close() ; // 關檔
			
		} // WriteFile
		
		void PrintAll() {  // 印出所有pokemon的資料 
			
			for ( int i = 0 ; i < list.size() ; i++ ) {
				
				cout << left << setw(1) << "[" ; 
				cout << right << setw(3) << i + 1 ;
				cout << setw(1) << "]" ;
				cout << "   " ;
				cout << left << setw(20) << list.at(i).schoolname ;
				cout << left << setw(34) << list.at(i).depname ;
				cout << left << setw(8) << list.at(i).course ;
				cout << left << setw(8) << list.at(i).level ;
				cout << left << setw(8) << list.at(i).stunum ;
				cout << left << setw(8) << list.at(i).tecnum ;
				cout << left << setw(8) << list.at(i).grad << endl ;
				
			} // for
			
		} // PrintAll
		
		
		void clearFile() {
			// 把全部的資料刪除 
			
			list.clear() ;
			
		} // clearFile

		vector<InputFile> GetList() {
			// 取得資料 
			
			return list ;
			
		} // GetList()
		
}; // File

class BST : public File {
	
	int treeHigh( Node * root ) {
		// 計算樹高，並回傳 
		
		int left = 0 ;
		int right = 0 ;
		
		if ( root == NULL )
			return 0 ;
			
		left = left + treeHigh(root->left) + 1 ;
		right = right + treeHigh(root->right) + 1 ;
		
		if ( left > right ) return left ;
		return right ;
		
	} // treeHigh
	
	public :
		
		Node * newNode( Node * root, InputFile data ) {
			// 建立新的node 
			
			root = new Node ;
			root->data.push_back(data) ;
			root->left = root->right = NULL ;
			return root ;
			
		} // newNode
		
		
		Node * build( Node * root, InputFile data ) {
			// 建立樹 
			
			if ( root == NULL ) {  // base case
			
				root = newNode(root, data) ;	
				
			} // if
			else if ( data.grad < root->data.at(0).grad ) {  // 若data裡的hp小於樹目前位置的hp 
				
				root->left = build( root->left, data ) ; // 往左邊放 
				
			} // else if
			else if ( data.grad >= root->data.at(0).grad ) {  // 若data裡的hp大於樹目前位置的hp
			
				root->right = build( root->right, data ) ; // 往右邊放
				
			} // else if
			
			return root ;  // 回傳已經建好的樹 
			
		} // build

		
		void showHigh( Node * root ) {
			// 印出目前樹的樹高 
			
			int h = treeHigh(root) ;
			
			cout << endl << "tree height {Number of graduates} = " << h << endl ;
			
		} // showHigh

		Node * deleteNode( Node * root, int num ) {  //刪除節點 

			Node * temp = NULL ;
			Node * cur = NULL ;
			
			if( root == NULL ) {
				return root;
			}
			
			if( num > root->data.at(0).grad ) {   //往右邊走 
				root -> right = deleteNode(root->right, num) ;
			}
			else if( num < root->data.at(0).grad ) {  //往左邊走  
				root -> left = deleteNode(root->left, num) ;
			}
			else {
				if( root -> left == NULL  ){	//左邊空 
					if( root -> data.size() == 1 ){ //是否只有一個 
						temp = root -> right ;
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //刪vector編號最大的 
						root->data.erase(root->data.begin()) ;
						return root ;
					}
				}
				else if( root -> right == NULL  ) { //右邊空 
					if( root -> data.size() == 1 ){ //是否只有一個 
						temp = root -> left ;
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //刪vector編號最大的 
						root->data.erase(root->data.begin()) ;
						return root;
					}
				}
				else if ( root-> right != NULL && root -> left != NULL ) {   //兩邊都有東西(inorder successor) 
				
					cur = root -> right ;
					while ( cur->left != NULL ) { //找最左邊的subtree 
        			cur = cur->left;
    				}
					temp = cur ;
					root->data = temp->data ;   
					root -> right = deleteNode(root->right, temp->data.at(0).grad) ;
				}
			}
			
			return root;
		} 
		
		Node * deleteAll( Node * root ) {
			// 刪除全部的樹 
			
			if ( root != NULL ) {
				
				deleteAll(root->left) ;
				deleteAll(root->right) ;
				delete root ;
				
			} // if
			
			return root ;
			
		} // deleteAll
		
				 
}; // BST

bool isDigit( string str ) {
// 判斷是否為數字 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

Node * mission1( Node * root, BST & tree ) {
	// 任務一 
	
	vector<InputFile> list ; // 存放讀取file的資料 
	
	if ( root != NULL ) { // 若樹已經被建造，打掉
			tree.clearFile() ;
			root = tree.deleteAll(root) ;
			root = NULL ;
	} // if
	
	if ( tree.ReadFile("input") ) { // 若有讀到資料，進入 
	 
		tree.PrintAll() ; // 印出讀到的所有資料 
		
		list = tree.GetList() ; // 取出讀到的資料 
		
		for ( int i = 0 ; i < list.size() ; i++ ) {

			root = tree.build(root, list.at(i)) ; // 開始建立樹 		
		}
		system("pause") ;
		tree.showHigh(root) ; // 印出樹高 
		
	} // if
	
	return root ; // 回傳樹 
	
} // mission1

void mission2( Node * root, BST tree, vector<InputFile> & list ) {
	int delnum ;
	int count = 0 ;
	cout << "Input the number of graduates:" ;
	cin >> delnum ;
	for ( int i = 0 ; i < list.size() ; i++) {
		if ( list.at(i).grad <= delnum ) {
			count++ ;
			root = tree.deleteNode(root, list.at(i).grad) ;
			cout << left << "[" ; 
			cout << right << setw(3) << count ;
			cout << setw(1) << "]" ;
			cout << "   " ;
			cout << left << setw(20) << list.at(i).schoolname ;
			cout << left << setw(34) << list.at(i).depname ;
			cout << left << setw(8) << list.at(i).course ;
			cout << left << setw(8) << list.at(i).level ;
			cout << left << setw(8) << list.at(i).stunum ;
			cout << left << setw(8) << list.at(i).tecnum ;
			cout << left << setw(8) << list.at(i).grad << endl ;
			list.erase(list.begin() + i ) ;
			i-- ;
		}
	}
	
	
	if ( count == 0 ) {
		cout << "There is no match!" << endl ;
	}
	tree.showHigh(root) ;

} // mission2


int main() {
	
	string command = "/0" ; // 讀取指令 
	int cd = -1 ;           // int的指令
	Node * root = NULL ;    // 樹 
	BST tree ;              // class of BST 
	vector<InputFile> list ;
	
	do { 
	
		cout << endl << "*** University Graduate Information System ***" ;
		cout << endl << "* 0. QUIT                                    *" ;
		cout << endl << "* 1. Create Binary Search Trees              *" ;
		cout << endl << "* 2. Removal by Number of Graduates          *" ;
		cout << endl << "**********************************************" ;
		cout << endl << "Input a command(0, 1, 2) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // 是否為int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			root = mission1(root, tree) ; // 進入任務一 
			list = tree.GetList() ;
		}
		else if ( cd == 2 ) mission2(root, tree, list) ; // 進入任務二 
		else cout << endl << "Command is NOT exist !!" << endl ; // 無此指令 
		
	 	}while ( cd != 0 ) ;
	
	root = tree.deleteAll(root) ;  // 刪除資料 
	system("pause") ;
	return 0 ;
	
} // main
