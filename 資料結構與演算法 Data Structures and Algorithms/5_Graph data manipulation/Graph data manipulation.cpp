//DS2ex4_27_11027222_11027206
 
#include <bits/stdc++.h>

using namespace std ;
#define COLUMNS 6
#define MAX_LEN 10
#define BIG_INT 255

struct InputFile { // store bin data 
	char sendID[MAX_LEN] ; // sender
	char getID[MAX_LEN] ;  // recipient
	float weight ;
}; // InputFile

struct Getlist {  //�ΨӦsrecipient��struct 
	char getID[MAX_LEN] ;  
	float weight ;
	Getlist *next = NULL ; 
};

struct Node { // �ΨӦssender �b adjacency�� 
	char sendID[MAX_LEN] ;
	Getlist *ptr = NULL ;  // �s��esender���o�e���H 
	Getlist *last = NULL ; // always point at last data   
	
	static bool compareID(Node p1, Node p2) {
		if ( strcmp( p1.sendID, p2 .sendID ) > 0 ) {
			return false ;
		}
		else {
			return true ;
		}
	} 
};

class File {
	string filenum ;
	int n ;
	
public :
	vector<InputFile> data ; // store bin data  
	
	int GetInputsize() {
		return n ;
	}

	string fileN() {
		return filenum;
	}
	
	
	int readBinary(string & a) {
		string fileName;
		fstream binFile;
		InputFile oneSt;
		int stNo = 0;
		int n = 0 ;
		while(1) {
			cout << "Input a file number ([0] Quit): ";
			cin >> fileName;
			a = fileName ;
			if(fileName == "0") return 0;
			fileName = "pairs" + fileName + ".bin";
			binFile.open(fileName.c_str(), fstream::in|fstream::binary) ;
			if( binFile.is_open() ) break;
			
		}
		if( binFile.is_open() ) {
			
			binFile.seekg(0,binFile.end );
	        stNo = binFile.tellg() / sizeof(oneSt) ;
	        binFile.seekg(0,binFile.beg);
	        data.clear() ;
	        data.resize(stNo) ;
	        
	        for(int i = 0 ; i < stNo ; i++)  {
	        	binFile.read((char*)&oneSt, sizeof(oneSt)) ;
	            strcpy(data[i].sendID, oneSt.sendID ) ;
	            strcpy(data[i].getID, oneSt.getID ) ;
	            data[i].weight = oneSt.weight ;
	            if ( i != 0 ) {
	            	if ( strcmp(data[i-1].sendID,data[i].sendID) != 0 ) {
	            		n++ ;
					}
				}
	            
			}
			
		}
		
		binFile.close() ;
		return ++n ;
	}	

	void clearFile() {
	// ���������ƧR�� 
			
		data.clear() ;
	} // clearFile
	
};

class AdjacencyLists {
	
	int checkSend( char temp[MAX_LEN] ) { 
	/*
	�ˬdsender�O�_���badjacency list�� 
	������return�L��index 
	*/  
		for ( int i = 0 ; i < adjlist.size(); i++) {
			if ( strcmp(adjlist[i].sendID, temp) == 0 ) {
				return i ;  
			}
		}
		return -1 ;
	}
	
	
	int checkGet( char temp[MAX_LEN] ) {
	/*
	�ˬdrecipient�O�_���badjacency list�� 
	������return�L��index 
	*/  
		for ( int i = 0 ; i < check.size(); i++) {
			if ( strcmp(check[i].sendID, temp) == 0 ) {
				return i ;
			}
		}
		return -1 ;
	}
	
public:
	vector<Node> adjlist ; 
	int numofid ;
	int numofnode ;
	vector<Node> check ; //�sgetID 
		
