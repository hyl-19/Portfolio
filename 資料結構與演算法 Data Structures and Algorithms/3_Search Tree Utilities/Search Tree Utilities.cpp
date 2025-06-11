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
	int num ;          //�Ǹ� 
	string schoolname ; // �ǮզW�� 
	string depname ;	// ��t�W�� 
	string type ;		// ��]�O
	string degree ;		// ���ŧO
	int gradnum ;	// �ǥͼ�
	string line ;   // �s�@���� 
}; // InputFile

class File {
	
	 
	string ID ;               // �s�ɮץN�X
	string title ;            // ���Y 
	
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
	
	void GetLineOfData( string line, InputFile & list ) {
    	// �h�sline�̭�����T 
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
		// �׾ǥͼƼƦr���S��input "XXX"
			
		int n = num.size() ;
		if ( num[0] == '\"' && num[n-1] == '\"' ) {
			num = num.erase(n-1, n) ; // �����᭱�����޸� 
			num = num.erase(0, 1) ;   // �����e�������޸� 
			num = num.erase(1, 1) ;   // �����������r�� 
		} // if
				
	} // FixNum 
	
	public :
		
		vector<InputFile> list ;  // �sŪ�J��data
		
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


bool isDigit( string str ) {
// �P�_�O�_���Ʀr 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

struct schooldata {
	string key ;          //�s�զW 
	vector <int> index ;  //�s�Ǹ� 
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
    tt_Node *ptrtemp = NULL ; 		//�s�������k�䪺���	
    schooldata midtemp ; 		//�s�n���W�᪺node���(��������)	    
    bool spilt ;            	//�ݭn���n������ 
    
  	public:
  		
		bool search( tt_Node * cur, int index, string str ) {     
		//�M�䦳�S���@�˪�data�ä@�B�B�j�M�A�@�˪��ܴNpush_back()���enode�� 
		//�����return true�A�S���Nreturn false 
			
  			if ( cur != NULL ) {
  				
  				if ( cur -> data.size() == 1  ) {  // 2-node
					if( str == cur -> data.at(0).key ) {         //�@�˰�push_back() 
						cur -> data.at(0).index.push_back( index ) ;
						return true ;
					}
					else if ( str < cur -> data.at(0).key ) {    //����pgo left  
						return search( cur -> left, index, str ) ; // ����jgo right 
					}
					else{
  						return search( cur -> right, index, str ) ; 
					}
				}
				else  if ( cur -> data.size() == 2 ) { // 3-node  
					if ( str == cur -> data.at(0).key ) {         //�@�˰�push_back()  
						cur -> data.at(0).index.push_back( index ) ;
						return true ;	
					}
					else if ( str == cur -> data.at(1).key ) {     //�@�˰�push_back()  
						cur -> data.at(1).index.push_back( index ) ;
						return true ;
					}
					else if ( str < cur -> data.at(0).key ) {     //����pgo left 
						return search( cur -> left, index, str ) ;
					}
					else if ( str < cur-> data.at(1).key ) {      // ���� go mid 
						return search( cur -> mid, index, str ) ;
					}
					else {                                       // ����j go right 
						return search( cur -> right, index, str ) ;
					}
				}
			}
			
			return false ;
			
		}
		
		bool checkleaf( tt_Node *cur ) { 
		//�P�_�O���O���l�`�I 
			if ( cur -> left == NULL && cur -> mid == NULL && cur -> right == NULL ) {
				return true ;
			}
			else {
				return false ;
			}
		} 
		
		void spiltreset() { 
		//���]��������|�Ψ쪺data 
			midtemp.key = "\n" ;
			midtemp.index.clear() ;
			ptrtemp = NULL ;
			spilt = false ;
		}
		
		void spiltnode( tt_Node *&cur, int index, string str, bool isroot ) { 
			/*
			��ptrtemp�إ�new node�A�̭���temp�sindex&&str�A�A��sort�h���Ƨ�
			��̤p����bcur�A�����n�����W�h���smidtemp�Aptrtemp�s�̤j�� 
			*/
			if ( isroot == true ) {   
			/*
			�p�G�Ӹ`�I�Oroot�A���Ф@�ӫ���temp�smidtemp(�������ɤ�������)
			����Ocur(�s�p���`�I)�A�k��Optrtemp(�j���`�I)�A �A��cur(root)��s��temp 
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
			��n��������Ʀs���node�̡Anode��vector�j�p == 3�A�b��L�̰��Ƨ�
			�p���scur�A�������smidtemp�A�j���sptrtemp�A�O�_�n������true 
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
		���b�O�_�bleaf�A�M���j�p�ݭn�����̨�(���j)�A�bleaf�`�I�ݭn���J�`�I���j�p
		1�Npush_back�A2�N�n�����A
		�n�����N���W���]!=leaf�������覡�A�ݤW�h�`�I��ƶq�O1�٬O2�A�M�w�n���n�~�򩹤W�� 
		*/            
  			if ( cur == NULL ) {  //�p�G��e�`�I�ONULL���ܴN�s�W�@�ӷs�`�I 
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
				if ( checkleaf(cur) == true ) {          //�Oleaf�`�I 
					if ( cur -> data.size() == 1 ) {     // ------------size == 1-------------
						schooldata temp ;
						temp.key = str ;
						temp.index.push_back( index ) ;
						spilt = false ;
						if ( str < cur -> data.at(0).key ) { 
						//����p��e��     
							cur -> data.insert(cur -> data.begin(), temp ) ;
						}
						else if ( str > cur -> data.at(0).key ) {  
						//����j��᭱ 
							cur -> data.push_back( temp ) ;
						}
					}
					else if ( cur -> data.size() == 2 ) { //------------size == 2-------------
					//�������`�I�b�ݬO���Oroot 
						spiltnode( cur, index, str, false ) ;
						if ( cur == root && spilt == true ) {
							spiltnode( cur, index, str, true ) ;
						}
					}
				}
				else if ( checkleaf(cur) == false ) {   //--------���Oleaf�`�I------------
					int flag = 0 ;
					if ( cur -> data.size() == 1 ) {  //------------size == 1-------------
						if ( str < cur -> data.at(0).key ) {    //���@�� 
							insertnode( cur -> left, index, str ) ;
							flag = 1 ;
						}
						else if ( str > cur -> data.at(0).key ) { //���k�� 
							insertnode( cur -> right, index, str ) ;          
							flag = 3 ;
						}
						
						if ( spilt == true ) {     
						/*
						�W�h�u���@�Ӫ�����:                                         *		      * * 
						case1:�����|����쥻��������W�Ӫ�ptrtemp     			   / \	   =>	 / | \
						case2:�����|�令�쥻���k��A�k��令�k��W�Ӫ��̤j�I      l	  r	        l  m  r
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
							insertnode( cur -> left, index, str ) ;  //�p�������� 
							flag = 1;
						}
						else if ( cur -> data.at(0).key < str &&  str < cur -> data.at(1).key ) {   //������������ 
							insertnode( cur -> mid, index, str ) ;
							flag = 2;
						}
						else if ( str > cur -> data.at(1).key ) {    // �j�����k�� 
							insertnode( cur -> right, index, str ) ;
							flag = 3;
						}
							
						if ( spilt == true ) {
						/*
						cur�s�̤p�Atemp�s�̤j�Amidtemp�O������W�h����� 
						*/ 
							tt_Node *temp = new tt_Node ;	
							cur -> data.push_back( midtemp ) ;
							sort(cur->data.begin(), cur->data.end(), tt_Node::compareschool) ;
							temp -> data.push_back(cur->data.at(2)) ;
							cur -> data.pop_back() ;
							swap(midtemp, cur -> data.at(1)) ; // midtemp�|�Q��s����node��������� 
							cur -> data.pop_back() ;
							
							if ( flag == 1 ) { 
							/*
							temp���䱵cur�������A�k�䱵cur���k��A����=NULL
							ptrtemp���cur�k�� 
							*/  
								temp -> left = cur -> mid ;
								temp -> mid = NULL ;
								temp -> right = cur -> right ;
								cur -> right = ptrtemp ;
							}
							else if ( flag == 2 ) { 
							/*
							temp���䱵ptrtemp�A�k�䱵cur���k��A����=NULL
							cur�������n���k�� 
							*/  
								temp -> left = ptrtemp ;
								temp -> mid = NULL ;
								temp -> right = cur -> right ;
								cur -> right = cur -> mid ;
							
							}
							else if ( flag == 3 ) {  
							/*
							temp��cur���k��A�k�䱵ptrtemp�A����=NULL
							cur�������n���k��
							*/
								temp -> left = cur -> right ;
								temp -> mid = NULL ;
								temp -> right = ptrtemp ;
								cur -> right = cur -> mid ;
							}
														
							cur -> mid = NULL ;  // ��2-node�������a 
							ptrtemp = temp ;     //��s�k��̤j��� 
							temp = NULL ;	
						}
					}
					if ( cur == root && spilt == true ) {
						//���i��̫�Oroot 
						spiltnode( cur, index, str, true ) ;
					}
				}
			}	
		}
  		
    	void build( vector<InputFile> data ) {
    	/*
    	����search�P�_���S���@�˪�data�A�S���Ainsert�i�h 
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
	int key ;						//�s�ǥͤH�� 
 	vector <int> num ;  //�s�Ǹ�
	Node *left ;
	Node *right ;
};

typedef Node *nodetype; 

class AVL_tree : public File {

	nodetype root ;		//���V���
	vector<int> path;	//�s�W���`�I�q�𸭨��ڪ����|
	int nodess;				//�`�@�`�I��
	

	nodetype rotateLL(nodetype a){		//�@������(LL)
		nodetype b = a->left; 
		a->left = b->right;
		b->right = a;
		return b;
	} // rotate LR

	nodetype rotateRR(nodetype a){		//�@������(RR)
		nodetype b = a->right; 
		a->right = b->left;
		b->left = a;
		return b;
	} // rotate LR

	nodetype rotateLR(nodetype a){		//�G������(LR)
		a->left = rotateRR(a->left);
		a = rotateLL(a);
		return a;
	} // rotate LR

	nodetype rotateRL(nodetype a){		//�G������(RL)
		a->right = rotateLL(a->right);
		a = rotateRR(a);
		return a;
	} // rotate LR

	void addone(int value, int no){		//�s�W
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
			while(temp != NULL){					//���n�s�W����m
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

	int getH(nodetype a) {        //�p���
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

    int BF(nodetype a){				//�p�⥭�ūY��
  		int count = 0;
  		count = getH(a->left) - getH(a->right);
  		return count;
    } // BF

    void printroot(vector<InputFile> list){		//�L�X��کҦ����
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
	void insert(vector<InputFile> list){			//�@���@���s�W
		root = NULL;
		nodess = 0;
		for(int i = 0; i < list.size(); i++){
			addone(list[i].gradnum, list[i].num); //�s�W
			fix(root, NULL);											//�ˬd�O�_���Ũíץ�
		} // for
	} // insert

	void fix(nodetype cur, nodetype parent){	//��s�W�`�I�����|���ˬd�íץ�
		if(path.size() != 0){										//�q�𸭩���ڶ}�l�ˬd
			if(cur == root && cur->key == path[path.size()-1]){
				path.pop_back();								//�ˬd���R�����|
				fix(cur, NULL);									
				check(cur, root);								//�ˬd�B�ץ�
			} // if

			else if(cur->left != NULL && cur->left->key == path[path.size()-1]){
				path.pop_back();								//�ˬd���R�����|
				fix(cur->left, cur);
				check(cur->left, cur->left);		//�ˬd�B�ץ�
			} // else if

			else if(cur->right != NULL && cur->right->key == path[path.size()-1]){
				path.pop_back();								//�ˬd���R�����|
				fix(cur->right, cur);
				check(cur->right, cur->right);	//�ˬd�B�ץ�
			} // else if
		} // if
	} // fix

	void check(nodetype a, nodetype &fix){
		int bf = BF(a), bfchild = 0;
		if(bf == 2){													//���䭫
			bfchild = BF(a->left);
			if(bfchild == 1 || bfchild == 0)		//����p�Ĥ]�O���䭫LL
				fix = rotateLL(a);
			else																//����p�ĥk�䭫LR
				fix = rotateLR(a);
		} // if

		else if(bf == -2){										//�k�䭫
			bfchild = BF(a->right);
			if(bfchild == -1 || bfchild == 0)		//�k��p�Ĥ]�O�k�䭫RR
				fix = rotateRR(a);
			else																//�k��p�ĥ��䭫RL
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
	string command = "/0" ; // Ū�����O 
	int cd = -1 ;           // int�����O
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
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			data.clearFile();
			if ( data.ReadFile("input") ) {
				mission1( data.list ) ; // �i�J���Ȥ@
				check = true ;
			}
		}
		else if ( cd == 2 ){
			if ( check == true ) {
				mission2( data.list, m2 ) ; // �i�J���ȤG 
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
			cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		}
	}while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
