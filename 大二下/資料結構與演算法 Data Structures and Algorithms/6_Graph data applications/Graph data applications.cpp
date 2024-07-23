//DS2ex5_27_11027222_11027206
 
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

struct Getlist {  //用來存recipient的struct 
	char getID[MAX_LEN] ;  
	float weight ;
	Getlist *next = NULL ; 
};

struct Node { 				//用來存sender 在 adjacency裡  
	char sendID[MAX_LEN] ;
	Getlist *ptr = NULL ;  	// 存當前sender有發送的人 
	Getlist *last = NULL ; 	// always point at last data   
	
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
	float barrier ;
	
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
			cout << "Input a real number in (0,1]:";
			cin >> barrier;
			if ( 0 < barrier && barrier <= 1 ) {
				break ;
			}
			else {
				cout << "### It is NOT in (0,1] ###" << endl ;
			}
		}
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
	            //cout << oneSt.sendID << " " << oneSt.getID << " " << oneSt.weight << endl ;
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
	// 把全部的資料刪除 
			
		data.clear() ;
	} // clearFile
	
	float GetBar() {
		return barrier ;
	}
	
};

class AdjacencyLists {
	
	int checkSend( char temp[MAX_LEN] ) { 
	/*
	檢查sender是否有在adjacency list裡 
	有的話return他的index 
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
	檢查recipient是否有在adjacency list裡 
	有的話return他的index 
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
	vector<Node> check ; //存getID 
		
	
	void build( vector<InputFile> data, int n, float bar ) {
		/*
		先判斷sendID是否在adjacency list裡，有找到的話回傳index，就在他的last新增一個getID
		沒找到就丟進adjacency並新增Getlist的linked list存recipient 
		*/	
		numofid = n ;
		numofnode = data.size() ;
		for ( int i = 0 ; i< data.size() ; i++ ) {
			if (data[i].weight > bar ) {
				continue ;
			}
			//===================================================1
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
			//===================================================2
			swap(data[i].sendID,data[i].getID) ;
			index = checkSend(data[i].sendID) ;
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
			swap(data[i].sendID,data[i].getID) ;
		}
	}
	
