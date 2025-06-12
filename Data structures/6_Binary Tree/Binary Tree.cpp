// 07組 11027212 黃建閎 11027222 黃彥霖
// DS 6

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

struct pokemon {
	
	string line ;   // 存一行資料 
	int No ;        // pokemon的號碼 
	string name ;   // pokemon Name 
	string type1 ;  // pokemon type 1
	int total ;     // 總和 
	int hp ;        // pokemon HP
	int atk ;       // pokemon Attack
	int def ;       // pokemon Defense
	
}; // pokemon

struct Node {
	// tree node data
		
	vector<pokemon> data ;
	Node * right ;
	Node * left ;
		
}; // Node

class File {
	
	vector<pokemon> list ;  // 存清單
	string ID ;             // 檔案代碼
	string title ;          // 標頭 
	
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
	
	void GetLineOfData( string line, pokemon & list ) {
    	// 去存line裡面的資訊 
    	string data = "/0" ;
    		
		GetString(line, 1, data) ;
		FixNum(data) ;
		list.No = atoi(data.c_str()) ;
		
		GetString(line, 2, list.name) ;
			
		GetString(line, 3, list.type1) ;
			
		GetString(line, 5, data) ;
		FixNum(data) ;
		list.total = atoi(data.c_str()) ;
    		   		
		GetString(line, 6, data) ;
		FixNum(data) ;
		list.hp = atoi(data.c_str()) ;
		
		GetString(line, 7, data) ;
		FixNum(data) ;
		list.atk = atoi(data.c_str()) ;
		
		GetString(line, 8, data) ;
		FixNum(data) ;
		list.def = atoi(data.c_str()) ;
			
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
		
		File() {
			
			ID = "\0" ;	
			
		} // constructor
		
		string FileName( string str ) { 
		// 回傳完整的 file name
		
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// 存取 file 裡的 data
		
			pokemon data ;
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
				getline(in, title) ;  // 讀標頭

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
		
		void DeleteFile( pokemon data ) {
			// 刪除特定的資料 
			
			for ( int i = 0 ; i < list.size() ; i++ ) {
				
				if ( data.No == list.at(i).No ) {
					cout << title << endl ;
					cout << list.at(i).line << endl ;
					list.erase(list.begin() + i) ;
					return ;
				} // if
				
			} // for
			
		} // DeleteFile
		
		void clearFile() {
			// 把全部的資料刪除 
			
			list.clear() ;
			
		} // clearFile
		
		int getMAX() {
			// 找出資料裡最大的HP 
			
			int HP_MAX = 0 ;
			
			for ( int i = 0 ; i < list.size() ; i++ ) {
				
				if ( HP_MAX < list.at(i).hp ) HP_MAX = list.at(i).hp ;
				
			} // for
			
			return HP_MAX ;
			
		} // findMAX
		
		vector<pokemon> GetList() {
			// 取得資料 
			
			return list ;
			
		} // GetList()
		
		void PrintAll() {  // 印出所有pokemon的資料 
			
			cout << endl << right << setw(11) << "#" ;
			cout << "    " ;
			cout << left << setw(25) << "Name" ;
			cout << left << setw(15) << "Type 1" ;
			cout << left << setw(10) << "HP" ;
			cout << left << setw(10) << "Attack" ;
			cout << left << setw(10) << "Defense" << endl ; 
			
			for ( int i = 0 ; i < list.size() ; i++ ) {
				
				cout << left << setw(2) << "[" ; 
				cout << right << setw(3) << i + 1 ;
				cout << setw(2) << "]" ;
				cout << "   " ;
				cout << left << setw(5) << list.at(i).No ;
				cout << left << setw(25) << list.at(i).name ;
				cout << left << setw(15) << list.at(i).type1 ;
				cout << left << setw(10) << list.at(i).hp ;
				cout << left << setw(10) << list.at(i).atk ;
				cout << left << setw(10) << list.at(i).def << endl ;
				
			} // for
			
		} // PrintAll
		
		void show( vector<pokemon> arr ) {  // 印出特定的pokemon 資料 
			
			cout << endl << right << setw(11) << "#" ;
			cout << "    " ;
			cout << left << setw(25) << "Name" ;
			cout << left << setw(15) << "Type 1" ;
			cout << left << setw(10) << "Total" ;
			cout << left << setw(10) << "HP" ;
			cout << left << setw(10) << "Attack" ;
			cout << left << setw(10) << "Defense" << endl ; 
			
			for ( int i = 0 ; i < arr.size() ; i++ ) {
				
				cout << left << setw(2) << "[" ; 
				cout << right << setw(3) << i + 1 ;
				cout << setw(2) << "]" ;
				cout << "   " ;
				cout << left << setw(5) << arr.at(i).No ;
				cout << left << setw(25) << arr.at(i).name ;
				cout << left << setw(15) << arr.at(i).type1 ;
				cout << left << setw(10) << arr.at(i).total ;
				cout << left << setw(10) << arr.at(i).hp ;
				cout << left << setw(10) << arr.at(i).atk ;
				cout << left << setw(10) << arr.at(i).def << endl ;
				
			} // for
			
		} // show
		
		~File() {
			
			list.clear() ;
			ID = "/0" ;
			
		} // destructor
		
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
	
	Node * getMinNode( Node * root ) {
		// 找出樹裡HP最小的node 
		
		Node * tmp = root ;
		
		while ( tmp && tmp->left != NULL )
			tmp = tmp->left ;
			
		return tmp ;
		
	} // getMinNode
	
	void storeNodes( Node * root, vector<Node*> & nodes ) {
		
		if ( root == NULL ) return ;
		
		storeNodes(root->left, nodes) ;
		nodes.push_back(root) ;
		storeNodes(root->right, nodes) ;
		
	} // storeNodes
	
	Node * buildUtil( vector<Node*> nodes, int start, int end ) {
		
		if ( start > end ) return NULL ;
		
		int mid = (start + end ) / 2 ;
		Node * root = nodes[mid] ;
		
		root->left = buildUtil(nodes, start, mid-1) ;
		root->right = buildUtil(nodes, mid+1, end) ;
		
		return root ;
		
	} // buildUtil
	
	void printCurrentLevel( Node * root, int level ) {
		
		if ( root == NULL ) return ;
		
		if ( level == 1 ) {
			cout << " ( " ;
			cout << root->data.at(0).hp << ", " ;
			for ( int i = 0 ; i < root->data.size() ; i++ ) {
				
				cout << root->data.at(i).No ;
				if ( i != root->data.size()-1 ) cout << ", " ;
				
			} // for
			cout << " )" ;
		} // if
		else if ( level > 1 ) {
			
			printCurrentLevel(root->left, level-1) ;
			printCurrentLevel(root->right, level-1) ;
			
		} // else if
		
	} // printCurrentLevel
	
	public :
		
		Node * newNode( Node * root, pokemon data ) {
			// 建立新的node 
			
			root = new Node ;
			root->data.push_back(data) ;
			root->left = root->right = NULL ;
			return root ;
			
		} // newNode
		
		Node * build( Node * root, pokemon data ) {
			// 建立樹 
			
			if ( root == NULL ) {  // base case
				
				root = newNode(root, data) ;	
				
			} // if
			else if ( data.hp < root->data.at(0).hp ) {  // 若data裡的hp小於樹目前位置的hp 
				
				root->left = build( root->left, data ) ; // 往左邊放 
				
			} // else if
			else if ( data.hp > root->data.at(0).hp ) {  // 若data裡的hp大於樹目前位置的hp
			
				root->right = build( root->right, data ) ; // 往右邊放
				
			} // else if
			else {  //  若data裡的hp等於樹目前位置的hp
				
				root->data.push_back(data) ; // 放到目前node的位置裡 
				
			} // else
				
			return root ;  // 回傳已經建好的樹 
			
		} // build
		
		Node * buildBalance( Node * root ) {
			
			vector<Node*> nodes ;
			storeNodes(root, nodes) ;

			return buildUtil(nodes, 0, nodes.size()-1) ; 
			
		} // buildBalance
		
		void showHigh( Node * root ) {
			// 印出目前樹的樹高 
			
			int h = treeHigh(root) ;
			
			cout << endl << "HP tree height = " << h << endl ;
			
		} // showHigh
		
		void search( Node * root, vector<pokemon> & list, int value, int & count ) {
			// 尋找最低標準(value)以上的node 
			
			if ( root == NULL ) return ; // base case
			
			if ( value > root->data.at(0).hp ) { // 若最低標準大於目前節點位置的hp 
				count++ ; // 走訪節點+1 
				search(root->right, list, value, count) ; // 往右邊尋找，以免走到不必要的節點 
			} // if
			else if ( value <= root->data.at(0).hp ) { // 若最低標準小於等於目前節點位置的hp 
				count ++ ; // 走訪節點+1 
				search(root->right, list, value, count) ; // 往右邊尋找 
				
				// 把需要的節點放入vector裡面 
				for ( int i = 0 ; i < root->data.size() ; i++ )
					list.push_back(root->data.at(i)) ;  
				
				if ( value < root->data.at(0).hp ) // 若最低標準小於目前節點位置的hp
					search(root->left, list, value, count) ; // 往右邊尋找
					// 因為進入迴圈後會進入else if裡面，所以不用再加走訪節點數量 
	
			} // else if
			
		} // search
			
		Node * deleteNode( Node * root, int num, pokemon & del ) {  //刪除節點 

			Node * temp = NULL ;
			Node * cur = NULL ;
			
			if( root == NULL ) {
				return root;
			}
			
			if( num > root->data.at(0).hp ) {   //往右邊走 
				root -> right = deleteNode(root->right, num, del) ;
			}
			else if( num < root->data.at(0).hp ) {  //往左邊走  
				root -> left = deleteNode(root->left, num, del) ;
			}
			else {
				if( root -> left == NULL  ){	//左邊空 
					if( root -> data.size() == 1 ){ //是否只有一個 
						temp = root -> right ;
						swap(del, root->data.at(0)) ; //存del並刪掉 
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //刪vector編號最大的 
						swap(del, root->data.at(0)) ;  
						root->data.erase(root->data.begin()) ;
						return root ;
					}
				}
				else if( root -> right == NULL  ) { //右邊空 
					if( root -> data.size() == 1 ){ //是否只有一個 
						temp = root -> left ;
						swap(del, root->data.at(0)) ; //存del並刪掉  
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //刪vector編號最大的 
						swap(del, root->data.at(0)) ;
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
					root -> right = deleteNode(root->right, temp->data.at(0).hp, del) ;
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
		
		int findMAX( Node * root ) {
			// 在樹裡找出最大值 
	
			if( root == NULL ) return 0 ;   // base case

    		int max = root->data.at(0).hp ; // 先把第一筆資料放入 
    		
    		int mleft = findMAX(root->left) ; // 從樹的左側找最大值 
    		int mright = findMAX(root->right) ; // 從樹的右側找最大值 
    
    		if ( mleft > max ) max = mleft ; // 比較大小 
        
    		if ( mright > max ) max = mright ; // 比較大小 
        
    		return max ; // 回傳最大值 
    
		} // findMAX
		
		void printLevelOrder( Node * root ) {
			
			int h = treeHigh(root) ;
			
			cout << "HP tree :" << endl ;
			for ( int i = 1 ; i <= h ; i++ ) {
				cout << "<level " << i << ">" ;
				printCurrentLevel(root, i) ;
				cout << endl ;
			} // for
			
		} // printLevelOrder
		
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
	
	vector<pokemon> list ; // 存放讀取file的資料 
	
	if ( root != NULL ) { // 若樹已經被建造，打掉
			tree.clearFile() ;
			root = tree.deleteAll(root) ;
			root = NULL ;
	    } // if
	
	if ( tree.ReadFile("input") ) { // 若有讀到資料，進入 
	 
		tree.PrintAll() ; // 印出讀到的所有資料 
		
		list = tree.GetList() ; // 取出讀到的資料 
		
		for ( int i = 0 ; i < list.size() ; i++ )
			root = tree.build(root, list.at(i)) ; // 開始建立樹 

		tree.showHigh(root) ; // 印出樹高 
		
	} // if
	
	return root ; // 回傳樹 
	
} // mission1

void mission2( Node * root, BST tree ) {
	// 任務二 
	
	if ( root == NULL ) { // 若樹還沒被建立，要先執行任務一 
		
		cout << endl << "----- Execute Mission 1 first! -----" << endl ;
		return ;
		
	} // if
	
	string num = "0" ; // 讀取最低標準 
	int n = 0 ; // int of num 
	
	cout << "Threshold ( a positive integer ) : " ;
	cin >> num ;
	
	do {
		
		if ( !isDigit(num) ) { // 若讀取的資料不是數字 
			
			cout << endl << "### It is NOT positive integer. ###" << endl ;
			cout << "Try again : " ;
			cin >> num ;
			
		} // if
		else { // 若是數字 
			
			n = atoi(num.c_str()) ; // 轉成數字 
			
			if ( !(0 < n && n <= tree.getMAX()) ) { // 最低標準的範圍為 1~MAX 
				
				cout << endl << "### It is NOT in [1, " << tree.getMAX() << "]. ###" << endl ;
				cout << "Try again : " ;
				cin >> num ;
				
			} // if
			
		} // else
		
	} while ( !(1 <= n && n <= tree.getMAX()) ) ;
	
	vector<pokemon> find ; // 存放最低標準以上的資料 
	int count = 0 ; // 走訪節點數目 
	
	tree.search(root, find, n, count) ; // 尋找node 
	
	tree.show(find) ; // 印出找到的資料 
	
	cout << "Number of visits nodes = " << count << endl ; // 印出走訪節點的數目 

} // mission2

Node * mission3( Node * root, BST & tree ) {
	
	if ( root == NULL ) { // 若樹還沒被建立，要先執行任務一 
		
		cout << endl << "----- Execute Mission 1 first! -----" << endl ;
		return NULL ;
		
	} // if
	
	pokemon delData ;  // 存被刪除的資料 
	int num = tree.findMAX(root) ;	// 存放目前最大值 
	
	root = tree.deleteNode(root, num, delData) ; // 刪除MAX HP node	
	
	tree.DeleteFile(delData) ;  // 刪除list裡的資料
	tree.showHigh(root) ;       // 印出目前樹高 
	
	return root ; // 回傳更改完的樹 
	
} // mission3

Node * mission4( Node * root, BST & tree ) {
	
	if ( root == NULL ) { // 若樹還沒被建立，要先執行任務一 
		
		cout << endl << "----- Execute Mission 1 first! -----" << endl ;
		return NULL ;
		
	} // if
	
	int count = 1 ;
	
	root = tree.buildBalance(root) ;
	
	tree.printLevelOrder(root) ;
	
	return root ;
	
} // mission4

int main() {
	
	string command = "/0" ; // 讀取指令 
	int cd = -1 ;           // int的指令
	Node * root = NULL ;    // 樹 
	BST tree ;              // class of BST 
	
	do { 
	
		cout << endl << "*** Binary Search Tree on Pokemon ***" ;
		cout << endl << "* 0. QUIT                           *" ;
		cout << endl << "* 1. Read one file to build BST     *" ;
		cout << endl << "* 2. Threshold search on one column *" ;
		cout << endl << "* 3. Delete the max on one column   *" ;
		cout << endl << "* 4. Convert into balanced BST      *" ;
		cout << endl << "*************************************" ;
		cout << endl << "Input a command(0, 1, 2, 3, 4) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // 是否為int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) root = mission1(root, tree) ; // 進入任務一 
		else if ( cd == 2 ) mission2(root, tree) ; // 進入任務二 
		else if ( cd == 3 ) root = mission3(root, tree) ; // 進入任務三
		else if ( cd == 4 ) root = mission4(root, tree) ;
		else cout << endl << "Command is NOT exist !!" << endl ; // 無此指令 
		
	} while ( cd != 0 ) ;
	
	root = tree.deleteAll(root) ;  // 刪除資料 
	system("pause") ;
	return 0 ;
	
} // main
