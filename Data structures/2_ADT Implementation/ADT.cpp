# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>

using namespace std ;

// DS 2
// 11027212 ���ض� 11027222 �����M 

class Data {
	
    public:
    	
        string rowData ;     // row data 
        string colName ;     // college name
        int depNumber ;      // department number 
        string depName ;     // department name
        int numOfStu ;       // number of students
        int numOfGrad ;      // number of graduates
     
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
		
		void FixNum( string & num ) {
			// �h�׾ǥͼƪ��Ʀr�A"1,038" 
			
			int n = num.size() ;
			if ( num[0] == '\"' && num[n-1] == '\"' ) {
				num = num.erase(n-1, n) ; // �����᭱�����޸� 
				num = num.erase(0, 1) ; // �����e�������޸� 
				num = num.erase(1, 1) ; // �����������r�� 
			} // if
				
		} // FixNum
		
    	void GetLineOfData() {
    		// �h�sline�̭�����T 
    		
    		string data = "/0" ;
    		
			GetString(rowData, 2, colName) ;
			GetString(rowData, 3, data) ;
			FixNum(data) ;
			depNumber = atoi(data.c_str()) ;
			GetString(rowData, 4, depName) ;
			GetString(rowData, 7, data) ;
			FixNum(data) ;
			numOfStu = atoi(data.c_str()) ;
			GetString(rowData, 9, data) ;
			FixNum(data) ;
			numOfGrad = atoi(data.c_str()) ;
			cout << rowData << endl ;
			cout << numOfGrad << endl ;
		} // GetLineOfData
		
}; // class

bool IsDigit( const char* str ) {       
	// �P�_�Ʀr�O���Oint
	 
	int temp = 0 ;
	if ( str[0] == '+' ) {              // +X�]��int���@�ءA�Ѯv��code�i�H 
		for ( int i = 1 ; i < strlen( str ) ; i++) {
		
        	int temp = str[i] - '0' ;
        	if ( temp >= 0 && temp <= 9 )     // ���O�Ʀr�N�v�@�ˬd 
        	    continue ;
        	else
            	return false;
    	} // for
	} // if
	else {
		for ( int i = 0 ; i < strlen( str ) ; i++) {
		
        	int temp = str[i] - '0' ;
        	if ( temp >= 0 && temp <= 9 )     // ���O�Ʀr�N�v�@�ˬd 
        	    continue ;
        	else
       	    	return false;
    	} // for
	} // else
	
    return true;
		
} // IsDigit

void CheckFileNmae( string & str, int command ) {
	// �h�ˬdŪ�J���r�ꬰ�N�X�Ϊ̬O����ɦW
	// �æ^�ǥN�X 
	   
	int len = str.length() ;
	char temp[len] ;
	char change[5] ;
	
	for ( int i = 0 ; i < len ; i++ )      // ��r���ন�r���}�C 
		temp[i] = str[i] ;
	
	if( IsDigit(temp) )
		return ;

	int input = str.find("input") ; // �䦳�S��"input"�r�� 
	size_t copy = str.find("copy") ;   // �䦳�S��"copy"�r��
	size_t txt = str.find(".txt") ;    // �䦳�S��".txt"�r��
	int j = 0 ;

	if( (input != str.npos && command == 1)|| copy != str.npos ) {     
		if ( txt != str.npos ){
			for ( int i = 0 ; i < len ; i++ ) {
				if ( '0' <= str[i] && str[i] <= '9' ) { // ���X�Ʀr���� 
					change[j] = str[i] ; 
					j++ ;
				} // if
			} // for
			
			str = change ; // �^�ǥN�X 
		} // if
	} // if
	
	
} // CheckFileNmae

void InsertData( vector<Data> & arr1, vector<Data> arr2 ) {
	// ���ĤT�D�X�֪�Function 
	
	int bothsame = 0 ;   // �P�զP�t����m 
	int samesc = 0 ;     // �P�դ��P�t����m 
	for ( int i = 0 ; i < arr2.size() ; i++ ) {	   // �q�ĤG�Ӥ�󩹲Ĥ@��insert�i�h 
		bothsame = samesc = -1 ; // ��l�ƭȡA�T�O�C���j��@�� 
		for( int j = 0 ; j < arr1.size() ; j++ ) {
			if( arr2.at(i).colName == arr1.at(j).colName &&     
				arr2.at(i).depName == arr1.at(j).depName ) { //�p�G�P�զP�t�A��Ĥ@�Ӥ��P�զP�t����m�s�ibothsame 
				bothsame = j ;                                         //�P�ɥi�H���̫�@�ӦP�զP�t��m 
			} // if			
			if ( arr2.at(i).colName == arr1.at(j).colName  )  //����P�ժ��̫�@�Ӧb�� 
				samesc = j ;		
		} // for 
		
		if( bothsame != -1 )       // ���P�_�P�զP�t���S���X�{�A�����ܪ�����ĤG�Ӥ����insert�i�h 
			arr1.insert( arr1.begin() + bothsame + 1, arr2.at(i) ) ;
			
		else if ( bothsame == -1 && samesc != -1 )    //���P�զ��S���P�t�A��ĤG�Ӥ���ƥ��Ĥ@�Ӥ��P�ճ̫᭱ 
			arr1.insert( arr1.begin() + samesc + 1, arr2.at(i) ) ;
			
		else if ( bothsame == -1 && samesc == -1 )     //���S���P�զP�t�N������̫᭱
			arr1.push_back(arr2.at(i)) ;
		 
	} // for
	
} // InsertData

