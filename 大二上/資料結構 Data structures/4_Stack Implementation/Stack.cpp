// 07組 11027212 黃建閎 11027222 黃彥霖
// DS 4

# include<iostream>
# include<fstream>
# include<vector>
# include<cstring>
# include<cstdlib>
# include<algorithm>
# include<string.h>
# include<ctime>
# include<iomanip>

using namespace std ;

struct Type {
		 
		int OID ;       // 訂單編號 
		int arrival ;   // 下單時刻 
		int duration ;  // 製作耗時
		int timeOut ;   // 逾時時刻
		
		int CID ;       // 廚師編號 
		int delay ;     // 延誤時間
		int abort ;     // 取消時刻
		int departure ; // 完成時刻
		
		// delay = abort - arrival
		// departure = arrival + delay + duration
	
}; // Type
	
class JobList {
	
	vector<Type> Joblist ;  // 存工作清單 
	string ID ;             // 存檔案代碼
	string title ;          // 存標頭
	int JobNum ;            // 幾個工作清單數目 
	
	void SetNum() {
		// 設定長度 
		
		JobNum = Joblist.size() ;
		
	} // SetNum
	
	void SortOID() {
		// 對OID進行希爾德排序 
		
		for ( int gap = Joblist.size() / 2 ; gap > 0 ; gap /= 2 ) {
            for ( int i = gap ; i < Joblist.size() ; i++ ) {
            	vector<Type> temp ;
                temp.push_back(Joblist.at(i)) ;
                int j ;
                	
                for ( j = i ; j >= gap && Joblist.at(j-gap).arrival == temp.at(0).arrival &&
				      Joblist.at(j-gap).OID > temp.at(0).OID ; j -= gap )
				      
                    swap(Joblist[j], Joblist[j-gap]) ;	
                	
                swap(Joblist[j], temp[0]) ;
                temp.clear() ;
			} // for
        } // for
		
	} // SortOID
	
	public :
		
		string FileName( string str ) { 
		// 回傳完整的 file name
		
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// 存取 file 裡的 data
		
			ifstream in ;
			string file ; // 檔案名稱 
			Type type ;   // 資料 
			Type temp ;   // 存上一筆資料 
			
    		cout << endl << "Input a file number (e.g. 401, 402, 403, ... ) :" ;
    		cin >> ID ; // 讀入檔案代碼 

    		file = FileName(name) ; // 檔案完整名稱 
    			
    		in.open(file.c_str(), ios::in) ; // 在讀入模式下開啟in檔案
    	
    		if ( !in.is_open() ) { // 找不到此檔案 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				
				getline(in, title) ; // 讀入標頭
				
				do {
					in >> type.OID >> type.arrival >> type.duration >> type.timeOut ; // 讀取資料
					if ( type.OID != temp.OID )   // 以免有重複的資料 
						Joblist.push_back(type) ; // 存入資料
					temp = type ;
				} while ( !in.eof() ) ;
				
			} // else
			
			SetNum() ;   // 找出讀了幾筆資料 
			in.close() ; // 關檔 
			return true ;
			
		} // ReadFile
		
		void WriteFile( string name ) {
			// 寫檔案 str 為檔案名稱 
			
			string file ;
			
			file = FileName(name) ; // 檔案完整名稱
			 
			ofstream out(file.c_str()) ; // 建立檔案 
			
			out << title << endl ; // 寫入標頭 
			
			for ( int i = 0 ; i < Joblist.size() ; i++ ) {
				// 寫入資料 
				
				out << Joblist.at(i).OID << "\t" ;
				out << Joblist.at(i).arrival << "\t" ;
				out << Joblist.at(i).duration << "\t" ;
				out << Joblist.at(i).timeOut ;
				if ( i != Joblist.size() - 1 )
					out << endl ;
				
			} // for
			
			out.close() ; // 關檔 
			
		} // WriteFile
		
