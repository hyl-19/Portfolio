# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>

using namespace std ;

// DS 2
// 11027212 黃建閎 11027222 黃彥霖 

class Data {
	
    public:
    	
        string rowData ;     // row data 
        string colName ;     // college name
        int depNumber ;      // department number 
        string depName ;     // department name
        int numOfStu ;       // number of students
        int numOfGrad ;      // number of graduates
     
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
		
		void FixNum( string & num ) {
			// 去修學生數的數字，"1,038" 
			
			int n = num.size() ;
			if ( num[0] == '\"' && num[n-1] == '\"' ) {
				num = num.erase(n-1, n) ; // 消除後面的雙引號 
				num = num.erase(0, 1) ; // 消除前面的雙引號 
				num = num.erase(1, 1) ; // 消除中間的逗號 
			} // if
				
		} // FixNum
		
    	void GetLineOfData() {
    		// 去存line裡面的資訊 
    		
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
	// 判斷數字是不是int
	 
	int temp = 0 ;
	if ( str[0] == '+' ) {              // +X也算int的一種，老師的code可以 
		for ( int i = 1 ; i < strlen( str ) ; i++) {
		
        	int temp = str[i] - '0' ;
        	if ( temp >= 0 && temp <= 9 )     // 都是數字就逐一檢查 
        	    continue ;
        	else
            	return false;
    	} // for
	} // if
	else {
		for ( int i = 0 ; i < strlen( str ) ; i++) {
		
        	int temp = str[i] - '0' ;
        	if ( temp >= 0 && temp <= 9 )     // 都是數字就逐一檢查 
        	    continue ;
        	else
       	    	return false;
    	} // for
	} // else
	
    return true;
		
} // IsDigit

void CheckFileNmae( string & str, int command ) {
	// 去檢查讀入的字串為代碼或者是整個檔名
	// 並回傳代碼 
	   
	int len = str.length() ;
	char temp[len] ;
	char change[5] ;
	
	for ( int i = 0 ; i < len ; i++ )      // 把字串轉成字元陣列 
		temp[i] = str[i] ;
	
	if( IsDigit(temp) )
		return ;

	int input = str.find("input") ; // 找有沒有"input"字串 
	size_t copy = str.find("copy") ;   // 找有沒有"copy"字串
	size_t txt = str.find(".txt") ;    // 找有沒有".txt"字串
	int j = 0 ;

	if( (input != str.npos && command == 1)|| copy != str.npos ) {     
		if ( txt != str.npos ){
			for ( int i = 0 ; i < len ; i++ ) {
				if ( '0' <= str[i] && str[i] <= '9' ) { // 取出數字部分 
					change[j] = str[i] ; 
					j++ ;
				} // if
			} // for
			
			str = change ; // 回傳代碼 
		} // if
	} // if
	
	
} // CheckFileNmae

void InsertData( vector<Data> & arr1, vector<Data> arr2 ) {
	// 為第三題合併的Function 
	
	int bothsame = 0 ;   // 同校同系的位置 
	int samesc = 0 ;     // 同校不同系的位置 
	for ( int i = 0 ; i < arr2.size() ; i++ ) {	   // 從第二個文件往第一個insert進去 
		bothsame = samesc = -1 ; // 初始化值，確保每次迴圈一樣 
		for( int j = 0 ; j < arr1.size() ; j++ ) {
			if( arr2.at(i).colName == arr1.at(j).colName &&     
				arr2.at(i).depName == arr1.at(j).depName ) { //如果同校同系，把第一個文件同校同系的位置存進bothsame 
				bothsame = j ;                                         //同時可以找到最後一個同校同系位置 
			} // if			
			if ( arr2.at(i).colName == arr1.at(j).colName  )  //能找到同校的最後一個在哪 
				samesc = j ;		
		} // for 
		
		if( bothsame != -1 )       // 先判斷同校同系有沒有出現，有的話直接把第二個文件資料insert進去 
			arr1.insert( arr1.begin() + bothsame + 1, arr2.at(i) ) ;
			
		else if ( bothsame == -1 && samesc != -1 )    //有同校但沒有同系，把第二個文件資料丟到第一個文件同校最後面 
			arr1.insert( arr1.begin() + samesc + 1, arr2.at(i) ) ;
			
		else if ( bothsame == -1 && samesc == -1 )     //都沒有同校同系就直接丟最後面
			arr1.push_back(arr2.at(i)) ;
		 
	} // for
	
} // InsertData

void mission1() {
	// 任務一的Function 
	
    string code = "/0" ;  // 存檔名或代碼 
    string fileName = "/0" ; // 完整的檔名 
    char file[100] ; // 存字元陣列的檔名 
    ifstream in ; 
    
    do {
    	
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code ; // 讀入檔名或代碼
    	CheckFileNmae( code, 1 ) ; // 檢查 
    	
    	fileName = "input" + code + ".txt" ;  // 改變檔案名稱    
    	strcpy( file, fileName.c_str() ) ; // 轉成字元陣列 
    	in.open(file, ios::in) ;    // 在讀取模式下開啟in檔案 
    	
    	if ( code == "0" ) return ; // 若輸入為0跳出任務一 
    	else if ( !in.is_open() )     // 找不到此檔案 
			cout << endl << "### " << fileName << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	Data data ; // 建立一個Class 
	vector<Data> dataFile ; // 動態陣列 
	
	while(getline(in, data.rowData)) { // 存資料 
		data.GetLineOfData() ;
		dataFile.push_back(data) ;
	} // while
	
	fileName = "copy" + code + ".txt" ; // 建立檔名 
	strcpy( file, fileName.c_str() ) ; // 轉成字元陣列 
	ofstream out(file) ; // 建檔 
	for ( int i = 3 ; i < dataFile.size() ; i++ )
		out << dataFile.at(i).rowData << endl ; // 寫檔 
	
	int num = dataFile.size() - 3 ; // 取出有幾筆資料 
	cout << endl << "Number of records = " << num << endl ;
	
	in.close() ; // 關檔案 
	out.close() ; // 關檔案 
	
} // mission1

void mission2() {
	// 任務二的Function
	
	string code = "/0" ; // 存檔名或代碼 
    string fileName = "/0" ; // 完整的檔名 
    char file[100] ;  // 存字元陣列的檔名
    ifstream in ;
    Data data ; // 建立一個Class 
    
    do {
    
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code ; // 讀入檔名或代碼
    	CheckFileNmae(code, 2) ; // 檢查 

    	fileName = "copy" + code + ".txt" ; // 改變檔案名稱 
    	strcpy( file, fileName.c_str() ) ; // 轉成字元陣列 
    	in.open(file, ios::in) ; // 在讀入模式下開啟in檔案 
    	
    	if ( code == "0" ) return ; // 若輸入為0跳出任務二 
    	else if ( !in.is_open() ) // 找不到此檔案
			cout << endl << "### " << fileName << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	int lowOfStu = 0 ; // 存最小學生數 
	int lowOfGrad = 0 ; // 存最小畢業人數 
	char str[100] ; // 檢查使用 
	
	while( true ) {
		cout << endl << "Input a lower bound on number of students: " ;
		cin >> str ;  // 讀入最小學生數 
		if( IsDigit(str) ) { // 判斷是不是數字 
			lowOfStu = atoi( str ) ; // char轉int 
			break ;
		}
	}
	
	while( true ) {
		cout << endl << "Input a lower bound on number of graduates: " ;
		cin >> str ;	// 讀入最小畢業人數
		if( IsDigit(str) ) { // 判斷是不是數字
			lowOfGrad = atoi(str) ; // char轉int
			break ;
		}
	}
	
	vector<Data> dataFile ;  // 動態陣列
	
	while(getline(in, data.rowData)) { // 存資料 
		data.GetLineOfData() ;
		dataFile.push_back(data) ;
	} // while
	
	vector<Data> finalFile ; // 最後要寫入的動態陣列 
	
	for ( int i = 0 ; i < dataFile.size() ; i ++ ) { // 篩選資料 
		if ( lowOfStu <= dataFile.at(i).numOfStu && lowOfGrad <= dataFile.at(i).numOfGrad )
			finalFile.push_back(dataFile.at(i)) ;
	} // for
	
	fileName = "copy" + code + ".txt" ; // 建立檔名 
	strcpy( file, fileName.c_str() ) ; // 轉成字元陣列 
	ofstream out(file) ;  // 建檔
	
	for ( int i = 0 ; i < finalFile.size() ; i++ )
		out << finalFile.at(i).rowData << endl ; // 寫檔 
	
	int num = finalFile.size() ; // 取出有幾筆資料 
	cout << endl << "Number of records = " << num << endl ;

	in.close() ; // 關檔案 
	out.close() ; // 關檔案 
	
} // mission2

void mission3() {
	// 任務三的Function
	
	string code1 = "/0" ; // 存第一筆檔名或代碼 
	string code2 = "/0" ; // 存第二筆檔名或代碼 
    string fileName1 = "/0" ; // 存第一筆完整檔名 
    string fileName2 = "/0" ; // 存第二筆完整檔名 
    char file1[100] ; // 存第一筆字串陣列的檔名 
    char file2[100] ; // 存第二筆字串陣列的檔名
    ifstream in ;
    Data data1 ; // 建立Class 
    Data data2 ; // 建立Class
    
    do {
    	
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code1 ; // 讀入檔名或代碼
    	CheckFileNmae( code1, 3 ) ; // 檢查

    	fileName1 = "copy" + code1 + ".txt" ; // 改變檔案名稱
    	strcpy( file1, fileName1.c_str() ) ; // 轉成字元陣列
    	in.open(file1, ios::in) ; // 在讀入模式下開啟in檔案
    	
    	if ( code1 == "0" ) return ; // 若輸入為0跳出任務三 
    	else if ( !in.is_open() ) // 找不到此檔案 
			cout << endl << "### " << fileName1 << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	vector<Data> dataFile1 ; // 建立第一筆動態陣列 
	
	while(getline(in, data1.rowData)) { // 存第一筆資料
		data1.GetLineOfData() ;
		dataFile1.push_back(data1) ;
	} // while
	
	in.close() ; // 關檔案 
	
    do {
    	
    	cout << endl << "Input 201, 202, 203...[0]Quit: " ;
    	cin >> code2 ; // 讀入檔名或代碼
    	CheckFileNmae( code2, 3 ) ; // 檢查

    	fileName2 = "copy" + code2 + ".txt" ; // 改變檔案名稱
    	strcpy( file2, fileName2.c_str() ) ; // 轉成字元陣列
    	in.open(file2, ios::in) ; // 在讀入模式下開啟in檔案
    	
    	if ( code2 == "0" ) return ; // 若輸入為0跳出任務三
    	else if ( !in.is_open() ) // 找不到此檔案
			cout << endl << "### " << fileName2 << " does NOT exist! ###" << endl ; 
    	
	} while( !in.is_open() ) ;
	
	vector<Data> dataFile2 ; // 建立第二筆動態陣列
	
	while(getline(in, data2.rowData)) { // 存第二筆資料 
		data2.GetLineOfData() ;
		dataFile2.push_back(data2) ;
	} // while
	
	InsertData( dataFile1, dataFile2 ) ; // 開始並檔 
	 
	fileName1 = "output" + code1 + "_" + code2 + ".txt" ; // 建立檔名 
	strcpy( file1, fileName1.c_str() ) ; // 轉成字元陣列 
	ofstream out(file1) ; // 建檔
	 
	for ( int i = 0 ; i < dataFile1.size() ; i++ )
		out << dataFile1.at(i).rowData << endl ; // 寫檔 
	
	int num = dataFile1.size() ; // 取出有幾筆資料 
	cout << endl << "Number of records = " << num << endl ;

	in.close() ; // 關檔案 
	out.close() ; // 關檔案 
	
} // mission3

int main() {
	
	int command = 0 ; // 存指令 
	char input[100] ; // 存讀入的指令 
	
	do {
		
		cout << endl << "***  File Object Manipulator  ***" ;
		cout << endl << "* 0.QUIT                        *" ;
		cout << endl << "* 1.COPY (Read & Save a file)   *" ;
		cout << endl << "* 2.FILTER (Reduce a file)      *" ;
		cout << endl << "* 3.MERGE (Join two files)      *" ;
		cout << endl << "*********************************" ;
		cout << endl << "Input a choice(0, 1, 2, 3): " ;
		cin >> input ; // 讀入指令
		
		if ( IsDigit ( input ) ) // 判斷是否為int 
			command = atoi( input ) ; // 轉成int 
		else
			return 0 ;
			
		if ( command == 0 ) return 0 ; // 指令為0，結束 
		else if ( command == 1 ) mission1() ; // 指令為1，執行任務一 
		else if ( command == 2 ) mission2() ; // 指令為2，執行任務二 
		else if ( command == 3 ) mission3() ; // 指令為3，執行任務三 
		else  cout << endl << "Command dose NOT exsit!" << endl ; // 都不是有效指令 
		 
	} while(command != 0) ;
	
	system("pause") ;
	return 0 ;
	
} // main()