void mission1() {
	// ���Ȥ@��Function 
	
    string code = "/0" ;  // �s�ɦW�ΥN�X 
    string fileName = "/0" ; // ���㪺�ɦW 
    char file[100] ; // �s�r���}�C���ɦW 
    ifstream in ; 
    
    do {
    	
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code ; // Ū�J�ɦW�ΥN�X
    	CheckFileNmae( code, 1 ) ; // �ˬd 
    	
    	fileName = "input" + code + ".txt" ;  // �����ɮצW��    
    	strcpy( file, fileName.c_str() ) ; // �ন�r���}�C 
    	in.open(file, ios::in) ;    // �bŪ���Ҧ��U�}��in�ɮ� 
    	
    	if ( code == "0" ) return ; // �Y��J��0���X���Ȥ@ 
    	else if ( !in.is_open() )     // �䤣�즹�ɮ� 
			cout << endl << "### " << fileName << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	Data data ; // �إߤ@��Class 
	vector<Data> dataFile ; // �ʺA�}�C 
	
	while(getline(in, data.rowData)) { // �s��� 
		data.GetLineOfData() ;
		dataFile.push_back(data) ;
	} // while
	
	fileName = "copy" + code + ".txt" ; // �إ��ɦW 
	strcpy( file, fileName.c_str() ) ; // �ন�r���}�C 
	ofstream out(file) ; // ���� 
	for ( int i = 3 ; i < dataFile.size() ; i++ )
		out << dataFile.at(i).rowData << endl ; // �g�� 
	
	int num = dataFile.size() - 3 ; // ���X���X����� 
	cout << endl << "Number of records = " << num << endl ;
	
	in.close() ; // ���ɮ� 
	out.close() ; // ���ɮ� 
	
} // mission1

void mission2() {
	// ���ȤG��Function
	
	string code = "/0" ; // �s�ɦW�ΥN�X 
    string fileName = "/0" ; // ���㪺�ɦW 
    char file[100] ;  // �s�r���}�C���ɦW
    ifstream in ;
    Data data ; // �إߤ@��Class 
    
    do {
    
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code ; // Ū�J�ɦW�ΥN�X
    	CheckFileNmae(code, 2) ; // �ˬd 

    	fileName = "copy" + code + ".txt" ; // �����ɮצW�� 
    	strcpy( file, fileName.c_str() ) ; // �ন�r���}�C 
    	in.open(file, ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ� 
    	
    	if ( code == "0" ) return ; // �Y��J��0���X���ȤG 
    	else if ( !in.is_open() ) // �䤣�즹�ɮ�
			cout << endl << "### " << fileName << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	int lowOfStu = 0 ; // �s�̤p�ǥͼ� 
	int lowOfGrad = 0 ; // �s�̤p���~�H�� 
	char str[100] ; // �ˬd�ϥ� 
	
	while( true ) {
		cout << endl << "Input a lower bound on number of students: " ;
		cin >> str ;  // Ū�J�̤p�ǥͼ� 
		if( IsDigit(str) ) { // �P�_�O���O�Ʀr 
			lowOfStu = atoi( str ) ; // char��int 
			break ;
		}
	}
	
	while( true ) {
		cout << endl << "Input a lower bound on number of graduates: " ;
		cin >> str ;	// Ū�J�̤p���~�H��
		if( IsDigit(str) ) { // �P�_�O���O�Ʀr
			lowOfGrad = atoi(str) ; // char��int
			break ;
		}
	}
	
	vector<Data> dataFile ;  // �ʺA�}�C
	
	while(getline(in, data.rowData)) { // �s��� 
		data.GetLineOfData() ;
		dataFile.push_back(data) ;
	} // while
	
	vector<Data> finalFile ; // �̫�n�g�J���ʺA�}�C 
	
	for ( int i = 0 ; i < dataFile.size() ; i ++ ) { // �z���� 
		if ( lowOfStu <= dataFile.at(i).numOfStu && lowOfGrad <= dataFile.at(i).numOfGrad )
			finalFile.push_back(dataFile.at(i)) ;
	} // for
	
	fileName = "copy" + code + ".txt" ; // �إ��ɦW 
	strcpy( file, fileName.c_str() ) ; // �ন�r���}�C 
	ofstream out(file) ;  // ����
	
	for ( int i = 0 ; i < finalFile.size() ; i++ )
		out << finalFile.at(i).rowData << endl ; // �g�� 
	
	int num = finalFile.size() ; // ���X���X����� 
	cout << endl << "Number of records = " << num << endl ;

	in.close() ; // ���ɮ� 
	out.close() ; // ���ɮ� 
	
} // mission2

void mission3() {
	// ���ȤT��Function
	
	string code1 = "/0" ; // �s�Ĥ@���ɦW�ΥN�X 
	string code2 = "/0" ; // �s�ĤG���ɦW�ΥN�X 
    string fileName1 = "/0" ; // �s�Ĥ@�������ɦW 
    string fileName2 = "/0" ; // �s�ĤG�������ɦW 
    char file1[100] ; // �s�Ĥ@���r��}�C���ɦW 
    char file2[100] ; // �s�ĤG���r��}�C���ɦW
    ifstream in ;
    Data data1 ; // �إ�Class 
    Data data2 ; // �إ�Class
    
    do {
    	
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code1 ; // Ū�J�ɦW�ΥN�X
    	CheckFileNmae( code1, 3 ) ; // �ˬd

    	fileName1 = "copy" + code1 + ".txt" ; // �����ɮצW��
    	strcpy( file1, fileName1.c_str() ) ; // �ন�r���}�C
    	in.open(file1, ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    	if ( code1 == "0" ) return ; // �Y��J��0���X���ȤT 
    	else if ( !in.is_open() ) // �䤣�즹�ɮ� 
			cout << endl << "### " << fileName1 << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	vector<Data> dataFile1 ; // �إ߲Ĥ@���ʺA�}�C 
	
	while(getline(in, data1.rowData)) { // �s�Ĥ@�����
		data1.GetLineOfData() ;
		dataFile1.push_back(data1) ;
	} // while
	
	in.close() ; // ���ɮ� 
	
    do {
    	
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code2 ; // Ū�J�ɦW�ΥN�X
    	CheckFileNmae( code2, 3 ) ; // �ˬd

    	fileName2 = "copy" + code2 + ".txt" ; // �����ɮצW��
    	strcpy( file2, fileName2.c_str() ) ; // �ন�r���}�C
    	in.open(file2, ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    	if ( code2 == "0" ) return ; // �Y��J��0���X���ȤT
    	else if ( !in.is_open() ) // �䤣�즹�ɮ�
			cout << endl << "### " << fileName2 << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	vector<Data> dataFile2 ; // �إ߲ĤG���ʺA�}�C
	
	while(getline(in, data2.rowData)) { // �s�ĤG����� 
		data2.GetLineOfData() ;
		dataFile2.push_back(data2) ;
	} // while
	
	InsertData( dataFile1, dataFile2 ) ; // �}�l���� 
	 
	fileName1 = "output" + code1 + "_" + code2 + ".txt" ; // �إ��ɦW 
	strcpy( file1, fileName1.c_str() ) ; // �ন�r���}�C 
	ofstream out(file1) ; // ����
	 
	for ( int i = 0 ; i < dataFile1.size() ; i++ )
		out << dataFile1.at(i).rowData << endl ; // �g�� 
	
	int num = dataFile1.size() ; // ���X���X����� 
	cout << endl << "Number of records = " << num << endl ;

	in.close() ; // ���ɮ� 
	out.close() ; // ���ɮ� 
	
} // mission3

int main() {
	
	int command = 0 ; // �s���O 
	char input[100] ; // �sŪ�J�����O 
	
	do {
		
		cout << endl << "***  File Object Manipulator  ***" ;
		cout << endl << "* 0.QUIT                        *" ;
		cout << endl << "* 1.COPY (Read & Save a file)   *" ;
		cout << endl << "* 2.FILTER (Reduce a file)      *" ;
		cout << endl << "* 3.MERGE (Join two files)      *" ;
		cout << endl << "*********************************" ;
		cout << endl << "Input a choice(0, 1, 2, 3): " ;
		cin >> input ; // Ū�J���O
		
		if ( IsDigit ( input ) ) // �P�_�O�_��int 
			command = atoi( input ) ; // �নint 
		else
			return 0 ;
			
		if ( command == 0 ) return 0 ; // ���O��0�A���� 
		else if ( command == 1 ) mission1() ; // ���O��1�A������Ȥ@ 
		else if ( command == 2 ) mission2() ; // ���O��2�A������ȤG 
		else if ( command == 3 ) mission3() ; // ���O��3�A������ȤT 
		else  cout << endl << "Command dose NOT exsit!" << endl ; // �����O���ī��O 
		 
	} while(command != 0) ;
	
	system("pause") ;
	return 0 ;
	
} // main()
