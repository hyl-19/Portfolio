// 07�� 11027212 ���ض� 11027222 �����M
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
		 
		int OID ;       // �q��s�� 
		int arrival ;   // �U��ɨ� 
		int duration ;  // �s�@�Ӯ�
		int timeOut ;   // �O�ɮɨ�
		
		int CID ;       // �p�v�s�� 
		int delay ;     // ���~�ɶ�
		int abort ;     // �����ɨ�
		int departure ; // �����ɨ�
		
		// delay = abort - arrival
		// departure = arrival + delay + duration
	
}; // Type
	
class JobList {
	
	vector<Type> Joblist ;  // �s�u�@�M�� 
	string ID ;             // �s�ɮץN�X
	string title ;          // �s���Y
	int JobNum ;            // �X�Ӥu�@�M��ƥ� 
	
	void SetNum() {
		// �]�w���� 
		
		JobNum = Joblist.size() ;
		
	} // SetNum
	
	void SortOID() {
		// ��OID�i��ƺ��w�Ƨ� 
		
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
		// �^�ǧ��㪺 file name
		
			return str + ID + ".txt" ;
		
		} // FileName
		
		bool ReadFile( string name ) {
		// �s�� file �̪� data
		
			ifstream in ;
			string file ; // �ɮצW�� 
			Type type ;   // ��� 
			Type temp ;   // �s�W�@����� 
			
    		cout << endl << "Input a file number (e.g. 401, 402, 403, ... ) :" ;
    		cin >> ID ; // Ū�J�ɮץN�X 

    		file = FileName(name) ; // �ɮק���W�� 
    			
    		in.open(file.c_str(), ios::in) ; // �bŪ�J�Ҧ��U�}��in�ɮ�
    	
    		if ( !in.is_open() ) { // �䤣�즹�ɮ� 
				cout << endl << "### input" << ID << ".txt does NOT exist! ###" << endl ;
				return false ;
			} // if
			else {
				
				getline(in, title) ; // Ū�J���Y
				
				do {
					in >> type.OID >> type.arrival >> type.duration >> type.timeOut ; // Ū�����
					if ( type.OID != temp.OID )   // �H�K�����ƪ���� 
						Joblist.push_back(type) ; // �s�J���
					temp = type ;
				} while ( !in.eof() ) ;
				
			} // else
			
			SetNum() ;   // ��XŪ�F�X����� 
			in.close() ; // ���� 
			return true ;
			
		} // ReadFile
		
		void WriteFile( string name ) {
			// �g�ɮ� str ���ɮצW�� 
			
			string file ;
			
			file = FileName(name) ; // �ɮק���W��
			 
			ofstream out(file.c_str()) ; // �إ��ɮ� 
			
			out << title << endl ; // �g�J���Y 
			
			for ( int i = 0 ; i < Joblist.size() ; i++ ) {
				// �g�J��� 
				
				out << Joblist.at(i).OID << "\t" ;
				out << Joblist.at(i).arrival << "\t" ;
				out << Joblist.at(i).duration << "\t" ;
				out << Joblist.at(i).timeOut ;
				if ( i != Joblist.size() - 1 )
					out << endl ;
				
			} // for
			
			out.close() ; // ���� 
			
		} // WriteFile
		
		void SortData() {
		// �ƺ��w�Ƨ� 
        	
        	for ( int gap = Joblist.size() / 2 ; gap > 0 ; gap /= 2 ) {
        		// ����X�`��ƪ��@�b�A�ñq��ƪ��@�b�}�l
            	for ( int i = gap ; i < Joblist.size() ; i++ ) {
                	vector<Type> temp ; 
                	temp.push_back(Joblist.at(i)) ;
                	// �H�K��ƶ]���ҥH���s�Jtemp�̭� 
                	
                	int j ;
                	for ( j = i ; j >= gap && Joblist.at(j-gap).arrival > temp.at(0).arrival ; j -= gap )
                		// ��X���T����m�å洫��� 
                        swap(Joblist[j], Joblist[j-gap]) ;
                	
                	swap(Joblist[j], temp[0]) ;
                	// ��temp��^��ӥ��T����m 
                	temp.clear() ;
				} // for
        	} // for
        	
        	SortOID() ; // �洫OID 
			
		} // SortData
		
