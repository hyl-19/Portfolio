//DS2ex2_27_11027222_11027206
 
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
	int num ;          //序號 
	string schoolname ; // 學校名稱 
	string depname ;	// 科系名稱 
	string type ;		// 日夜別
	string degree ;		// 等級別
	int gradnum ;	// 學生數
	string line ;   // 存一行資料 
}; // InputFile

class File {
	
	 
	string ID ;               // 存檔案代碼
	string title ;            // 標頭 
	
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
	
	void GetLineOfData( string line, InputFile & list ) {
    	// 去存line裡面的資訊 
    	string data = "/0" ;
		
		GetString(line, 2, list.schoolname) ;
		GetString(line, 4, list.depname) ;
		GetString(line, 5, list.type) ;
		GetString(line, 6, list.degree) ;
	
		GetString(line, 9, data) ;
		FixNum(data) ;
		list.gradnum = atoi(data.c_str()) ;
		
	} // GetLineOfData
		
	void FixNum( string & num ) {
		// 修學生數數字的特殊input "XXX"
			
		int n = num.size() ;
		if ( num[0] == '\"' && num[n-1] == '\"' ) {
			num = num.erase(n-1, n) ; // 消除後面的雙引號 
			num = num.erase(0, 1) ;   // 消除前面的雙引號 
			num = num.erase(1, 1) ;   // 消除中間的逗號 
		} // if
				
	} // FixNum 
	
	public :
		
