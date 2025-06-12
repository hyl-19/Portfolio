// 07�� 11027212 ���ض� 11027222 �����M
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
	
	string line ;   // �s�@���� 
	int No ;        // pokemon�����X 
	string name ;   // pokemon Name 
	string type1 ;  // pokemon type 1
	int total ;     // �`�M 
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
	
	vector<pokemon> list ;  // �s�M��
	string ID ;             // �ɮץN�X
	string title ;          // ���Y 
	
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
	
	void GetLineOfData( string line, pokemon & list ) {
    	// �h�sline�̭�����T 
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
		//  �h�׾ǥͼƪ��Ʀr�A"1,038"
			
		int n = num.size() ;
		if ( num[0] == '\"' && num[n-1] == '\"' ) {
			num = num.erase(n-1, n) ; // �����᭱�����޸� 
			num = num.erase(0, 1) ; // �����e�������޸� 
			num = num.erase(1, 1) ; // �����������r�� 
		} // if
				
	} // FixNum 
	
	public :
		
		File() {
			
			ID = "\0" ;	
			
		} // constructor
		
		string FileName( string str ) { 
		// �^�ǧ��㪺 file name
		
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// �s�� file �̪� data
		
			pokemon data ;
			ifstream in ;
			string file ; // �ɮצW��
				
    		cout << endl << "Input a file number [0: quit] : " ;
    		cin >> ID ; // Ū�J�ɮץN�X 
			
			if ( ID == "0" )
				return false ;

    		file = FileName(name) ; // �ɮק���W�� 
    			
    		in.open(file.c_str(), ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    		if ( !in.is_open() ) { // �䤣�즹�ɮ� 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				getline(in, title) ;  // Ū���Y

				while( getline(in, data.line) ) { // �s���
					GetLineOfData(data.line, data) ;
					list.push_back(data) ;
				} // while
						
			} // else
			
			in.close() ; // ���� 
			
			return true ;
		
		} // ReadFile
		
		void WriteFile( string name ) {
			// �g�ɮ� str ���ɮצW�� 
			
			string file ;
			
			file = FileName(name) ; // �ɮק���W��
			 
			ofstream out(file.c_str()) ; // �إ��ɮ� 
			
			for ( int i = 0 ; i < list.size() ; i++ ) // �g�J��� 
				out << list.at(i).line << endl ;
			
			out.close() ; // ����
			
		} // WriteFile
		
		void DeleteFile( pokemon data ) {
			// �R���S�w����� 
			
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
			// ���������ƧR�� 
			
			list.clear() ;
			
		} // clearFile
		
		int getMAX() {
			// ��X��Ƹ̳̤j��HP 
			
			int HP_MAX = 0 ;
			
			for ( int i = 0 ; i < list.size() ; i++ ) {
				
				if ( HP_MAX < list.at(i).hp ) HP_MAX = list.at(i).hp ;
				
			} // for
			
			return HP_MAX ;
			
		} // findMAX
		
		vector<pokemon> GetList() {
			// ���o��� 
			
			return list ;
			
		} // GetList()
		
		void PrintAll() {  // �L�X�Ҧ�pokemon����� 
			
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
		
		void show( vector<pokemon> arr ) {  // �L�X�S�w��pokemon ��� 
			
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
		// �p��𰪡A�æ^�� 
		
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
		// ��X���HP�̤p��node 
		
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
			// �إ߷s��node 
			
			root = new Node ;
			root->data.push_back(data) ;
			root->left = root->right = NULL ;
			return root ;
			
		} // newNode
		
		Node * build( Node * root, pokemon data ) {
			// �إ߾� 
			
			if ( root == NULL ) {  // base case
				
				root = newNode(root, data) ;	
				
			} // if
			else if ( data.hp < root->data.at(0).hp ) {  // �Ydata�̪�hp�p���ثe��m��hp 
				
				root->left = build( root->left, data ) ; // ������� 
				
			} // else if
			else if ( data.hp > root->data.at(0).hp ) {  // �Ydata�̪�hp�j���ثe��m��hp
			
				root->right = build( root->right, data ) ; // ���k���
				
			} // else if
			else {  //  �Ydata�̪�hp�����ثe��m��hp
				
				root->data.push_back(data) ; // ���ثenode����m�� 
				
			} // else
				
			return root ;  // �^�Ǥw�g�ئn���� 
			
		} // build
		
		Node * buildBalance( Node * root ) {
			
			vector<Node*> nodes ;
			storeNodes(root, nodes) ;

			return buildUtil(nodes, 0, nodes.size()-1) ; 
			
		} // buildBalance
		
		void showHigh( Node * root ) {
			// �L�X�ثe�𪺾� 
			
			int h = treeHigh(root) ;
			
			cout << endl << "HP tree height = " << h << endl ;
			
		} // showHigh
		
		void search( Node * root, vector<pokemon> & list, int value, int & count ) {
			// �M��̧C�з�(value)�H�W��node 
			
			if ( root == NULL ) return ; // base case
			
			if ( value > root->data.at(0).hp ) { // �Y�̧C�зǤj��ثe�`�I��m��hp 
				count++ ; // ���X�`�I+1 
				search(root->right, list, value, count) ; // ���k��M��A�H�K���줣���n���`�I 
			} // if
			else if ( value <= root->data.at(0).hp ) { // �Y�̧C�зǤp�󵥩�ثe�`�I��m��hp 
				count ++ ; // ���X�`�I+1 
				search(root->right, list, value, count) ; // ���k��M�� 
				
				// ��ݭn���`�I��Jvector�̭� 
				for ( int i = 0 ; i < root->data.size() ; i++ )
					list.push_back(root->data.at(i)) ;  
				
				if ( value < root->data.at(0).hp ) // �Y�̧C�зǤp��ثe�`�I��m��hp
					search(root->left, list, value, count) ; // ���k��M��
					// �]���i�J�j���|�i�Jelse if�̭��A�ҥH���ΦA�[���X�`�I�ƶq 
	
			} // else if
			
		} // search
			
		Node * deleteNode( Node * root, int num, pokemon & del ) {  //�R���`�I 

			Node * temp = NULL ;
			Node * cur = NULL ;
			
			if( root == NULL ) {
				return root;
			}
			
			if( num > root->data.at(0).hp ) {   //���k�䨫 
				root -> right = deleteNode(root->right, num, del) ;
			}
			else if( num < root->data.at(0).hp ) {  //�����䨫  
				root -> left = deleteNode(root->left, num, del) ;
			}
			else {
				if( root -> left == NULL  ){	//����� 
					if( root -> data.size() == 1 ){ //�O�_�u���@�� 
						temp = root -> right ;
						swap(del, root->data.at(0)) ; //�sdel�çR�� 
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //�Rvector�s���̤j�� 
						swap(del, root->data.at(0)) ;  
						root->data.erase(root->data.begin()) ;
						return root ;
					}
				}
				else if( root -> right == NULL  ) { //�k��� 
					if( root -> data.size() == 1 ){ //�O�_�u���@�� 
						temp = root -> left ;
						swap(del, root->data.at(0)) ; //�sdel�çR��  
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //�Rvector�s���̤j�� 
						swap(del, root->data.at(0)) ;
						root->data.erase(root->data.begin()) ;
						return root;
					}
				}
				else if ( root-> right != NULL && root -> left != NULL ) {   //���䳣���F��(inorder successor) 
				
					cur = root -> right ;
					while ( cur->left != NULL ) { //��̥��䪺subtree 
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
			// �R���������� 
			
			if ( root != NULL ) {
				
				deleteAll(root->left) ;
				deleteAll(root->right) ;
				delete root ;
				
			} // if
			
			return root ;
			
		} // deleteAll
		
		int findMAX( Node * root ) {
			// �b��̧�X�̤j�� 
	
			if( root == NULL ) return 0 ;   // base case

    		int max = root->data.at(0).hp ; // ����Ĥ@����Ʃ�J 
    		
    		int mleft = findMAX(root->left) ; // �q�𪺥�����̤j�� 
    		int mright = findMAX(root->right) ; // �q�𪺥k����̤j�� 
    
    		if ( mleft > max ) max = mleft ; // ����j�p 
        
    		if ( mright > max ) max = mright ; // ����j�p 
        
    		return max ; // �^�ǳ̤j�� 
    
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
// �P�_�O�_���Ʀr 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

Node * mission1( Node * root, BST & tree ) {
	// ���Ȥ@ 
	
	vector<pokemon> list ; // �s��Ū��file����� 
	
	if ( root != NULL ) { // �Y��w�g�Q�سy�A����
			tree.clearFile() ;
			root = tree.deleteAll(root) ;
			root = NULL ;
	    } // if
	
	if ( tree.ReadFile("input") ) { // �Y��Ū���ơA�i�J 
	 
		tree.PrintAll() ; // �L�XŪ�쪺�Ҧ���� 
		
		list = tree.GetList() ; // ���XŪ�쪺��� 
		
		for ( int i = 0 ; i < list.size() ; i++ )
			root = tree.build(root, list.at(i)) ; // �}�l�إ߾� 

		tree.showHigh(root) ; // �L�X�� 
		
	} // if
	
	return root ; // �^�Ǿ� 
	
} // mission1

void mission2( Node * root, BST tree ) {
	// ���ȤG 
	
	if ( root == NULL ) { // �Y���٨S�Q�إߡA�n��������Ȥ@ 
		
		cout << endl << "----- Execute Mission 1 first! -----" << endl ;
		return ;
		
	} // if
	
	string num = "0" ; // Ū���̧C�з� 
	int n = 0 ; // int of num 
	
	cout << "Threshold ( a positive integer ) : " ;
	cin >> num ;
	
	do {
		
		if ( !isDigit(num) ) { // �YŪ������Ƥ��O�Ʀr 
			
			cout << endl << "### It is NOT positive integer. ###" << endl ;
			cout << "Try again : " ;
			cin >> num ;
			
		} // if
		else { // �Y�O�Ʀr 
			
			n = atoi(num.c_str()) ; // �ন�Ʀr 
			
			if ( !(0 < n && n <= tree.getMAX()) ) { // �̧C�зǪ��d�� 1~MAX 
				
				cout << endl << "### It is NOT in [1, " << tree.getMAX() << "]. ###" << endl ;
				cout << "Try again : " ;
				cin >> num ;
				
			} // if
			
		} // else
		
	} while ( !(1 <= n && n <= tree.getMAX()) ) ;
	
	vector<pokemon> find ; // �s��̧C�зǥH�W����� 
	int count = 0 ; // ���X�`�I�ƥ� 
	
	tree.search(root, find, n, count) ; // �M��node 
	
	tree.show(find) ; // �L�X��쪺��� 
	
	cout << "Number of visits nodes = " << count << endl ; // �L�X���X�`�I���ƥ� 

} // mission2

Node * mission3( Node * root, BST & tree ) {
	
	if ( root == NULL ) { // �Y���٨S�Q�إߡA�n��������Ȥ@ 
		
		cout << endl << "----- Execute Mission 1 first! -----" << endl ;
		return NULL ;
		
	} // if
	
	pokemon delData ;  // �s�Q�R������� 
	int num = tree.findMAX(root) ;	// �s��ثe�̤j�� 
	
	root = tree.deleteNode(root, num, delData) ; // �R��MAX HP node	
	
	tree.DeleteFile(delData) ;  // �R��list�̪����
	tree.showHigh(root) ;       // �L�X�ثe�� 
	
	return root ; // �^�ǧ�粒���� 
	
} // mission3

Node * mission4( Node * root, BST & tree ) {
	
	if ( root == NULL ) { // �Y���٨S�Q�إߡA�n��������Ȥ@ 
		
		cout << endl << "----- Execute Mission 1 first! -----" << endl ;
		return NULL ;
		
	} // if
	
	int count = 1 ;
	
	root = tree.buildBalance(root) ;
	
	tree.printLevelOrder(root) ;
	
	return root ;
	
} // mission4

int main() {
	
	string command = "/0" ; // Ū�����O 
	int cd = -1 ;           // int�����O
	Node * root = NULL ;    // �� 
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
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) root = mission1(root, tree) ; // �i�J���Ȥ@ 
		else if ( cd == 2 ) mission2(root, tree) ; // �i�J���ȤG 
		else if ( cd == 3 ) root = mission3(root, tree) ; // �i�J���ȤT
		else if ( cd == 4 ) root = mission4(root, tree) ;
		else cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		
	} while ( cd != 0 ) ;
	
	root = tree.deleteAll(root) ;  // �R����� 
	system("pause") ;
	return 0 ;
	
} // main