		void PrintAll() {
		// �h�L�X��������� 
			
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
		// ���o���w��m����� 
			
			return Joblist.at(i) ;
			
		} // GetData
		
		void DeletData( int i ) {
		// �R�����w��m����� 
			
			Joblist.erase( Joblist.begin() + i ) ; 
			
		} // DeleteData
		
		int GetNum() {
		// ���o�u�@�M��ƥ� 
			
			return JobNum ;
			
		} // GetNum 
		
		bool isEmpty() {
		// �O�_���� 
			
			if ( Joblist.size() == 0 ) return true ;
			return false ;
			
		} // isEmpty
		
		~JobList() {
			
			Joblist.clear() ; 
			
		} // destructor 
		 
}; // JobList

class Queue {   // ��C
	
	vector<Type> Q ;
	
	public :
		
		bool isFull() {
			// �ˬd�Ŷ��O�_���̤j�� 
			
			if ( Q.size() == 3 ) return true ;
			return false ;
			
		} // isFull
		
		bool isEmpty() {
			// �ˬd�O�_���Ū� 
			
			if ( Q.size() == 0 ) return true ;
			return false ;
			
		} // isEmpty
		
		void enQueue( Type type ) {
			// ��J��� 
			
			Q.push_back(type) ;
			
		} // Put
		
		Type getFront() {
			// ���o��� 
			
			return Q.at(0) ;
			
		} // Get
		
		void deQueue() {
			// �R����� 
			
			Q.erase(Q.begin()) ;
			
		} // Delete
		
		int GetSize() {
			// ���o���� 
			
			return Q.size() ;
			
		} // Size
		
		void PrintQ() {
			
			for ( int i = 0 ; i < Q.size() ; i++ )
				cout << Q.at(i).OID << ", " ;
				
			cout << endl ;
			
		} // debug

}; // Queue

class Work : public JobList {
	
	vector<Type> Abort ;    // �����q��
	vector<Type> TimeOut ;  // �O�ɭq�� 
	
	int totalDelay() {
		// �p���`Delay 
		
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
		// �p�⥢�Ѳv 
		
		return (double)(Abort.size() + TimeOut.size()) / GetNum() * 100 ;
		
	} // persentage
	
	void WriteFinishFile( string name ) {
		// �g�X���������ɮ�( �LCID���� ) 
		 	
		string file ; // �s�ɮצW�� 
			
		file = FileName(name) ; // �ɮק���W��
			 
		ofstream out(file.c_str()) ; // �إ��ɮ� 
			
		out << "\t[Abort List]" << endl ; // �g�J���Y
		out << "\tOID\tDelay\tAbort" << endl ; // �g�J���Y
			
		for ( int i = 0 ; i < Abort.size() ; i++ ) {
			// �g�J�����M�� 
				
			out << "[" << i+1 << "]" << "\t" ;
			out << Abort.at(i).OID << "\t" ;
			out << Abort.at(i).delay << "\t" ;
			out << Abort.at(i).abort << endl ; 
				
		} // for
			
		out << "\t[Timeout List]" << endl ; // �g�J���Y
		out << "\tOID\tDelay\tDeparture" << endl ; // �g�J���Y
			
		for ( int i = 0 ; i < TimeOut.size() ; i++ ) {
			// �g�J�O�ɲM�� 
				
			out << "[" << i+1 << "]" << "\t" ;
			out << TimeOut.at(i).OID << "\t" ;
			out << TimeOut.at(i).delay << "\t" ;
			out << TimeOut.at(i).departure << endl ; 
				
		} // for
			
		out << "[Total Delay]" << endl ;
		out << totalDelay() << " min." << endl ; // �g�J�` Delay 
			
		out << "[Failure Persentage]" << endl ;
		out << fixed << setprecision(2) << persentage() << " %" << endl ; // �g�J���Ѳv 
			
		out.close() ; // ����
		 	
	} // WriteFinishFile
	
	public :
		 
		void PutAbort( Type type ) {
			// ��J�����M�� 
			
			Abort.push_back(type) ;
		 	
		} // PutAbort
		 
