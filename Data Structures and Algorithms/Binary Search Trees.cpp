//11027222�����M
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
	
	string line ;   // �s�@���� 
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
	
	vector<InputFile> list ;  // �s�M��
	string ID ;               // �ɮץN�X
	string title ;            // ���Y 
	
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
	
	void GetLineOfData( string line, InputFile & list ) {
    	// �h�sline�̭�����T 
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
		//  �h�׾ǥͼƪ��Ʀr�A"1,038"
			
		int n = num.size() ;
		if ( num[0] == '\"' && num[n-1] == '\"' ) {
			num = num.erase(n-1, n) ; // �����᭱�����޸� 
			num = num.erase(0, 1) ; // �����e�������޸� 
			num = num.erase(1, 1) ; // �����������r�� 
		} // if
				
	} // FixNum 
	
	public :

		string FileName( string str ) { 
		// �^�ǧ��㪺 file name
		
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// �s�� file �̪� data
		
			InputFile data ;
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
				for ( int i = 0 ; i < 3 ; i++) {
					getline(in, title) ;  // Ū���Y
				}

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
		
		void PrintAll() {  // �L�X�Ҧ�pokemon����� 
			
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
			// ���������ƧR�� 
			
			list.clear() ;
			
		} // clearFile

		vector<InputFile> GetList() {
			// ���o��� 
			
			return list ;
			
		} // GetList()
		
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
	
	public :
		
		Node * newNode( Node * root, InputFile data ) {
			// �إ߷s��node 
			
			root = new Node ;
			root->data.push_back(data) ;
			root->left = root->right = NULL ;
			return root ;
			
		} // newNode
		
		
		Node * build( Node * root, InputFile data ) {
			// �إ߾� 
			
			if ( root == NULL ) {  // base case
			
				root = newNode(root, data) ;	
				
			} // if
			else if ( data.grad < root->data.at(0).grad ) {  // �Ydata�̪�hp�p���ثe��m��hp 
				
				root->left = build( root->left, data ) ; // ������� 
				
			} // else if
			else if ( data.grad >= root->data.at(0).grad ) {  // �Ydata�̪�hp�j���ثe��m��hp
			
				root->right = build( root->right, data ) ; // ���k���
				
			} // else if
			
			return root ;  // �^�Ǥw�g�ئn���� 
			
		} // build

		
		void showHigh( Node * root ) {
			// �L�X�ثe�𪺾� 
			
			int h = treeHigh(root) ;
			
			cout << endl << "tree height {Number of graduates} = " << h << endl ;
			
		} // showHigh

		Node * deleteNode( Node * root, int num ) {  //�R���`�I 

			Node * temp = NULL ;
			Node * cur = NULL ;
			
			if( root == NULL ) {
				return root;
			}
			
			if( num > root->data.at(0).grad ) {   //���k�䨫 
				root -> right = deleteNode(root->right, num) ;
			}
			else if( num < root->data.at(0).grad ) {  //�����䨫  
				root -> left = deleteNode(root->left, num) ;
			}
			else {
				if( root -> left == NULL  ){	//����� 
					if( root -> data.size() == 1 ){ //�O�_�u���@�� 
						temp = root -> right ;
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //�Rvector�s���̤j�� 
						root->data.erase(root->data.begin()) ;
						return root ;
					}
				}
				else if( root -> right == NULL  ) { //�k��� 
					if( root -> data.size() == 1 ){ //�O�_�u���@�� 
						temp = root -> left ;
						delete root ;
						root = NULL ;
						return temp ;
					}
					else {  //�Rvector�s���̤j�� 
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
					root -> right = deleteNode(root->right, temp->data.at(0).grad) ;
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
	
	vector<InputFile> list ; // �s��Ū��file����� 
	
	if ( root != NULL ) { // �Y��w�g�Q�سy�A����
			tree.clearFile() ;
			root = tree.deleteAll(root) ;
			root = NULL ;
	} // if
	
	if ( tree.ReadFile("input") ) { // �Y��Ū���ơA�i�J 
	 
		tree.PrintAll() ; // �L�XŪ�쪺�Ҧ���� 
		
		list = tree.GetList() ; // ���XŪ�쪺��� 
		
		for ( int i = 0 ; i < list.size() ; i++ ) {

			root = tree.build(root, list.at(i)) ; // �}�l�إ߾� 		
		}
		system("pause") ;
		tree.showHigh(root) ; // �L�X�� 
		
	} // if
	
	return root ; // �^�Ǿ� 
	
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
	
	string command = "/0" ; // Ū�����O 
	int cd = -1 ;           // int�����O
	Node * root = NULL ;    // �� 
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
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			root = mission1(root, tree) ; // �i�J���Ȥ@ 
			list = tree.GetList() ;
		}
		else if ( cd == 2 ) mission2(root, tree, list) ; // �i�J���ȤG 
		else cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		
	 	}while ( cd != 0 ) ;
	
	root = tree.deleteAll(root) ;  // �R����� 
	system("pause") ;
	return 0 ;
	
} // main
