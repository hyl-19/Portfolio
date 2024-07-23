//DS2ex3_27_11027222_11027206
 
# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>
# include<string>
# include<iomanip>
# include<math.h>

using namespace std ;
#define COLUMNS 6
#define MAX_LEN 10
#define BIG_INT 255

struct InputFile {
	char stid[MAX_LEN] ;
	char stname[MAX_LEN] ;
	unsigned char stscore[COLUMNS] ;
	float mean ;
}; // InputFile

struct Data {
	int index ;
	char stid[MAX_LEN] ;
	char stname[MAX_LEN] ;
	float mean ;
};

class File {
	string filenum ;
	int n ;
	
	
public :
	vector<Data> data ;
	
	int GetInputsize() {
		return n ;
	}

	string fileN() {
		return filenum;
	}
	
	int TextToBinary() {
		int stNo = 0 ;
    	fstream inFile, outFile;
    	fstream bFile ;
    	string filename;
    	
   		do {
        	cout << "\nInput a file number: ";
	        cin >> filenum;
	        if (!filenum.compare("0")) {
	            return 0 ;
	        }
	        inFile.open(("input" + filenum + ".txt").c_str(), fstream::in);
	        bFile.open(("input" + filenum + ".bin").c_str(), fstream::in|fstream::binary);
	        
	        if (inFile.is_open()) { // have txt 
	        	if(!bFile.is_open()){
	        		cout << "\n### input" << filenum << ".bin does not exist! ###\n" ;
				}
				
	            break ;
	        }
	        else {
	        	if(!bFile.is_open()){ //txt & bin doesn't exist
	        		cout << "\n### input" << filenum << ".txt does not exist! ###\n" ;
	        		cout << "\n### input" << filenum << ".bin does not exist! ###\n" ;
	        		return 0 ;
				}
				else {
					bFile.close() ;
					return stNo ;
				}
			}
	    } while (1);

	    filename = "input" + filenum + ".bin";
 	    outFile.open(filename.c_str(), fstream::out | fstream::binary);
 	    if (outFile.is_open()) {
 	        char rbuf[BIG_INT];
	        while (inFile.getline(rbuf, BIG_INT, '\n')) {
	            string temp;
			    InputFile oneSt;
		        int cNO = 0;
	            int pre = 0;
	            int pos = 0;
	
	            stNo++;
	            temp.assign(rbuf);
	            pos = temp.find_first_of('\t', pre);
	            while (pos != string::npos) {
	                switch (++cNO) {
	                    case 1:
	                        strcpy(oneSt.stid, temp.substr(pre, pos - pre).c_str());
	                        break;
	                    case 2:
	                        strcpy(oneSt.stname, temp.substr(pre, pos - pre).c_str());
	                        break;
	                    default:
	                        oneSt.stscore[cNO - 3] = atoi(temp.substr(pre, pos - pre).c_str());
	                        break;
	                }
	                pre = ++pos;
	                pos = temp.find_first_of('\t', pre);
	            }
	            pos = temp.find_last_of('\t');
	            oneSt.mean = atof(temp.substr(pos + 1).c_str());
	            outFile.write((char*)&oneSt, sizeof(oneSt));
	        }
	        outFile.close();
	    }
	    bFile.close() ;
	    inFile.close();
	    n = stNo ;
	    return stNo;
	}

	int readBinary() {
		fstream binFile ;
		InputFile oneSt ; 
		int stNo = 0 ; 
		string fileName = "input" + filenum + ".bin" ;
		binFile.open(fileName.c_str(), fstream::in|fstream::binary) ;
		if(binFile.is_open()) {
			binFile.seekg(0,binFile.end );
			stNo = binFile.tellg() / sizeof(oneSt) ;
			binFile.seekg(0,binFile.beg);
			data.clear() ;
			data.resize(stNo) ;
			for(int i = 0 ; i < stNo ; i++) { // ���Ʀs�Jdata�� 
				binFile.read((char*)&oneSt, sizeof(oneSt)) ;
				strcpy(data.at(i).stid, oneSt.stid ) ;
				strcpy(data.at(i).stname, oneSt.stname ) ;
				data[i].mean = oneSt.mean ;
				
			}
		} 
		binFile.close() ;
		n = stNo ;
		return stNo ;
	}	
	