		void PutTimeOut(Type type) {
		 	// ��J�O�ɲM��
	
		 	TimeOut.push_back(type) ;
		 	
		} // PutTimeOut
		
		void WriteFinishFile( string name, int CID ) {
		 	// �g�X���������ɮ�(��CID������)
		 	
		 	if ( CID == 1 ) { // �Y�p�v�u���@��A�N����CID 
		 		WriteFinishFile(name) ;
		 		return ;
			} // if
		 	
		 	if ( CID == 2 )
		 		name = "two" ;
		 	
		 	string file ; // �s�ɮצW�� 
			
			file = FileName(name) ; // �ɮק���W��
			 
			ofstream out(file.c_str()) ; // �إ��ɮ� 
			
			out << "\t[Abort List]" << endl ; // �g�J���Y
			out << "\tOID\tCID\tDelay\tAbort" << endl ; // �g�J���Y
			
			for ( int i = 0 ; i < Abort.size() ; i++ ) {
				// �g�J�����M�� 
				
				out << "[" << i+1 << "]" << "\t" ;
				out << Abort.at(i).OID << "\t" ;
				out << Abort.at(i).CID << "\t" ;
				out << Abort.at(i).delay << "\t" ;
				out << Abort.at(i).abort << endl ; 
				
			} // for
			
			out << "\t[Timeout List]" << endl ; // �g�J���Y
			out << "\tOID\tCID\tDelay\tDeparture" << endl ; // �g�J���Y 
			
			for ( int i = 0 ; i < TimeOut.size() ; i++ ) {
				// �g�J�O�ɲM�� 
				
				out << "[" << i+1 << "]" << "\t" ;
				out << TimeOut.at(i).OID << "\t" ;
				out << TimeOut.at(i).CID << "\t" ;
				out << TimeOut.at(i).delay << "\t" ;
				out << TimeOut.at(i).departure << endl ; 
				
			} // for
			
			out << "[Total Delay]" << endl ;
			out << totalDelay() << " min." << endl ; // �g�J�` Delay 
			
			out << "[Failure Persentage]" << endl ;
			out << fixed << setprecision(2) << persentage() << " %" << endl ; // �g�J���Ѳv 
			
			out.close() ; // ����
		 	
		} // WriteFinishFile
		 
		~Work() {
		 	
			Abort.clear() ;
		 	TimeOut.clear() ;
		 	
		} // destructor
	
}; // Work

class Cook {
	
	Type cook ;             // �p�v
	int time ;              // ���m�ɶ�
	
	public :
		
		Cook() {
			
			cook = {0} ; 
			time = 0 ;
			
		} // constructor
		
		void SetWork( Type type, int delay ) {
		 	// ���u�@ 
		 	 
		 	cook.OID = type.OID ;
		 	cook.arrival = type.arrival ;
		 	cook.timeOut = type.timeOut ;
		 	cook.delay = delay ;
		 	cook.departure = type.arrival + type.duration ;
		 	
		} // SetWork
		
		void SetCID( int CID ) {
			// �]�w�o�O�X���p�v 
			
			cook.CID = CID ;
			
		} // SetCID
		 
		void SetTime( int t ) {
		 	// �]�w���m�ɶ� 
		 	
		 	time = t ;
		 	
		} // SetTime
		 
		int GetTime() {
		 	// ���o���m�ɶ� 
		 	
		 	return time ;
		 	
		} // GetTime
		 
		Type GetCookData() {
		 	// ���o�p�v��W���u�@�M�� 
		 	
		 	return cook ;
		 	
		} // GetCookData
	
}; // Cook

class Simulation {
	
	vector<Queue> Q ;  // �h����C 
	vector<Cook> C  ;  // �h�Ӽp�v
	int CID         ;  // �p�v�s��
	int total       ;  // �s��JM
	