		void SortData() {
		// 希爾德排序 
        	
        	for ( int gap = Joblist.size() / 2 ; gap > 0 ; gap /= 2 ) {
        		// 先找出總資料的一半，並從資料的一半開始
            	for ( int i = gap ; i < Joblist.size() ; i++ ) {
                	vector<Type> temp ; 
                	temp.push_back(Joblist.at(i)) ;
                	// 以免資料跑掉所以先存入temp裡面 
                	
                	int j ;
                	for ( j = i ; j >= gap && Joblist.at(j-gap).arrival > temp.at(0).arrival ; j -= gap )
                		// 找出正確的位置並交換資料 
                        swap(Joblist[j], Joblist[j-gap]) ;
                	
                	swap(Joblist[j], temp[0]) ;
                	// 讓temp放回原來正確的位置 
                	temp.clear() ;
				} // for
        	} // for
        	
        	SortOID() ; // 交換OID 
			
		} // SortData
		
		void PrintAll() {
		// 去印出全部的資料 
			
			cout << endl << "\t" << title << endl ;
			
			for ( int i = 0 ; i < Joblist.size() ; i++ ) {
				
				cout << "(" << i+1 << ")" ; 
				cout << "\t" << Joblist.at(i).OID ;
				cout << "\t" << Joblist.at(i).arrival ;
				cout << "\t" << Joblist.at(i).duration ;
				cout << "\t" << Joblist.at(i).timeOut << endl ;
				
			} // for
			
		} // PrintAll
		
		Type GetData( int i ) {
		// 取得指定位置的資料 
			
			return Joblist.at(i) ;
			
		} // GetData
		
		void DeletData( int i ) {
		// 刪除指定位置的資料 
			
			Joblist.erase( Joblist.begin() + i ) ; 
			
		} // DeleteData
		
		int GetNum() {
		// 取得工作清單數目 
			
			return JobNum ;
			
		} // GetNum 
		
		bool isEmpty() {
		// 是否為空 
			
			if ( Joblist.size() == 0 ) return true ;
			return false ;
			
		} // isEmpty
		
		~JobList() {
			
			Joblist.clear() ; 
			
		} // destructor 
		 
}; // JobList

class Queue {   // 佇列
	
	vector<Type> Q ;
	
	public :
		
		bool isFull() {
			// 檢查空間是否為最大值 
			
			if ( Q.size() == 3 ) return true ;
			return false ;
			
		} // isFull
		
		bool isEmpty() {
			// 檢查是否為空的 
			
			if ( Q.size() == 0 ) return true ;
			return false ;
			
		} // isEmpty
		
		void enQueue( Type type ) {
			// 放入資料 
			
			Q.push_back(type) ;
			
		} // Put
		
		Type getFront() {
			// 取得資料 
			
			return Q.at(0) ;
			
		} // Get
		
		void deQueue() {
			// 刪除資料 
			
			Q.erase(Q.begin()) ;
			
		} // Delete
		
		int GetSize() {
			// 取得長度 
			
			return Q.size() ;
			
		} // Size
		
		void PrintQ() {
			
			for ( int i = 0 ; i < Q.size() ; i++ )
				cout << Q.at(i).OID << ", " ;
				
			cout << endl ;
			
		} // debug

}; // Queue

class Work : public JobList {
	
	vector<Type> Abort ;    // 取消訂單
	vector<Type> TimeOut ;  // 逾時訂單 
	
	int totalDelay() {
		// 計算總Delay 
		
		int time = 0 ;
		
		for ( int i = 0 ; i < Abort.size() ; i++ ) {
			time = time + Abort.at(i).delay ;
		} // for
		
		for ( int i = 0 ; i < TimeOut.size() ; i++ ) {
			time = time + TimeOut.at(i).delay ;
		} // for
		
		return time ;
		
	} // totalDelay
	
	double persentage() {
		// 計算失敗率 
		
		return (double)(Abort.size() + TimeOut.size()) / GetNum() * 100 ;
		
	} // persentage
	