	void build( vector<InputFile> data, int n ) {
		/*
		���P�_sendID�O�_�badjacency list�̡A����쪺�ܦ^��index�A�N�b�L��last�s�W�@��getID
		�S���N��iadjacency�÷s�WGetlist��linked list�srecipient 
		*/	
		numofid = n ;
		numofnode = data.size() ;
		for ( int i = 0 ; i< data.size() ; i++ ) {
			int index = checkSend(data[i].sendID) ;
			if( index == -1 ) {
				Node temp ;
				strcpy(temp.sendID, data[i].sendID) ;
				temp.ptr = NULL ;
				adjlist.push_back(temp) ;
				//================================
				int k = adjlist.size()-1 ;
				adjlist[k].ptr = new Getlist ;
				strcpy(adjlist[k].ptr -> getID , data[i].getID) ;
				adjlist[k].ptr -> weight = data[i].weight ;
				adjlist[k].last = adjlist[k].ptr ;
			}	
			else {
				Getlist* temp = new Getlist ;
				strcpy(temp->getID, data[i].getID) ;
				temp -> weight = data[i].weight ;
				temp -> next = NULL ;
				adjlist[index].last -> next = temp ; 
				adjlist[index].last = adjlist[index].last -> next ;
			}
			
			if ( checkGet(data[i].getID) == -1 ) {
				//�T�O�C��getID���s��B�����ơA�Ȧ����T�����o�T�����H 
				Node temp ;
				strcpy(temp.sendID, data[i].getID) ;
				temp.ptr = NULL ;
				check.push_back(temp) ;
			}
		}
	}
	
	void Writefile( string filename ) {
		
		string file = "pairs" + filename + ".adj" ;
		ofstream out(file.c_str()) ;
		out << "<<< There are " << numofid << " IDs in total. >>>" << endl ;
		for ( int i = 0 ; i < adjlist.size(); i++ ) {
			out << "[" << setw(3) << i+1 << "] "  << adjlist[i].sendID << ": " << endl ;
			Getlist* temp = adjlist[i].ptr ;
			int num = 0 ;
			int count = 0 ;
			while ( temp != NULL ) {
				out << "\t(" << setw(2) << num+1 << ") " << temp -> getID << "," << setw(6) << temp -> weight ;
				temp = temp -> next ;
				num++ ;
				count++ ;
				if ( count == 10 ) {
					count = 0 ;
					out << endl  ;
				}
			}
			out << endl ;
		}
		printf("\n<<< There are %d IDs in total. >>>\n",numofid) ;
		printf("\n<<< There are %d nodes in total. >>>\n",numofnode) ;
		out << "<<< There are " << numofnode << " nodes in total. >>>" << endl ;
		out.close() ;
	}
	
	void sortmain() {
		
		for ( int i = 0 ; i < check.size() ; i++ ) { //�ˬdcheck����getID�����badjacency list�̭� 
			bool same = false ;
			for ( int j = 0 ; j < adjlist.size(); j++ ) {
				if ( strcmp(check[i].sendID, adjlist[j].sendID) == 0 ) {
					same = true ;
				}
			}
			
			if ( same == false ) {
				adjlist.push_back(check[i]) ;
			}
		}
		
		sort(adjlist.begin(), adjlist.end(), Node :: compareID) ; //sort adjacenct list
		
		for ( int i = 0 ; i < adjlist.size(); i++ ) { // sort eack linked list in adjlist 
			Getlist *head = adjlist[i].ptr ;
			Getlist *tail = NULL ;
			if ( head == NULL ) {
				return ;
			}
			while ( head != NULL ) {
				tail = head -> next ; 
				while ( tail != NULL ) {
					if ( strcmp(head->getID, tail->getID) > 0 ) {
						swap(head -> getID, tail->getID) ;
						swap(head->weight, tail->weight) ;
					}
					tail = tail -> next ;
				}
				head = head -> next ;
			}
		}
	}

};

struct Node_bfs{
	vector<string> bfs ;
	string ID ;
};

class AL_BFS {
	vector<Node_bfs> bfsAns ;
	
public :
	vector<Node> list ;
	