	void Writefile( vector<Data> data, string name, string filename ) {
		
		string file = name + filename + ".txt" ;
		ofstream out(file.c_str()) ;
		if (  name == "quadratic" ) {
			out << " --- Hash table created by Quadratic probing ---" << endl ;
		}
		else if ( name == "double" ) {
			out << " --- Hash table created by Double hashing    ---" << endl ;
		}

		for ( int i = 0 ; i < data.size(); i++ ) {
			if ( data[i].stname[0] != '\0' ) {
				out << "[" << setw(3) << i << "] " << setw(10) ;
				out << data[i].index << ", " << setw(10) << data[i].stid <<  ", " << setw(10)  ;
				out << data[i].stname << ", " << setw(10) << data[i].mean << endl ;
			}
			else {
				out << "[" << setw(3) << i << "] " << endl ;
			}
			
		}
		out << " ----------------------------------------------------- " << endl ;
		out.close() ;

		if (  name == "quadratic" ) {
			cout << "\nHash table has been successfully created by Quadratic probing" << endl ;
		}
		else if( name == "double" ) {
			cout << "\nHash table has been successfully created by Double hashing" << endl ;
		}
	}

	void clearFile() {
	// ���������ƧR�� 
			
		data.clear() ;
	} // clearFile
	
};

class Quadratic_Hash : public File {
	
	vector<Data> hashresult ; // result of hash table 
	vector<Data> data;
	int size ;
	
	int hash( int &num ) {  //�p�����굲�G�Anum�s�p��X����m�Aindex�s���ө񪺦�m 
		int fail = num ;
		char id[MAX_LEN] ;
		strcpy(id, data[num].stid) ;
		long long int mul = 1 ;
		for ( int i = 0 ; id[i] != '\0' ; i++ ) {  // id �� ascii �ۭ� 
			int n = id[i] ;
			mul *= n ;
		}    

		int index = mul % size ;
		num = index ;
		int count = 1 ;
		while ( hashresult[index].stname[0] != '\0' ) {    // ����k��L��index�AN^2 
			if ( count == 1 ) {
				index = index + pow(count,2) ;
			}
			else {
				index = index + pow(count,2) - pow(count-1,2) ;
			}
			
			count++ ;
			if ( index >= size ) {
				index %= size ;
			}
			if ( count == size ) {
				cout << "### failed at[" << fail << "]. ###"  << endl ;
				return -1 ;
			}
		}
		
		return index ;
	}
	
	void primenumber() { //��1.2����� 
		int num = data.size() ;
		num = num * 1.2 ;
		int count = 0 ;
		for ( int i = num + 1 ; ; i++ ) {
			
			count = 0 ;
			for ( int j = 2 ; j < i ; j++ ) {
				if ( i % j == 0 ) {
					count++ ;
				}
			}
			if ( count == 0 ) {
				size = i ;
				return ;
			}
		}
	}
	
	void findID( char id[MAX_LEN] ) {
		
		long long int mul = 1 ;
		for ( int i = 0 ; id[i] != '\0' ; i++ ) {
			int n = id[i] ;
			mul *= n ;
		}

		int index = mul % size ;
		int num = index ;
		int count = 1 ;
		
		while ( strcmp( hashresult[index].stid, id ) != 0  ) {
			
			if ( count == 1 ) {
				index = index + pow(count,2) ;
			}
			else {
				index = index + pow(count,2) - pow(count-1,2) ;
			}
			
			count++ ;
			if ( index >= size ) {
				index %= size ;
			}
			if ( hashresult[index].stname[0] == '\0' ) { 
				cout << id << " is not found after " << count  << " probes." << endl ;
				break ;
			}
		}
		
		if ( strcmp( hashresult[index].stid, id ) == 0 ) {
			cout << "\n{ " << hashresult[index].stid << ", " << hashresult[index].stname << ", " << hashresult[index].mean  
			<< " } is found after " << count << " probes." << endl ;
			return ;	
		}
		
			
		
		
		
	}
	
public :

	void Hashtable( vector<Data> data1 ) {
		data = data1;
		int num, index ;
		primenumber() ;
		hashresult.resize(size) ;
		for( int i = 0 ; i < data.size() ; i++ ) {   //�qdata�Ĥ@�Ӹ�ƶ}�l�[�Jhash table 
			num = i ;
			index = hash( num ) ;
			if ( index != -1 ) {
				hashresult.at(index).index = num ;
				strcpy(hashresult[index].stid, data[i].stid) ;
				strcpy(hashresult[index].stname, data[i].stname) ;
				hashresult[index].mean = data[i].mean ;
			}

		}	
	}
	