	void WriteFinishFile( string name ) {
		// 寫出模擬完的檔案( 無CID版本 ) 
		 	
		string file ; // 存檔案名稱 
			
		file = FileName(name) ; // 檔案完整名稱
			 
		ofstream out(file.c_str()) ; // 建立檔案 
			
		out << "\t[Abort List]" << endl ; // 寫入標頭
		out << "\tOID\tDelay\tAbort" << endl ; // 寫入標頭
			
		for ( int i = 0 ; i < Abort.size() ; i++ ) {
			// 寫入取消清單 
				
			out << "[" << i+1 << "]" << "\t" ;
			out << Abort.at(i).OID << "\t" ;
			out << Abort.at(i).delay << "\t" ;
			out << Abort.at(i).abort << endl ; 
				
		} // for
			
		out << "\t[Timeout List]" << endl ; // 寫入標頭
		out << "\tOID\tDelay\tDeparture" << endl ; // 寫入標頭
			
		for ( int i = 0 ; i < TimeOut.size() ; i++ ) {
			// 寫入逾時清單 
				
			out << "[" << i+1 << "]" << "\t" ;
			out << TimeOut.at(i).OID << "\t" ;
			out << TimeOut.at(i).delay << "\t" ;
			out << TimeOut.at(i).departure << endl ; 
				
		} // for
			
		out << "[Total Delay]" << endl ;
		out << totalDelay() << " min." << endl ; // 寫入總 Delay 
			
		out << "[Failure Persentage]" << endl ;
		out << fixed << setprecision(2) << persentage() << " %" << endl ; // 寫入失敗率 
			
		out.close() ; // 關檔
		 	
	} // WriteFinishFile
	
	public :
		 
		void PutAbort( Type type ) {
			// 放入取消清單 
			
			Abort.push_back(type) ;
		 	
		} // PutAbort
		 
		void PutTimeOut(Type type) {
		 	// 放入逾時清單
	
		 	TimeOut.push_back(type) ;
		 	
		} // PutTimeOut
		
		void WriteFinishFile( string name, int CID ) {
		 	// 寫出模擬完的檔案(有CID版本的)
		 	
		 	if ( CID == 1 ) { // 若廚師只有一位，就不用CID 
		 		WriteFinishFile(name) ;
		 		return ;
			} // if
		 	
		 	if ( CID == 2 )
		 		name = "two" ;
		 	
		 	string file ; // 存檔案名稱 
			
			file = FileName(name) ; // 檔案完整名稱
			 
			ofstream out(file.c_str()) ; // 建立檔案 
			
			out << "\t[Abort List]" << endl ; // 寫入標頭
			out << "\tOID\tCID\tDelay\tAbort" << endl ; // 寫入標頭
			
			for ( int i = 0 ; i < Abort.size() ; i++ ) {
				// 寫入取消清單 
				
				out << "[" << i+1 << "]" << "\t" ;
				out << Abort.at(i).OID << "\t" ;
				out << Abort.at(i).CID << "\t" ;
				out << Abort.at(i).delay << "\t" ;
				out << Abort.at(i).abort << endl ; 
				
			} // for
			
			out << "\t[Timeout List]" << endl ; // 寫入標頭
			out << "\tOID\tCID\tDelay\tDeparture" << endl ; // 寫入標頭 
			
			for ( int i = 0 ; i < TimeOut.size() ; i++ ) {
				// 寫入逾時清單 
				
				out << "[" << i+1 << "]" << "\t" ;
				out << TimeOut.at(i).OID << "\t" ;
				out << TimeOut.at(i).CID << "\t" ;
				out << TimeOut.at(i).delay << "\t" ;
				out << TimeOut.at(i).departure << endl ; 
				
			} // for
			
			out << "[Total Delay]" << endl ;
			out << totalDelay() << " min." << endl ; // 寫入總 Delay 
			
			out << "[Failure Persentage]" << endl ;
			out << fixed << setprecision(2) << persentage() << " %" << endl ; // 寫入失敗率 
			
			out.close() ; // 關檔
		 	
		} // WriteFinishFile
		 