	void SetQueueWork( Type type, Work & W ) {
		// �B�zQueue���u�@ 
			
		if ( type.timeOut <= C.at(CID-1).GetTime() ) {      // �Y�O�ɮɨ� <= ���m�ɨ�A����
			type.abort = C.at(CID-1).GetTime() ;
			type.delay = type.abort - type.arrival ;
			W.PutAbort(type) ;
		} // if
		else if ( type.timeOut < C.at(CID-1).GetTime() + type.duration ) {
			// �Y�O�ɮɨ� < ���m�ɨ� + �s�@�ɶ��A�g�J�O�ɲM��
			type.delay = C.at(CID-1).GetTime() - type.arrival ;
			type.departure = type.arrival + type.delay + type.duration ;
			W.PutTimeOut(type) ;
			C.at(CID-1).SetTime(type.departure) ;            // ��s���m�ɨ� 
		} // else if
		else {                                     // �Y�H�W�����O�A�p�v���\���� 
			if ( C.at(CID-1).GetTime() < type.arrival ) {    // �Y���m�ɨ� < ��F�ɨ� 
				C.at(CID-1).SetWork(type, 0) ;               // delay = 0 
				C.at(CID-1).SetTime(type.arrival + type.duration) ; // ���m�ɨ� = ��F�ɨ� + �����ɶ� 
			} // if
			else {                                 // �Y���m�ɨ� == ��F�ɨ� 
				C.at(CID-1).SetWork(type, C.at(CID-1).GetTime() - type.arrival - type.duration) ; 
				// delay = ���m�ɨ� + arrival + duration 
				C.at(CID-1).SetTime(C.at(CID-1).GetTime() + type.duration) ; // ���m�ɨ� = ���m�ɨ� + duration 
			} // else
		} // else
			
	} // SetQueueWork
	