	vector<Data> Gethash() {
		return hashresult ;
	}
	
	int collision_suc ( int num ) {
		//�q�ª�data�@�Ӥ@�ӧ��hashresult��F�X��comparison 
		char id[MAX_LEN] ;
		strcpy(id, data[num].stid) ;
		long long int mul = 1 ;
		for ( int i = 0 ; id[i] != '\0' ; i++ ) {
			int n = id[i] ;
			mul *= n ;
		}

		int index = mul % size ;
		int count = 1 ;
		while ( strcmp( hashresult[index].stid, data[num].stid ) != 0 ) {
			if ( count == 1 ) {
				index = index + pow(count,2) ;
			}
			else {
				index = index + pow(count,2) - pow(count-1,2) ;
			}
			
			count++ ;
			if ( index >= size ) {
				index %= size ;
			}
		}
		
		return count ;
	}
		
	int collision_fail ( int num ) {
		//�qhashresult�Y�}�l�ݥδX������k�|���Ū��Ŷ� 
		if (hashresult[num].stname[0] == '\0' ) {
			return 1 ;
		}
		
		int index = num ;
		int count = 1 ;
		while ( hashresult[index].stname[0] != '\0' ) {
			if ( count == 1 ) {
				index = index + pow(count,2) ;
			}
			else {
				index = index + pow(count,2) - pow(count-1,2) ;
			}
			
			count++ ;
			if ( index >= size ) {
				index %= size ;
			}
		}
		
		return count ;
	}
		
	void suc() {
		float count = 0 ;
		for ( int i = 0 ; i < data.size() ; i++ ) {
			count += collision_suc( i ) ;
		}
		count /= data.size() ;
		cout << "successful search: " <<  setprecision(5) << count << " comparisons on average" << endl << endl ;
	}
	
	void fail() {
		float count = 0 ;
		for ( int i = 0 ; i < hashresult.size() ; i++ ) {
			count += collision_fail( i ) ;
		}
		count /= hashresult.size() ;
		cout << "unsuccessful search: " <<  setprecision(5) << count - 1 << " comparisons on average" << endl << endl ;
	}
	
	void search() {
		char in[MAX_LEN] ;
		cout << "Input a student ID to search ([0] Quit):" ;
		cin >> in ;
		while ( strcmp( in, "0" ) != 0 ) {
			findID( in ) ;
			cout << "\nInput a student ID to search ([0] Quit):" ;
			cin >> in ;
		}
	
	}
	
};


class Double_Hash : public File {
	vector<Data> doublehash;
	vector<Data> data;			//�s���Ȥ@Ū�J���e
	int size, stepsize;			//size�O�����j�p; stepsize�O�̰��B����
	float numOfSearch ;			//�j�M������

	int dhash( int &num ) {		
		//�Ĥ@���j�M���������ơA����p�G���J��I���N�ΨB����Ƨ�n�񪺦�m

		char id[MAX_LEN] ;
		strcpy(id, data[num].stid) ;
		long long int mul = 1 ;
		for ( int i = 0 ; i < MAX_LEN && id[i] != '\0'; i++ ) {
			int n = id[i] ;
			mul *= n ;
		}

		int index = mul % size ;
		num = index ;
		numOfSearch++;

		while( doublehash[index].stname[0] != '\0' ) {
			index = index + ( stepsize - ( mul % stepsize ));

			if( index >= size ){
				index %= size;
			}

			numOfSearch++;
		}
			
		return index;
	}

	void primenumber() {
		//�p�������j�p(>�`��Ƽ�*1.2���̤p���)

		int num = data.size() ;
		num = num * 1.2 ;
		int count = 0 ;
		for ( int i = num + 1 ; ; i++ ) {
			
			count = 0 ;
			for ( int j = 2 ; j < i ; j++ ) {
				if ( i % j == 0 ) {
					count++ ;
				}
			}
			if ( count == 0 ) {
				size = i ;
				return ;
			}
		}
	}