		~Work() {
		 	
			Abort.clear() ;
		 	TimeOut.clear() ;
		 	
		} // destructor
	
}; // Work

class Cook {
	
	Type cook ;             // 廚師
	int time ;              // 閒置時間
	
	public :
		
		Cook() {
			
			cook = {0} ; 
			time = 0 ;
			
		} // constructor
		
		void SetWork( Type type, int delay ) {
		 	// 派工作 
		 	 
		 	cook.OID = type.OID ;
		 	cook.arrival = type.arrival ;
		 	cook.timeOut = type.timeOut ;
		 	cook.delay = delay ;
		 	cook.departure = type.arrival + type.duration ;
		 	
		} // SetWork
		
		void SetCID( int CID ) {
			// 設定這是幾號廚師 
			
			cook.CID = CID ;
			
		} // SetCID
		 
		void SetTime( int t ) {
		 	// 設定閒置時間 
		 	
		 	time = t ;
		 	
		} // SetTime
		 
		int GetTime() {
		 	// 取得閒置時間 
		 	
		 	return time ;
		 	
		} // GetTime
		 
		Type GetCookData() {
		 	// 取得廚師手上的工作清單 
		 	
		 	return cook ;
		 	
		} // GetCookData
	
}; // Cook

class Simulation {
	
	vector<Queue> Q ;  // 多重佇列 
	vector<Cook> C  ;  // 多個廚師
	int CID         ;  // 廚師編號
	int total       ;  // 存輸入M
	
	void SetQueueWork( Type type, Work & W ) {
		// 處理Queue的工作 
			
		if ( type.timeOut <= C.at(CID-1).GetTime() ) {      // 若逾時時刻 <= 閒置時刻，取消
			type.abort = C.at(CID-1).GetTime() ;
			type.delay = type.abort - type.arrival ;
			W.PutAbort(type) ;
		} // if
		else if ( type.timeOut < C.at(CID-1).GetTime() + type.duration ) {
			// 若逾時時刻 < 閒置時刻 + 製作時間，寫入逾時清單
			type.delay = C.at(CID-1).GetTime() - type.arrival ;
			type.departure = type.arrival + type.delay + type.duration ;
			W.PutTimeOut(type) ;
			C.at(CID-1).SetTime(type.departure) ;            // 更新閒置時刻 
		} // else if
		else {                                     // 若以上都不是，廚師成功接單 
			if ( C.at(CID-1).GetTime() < type.arrival ) {    // 若閒置時刻 < 到達時刻 
				C.at(CID-1).SetWork(type, 0) ;               // delay = 0 
				C.at(CID-1).SetTime(type.arrival + type.duration) ; // 閒置時刻 = 到達時刻 + 完成時間 
			} // if
			else {                                 // 若閒置時刻 == 到達時刻 
				C.at(CID-1).SetWork(type, C.at(CID-1).GetTime() - type.arrival - type.duration) ; 
				// delay = 閒置時刻 + arrival + duration 
				C.at(CID-1).SetTime(C.at(CID-1).GetTime() + type.duration) ; // 閒置時刻 = 閒置時刻 + duration 
			} // else
		} // else
			
	} // SetQueueWork
	
	bool Find() {
		
		int min = 4 ; // min queue size
		
		for ( int i = 0 ; i < total ; i++ ) {
			// 先找出 Queue size 最小值 
			
			if ( min > Q.at(i).GetSize() )
				min = Q.at(i).GetSize() ;
			
		} // for
		
		if ( min == 3 ) return false ;
		// 看是否全部的 Queue 為滿的 
		
		for ( int i = 0 ; i < total ; i++ ) {
			// 找出代號最小的廚師 
			
			if ( min == Q.at(i).GetSize() ) {
				CID = i + 1 ; // 並設定廚師代碼 
				return true; 
			} // if
			
		} // for
		
		return false ;
		
	} // Find
	
	public :
		