	void bfs() {
		set<string> road ;//�sbfs�����| 
		int last = 0 ;
		int listsize = list.size() ;
		
		for ( int i = 0 ; i < listsize; i++ ) {
			queue <string> q ;
			road.clear() ;
			string temp = list[i].sendID ;
			//======start BFS===========================
			q.push(temp) ;
			road.insert(temp) ;
			while(q.empty()==false) {
				string a = q.front() ; //���queue�̫e������ 
				q.pop() ;
				
				for ( int j = 0 ; j < listsize; j++) {
					string findstr = list[j].sendID ;
					if ( a == findstr ) {
						Getlist *p = list[j].ptr ;
						
						while(p!=NULL) {
							string in = p -> getID ;
							
							if( road.count(in) == false ) { //��e���ȨS�����L�A�s�i�h�å�iqueue  
								q.push(in) ;
								road.insert(in) ;
							}	
							p = p -> next ;
						}
						break ;
					}
					
					if( road.size() == list.size() ) {
						break ;
					}
				}	
			}
			
			Node_bfs tempnode ;
			tempnode.ID = list[i].sendID ; //�ssendID 
			set<string>::iterator iter;
			road.erase(list[i].sendID) ; //�R���ۤv 
			
  			for (iter = road.begin(); iter != road.end(); iter++) { //��set���F��s�ivector 
    			tempnode.bfs.push_back(*iter) ;
  			}
  			
  			if ( bfsAns.size() == 0 || last >= tempnode.bfs.size() ) { //�Ŷ���0�Τj�p<=�̫�A����push 
  				bfsAns.push_back(tempnode) ;
  				last = tempnode.bfs.size() ;
			}
  			
  			for ( int i = 0 ; i < bfsAns.size(); i++ ) {  //���ө�i�h����minsert�i�h 
  				if( tempnode.bfs.size() > bfsAns[i].bfs.size() ) {
  					bfsAns.insert(bfsAns.begin()+i,tempnode) ;
  					last = bfsAns[bfsAns.size()-1].bfs.size() ;
  					break ;
				}
			}
			
		}
	}
	
	
	void Writefile( string filename ) {
		
		string file = "pairs" + filename + ".cnt" ;
		ofstream out(file.c_str()) ;
		//adjlist.sort() ;
		out << "<<< There are " << bfsAns.size() << " IDs in total. >>>" << endl ;
		for ( int i = 0 ; i < bfsAns.size(); i++ ) {
			out << "[" << setw(3) << i+1 << "] "  << bfsAns[i].ID << "(" << bfsAns[i].bfs.size() << "): " << endl ;
			int count = 0 ;
			int num = 0 ;
			for( int j = 0 ; j < bfsAns[i].bfs.size() ; j++ ) {
				out << "\t(" << setw(2) << num+1 << ") " << bfsAns[i].bfs[j] ;
				num++ ;
				count++ ;
				if ( count == 10 ) {
					count = 0 ;
					out << endl  ;
				}
			} 

			out << endl ;
			
		}
		printf("\n<<< There are %d IDs in total. >>>\n",bfsAns.size()) ;
		out.close() ;

	}
};

struct Node_dfs{
	vector<string> dfs ;
	string ID ;
};

class Influence {
	vector<Node_dfs> dfsAns ;
public:
	vector<Node> list ;
	
	void dfs( int cd ) {
		double inf = 0.0 ;
		if ( cd == 3 ) {
			do {
				cout << "\nInput a real number in [0,1]:" ;
				cin >> inf ;
				if (!( 0 <= inf && inf <= 1 ))	{
					cout << "\n### It is NOT in [0,1] ###" << endl ;
				}
			}while( !( 0 <= inf && inf <= 1 ) ) ;

		}
		
		set<string> road ;//�sbfs�����| 
		
		int last = 0 ;
		int listsize = list.size() ;
		
		for ( int i = 0 ; i < listsize; i++ ) {
			stack <string> s ;
			road.clear() ;
			string temp = list[i].sendID ;
			//======start DFS===========================
			s.push(temp) ;
			road.insert(temp) ;
			while(s.empty()==false) {
				string a = s.top() ; //���stack top
				s.pop() ;
				
				for ( int j = 0 ; j < listsize; j++) {
					string findstr = list[j].sendID ;
					if ( a == findstr ) {
						Getlist *p = list[j].ptr ;
						
						while(p!=NULL) {
							string in = p -> getID ;
							if ( cd == 4 ) {
								inf = (double)rand() / RAND_MAX ;
							}
							if( road.count(in) == false && p->weight >= inf ) { //��e���ȨS�����L�A�s�i�h�å�istack && p->weight >= inf
								s.push(in) ;
								road.insert(in) ;
							}	
							p = p -> next ;
						}
						break ;
					}
				}	
			}
			
			Node_dfs tempnode ;
			tempnode.ID = list[i].sendID ; //�ssendID 
			set<string>::iterator iter;
			road.erase(list[i].sendID) ; //�R���ۤv 
			
  			for (iter = road.begin(); iter != road.end(); iter++) { //��set���F��s�ivector 
    			tempnode.dfs.push_back(*iter) ;
  			}
  			
  			
  			if ( dfsAns.size() == 0 || last >= tempnode.dfs.size() ) { //�Ŷ���0�Τj�p<=�̫�A����push 
  				dfsAns.push_back(tempnode) ;
  				last = tempnode.dfs.size() ;
			}
  			
  			for ( int i = 0 ; i < dfsAns.size(); i++ ) {  //���ө�i�h����minsert�i�h 
  				if( tempnode.dfs.size() > dfsAns[i].dfs.size() ) {
  					dfsAns.insert(dfsAns.begin()+i,tempnode) ;
  					last = dfsAns[dfsAns.size()-1].dfs.size() ;
  					break ;
				}
			}
			
		}
	
	}
	