	void highStep() {
		//�p��̰��B��(>����`��/3���̤p���)

		int num = data.size() ;
		num = num / 3 ;
		int count = 0 ;
		for ( int i = num + 1 ; ; i++ ) {
			
			count = 0 ;
			for ( int j = 2 ; j < i ; j++ ) {
				if ( i % j == 0 ) {
					count++ ;
				}
			}
			if ( count == 0 ) {
				stepsize = i ;
				return ;
			}
		}
	}

	float average() {
		//�p�⥭���������

		int datasize = data.size();
		float count = float( numOfSearch / datasize );
		return count;
	}

	bool find( char inputId[MAX_LEN] ) {
		int count = 0;
		bool isfind = 0;
		long long int mul = 1 ;
		for ( int i = 0 ; i < MAX_LEN && inputId[i] != '\0'; i++ ) {
			int n = inputId[i] ;
			mul *= n ;
		}

		int index = mul % size ;
		count++;

		while( strcmp( doublehash[index].stid, inputId ) != 0 ) {
			index = index + ( stepsize - ( mul % stepsize ));

			if( index >= size ){
				index %= size;
			}

			count++;
			if( doublehash[index].stname[0] == '\0' ) {
				isfind = 0;
				break;
			}
		}

		if( strcmp( doublehash[index].stid, inputId ) == 0 ){
			isfind = 1;
			cout << endl << "{ " << doublehash[index].stid << ", " << doublehash[index].stname << ", "
			 << doublehash[index].mean << " } is found after " << count << " probes." << endl ;
			return true;
		}

		cout << inputId << " is not found after " << count << " probes." << endl ;
		return false;
	}

public:
	
	void buildTable( vector<Data> data1 ) {
		//�NŪ�J����Ƥ@�Ӥ@�ө�Jdoublehash���A�إ������

		int num, index ;
		data = data1;
		numOfSearch = 0;
		primenumber() ;
		highStep() ;
		doublehash.resize(size) ;
		for( int i = 0 ; i < data.size() ; i++ ) {
			num = i ;
			index = dhash( num ) ;
			doublehash[index].index = num ;
			strcpy(doublehash[index].stid, data[i].stid) ;
			strcpy(doublehash[index].stname, data[i].stname) ;
			doublehash[index].mean = data[i].mean ;
		}	

	}

	vector<Data> getdoublHash() {
		return doublehash;
	}

	void printAverage() {
		//�L�X�����������

		cout << "successful search: " << setprecision(5) << average() << " comparisons on average" << endl;

	}

	Double_Hash() {
		size = 0;
		stepsize = 0;
		numOfSearch = 0.0;
	}

	void search() {
		char id[MAX_LEN];
		cout << "\nInput a student ID to search ([0] Quit): ";
		cin >> id;
		while( strcmp( id, "0" ) != 0 ) {
			find( id );
			cout << "\nInput a student ID to search ([0] Quit): ";
			cin >> id;
		}
	}
};

void mission1( vector<Data> data, string name ) {
	Quadratic_Hash item ;
	int num = 0 ;
	item.Hashtable( data ) ;								//�Υ��豴���إ������
	item.Writefile( item.Gethash(), "quadratic", name ) ;	//�g��
	item.fail() ;											//�L�X�j�M���s�b�Ȫ������������
	item.suc() ;											//�L�X�j�M�{�s�Ȫ������������
	item.search() ;
}

void mission2( vector<Data> data, string name ) {
	Double_Hash dhash;
	dhash.buildTable( data );									//����������إ������
	dhash.Writefile( dhash.getdoublHash(), "double", name ) ;	//�g��
	dhash.printAverage();										//�L�X�j�M�{�s�Ȫ������������
	dhash.search();
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
	int isRead = 0;
	
	do { 
	
		cout << endl << "******* Hash Table ******" ;
		cout << endl << "* 0. QUIT               *" ;
		cout << endl << "* 1. Quadratic probing  *" ;
		cout << endl << "* 2. Double hashing     *" ;
		cout << endl << "*************************" ;
		cout << endl << "Input a command(0, 1, 2) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) {
			input.clearFile();
			isRead = input.TextToBinary() ;		//Ū��
			if( isRead != 0 ){
				name = input.fileN();
				input.readBinary() ;			//�ন�G�i��
				mission1( input.data, name ) ;
				check = true ;
			}
		}
		else if ( cd == 2 ){
			if( check == true ){
				mission2( input.data, name ) ; // �i�J���ȤG 
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