		Simulation( int M ) {
			
			Cook cook ;
			Queue q ;
			
			for ( int i = 0 ; i < M ; i++ ) {
				
				C.push_back(cook) ;
				Q.push_back(q) ;
				
			} // for
			
			CID = 0 ;
			total = M ;
			
		} // constructor
		
		bool WorkToCook( Type type ) {
			// 廚師接工作

			for ( int i = 0 ; i < total ; i++ ) {
				
				if ( C.at(i).GetTime() <= type.arrival && Q.at(i).isEmpty() ) {
					// 若廚師閒置，且Queue沒清單 
					C.at(i).SetCID(i+1) ;
					C.at(i).SetWork(type, 0) ;
					C.at(i).SetTime(type.arrival + type.duration) ;	
					CID = i + 1 ;
					return true ;
				} // if
				
			} // for
			
			return false ;
			
		} // WorkToCook
		
		void takeWork( Type type, Work & w ) {
			// 從 Queue 拿工作給廚師
			
			Type list ; // Queue of work
			
			for ( int i = 0 ; i < total ; i++ ) {

				while ( C.at(i).GetTime() <= type.arrival && !Q.at(i).isEmpty() ) { 
					list = Q.at(i).getFront() ;       // 取出Queue的工作
					CID = i + 1 ;                     // 設定CID 
					SetQueueWork(list, w) ;           // 派工作
					Q.at(i).deQueue() ;               // 刪除已派的工作
				} // while
				
			} // for
			
		} // takeWork
		
		void SetQueue( Type type, Work & w ) {
			// 放入 Queue 
			// 若要取消，加入取消清單
			
			if ( Find() ) {
				type.CID = CID ;
				Q.at(CID-1).enQueue(type) ;
			} // if
			else {
				type.abort = type.arrival ;         // 取消時刻 = 下單時刻 
				type.delay = 0 ;                    // 延誤時間為 0
				type.CID = 0 ;                      // CID設為 0 
				w.PutAbort(type) ;                  // 加入取消清單
			} // else
			
		} // SetQueue
		
		void check( Work & w ) {
			
			Type list ;
			
			for ( int i = 0 ; i < total ; i++ ) {
				
				list = C.at(i).GetCookData() ;

				if ( list.timeOut < C.at(i).GetTime() + list.duration && Q.at(i).isEmpty() ) {
					list.delay = C.at(i).GetTime() - list.arrival ;
					list.departure = list.arrival + list.delay + list.duration ;
					w.PutTimeOut(list) ;
					C.at(i).SetTime(list.departure) ;
				} // if
				
			} // for
			
		} // check
		
		void lastWork( Work & w ) {
			// 做Queue剩下的工作
			Type list ;
			
			for ( int i = 0 ; i < total ; i++ ) {
			
				while ( !Q.at(i).isEmpty() ) {
					list = Q.at(i).getFront() ;     // 取出Queue的工作
					CID = i + 1 ;
					SetQueueWork(list, w) ;         // 派工作 
					Q.at(i).deQueue() ;             // 刪除已派的工作 
				} // while
				
			} // for
			
		} // lastWork
		
		void print() {
			
			Type list ;
			
			for ( int i = 0 ; i < total ; i++ ) {
				list = C.at(i).GetCookData() ;
				cout << i+1 << " : " << list.OID ;
				cout << "(" << C.at(i).GetTime() << ")" << endl ;
			} // for
			
			cout << endl << "Queue : " << endl ;
			
			for ( int i = 0 ; i < total ; i++ ) {
				cout << i+1 << " : " ;
				Q.at(i).PrintQ() ;
			} // for
			
			cout << "-----------------------" << endl ;
			
		} // debug
		
}; // Simulation