	void Writefile( string filename, float bar ) {
		
		stringstream temp;
		temp << bar ;
		string num = temp.str() ;
		string file = "pairs" + filename + "_" + num + ".adj" ;
		ofstream out(file.c_str()) ;
		numofid = adjlist.size() ;
		int node = 0 ;
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
				node++ ;
				if ( count == 10 ) {
					count = 0 ;
					out << endl  ;
				}
			}
			out << endl ;
		}
		
		numofnode = node ;
		printf("\n<<< There are %d IDs in total. >>>\n",numofid) ;
		printf("\n<<< There are %d nodes in total. >>>\n",numofnode) ;
		out << "<<< There are " << numofnode << " nodes in total. >>>" << endl ;
		out.close() ;
		
	}
	
	void sortmain() {
		
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

struct Node_dfs{
	vector<string> dfs ;
};

class AL_DFS {

	int isVisited( string temp ) {
		//找到temp的位置
		for ( int i = 0; i < list.size(); i++) {
			if ( temp == list[i].sendID ) {
				return i;
			}
		}

		return -1;
	}
	
public :
	vector<Node> list ;			//存任務0的資料
	vector<Node_dfs> dfsAns ;	
	
	void dfs() {
		vector<bool> visited(list.size(), false); //存是否走訪過
		set<string> road ; 
		int last = 0 ;
		int listsize = list.size() ;
		
		for ( int i = 0 ; i < listsize; i++ ) {
			stack <string> myStack ;
			road.clear() ;
			string temp = list[i].sendID ;
			//======start DFS===========================
			if ( visited[i] ) {		//拜訪過就換下一個
				continue;
			}

			myStack.push(temp) ;
			road.insert(temp) ;
			visited[i] = true;

			while ( !myStack.empty() ) {
				string stackTop = myStack.top() ; 
				myStack.pop();

				for ( int j = 0; j < listsize; j++ ) {
					if ( stackTop == list[j].sendID ) {
						Getlist *g = list[j].ptr ;

						while ( g != NULL ) {
							string in = g->getID ;
							int loc = isVisited( in );

							if ( !road.count(in) && !visited[loc]) { //當前的值沒有在路徑上且沒走訪過
								myStack.push(in);
								road.insert(in) ;
								visited[loc] = true;
							}	

							g = g->next;
						}

						break;
					}
				}
			}
			
			Node_dfs tempnode ;
			set<string>::iterator iter; 
			
  			for (iter = road.begin(); iter != road.end(); iter++) { //把set的東西存進vector 
    			tempnode.dfs.push_back(*iter) ;
  			}
  			
  			if ( dfsAns.size() == 0 || last > tempnode.dfs.size() ) { //空間為0或大小<=最後，直接push
  				dfsAns.push_back(tempnode) ;
  				last = tempnode.dfs.size() ;
			}
  			
  			for ( int i = 0 ; i < dfsAns.size(); i++ ) {  //找到該放進去的位置insert進去 
  				if( (tempnode.dfs.size() > dfsAns[i].dfs.size()) || (tempnode.dfs.size() == dfsAns[i].dfs.size() && tempnode.dfs[0] > dfsAns[i].dfs[0]) ) {
  					dfsAns.insert(dfsAns.begin()+i,tempnode) ;
  					last = dfsAns[dfsAns.size()-1].dfs.size() ;
  					break ;
				}
			}
		}
	}
	
	void Writefile( string filename, float bar ) {
		
		stringstream temp;
		temp << bar;
		string num = temp.str();
		string file = "pairs" + filename + "_" + num + ".cc" ;
		ofstream out(file.c_str()) ;

		out << "<<< There are " << dfsAns.size() << " connected components in total. >>>" << endl ;
		cout << endl << "<<< There are " << dfsAns.size() << " connected components in total. >>>" << endl ;
		for ( int i = 0 ; i < dfsAns.size(); i++ ) {
			out << "{" << setw(3) << i+1 << "} "  << "Connected Component: size = " << dfsAns[i].dfs.size() << endl ;
			cout << "{" << setw(3) << i+1 << "} "  << "Connected Component: size = " << dfsAns[i].dfs.size() << endl ;
			int count = 0 ;
			int num = 0 ;
			for( int j = 0 ; j < dfsAns[i].dfs.size() ; j++ ) {
				out << "\t(" << setw(3) << num+1 << ") " << dfsAns[i].dfs[j] ;
				num++ ;
				count++ ;
				if ( count == 8 ) {
					count = 0 ;
					out << endl  ;
				}
			} 

			out << endl ;
		}

		out.close() ;
	}
};

struct Node_short {
	string id;
	float weight;
};


class ShortPath {
	vector<Node_short> shortpath;
	
	int isVisited( string temp ) {
		for ( int i = 0; i < list.size(); i++) {
			if ( temp == list[i].sendID ) {
				return i;
			}
		}

		return -1;
	}

	void findConnected( string id ) {
		vector<bool> visited(list.size(), false); 
		set<string> road ;//¦sdfsªº¸ô®| 

		stack <string> myStack ;
		road.clear() ;
		string temp = id ;

		myStack.push(temp) ;
		road.insert(temp) ;
		for (int i = 0; i < list.size(); i++) {
			if (list[i].sendID == id) {
				visited[i] = true;
				break;
			}
		}

		while ( !myStack.empty() ) {
			string stackTop = myStack.top() ; 
			myStack.pop();

			for ( int j = 0; j < list.size(); j++ ) {
				if ( stackTop == list[j].sendID ) {
					Getlist *g = list[j].ptr ;

					while ( g != NULL ) {
						string in = g->getID ;
						int loc = isVisited( in );

						if ( !road.count(in) && loc != -1 && !visited[loc]) {
							myStack.push(in);
							road.insert(in) ;
							visited[loc] = true;
						}	

						g = g->next;
					}

					break;
				}
			}
		}

		set<string>::iterator iter; 
  		for (iter = road.begin(); iter != road.end(); iter++) { 
    		connected.push_back(*iter) ;
  		}
	}

	float findDistance( string start, string end ) {
		//找到start到end的權重並回傳

		for (int i = 0; i < list.size(); i++) {
			if (start == list[i].sendID) {
				Getlist *g = list[i].ptr;
				while ( g != NULL) {
					string str = g->getID;
					if (end == str) {
						return g->weight;
					}

					g = g->next;
				}

				break;
			}
		}

		return -1;
	}

	int findmin(set<string> road, vector<float> weight) {
		//找到沒有在road且權重最小的，並回傳他的位置

		int min = -1;
		for (int i = 0; i < weight.size(); i++) {
			if (!road.count(connected[i]) && weight[i] != -1) {
				if (min == -1 || weight[i] <= weight[min]) {
					min = i;
				}
			}
		}

		return min;
	}

	int findweight(string id) {
		//找到id對應的weight位置

		for (int i = 0; i < connected.size(); i++) {
			if (id == connected[i]) {
				return i;
			}
		}

		return -1;
	}

	bool isExisted(string id) {
		//判斷id是否存在list中

		for (int i = 0; i < list.size(); i++) {
			if (id == list[i].sendID) {
				return true;
			}
		}

		return false;
	}

public:
	vector<Node> list ;				//存任務0內容
	vector<string> connected;
	string filename;
	float bar;

	void Dijkstra() {
		set<string> road ;		
		string id;
		int step = 0;
		
		while (1) {
			road.clear();
			connected.clear();
			shortpath.clear();
			step = 0;

			Print();
			cout << "\nInput a student ID [0: exit]: ";
			cin >> id;
			if ( id == "0" ) return;
			if (!isExisted(id)) {
				cout << "\n### the student id does not exist! ###" << endl;
				continue;
			}

			findConnected( id ) ;	//找到id的連通成分，並存於connected中
			vector<float> weight(connected.size(), -1) ;	//weight紀錄權重
			string tmp = id;
			int cur = findweight(id);
			weight[cur] = 0;

			while ( step < connected.size() ) {
				Node_short tempnode;
				tempnode.id = tmp;
				tempnode.weight = weight[cur];
				shortpath.push_back(tempnode);

				if (step != connected.size()-1) {
					road.insert(tmp) ;

					for ( int i = 0; i < weight.size(); i++ ) {
						if (!road.count(connected[i])) {		//沒出現在road裡就計算一下新的權重
							float temppp = findDistance(connected[cur], connected[i]);
							if ( (temppp != -1 && weight[i] == -1) || (temppp != -1 && (temppp + weight[cur]) < weight[i]) ) {
								weight[i] = temppp + weight[cur];
							}
						}
					}

					cur = findmin(road, weight);		//找最小的權重
					tmp = connected[cur];
				}

				step++;
			}

			Writefile( filename, bar );
		}
	}

	void Print() {
		int count = 0;
		cout << endl;
		for (int i = 0; i < list.size(); i++ ) {
			cout << setw(10) << list[i].sendID;
			count++;
			if (count == 8) {
				cout << endl;
				count = 0;
			}
		}
	}

	void Writefile( string filename, float bar ) {
		int count = 0;
		stringstream temp;
		temp << bar;
		string num = temp.str();
		string file = "pairs" + filename + "_" + num + ".ds" ;
		ofstream out;
		out.open(file.c_str(), ios::out | ios::app); 
		if (out.is_open()) {
			out << endl << "origin: " << shortpath[0].id << endl;
			for ( int i = 1 ; i < shortpath.size(); i++ ) {
				count++;
				out << "(" << setw(2) << i << ")  " << shortpath[i].id << ", " << shortpath[i].weight << "\t";
				if (count == 8) {
					out << endl;
					count = 0;
				}
			}
			out << endl;
			out.close();
		}
	}
};

struct Node_tree {
	float weight;
	string id1;
	string id2;
};

struct Compare {
    bool operator()(const Node_tree& lhs, const Node_tree& rhs) {
        if (lhs.weight != rhs.weight) {
            return lhs.weight > rhs.weight;
        }

        if (lhs.id1 != rhs.id1) {
            return lhs.id1 > rhs.id1;
        }

        return lhs.id2 > rhs.id2;
    }
};

class SpanningTree {

	float findDistance( string start, string end ) {
		//找到start到end的權重並回傳

		for (int i = 0; i < list.size(); i++) {
			if (start == list[i].sendID) {
				Getlist *g = list[i].ptr;
				while ( g != NULL) {
					string str = g->getID;
					if (end == str) {
						return g->weight;
					}

					g = g->next;
				}

				break;
			}
		}

		return -1;
	}

	float countWeight() {
		float count = 0;
		for (int i = 0; i < spanning.size(); i++) {
			count += spanning[i].weight;
		}

		return count;
	}

	int find(string id, int no) {
		//找到id對應的位置

		for (int i = 0; i < connected[no].dfs.size(); i++) {
			if (id == connected[no].dfs[i]) {
				return i;
			}
		}

		return -1;
	}

public:
	vector<Node_dfs> connected; // the dfs result
	vector<Node> list ;				//存任務0內容
	vector<Node_tree> spanning;

	void Kruskal() {
		for (int i = 0; i < connected.size(); i++ ) {
			priority_queue<Node_tree, vector<Node_tree>, Compare> pq;
			vector<int> loc(connected[i].dfs.size());
			for (int a = 0; a < loc.size(); a++) {
				loc[a] = a;
			}

			spanning.clear();

			for (int j = 0; j < connected[i].dfs.size(); j++) {
				for (int k = j+1; k < connected[i].dfs.size(); k++) {
					float distance = findDistance( connected[i].dfs[j], connected[i].dfs[k] ) ;

					if (distance != -1) {
						Node_tree element;
						element.weight = distance;
						element.id1 = connected[i].dfs[j];
						element.id2 = connected[i].dfs[k];
						
						pq.push(element);
					}
				}
			}

			int edge = 0;
			while (edge < connected[i].dfs.size()-1) {
				Node_tree topElement = pq.top();
				float topWeignt = topElement.weight;
				string topId1 = topElement.id1 ;
				string topId2 = topElement.id2 ;
				cout << topElement.weight << " " << topElement.id1 << " " << topElement.id2 << endl ;
				pq.pop();

				int loc2 = find(topId2, i);
				int loc1 = find(topId1, i);
				
				cout << "1 and 2 : "<< loc1 << " " << loc2 << endl ;
				
				for ( int z = 0 ; z < loc.size(); z++) {
					cout << z << " " << loc[z] << endl ;
				}
				
				cout << "==============" << endl ;
				int before = -1, after = -1;
				if (loc[loc1] != loc[loc2]) {
					if (loc[loc1] < loc[loc2]) {
						before = loc[loc2]; // 2
						loc[loc2] = loc[loc1];
						after = loc[loc1];  // 1
					}
					else {
						before = loc[loc1];  // 1
						loc[loc1] = loc[loc2];	
						after = loc[loc2];	 // 2			
					}

					for (int temp = 0; temp < loc.size(); temp++) {
						if ( loc[temp] == before ) {
							loc[temp] = after;
						}
					}

					spanning.push_back(topElement);
					edge++;
				}	
					
					
			}

			float count = countWeight();
			cout << "The MST cost of connected component " << "{" << setw(2) << i+1 << "} = " << setprecision(5) << count << endl;
		}
	}
};


vector<Node> mission0( vector<InputFile> data, int n, string filenum, float bar ) {
	AdjacencyLists graph ;	
	graph.build(data, n, bar) ;
	graph.sortmain() ;
	graph.Writefile(filenum, bar) ;
	
	return graph.adjlist ;
}

vector<Node_dfs> mission1( vector<Node> data, string filenum, float bar ) {
	AL_DFS op ;
	op.list = data ;
	op.dfs() ;
	op.Writefile(filenum, bar) ;

	return op.dfsAns;
}

void mission2( vector<Node> data, string filenum, float bar ) {
	ShortPath sp;
	sp.list = data;
	sp.filename = filenum;
	sp.bar = bar;
	sp.Dijkstra();
}

void mission3( vector<Node> data, vector<Node_dfs> dfs ) {
	SpanningTree tree;
	tree.list = data;
	tree.connected = dfs;
	tree.Kruskal();
}

bool isDigit( string str ) {
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

int main() {
	
	string command = "\0" ;  
	int cd = -1 ;           
	bool check = false, check1 = false;
	File input ;
	string name = "\0";		
	int n = 0;
	vector<Node> tempa;
	vector<Node_dfs> dfs;
	string filenum ;
	do { 
	
		cout << endl << "******* Graph data applications ******" ;
		cout << endl << "* [Any other key: QUIT]              *" ;
		cout << endl << "* 0. Create adjacency lists          *" ;
		cout << endl << "* 0. Create adjacency lists          *" ;
		cout << endl << "* 1. Build connected components      *" ;
		cout << endl << "* 2. Find shortest paths by Dijkstra *" ;

		cout << endl << "**************************************" ;
		cout << endl << "Input a choice(0, 1, 2, 3) [Any other key: QUIT]:" ;
		cin >> command ;
		
		if ( isDigit(command) ) 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) {
			input.clearFile();
			n = input.readBinary(filenum) ;			
			tempa = mission0(input.data, n, filenum, input.GetBar() ) ;
			check = true ;	
		}

		else if ( cd == 1 ) {
			if( check == true ){
				dfs = mission1(tempa, filenum, input.GetBar() ) ; 
				check1 = true;
			}
			else{
				cout << "### There is no graph and choose 0 first. ###" << endl;
			}
		}

		else if ( cd == 2 ){
			if( check == true ){
				if ( check1 ){
					mission2( tempa, filenum, input.GetBar() ) ;  
				}
				else {
					cout << "### Choose 1 to find connected components. ###" << endl;
				}
			}
			else{
				cout << "### There is no graph and choose 0 first. ###" << endl;
			}
		}

		else if ( cd == 3 ) {
			if( check == true ){
				if ( check1 ){
					mission3( tempa, dfs ); 
				}
				else {
					cout << "### Choose 1 to find connected components. ###" << endl;
				}
			}
			else{
				cout << "### There is no graph and choose 0 first. ###" << endl;
			}			
		}

		else {
			return 0;
		}
		
	} while ( -1 < cd && cd < 4 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