	void Writefile_dfs( string filename, int cd ) {
		string file ;
		for ( int i = 0 ; i < dfsAns.size(); i++ ) {
			if ( dfsAns[i].dfs.size() <= 0 ) {
				dfsAns.erase(dfsAns.begin()+i) ;
				i-- ;
			}
		}
		if ( cd == 3 ) {
			file = "pairs" + filename + ".inf" ;
		}
		else if ( cd == 4 ) {
			file = "pairs" + filename + ".pro" ;
		}
		
		ofstream out(file.c_str()) ;
		//adjlist.sort() ;
		out << "<<< There are " << dfsAns.size() << " IDs in total. >>>" << endl ;
		for ( int i = 0 ; i < dfsAns.size(); i++ ) {
			out << "[" << setw(3) << i+1 << "] "  << dfsAns[i].ID << "(" << dfsAns[i].dfs.size() << "): " << endl ;
			int count = 0 ;
			int num = 0 ;
			for( int j = 0 ; j < dfsAns[i].dfs.size() ; j++ ) {
				out << "\t(" << setw(2) << num+1 << ") " << dfsAns[i].dfs[j] ;
				num++ ;
				count++ ;
				if ( count == 10 ) {
					count = 0 ;
					out << endl  ;
				}
			} 

			out << endl ;
			
		}
		printf("\n<<< There are %d IDs in total. >>>\n",dfsAns.size()) ;
		out.close() ;

	}
	
	
};

vector<Node> mission1( vector<InputFile> data, int n, string filenum ) {
	AdjacencyLists graph ;	
	graph.build(data, n) ;
	graph.sortmain() ;
	graph.Writefile(filenum) ;
	
	return graph.adjlist ;
}

void mission2( vector<Node> temp, string filenum ) {
	AL_BFS op ;
	op.list = temp ;
	op.bfs() ;
	op.Writefile(filenum) ;
}

void mission3_4( vector<Node> temp, string filenum, int cd ) {
	Influence op ;
	op.list = temp ;
	op.dfs(cd) ;
	op.Writefile_dfs(filenum,cd) ;
}



bool isDigit( string str ) {
// �P�_�O�_���Ʀr 
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

int main() {
	
	string command = "\0" ; // Ū�����O 
	int cd = -1 ;           // int�����O
	bool check = false;
	File input ;
	string name = "\0";		//�ɮצW��
	vector<Node> tempa ;
	string filenum ;
	do { 
	
		cout << endl << "**** Graph data manipulation *****" ;
		cout << endl << "* 0. QUIT                        *" ;
		cout << endl << "* 1. Build adjacency lists       *" ;
		cout << endl << "* 2. Compute connection counts   *" ;
		cout << endl << "* 3. Estimate influence values   *" ;
		cout << endl << "* 4. Probability-based influence *" ;
		cout << endl << "*********************************" ;
		cout << endl << "Input a command(0, 1, 2, 3, 4) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			input.clearFile();	
			
			int n = input.readBinary(filenum) ;			//�ন�G�i��
			tempa = mission1(input.data, n, filenum) ;
			check = true ;
			
		}
		else if ( cd == 2 ){
			if( check == true ){
				mission2( tempa, filenum ) ; // �i�J���ȤG 
			}
			else{
				cout << "### Choose 1 first. ###" << endl;
			}
		}
		else if ( cd == 3 ) {
			if( check == true ){
				mission3_4( tempa, filenum, 3 ) ; // �i�J���ȤG 
			}
			else{
				cout << "### Choose 1 first. ###" << endl;
			}
		}
		else if ( cd == 4 ) {
			if( check == true ){
				mission3_4( tempa, filenum, 4 ) ; // �i�J���ȤG 
			}
			else{
				cout << "### Choose 1 first. ###" << endl;
			}
		}
		else {
			cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		}
	}while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