		vector<InputFile> list ;  // 存讀入的data
		
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


bool isDigit( string str ) {
// 判斷是否為數字 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

struct schooldata {
	string key ;          //存校名 
	vector <int> index ;  //存序號 
};

struct tt_Node {
	vector <schooldata> data ; 
	tt_Node *left ;
	tt_Node *mid ;
	tt_Node *right ;
  
 	static bool compareschool(schooldata p1, schooldata p2) {
		return p1.key < p2 .key ;
	}
};

class two_three_tree : public File {

    tt_Node *root = NULL ;			
    tt_Node *ptrtemp = NULL ; 		//存分裂完右邊的資料	
    schooldata midtemp ; 		//存要往上丟的node資料(中間的值)	    
    bool spilt ;            	//看要不要做分裂 
    
  	public:
  		
		bool search( tt_Node * cur, int index, string str ) {     
		//尋找有沒有一樣的data並一步步搜尋，一樣的話就push_back()到當前node裡 
		//有找到return true，沒有就return false 
			
  			if ( cur != NULL ) {
  				
  				if ( cur -> data.size() == 1  ) {  // 2-node
					if( str == cur -> data.at(0).key ) {         //一樣做push_back() 
						cur -> data.at(0).index.push_back( index ) ;
						return true ;
					}
					else if ( str < cur -> data.at(0).key ) {    //比較小go left  
						return search( cur -> left, index, str ) ; // 比較大go right 
					}
					else{
  						return search( cur -> right, index, str ) ; 
					}
				}
				else  if ( cur -> data.size() == 2 ) { // 3-node  
					if ( str == cur -> data.at(0).key ) {         //一樣做push_back()  
						cur -> data.at(0).index.push_back( index ) ;
						return true ;	
					}
					else if ( str == cur -> data.at(1).key ) {     //一樣做push_back()  
						cur -> data.at(1).index.push_back( index ) ;
						return true ;
					}
					else if ( str < cur -> data.at(0).key ) {     //比較小go left 
						return search( cur -> left, index, str ) ;
					}
					else if ( str < cur-> data.at(1).key ) {      // 中間 go mid 
						return search( cur -> mid, index, str ) ;
					}
					else {                                       // 比較大 go right 
						return search( cur -> right, index, str ) ;
					}
				}
			}
			
			return false ;
			
		}
		
		bool checkleaf( tt_Node *cur ) { 
		//判斷是不是葉子節點 
			if ( cur -> left == NULL && cur -> mid == NULL && cur -> right == NULL ) {
				return true ;
			}
			else {
				return false ;
			}
		} 
		
		void spiltreset() { 
		//重設分裂完後會用到的data 
			midtemp.key = "\n" ;
			midtemp.index.clear() ;
			ptrtemp = NULL ;
			spilt = false ;
		}
		
		void spiltnode( tt_Node *&cur, int index, string str, bool isroot ) { 
			/*
			用ptrtemp建立new node，裡面放temp存index&&str，再用sort去做排序
			把最小的放在cur，中間要分裂上去的存midtemp，ptrtemp存最大的 
			*/
			if ( isroot == true ) {   
			/*
			如果該節點是root，先創一個指標temp存midtemp(剛剛分裂時中間的值)
			左邊是cur(存小的節點)，右邊是ptrtemp(大的節點)， 再把cur(root)更新成temp 
			*/
				tt_Node* temp = new tt_Node ;
				temp -> data.push_back( midtemp ) ;
				temp -> left =  cur ;
				temp -> mid = NULL ;  
				temp -> right = ptrtemp ;    
				cur = temp ;
				temp = NULL ;
				spiltreset() ;
			}
			else if ( isroot == false ) {
			/*
			把要分裂的資料存到該node裡，node的vector大小 == 3，在對他們做排序
			小的存cur，中間的存midtemp，大的存ptrtemp，是否要分裂改true 
			*/
				ptrtemp = new tt_Node ;
				ptrtemp -> left = NULL ;
				ptrtemp -> mid = NULL ;
				ptrtemp -> right = NULL ;
			
				schooldata temp ;
				temp.key = str ;
				temp.index.push_back(index) ;
				cur -> data.push_back(temp) ;
				sort(cur->data.begin(), cur->data.end(), tt_Node :: compareschool) ;
			
				ptrtemp->data.push_back(cur -> data.at(2) ) ;
				cur -> data.pop_back() ;
				swap( midtemp, cur->data.at(1) ) ;
				cur -> data.pop_back() ;
			
				spilt = true ;	
			}
		}
			
  		void insertnode( tt_Node *&cur, int index, string str ) { 
		/*
		先在是否在leaf，然後比大小看要往哪裡走(遞迴)，在leaf節點看要插入節點的大小
		1就push_back，2就要分裂，
		要分裂就往上走跑!=leaf的分裂方式，看上層節點資料量是1還是2，決定要不要繼續往上丟 
		*/            
  			if ( cur == NULL ) {  //如果當前節點是NULL的話就新增一個新節點 
  				cur = new tt_Node ;
  				schooldata temp ;
  				temp.key = str ;
  				temp.index.push_back( index ) ;
  				cur -> data.push_back( temp ) ;
  				cur -> left = NULL ;
  				cur -> mid = NULL ;
  				cur -> right = NULL ;
			}
			else {
				if ( checkleaf(cur) == true ) {          //是leaf節點 
					if ( cur -> data.size() == 1 ) {     // ------------size == 1-------------
						schooldata temp ;
						temp.key = str ;
						temp.index.push_back( index ) ;
						spilt = false ;
						if ( str < cur -> data.at(0).key ) { 
						//比較小丟前面     
							cur -> data.insert(cur -> data.begin(), temp ) ;
						}
						else if ( str > cur -> data.at(0).key ) {  
						//比較大丟後面 
							cur -> data.push_back( temp ) ;
						}
					}
					else if ( cur -> data.size() == 2 ) { //------------size == 2-------------
					//先分裂節點在看是不是root 
						spiltnode( cur, index, str, false ) ;
						if ( cur == root && spilt == true ) {
							spiltnode( cur, index, str, true ) ;
						}
					}
				}
				else if ( checkleaf(cur) == false ) {   //--------不是leaf節點------------
					int flag = 0 ;
					if ( cur -> data.size() == 1 ) {  //------------size == 1-------------
						if ( str < cur -> data.at(0).key ) {    //往作走 
							insertnode( cur -> left, index, str ) ;
							flag = 1 ;
						}
						else if ( str > cur -> data.at(0).key ) { //往右走 
							insertnode( cur -> right, index, str ) ;          
							flag = 3 ;
						}
						
						if ( spilt == true ) {     
						/*
						上層只有一個的分裂:                                         *		      * * 
						case1:中間會指到原本左邊分裂上來的ptrtemp     			   / \	   =>	 / | \
						case2:中間會改成原本的右邊，右邊改成右邊上來的最大點      l	  r	        l  m  r
						*/ 
							if ( flag == 1 ) {   
								cur -> data.insert(cur->data.begin(), midtemp) ;
								cur -> mid = ptrtemp ;                          
								spiltreset() ;	
							}
							else if ( flag == 3 ) {
								cur -> data.push_back( midtemp ) ;
								cur -> mid = cur -> right ;
								cur -> right = ptrtemp ;
								spiltreset() ;
							}
						}
					}
					else if ( cur -> data.size() == 2 ) { //------------size == 2-------------
						int flag = 0 ; 
						if ( str < cur -> data.at(0).key ) {
							insertnode( cur -> left, index, str ) ;  //小的往左走 
							flag = 1;
						}
						else if ( cur -> data.at(0).key < str &&  str < cur -> data.at(1).key ) {   //中間的往中走 
							insertnode( cur -> mid, index, str ) ;
							flag = 2;
						}
						else if ( str > cur -> data.at(1).key ) {    // 大的往右走 
							insertnode( cur -> right, index, str ) ;
							flag = 3;
						}
							
						if ( spilt == true ) {
						/*
						cur存最小，temp存最大，midtemp是中間丟上去的資料 
						*/ 
							tt_Node *temp = new tt_Node ;	
							cur -> data.push_back( midtemp ) ;
							sort(cur->data.begin(), cur->data.end(), tt_Node::compareschool) ;
							temp -> data.push_back(cur->data.at(2)) ;
							cur -> data.pop_back() ;
							swap(midtemp, cur -> data.at(1)) ; // midtemp會被更新成此node中間的資料 
							cur -> data.pop_back() ;
							
							if ( flag == 1 ) { 
							/*
							temp左邊接cur的中間，右邊接cur的右邊，中間=NULL
							ptrtemp丟到cur右邊 
							*/  
								temp -> left = cur -> mid ;
								temp -> mid = NULL ;
								temp -> right = cur -> right ;
								cur -> right = ptrtemp ;
							}
							else if ( flag == 2 ) { 
							/*
							temp左邊接ptrtemp，右邊接cur的右邊，中間=NULL
							cur的中間要改到右邊 
							*/  
								temp -> left = ptrtemp ;
								temp -> mid = NULL ;
								temp -> right = cur -> right ;
								cur -> right = cur -> mid ;
							
							}
							else if ( flag == 3 ) {  
							/*
							temp的cur的右邊，右邊接ptrtemp，中間=NULL
							cur的中間要改到右邊
							*/
								temp -> left = cur -> right ;
								temp -> mid = NULL ;
								temp -> right = ptrtemp ;
								cur -> right = cur -> mid ;
							}
														
							cur -> mid = NULL ;  // 變2-node中間接地 
							ptrtemp = temp ;     //更新右邊最大資料 
							temp = NULL ;	
						}
					}
					if ( cur == root && spilt == true ) {
						//有可能最後是root 
						spiltnode( cur, index, str, true ) ;
					}
				}
			}	
		}
  		
    	void build( vector<InputFile> data ) {
    	/*
    	先用search判斷有沒有一樣的data，沒有再insert進去 
		*/ 
      		for( int i = 0 ; i < data.size() ; i++ ) {
      					 
	    		if( !search( root, data.at(i).num, data.at(i).schoolname ) ) {
	    	    	insertnode( root, data.at(i).num, data.at(i).schoolname );
	    	 	}  
        	} 
        	
        	printdata( data ) ;
      	} 
      	
      	int findheight(tt_Node *root) {
      		if( root == NULL ) return 0 ;
      		else {
      			return findheight( root -> left ) +1 ;	
			} 
		}
		
		int findnodenum( tt_Node * root ) {
			if (root==NULL) {
				return 0 ;
			}
			return 1+findnodenum(root->left)+findnodenum(root->mid)+findnodenum(root->right);
		}
		
		void printdataindex(vector<InputFile> data, int i) {
			cout << data.at(i).schoolname << ", " << data.at(i).depname << ", " ;
			cout << data.at(i).type << ", " << data.at(i).degree << ", " << data.at(i).gradnum << endl ;	
		}

      	void printdata( vector<InputFile> indata ) {
      		cout << "tree height = " << findheight(root) << endl ;
      		int count = 0 ;
      		cout << "Number of nodes =" << findnodenum(root) << endl ;
      		vector<int> tempindex ;
      		for( int i = 0 ; i < root -> data.size() ; i++ ) {
      			for ( int j = 0 ; j < root->data.at(i).index.size() ;j++) {
      				tempindex.push_back(root->data.at(i).index.at(j)) ;	
				}
			}
			sort(tempindex.begin(), tempindex.end());
			for ( int i = 0 ; i < tempindex.size() ; i++ ) {
				cout << count+1 << ":" << setw(2) << "[" << tempindex.at(i) << "] " << setw(4) ;
				printdataindex(indata, tempindex.at(i)-1 ) ;
      			count++ ;
			}		
		}
      
};

struct Node {
	int key ;						//存學生人數 
 	vector <int> num ;  //存序號
	Node *left ;
	Node *right ;
};

typedef Node *nodetype; 

class AVL_tree : public File {

	nodetype root ;		//指向樹根
	vector<int> path;	//新增的節點從樹葉到樹根的路徑
	int nodess;				//總共節點數
	

	nodetype rotateLL(nodetype a){		//一次旋轉(LL)
		nodetype b = a->left; 
		a->left = b->right;
		b->right = a;
		return b;
	} // rotate LR

	nodetype rotateRR(nodetype a){		//一次旋轉(RR)
		nodetype b = a->right; 
		a->right = b->left;
		b->left = a;
		return b;
	} // rotate LR

	nodetype rotateLR(nodetype a){		//二次旋轉(LR)
		a->left = rotateRR(a->left);
		a = rotateLL(a);
		return a;
	} // rotate LR

	nodetype rotateRL(nodetype a){		//二次旋轉(RL)
		a->right = rotateLL(a->right);
		a = rotateRR(a);
		return a;
	} // rotate LR

	void addone(int value, int no){		//新增
		path.clear();
		nodetype temp = root;
		nodetype parent = NULL;

		if(root == NULL){
			root = new Node;
			root->key = value;
			root->num.push_back(no);
			root->left = NULL;
			root->right = NULL;
			nodess++;
		} // if

		else{
			while(temp != NULL){					//找到要新增的位置
				parent = temp;
				if(temp->key > value){
					path.insert(path.begin(), temp->key);
					temp = temp->left;
				} // if

				else if(temp->key < value){
					path.insert(path.begin(), temp->key);
					temp = temp->right;
				} // else if

				else if(temp->key == value){
					path.clear();
					break;
				} // else if
			} // while

			if(parent->key == value){
				parent->num.push_back(no);
			} // if

			else if(parent->key > value){
				parent->left = new Node;
				parent->left->key = value;
				parent->left->num.push_back(no);
				parent->left->left = NULL;
				parent->left->right = NULL;
				nodess++;
			} // else if

			else if(parent->key < value){
				parent->right = new Node;
				parent->right->key = value;
				parent->right->num.push_back(no);
				parent->right->left = NULL;
				parent->right->right = NULL;
				nodess++;
			} // else if
		} // else
	} // add 

	int getH(nodetype a) {        //計算樹高
        vector<nodetype> N;
        int H = 0, len;
        if (a == NULL)
        	return 0;

        N.push_back(a);
        while (N.size() != 0) {
            len = N.size();
            H++;

            while (len > 0) {
                nodetype temp = N[0];
                N.erase(N.begin());
                if (temp->left != NULL)
                    N.push_back(temp->left);

                if (temp->right != NULL)
                    N.push_back(temp->right);
                len--;
            } // while
        } // while

        return H;
    } // calculate the tree height

    int BF(nodetype a){				//計算平衡係數
  		int count = 0;
  		count = getH(a->left) - getH(a->right);
  		return count;
    } // BF

    void printroot(vector<InputFile> list){		//印出樹根所有資料
  	  	for(int i = 0, j = 0; i < list.size(), j < root->num.size(); i++){
  	   		if(list[i].num == root->num[j]){
  				cout << j+1 << ": [" << list[i].num << "] " << list[i].schoolname << ", "
  						<< list[i].depname << ", " << list[i].type << ", " << list[i].degree 
  						<< ", " << list[i].gradnum << endl;
  				j++;
  			} // if
  		} // for
  	} // printroot

public:
	vector<int> num ;
	void insert(vector<InputFile> list){			//一筆一筆新增
		root = NULL;
		nodess = 0;
		for(int i = 0; i < list.size(); i++){
			addone(list[i].gradnum, list[i].num); //新增
			fix(root, NULL);											//檢查是否平衡並修正
		} // for
	} // insert

	void fix(nodetype cur, nodetype parent){	//把新增節點的路徑都檢查並修正
		if(path.size() != 0){										//從樹葉往樹根開始檢查
			if(cur == root && cur->key == path[path.size()-1]){
				path.pop_back();								//檢查完刪掉路徑
				fix(cur, NULL);									
				check(cur, root);								//檢查且修正
			} // if

			else if(cur->left != NULL && cur->left->key == path[path.size()-1]){
				path.pop_back();								//檢查完刪掉路徑
				fix(cur->left, cur);
				check(cur->left, cur->left);		//檢查且修正
			} // else if

			else if(cur->right != NULL && cur->right->key == path[path.size()-1]){
				path.pop_back();								//檢查完刪掉路徑
				fix(cur->right, cur);
				check(cur->right, cur->right);	//檢查且修正
			} // else if
		} // if
	} // fix

	void check(nodetype a, nodetype &fix){
		int bf = BF(a), bfchild = 0;
		if(bf == 2){													//左邊重
			bfchild = BF(a->left);
			if(bfchild == 1 || bfchild == 0)		//左邊小孩也是左邊重LL
				fix = rotateLL(a);
			else																//左邊小孩右邊重LR
				fix = rotateLR(a);
		} // if

		else if(bf == -2){										//右邊重
			bfchild = BF(a->right);
			if(bfchild == -1 || bfchild == 0)		//右邊小孩也是右邊重RR
				fix = rotateRR(a);
			else																//右邊小孩左邊重RL
				fix = rotateRL(a);
		} // else if
	} // check

	void print(vector<InputFile> data){
		cout << "Tree height = " << getH(root) << endl;
		cout << "Number of nodes = " << nodess << endl;
		printroot(data);
	} // print
	
	void reset() {
		root = NULL ;
	}
	
	nodetype getroot(){
		return root ;
	}
	
	void inorder(nodetype temp) {
		if (temp != NULL) {
			inorder(temp->left) ;
			for ( int i = 0 ; i < temp->num.size() ;i++ ) {
				num.push_back(temp->num.at(temp->num.size()-1-i)) ;
			}
			//cout << temp->key << endl ;
			inorder(temp->right );
		}
	}
};

void mission1( vector<InputFile> data ) {
	two_three_tree tree ;
	tree.build( data ) ;
} // mission1

void mission2( vector<InputFile> data, AVL_tree &m2  ) {
	m2.reset() ;
	m2.insert(data);
	m2.print(data);
} // mission2

void mission3( vector<InputFile> data, AVL_tree &m2 ,int pnum ) {
	nodetype temp = NULL ;
	temp =  m2.getroot();
	m2.num.clear() ;
	m2.inorder(temp) ;
	
	reverse(m2.num.begin(), m2.num.end()) ;
	int count = 0 ;
	int last = 0 ;
	for ( int i = 0 ; i < pnum ; i++ ) {
		cout << count+1 << ":" << "[" << m2.num.at(i) << "] " ;
		//cout << data.at(m2.num.at(i)-1).gradnum << endl ;
		cout << data.at(m2.num.at(i)-1).schoolname << ", " << data.at(m2.num.at(i)-1).depname << ", " ;
		cout << data.at(m2.num.at(i)-1).type << ", " << data.at(m2.num.at(i)-1).degree << ", " << data.at(m2.num.at(i)-1).gradnum << endl ;
		last = data.at(m2.num.at(i)-1).gradnum ;
		count ++ ;
	}
	
	int index = pnum ;
	//cout << data.at(m2.num.at(index)-1).gradnum << endl ;
	if (pnum==m2.num.size() )
		return ;
	while(1) {
		if ( data.at(m2.num.at(index)-1).gradnum == last ) {
			cout << count+1 << ":" << "[" << m2.num.at(index) << "] " ;
			//cout << data.at(m2.num.at(i)-1).gradnum << endl ;
			cout << data.at(m2.num.at(index)-1).schoolname << ", " << data.at(m2.num.at(index)-1).depname << ", " ;
			cout << data.at(m2.num.at(index)-1).type << ", " << data.at(m2.num.at(index)-1).degree << ", " << data.at(m2.num.at(index)-1).gradnum << endl ;
			index++ ;
			count++ ;
			if ( count == data.size() ) {
				return ;
			}
		}
		else {
			break ;
		}
	}
	
}

int main() {
	File data ;
	string command = "/0" ; // 讀取指令 
	int cd = -1 ;           // int的指令
	bool check = false ;
	bool check2 = false ;
	AVL_tree m2 ;
	do { 
	
		cout << endl << "***  Search Tree Utilities  ***" ;
		cout << endl << "* 0. QUIT                     *" ;
		cout << endl << "* 1. Build 2-3 tree           *" ;
		cout << endl << "* 2. Build AVL tree           *" ;
		cout << endl << "* 3. Top-K search on AVL tree *" ;
		cout << endl << "*******************************" ;
		cout << endl << "Input a command(0, 1, 2) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // 是否為int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			data.clearFile();
			if ( data.ReadFile("input") ) {
				mission1( data.list ) ; // 進入任務一
				check = true ;
			}
		}
		else if ( cd == 2 ){
			if ( check == true ) {
				mission2( data.list, m2 ) ; // 進入任務二 
			}
			else {
				cout << "### Choose 1 first. ###" << endl ;
			}
			check2 = true ;
		}
		else if ( cd == 3 ) {
			if (check== false) {
				cout << "### Choose 1 first. ###" << endl ;
			}
			else if ( check2 == false ) {
				cout << "### Choose 2 first. ###" << endl ;
			}
			else {
				int num = 0 ;
				cout << "Enter K in [1,"<< data.list.size() <<"]:" ;
				cin >> num ;
				if ( 0 < num && num <= data.list.size() ) {
					mission3( data.list, m2, num ) ;
				}
			}
		}
		else {
			cout << endl << "Command is NOT exist !!" << endl ; // 無此指令 
		}
	}while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