	bool Find() {
		
		int min = 4 ; // min queue size
		
		for ( int i = 0 ; i < total ; i++ ) {
			// ����X Queue size �̤p�� 
			
			if ( min > Q.at(i).GetSize() )
				min = Q.at(i).GetSize() ;
			
		} // for
		
		if ( min == 3 ) return false ;
		// �ݬO�_������ Queue ������ 
		
		for ( int i = 0 ; i < total ; i++ ) {
			// ��X�N���̤p���p�v 
			
			if ( min == Q.at(i).GetSize() ) {
				CID = i + 1 ; // �ó]�w�p�v�N�X 
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
			// �p�v���u�@

			for ( int i = 0 ; i < total ; i++ ) {
				
				if ( C.at(i).GetTime() <= type.arrival && Q.at(i).isEmpty() ) {
					// �Y�p�v���m�A�BQueue�S�M�� 
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
			// �q Queue ���u�@���p�v
			
			Type list ; // Queue of work
			
			for ( int i = 0 ; i < total ; i++ ) {

				while ( C.at(i).GetTime() <= type.arrival && !Q.at(i).isEmpty() ) { 
					list = Q.at(i).getFront() ;       // ���XQueue���u�@
					CID = i + 1 ;                     // �]�wCID 
					SetQueueWork(list, w) ;           // ���u�@
					Q.at(i).deQueue() ;               // �R���w�����u�@
				} // while
				
			} // for
			
		} // takeWork
		
		void SetQueue( Type type, Work & w ) {
			// ��J Queue 
			// �Y�n�����A�[�J�����M��
			
			if ( Find() ) {
				type.CID = CID ;
				Q.at(CID-1).enQueue(type) ;
			} // if
			else {
				type.abort = type.arrival ;         // �����ɨ� = �U��ɨ� 
				type.delay = 0 ;                    // ���~�ɶ��� 0
				type.CID = 0 ;                      // CID�]�� 0 
				w.PutAbort(type) ;                  // �[�J�����M��
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
			// ��Queue�ѤU���u�@
			Type list ;
			
			for ( int i = 0 ; i < total ; i++ ) {
			
				while ( !Q.at(i).isEmpty() ) {
					list = Q.at(i).getFront() ;     // ���XQueue���u�@
					CID = i + 1 ;
					SetQueueWork(list, w) ;         // ���u�@ 
					Q.at(i).deQueue() ;             // �R���w�����u�@ 
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
// �P�_�O�_���Ʀr 
	
	for ( int i = 0 ; i < str.size() ; i++ ) {
		
		if ( !('0' <= str[i] && str[i] <= '9') ) 
			return false ;
		
	} // for
	
	return true ;
	
} // isDigit

void SetQueueWork( Type type, Cook & C, Work & W ) {
		// �B�zQueue���u�@ 
			
		if ( type.timeOut <= C.GetTime() ) {      // �Y�O�ɮɨ� <= ���m�ɨ�A����
			type.abort = C.GetTime() ;
			type.delay = type.abort - type.arrival ;
			W.PutAbort(type) ;
		} // if
		else if ( type.timeOut < C.GetTime() + type.duration ) {
			// �Y�O�ɮɨ� < ���m�ɨ� + �s�@�ɶ��A�g�J�O�ɲM��
			type.delay = C.GetTime() - type.arrival ;
			type.departure = type.arrival + type.delay + type.duration ;
			W.PutTimeOut(type) ;
			C.SetTime(type.departure) ;            // ��s���m�ɨ� 
		} // else if
		else {                                     // �Y�H�W�����O�A�p�v���\���� 
			if ( C.GetTime() < type.arrival ) {    // �Y���m�ɨ� < ��F�ɨ� 
				C.SetWork(type, 0) ;               // delay = 0 
				C.SetTime(type.arrival + type.duration) ; // ���m�ɨ� = ��F�ɨ� + �����ɶ� 
			} // if
			else {                                 // �Y���m�ɨ� == ��F�ɨ� 
				C.SetWork(type, C.GetTime() - type.arrival - type.duration) ; 
				// delay = ���m�ɨ� + arrival + duration 
				C.SetTime(C.GetTime() + type.duration) ; // ���m�ɨ� = ���m�ɨ� + duration 
			} // else
		} // else
			
} // SetQueueWork

void mission1() {
	// ���Ȥ@ 
	
	JobList job ;    // �u�@�M�� 
	clock_t cR ;     // ����Ū�ɪ��ɶ� 
	clock_t cS ;     // �����ƧǪ��ɶ� 
	clock_t cW ;     // �����g�ɪ��ɶ�
	
	cR = clock() ;          // �}�l�p��ɶ�
	if ( job.ReadFile("input") ) { // �YŪ�ɮצ��\�A���� 
		cR = clock() - cR ; // �����p��ɶ�
		
	    job.PrintAll() ;    // �L�XŪ�i�Ӫ���� 
	
	    system("pause") ;
	    
	 	cS = clock() ;      // �}�l�p��ɶ�
	    job.SortData() ;
	    cS = clock() - cS ; // �����p��ɶ�
	    
	    cW = clock() ;      // �}�l�p��ɶ�
	    job.WriteFile("sort") ;
	    cW = clock() - cW ; // �����p��ɶ� 
	    
	    // �L�X�Ҧ��ɶ� 
	    cout << endl << "Reading data : " << (int)cR/CLOCKS_PER_SEC << " clocks" ;
		cout << " (" << (double)cR/CLOCKS_PER_SEC << " ms)." << endl ;
		cout << endl << "Sorting data : " << (int)cS/CLOCKS_PER_SEC << " clocks" ;
		cout << " (" << (double)cS/CLOCKS_PER_SEC << " ms)." << endl ;
		cout << endl << "Writing data : " << (int)cW/CLOCKS_PER_SEC << " clocks" ;
		cout << " (" << (double)cW/CLOCKS_PER_SEC << " ms)." << endl ;
		
	    job.PrintAll() ; // �L�X�Ƨǧ������ 
	
	    system("pause") ; 
	    
	} // if
	
	cR = clock() - cR ;  // �����p��ɶ�
	
} // mission1

void mission2() {
	// ���ȤG 
	
	Work work ;         // �u�@�M�� 
	Cook C ;            // �p�v 
	Queue Q ;           // Queue 
	Type list = {0} ;   // �sJobList��Data 
	Type Q_list = {0} ; // �sQueue��Data 
	
	if ( work.ReadFile( "sort" ) ) { // �YŪ�ɮצ��\�A���� 
		
		work.PrintAll() ; // �L�XŪ�i�Ӫ���� 
		
		system("pause") ;

		while ( !work.isEmpty() ) {                       // �����u�@
			list = work.GetData(0) ;                      // ���X���
			if ( C.GetTime() <= list.arrival && Q.GetSize() == 0 ) {             
			// �p�G�p�v�O���m�A�BQueue�S���q�� 
				C.SetWork(list, 0) ;                      // ���u�@
				C.SetTime(list.arrival+list.duration) ;   // �]�w���m�ɨ�
			} // if 
			else {                                        // �Y�p�v���u�@
				while ( C.GetTime() <= list.arrival && !Q.isEmpty() ) {      
				// �Y�p�v�����q��A�BQueue���q�� 
					Q_list = Q.getFront() ;               // ���XQueue���u�@
					SetQueueWork(Q_list, C, work) ;       // ���u�@ 
					Q.deQueue() ;                         // �R���w�����u�@ 
				} // while
				
				if ( !Q.isFull() ) Q.enQueue(list) ;
				else {                                    // �YQueue���A�����q�� 
					list.abort = list.arrival ;           // �����ɨ� = �U��ɨ� 
					list.delay = 0 ;                      // ���~�ɶ��� 0 
					work.PutAbort(list) ;                 // �[�J�����M�� 
				} // else
			} // else
			
			work.DeletData(0) ;                           // �R�����X�����
 		} // while
		
		while ( !Q.isEmpty() ) {                          // ��Queue�ѤU���u�@
			Q_list = Q.getFront() ;                       // ���XQueue���u�@
			SetQueueWork( Q_list, C, work ) ;             // ���u�@ 
			Q.deQueue() ;                                 // �R���w�����u�@ 
		} // while

		work.WriteFinishFile("one", 1) ;                  // �g�ɮ�
		
	} // if
	
} // mission2

void mission3() {
	// ���ȤT 
	
	Work work ;         // �u�@�M�� 
	Cook cook1 ;        // �p�v No1 
    Cook cook2 ;        // �p�v No2 
	Queue Q1 ;          // Queue 1 
	Queue Q2 ;          // Queue 2
	Type list = {0} ;   // �sJobList��Data
	Type Q_list = {0} ; // �sQueue��Data
	
	if ( work.ReadFile( "sort" ) ) {    // �YŪ�ɮצ��\�A���� 
		
		work.PrintAll() ;               // �L�XŪ�쪺��� 
		
		system("pause") ;
		
		while ( !work.isEmpty() ) {     // �����u�@
			list = work.GetData(0) ;    // ���X���	 
				
			if ( cook1.GetTime() <= list.arrival && Q1.GetSize() == 0 ) {
				// �Y�p�v1���m�A�BQueue�S�M��A�p�v1���u�@ 
				cook1.SetCID(1) ;
				cook1.SetWork(list, 0) ;
				cook1.SetTime(list.arrival + list.duration) ;
			} // if
			else if ( cook2.GetTime() <= list.arrival && Q2.GetSize() == 0 ) {
				// �Y�p�v2���m�A�BQueue�S�M��A�p�v2���u�@
				cook2.SetCID(2) ;
				cook2.SetWork(list, 0) ;
				cook2.SetTime(list.arrival + list.duration) ;
			} // else if
			else {
				// �Y�p�v1���m�A�BQueue������ 
				while ( cook1.GetTime() <= list.arrival && !Q1.isEmpty() ) {
					Q_list = Q1.getFront() ;            // ���XQueue���u�@
					SetQueueWork(Q_list, cook1, work) ; // ���u�@
					Q1.deQueue() ;                      // �R���w�����u�@ 
				} // while
				
				// �Y�p�v2���m�A�BQueue������
				while ( cook2.GetTime() <= list.arrival && !Q2.isEmpty() ) {
					Q_list = Q2.getFront() ;            // ���XQueue���u�@
					SetQueueWork(Q_list, cook2, work) ; // ���u�@ 
					Q2.deQueue() ;                      // �R���w�����u�@ 
				} // while
				
				if ( Q1.GetSize() < Q2.GetSize() ) { 
					// ��X����p�v��Queue�ƶq����֡A�N��M�浹�L 
					list.CID = 1 ;
					Q1.enQueue(list) ;
				} // if
				else if ( Q1.GetSize() > Q2.GetSize() ) {
					// ��X����p�v��Queue�ƶq����֡A�N��M�浹�L
					list.CID = 2 ;
					Q2.enQueue(list) ;
				} // else if
				else if ( Q1.isFull() && Q2.isFull() ) {
					// �Y�p�v��Queue���O�����A�������� 
					list.abort = list.arrival ;         // �����ɨ� = �U��ɨ� 
					list.delay = 0 ;                    // ���~�ɶ��� 0
					list.CID = 0 ;                      // CID�]�� 0 
					work.PutAbort(list) ;               // �[�J�����M�� 
				} // else if
				else if ( Q1.GetSize() == Q2.GetSize() ) {
					// �Y�p�v��Queue���ƶq�ۦP�A�B�����������A���N���̤p���p�v 
					list.CID = 1 ;
					Q1.enQueue(list) ;
				} // else if
			} // else

			work.DeletData(0) ;                         // �R�����X���u�@ 
		} // while
		 
		while ( !Q1.isEmpty() ) {                       // ��Queue�ѤU���u�@
			Q_list = Q1.getFront() ;                    // ���XQueue���u�@
			SetQueueWork(Q_list, cook1, work) ;         // ���u�@ 
			Q1.deQueue() ;                              // �R���w�����u�@ 
		} // while
		 
		while ( !Q2.isEmpty() ) {                       // ��Queue�ѤU���u�@
			Q_list = Q2.getFront() ;                    // ���XQueue���u�@
			SetQueueWork(Q_list, cook2, work) ;         // ���u�@ 
			Q2.deQueue() ;                              // �R���w�����u�@ 
		} // while
		
		work.WriteFinishFile("two", 2) ;                // �g�J�ɮ�
 
	} // if
	
} // mission3

void mission4() {
	
	string Q_Num ;      // number of queue
	int M = 0 ;
	
	Work work ;         // �u�@�M��
	Type list = {0} ;   // �sJobList��Data  
	
	if ( work.ReadFile( "sort" ) ) {    // �YŪ�ɮצ��\�A����
	
		do {                            // Ū�J�h�֭Ӽp�v 
	
	    	cout << endl << "Input the number of queue : " ;
			cin >> Q_Num ;
		
			if ( isDigit(Q_Num) ) {        // �O�_��int 
				M = atoi(Q_Num.c_str()) ;  // str to int
		
				if ( !(M >= 1 && M <= 9) )
					cout << endl << "### It is NOT in [1, 9] ###" << endl ;
			} // if

		} while ( !(M >= 1 && M <= 9) ) ;
		
		Simulation S(M) ; // �����A�ó]�w�p�v�ƶq 
		
		work.PrintAll() ; // �L�XŪ�쪺��� 
		
		system("pause") ;
		
		while ( !work.isEmpty() ) {      // �����u�@
			list = work.GetData(0) ;     // ���X���	
			
			if ( !S.WorkToCook(list) ) { // �Y�p�v�S������
				S.takeWork(list, work) ; // Queue -> cook
				S.SetQueue(list, work) ; // list -> Queue
			} // if
			else 
				S.takeWork(list, work) ; // Queue -> cook
				
			//S.print() ;
			work.DeletData(0) ;          // �R�����
		} // while 
		
		S.check(work) ;
		
		S.lastWork(work) ;
		
		work.WriteFinishFile("more", M) ; // �g�J�ɮ�
		
	} // if
	
} // mission4

int main() {
	
	string command = "/0" ; // Ū�����O 
	int cd = -1 ;           // int�����O 
	
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
		
		if ( isDigit(command) ) // �O�_��int 
			cd = atoi(command.c_str()) ; // str to int
		else return 0 ;
		
		if ( cd == 0 ) continue ;
		else if ( cd == 1 ) mission1() ; // �i�J���Ȥ@ 
		else if ( cd == 2 ) mission2() ; // �i�J���ȤG 
		else if ( cd == 3 ) mission3() ; // �i�J���ȤT
		else if ( cd == 4 ) mission4() ; // �i�J���ȥ| 
		else cout << endl << "Command is NOT exist !!" << endl ; // �L�����O 
		
	} while ( cd != 0 ) ;
	
	system("pause") ;
	return 0 ;
	
} // main