bool isDigit( string str ) {
// 判斷是否為數字 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

void SetQueueWork( Type type, Cook & C, Work & W ) {
		// 處理Queue的工作 
			
		if ( type.timeOut <= C.GetTime() ) {      // 若逾時時刻 <= 閒置時刻，取消
			type.abort = C.GetTime() ;
			type.delay = type.abort - type.arrival ;
			W.PutAbort(type) ;
		} // if
		else if ( type.timeOut < C.GetTime() + type.duration ) {
			// 若逾時時刻 < 閒置時刻 + 製作時間，寫入逾時清單
			type.delay = C.GetTime() - type.arrival ;
			type.departure = type.arrival + type.delay + type.duration ;
			W.PutTimeOut(type) ;
			C.SetTime(type.departure) ;            // 更新閒置時刻 
		} // else if
		else {                                     // 若以上都不是，廚師成功接單 
			if ( C.GetTime() < type.arrival ) {    // 若閒置時刻 < 到達時刻 
				C.SetWork(type, 0) ;               // delay = 0 
				C.SetTime(type.arrival + type.duration) ; // 閒置時刻 = 到達時刻 + 完成時間 
			} // if
			else {                                 // 若閒置時刻 == 到達時刻 
				C.SetWork(type, C.GetTime() - type.arrival - type.duration) ; 
				// delay = 閒置時刻 + arrival + duration 
				C.SetTime(C.GetTime() + type.duration) ; // 閒置時刻 = 閒置時刻 + duration 
			} // else
		} // else
			
} // SetQueueWork

void mission1() {
	// 任務一 
	
	JobList job ;    // 工作清單 
	clock_t cR ;     // 紀錄讀檔的時間 
	clock_t cS ;     // 紀錄排序的時間 
	clock_t cW ;     // 紀錄寫檔的時間
	
	cR = clock() ;          // 開始計算時間
	if ( job.ReadFile("input") ) { // 若讀檔案成功，做事 
		cR = clock() - cR ; // 結束計算時間
		
	    job.PrintAll() ;    // 印出讀進來的資料 
	
	    system("pause") ;
	    
	 	cS = clock() ;      // 開始計算時間
	    job.SortData() ;
	    cS = clock() - cS ; // 結束計算時間
	    
	    cW = clock() ;      // 開始計算時間
	    job.WriteFile("sort") ;
	    cW = clock() - cW ; // 結束計算時間 
	    
	    // 印出所有時間 
	    cout << endl << "Reading data : " << (int)cR/CLOCKS_PER_SEC << " clocks" ;
		cout << " (" << (double)cR/CLOCKS_PER_SEC << " ms)." << endl ;
		cout << endl << "Sorting data : " << (int)cS/CLOCKS_PER_SEC << " clocks" ;
		cout << " (" << (double)cS/CLOCKS_PER_SEC << " ms)." << endl ;
		cout << endl << "Writing data : " << (int)cW/CLOCKS_PER_SEC << " clocks" ;
		cout << " (" << (double)cW/CLOCKS_PER_SEC << " ms)." << endl ;
		
	    job.PrintAll() ; // 印出排序完的資料 
	
	    system("pause") ; 
	    
	} // if
	
	cR = clock() - cR ;  // 結束計算時間
	
} // mission1

void mission2() {
	// 任務二 
	
	Work work ;         // 工作清單 
	Cook C ;            // 廚師 
	Queue Q ;           // Queue 
	Type list = {0} ;   // 存JobList的Data 
	Type Q_list = {0} ; // 存Queue的Data 
	
	if ( work.ReadFile( "sort" ) ) { // 若讀檔案成功，做事 
		
		work.PrintAll() ; // 印出讀進來的資料 
		
		system("pause") ;

		while ( !work.isEmpty() ) {                       // 先派工作
			list = work.GetData(0) ;                      // 取出資料
			if ( C.GetTime() <= list.arrival && Q.GetSize() == 0 ) {             
			// 如果廚師是閒置，且Queue沒有訂單 
				C.SetWork(list, 0) ;                      // 派工作
				C.SetTime(list.arrival+list.duration) ;   // 設定閒置時刻
			} // if 
			else {                                        // 若廚師有工作
				while ( C.GetTime() <= list.arrival && !Q.isEmpty() ) {      
				// 若廚師做完訂單，且Queue有訂單 
					Q_list = Q.getFront() ;               // 取出Queue的工作
					SetQueueWork(Q_list, C, work) ;       // 派工作 
					Q.deQueue() ;                         // 刪除已派的工作 
				} // while
				
				if ( !Q.isFull() ) Q.enQueue(list) ;
				else {                                    // 若Queue滿，取消訂單 
					list.abort = list.arrival ;           // 取消時刻 = 下單時刻 
					list.delay = 0 ;                      // 延誤時間為 0 
					work.PutAbort(list) ;                 // 加入取消清單 
				} // else
			} // else
			
			work.DeletData(0) ;                           // 刪除取出的資料
 		} // while
		
		while ( !Q.isEmpty() ) {                          // 做Queue剩下的工作
			Q_list = Q.getFront() ;                       // 取出Queue的工作
			SetQueueWork( Q_list, C, work ) ;             // 派工作 
			Q.deQueue() ;                                 // 刪除已派的工作 
		} // while

		work.WriteFinishFile("one", 1) ;                  // 寫檔案
		
	} // if
	
} // mission2

void mission3() {
	// 任務三 
	
	Work work ;         // 工作清單 
	Cook cook1 ;        // 廚師 No1 
    Cook cook2 ;        // 廚師 No2 
	Queue Q1 ;          // Queue 1 
	Queue Q2 ;          // Queue 2
	Type list = {0} ;   // 存JobList的Data
	Type Q_list = {0} ; // 存Queue的Data
	
	if ( work.ReadFile( "sort" ) ) {    // 若讀檔案成功，做事 
		
		work.PrintAll() ;               // 印出讀到的資料 
		
		system("pause") ;
		
		while ( !work.isEmpty() ) {     // 先派工作
			list = work.GetData(0) ;    // 取出資料	 
				
			if ( cook1.GetTime() <= list.arrival && Q1.GetSize() == 0 ) {
				// 若廚師1閒置，且Queue沒清單，廚師1接工作 
				cook1.SetCID(1) ;
				cook1.SetWork(list, 0) ;
				cook1.SetTime(list.arrival + list.duration) ;
			} // if
			else if ( cook2.GetTime() <= list.arrival && Q2.GetSize() == 0 ) {
				// 若廚師2閒置，且Queue沒清單，廚師2接工作
				cook2.SetCID(2) ;
				cook2.SetWork(list, 0) ;
				cook2.SetTime(list.arrival + list.duration) ;
			} // else if
			else {
				// 若廚師1閒置，且Queue不為空 
				while ( cook1.GetTime() <= list.arrival && !Q1.isEmpty() ) {
					Q_list = Q1.getFront() ;            // 取出Queue的工作
					SetQueueWork(Q_list, cook1, work) ; // 派工作
					Q1.deQueue() ;                      // 刪除已派的工作 
				} // while
				
				// 若廚師2閒置，且Queue不為空
				while ( cook2.GetTime() <= list.arrival && !Q2.isEmpty() ) {
					Q_list = Q2.getFront() ;            // 取出Queue的工作
					SetQueueWork(Q_list, cook2, work) ; // 派工作 
					Q2.deQueue() ;                      // 刪除已派的工作 
				} // while
				
				if ( Q1.GetSize() < Q2.GetSize() ) { 
					// 找出哪位廚師的Queue數量比較少，就把清單給他 
					list.CID = 1 ;
					Q1.enQueue(list) ;
				} // if
				else if ( Q1.GetSize() > Q2.GetSize() ) {
					// 找出哪位廚師的Queue數量比較少，就把清單給他
					list.CID = 2 ;
					Q2.enQueue(list) ;
				} // else if
				else if ( Q1.isFull() && Q2.isFull() ) {
					// 若廚師的Queue都是滿的，直接取消 
					list.abort = list.arrival ;         // 取消時刻 = 下單時刻 
					list.delay = 0 ;                    // 延誤時間為 0
					list.CID = 0 ;                      // CID設為 0 
					work.PutAbort(list) ;               // 加入取消清單 
				} // else if
				else if ( Q1.GetSize() == Q2.GetSize() ) {
					// 若廚師的Queue的數量相同，且都不為滿的，給代號最小的廚師 
					list.CID = 1 ;
					Q1.enQueue(list) ;
				} // else if
			} // else

			work.DeletData(0) ;                         // 刪除取出的工作 
		} // while
		 
		while ( !Q1.isEmpty() ) {                       // 做Queue剩下的工作
			Q_list = Q1.getFront() ;                    // 取出Queue的工作
			SetQueueWork(Q_list, cook1, work) ;         // 派工作 
			Q1.deQueue() ;                              // 刪除已派的工作 
		} // while
		 
		while ( !Q2.isEmpty() ) {                       // 做Queue剩下的工作
			Q_list = Q2.getFront() ;                    // 取出Queue的工作
			SetQueueWork(Q_list, cook2, work) ;         // 派工作 
			Q2.deQueue() ;                              // 刪除已派的工作 
		} // while
		
		work.WriteFinishFile("two", 2) ;                // 寫入檔案
 
	} // if
	
} // mission3

void mission4() {
	
	string Q_Num ;      // number of queue
	int M = 0 ;
	
	Work work ;         // 工作清單
	Type list = {0} ;   // 存JobList的Data  
	
	if ( work.ReadFile( "sort" ) ) {    // 若讀檔案成功，做事
	
		do {                            // 讀入多少個廚師 
	
	    	cout << endl << "Input the number of queue : " ;
			cin >> Q_Num ;
		
			if ( isDigit(Q_Num) ) {        // 是否為int 
				M = atoi(Q_Num.c_str()) ;  // str to int
		
				if ( !(M >= 1 && M <= 9) )
					cout << endl << "### It is NOT in [1, 9] ###" << endl ;
			} // if

		} while ( !(M >= 1 && M <= 9) ) ;
		
		Simulation S(M) ; // 模擬，並設定廚師數量 
		
		work.PrintAll() ; // 印出讀到的資料 
		
		system("pause") ;
		
		while ( !work.isEmpty() ) {      // 先派工作
			list = work.GetData(0) ;     // 取出資料	
			
			if ( !S.WorkToCook(list) ) { // 若廚師沒有接單
				S.takeWork(list, work) ; // Queue -> cook
				S.SetQueue(list, work) ; // list -> Queue
			} // if
			else 
				S.takeWork(list, work) ; // Queue -> cook
				
			//S.print() ;
			work.DeletData(0) ;          // 刪除資料
		} // while 
		
		S.check(work) ;
		
		S.lastWork(work) ;
		
		work.WriteFinishFile("more", M) ; // 寫入檔案
		
	} // if
	
} // mission4

int main() {
	
	string command = "/0" ; // 讀取指令 
	int cd = -1 ;           // int的指令 
	
	do { 
	
		cout << endl << "**** Simulate FIFO Queues by SQF ****" ;
		cout << endl << "* 0. Quit                           *" ;
		cout << endl << "* 1. Sort a file                    *" ;
		cout << endl << "* 2. Simulate one FIFO queue        *" ;
		cout << endl << "* 3. Simulate two queues by SQF     *" ;
		cout << endl << "* 4. Simulate mutiple queues by SQF *" ;
		cout << endl << "*************************************" ;
		cout << endl << "Input a command(0, 1, 2, 3, 4) : " ;
		cin >> command ;
		
		if ( isDigit(command) ) // 是否為int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) mission1() ; // 進入任務一 
		else if ( cd == 2 ) mission2() ; // 進入任務二 
		else if ( cd == 3 ) mission3() ; // 進入任務三
		else if ( cd == 4 ) mission4() ; // 進入任務四 
		else cout << endl << "Command is NOT exist !!" << endl ; // 無此指令 
		
	} while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
