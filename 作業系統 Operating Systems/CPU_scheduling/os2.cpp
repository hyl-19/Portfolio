#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std ;

struct Info {
    int id = 0 ;
    int cpu_burst = 0 ;
    int arr_time = 0 ;
    int priority = 0 ;

    int waiting_time = 0 ;
    int turnaround_time = 0 ;
    double rr = 0.0 ;

};

struct Answer {
    vector<Info> info ;
    vector<char> ans ;
};

bool compareArr_Id(const Info& a, const Info& b) {
    if (a.arr_time != b.arr_time) {
        return a.arr_time < b.arr_time ;
    }
    return a.id < b.id;
}

bool compareCpu_Arr_Id(const Info& a, const Info& b) {
    if (a.cpu_burst != b.cpu_burst) {
        return a.cpu_burst < b.cpu_burst ;
    }
    else if ( a.arr_time != b.arr_time)
        return a.arr_time < b.arr_time ;
    else 
        return a.id < b.id ;
}

bool compareById(const Info& a, const Info& b) {
    return a.id < b.id;
}

bool compareByRr_Arr_Id(const Info& a, const Info& b) { // Which RR is bigger, do first
    if (a.rr != b.rr) {
        return a.rr > b.rr ;
    }
    else if ( a.arr_time != b.arr_time)
        return a.arr_time < b.arr_time ;
    else 
        return a.id < b.id ;
}

bool compareByPri(const Info& a, const Info& b) {
    return a.priority < b.priority;
}

class File {
    int method ;
    int time_slice ;
    vector<Info> data ;
    string filename ;

public:

    void read( string name ) {
        filename = name ;
        ifstream in ;

        in.open( filename + ".txt");
        if ( in.is_open() == false ) {
            cout << "Failed to open file.\n" ;
            return ;
        }

        in >> method >> time_slice ;
        Info temp ;
        string line ;
        getline(in, line) ; // "/n"
        getline(in, line) ; // id.......
        while ( in >> temp.id >> temp.cpu_burst >> temp.arr_time >> temp.priority ) {
            data.push_back( temp ) ;
        }

        in.close() ;
    }

    void Write( Answer temp, string task ) {
        ofstream out ;
        out.open( "out_" + filename + ".txt" ) ;
        if ( task == "PPRR"){
            out << "Priority RR" << endl ;
        }
        else {
            out << task << endl ;
        }
        out << "==" << setw(12) << task << "==" << endl ;
        for ( int i = 0 ; i < temp.ans.size() ; i++ )
            out << temp.ans[i] ;
        out << endl ;

        out << "===========================================================" << endl << endl ;
        out << "Waiting Time" << endl << "ID" << "\t" << task << endl ;
        out << "===========================================================" << endl ;
        for ( int i = 0 ; i < temp.info.size() ; i++ ) {
            out << temp.info[i].id << "\t" << temp.info[i].waiting_time << endl ;
        }
        
        out << "===========================================================" << endl << endl ;
        out << "Turnaround Time" << endl << "ID" << "\t" << task << endl ;
        out << "===========================================================" << endl ;
        for ( int i = 0 ; i < temp.info.size() ; i++ ) {
            out << temp.info[i].id << "\t" << temp.info[i].turnaround_time << endl ;
        }
        out << "===========================================================" << endl ;
        out << endl ;

        out.close() ;
    }

    void WriteAll( Answer a, Answer b, Answer c, Answer d, Answer e, Answer f ) {
        ofstream out ;
        out.open( "out_" + filename + ".txt" ) ;
        
        out << "All" << endl ;

        out << "==" << setw(12) << "FCFS" << "==" << endl ;
        for ( int i = 0 ; i < a.ans.size() ; i++ )
            out << a.ans[i] ;
        out << endl ;
        out << "==" << setw(12) << "RR" << "==" << endl ;
        for ( int i = 0 ; i < b.ans.size() ; i++ )
            out << b.ans[i] ;
        out << endl ;
        out << "==" << setw(12) << "SJF" << "==" << endl ;
        for ( int i = 0 ; i < c.ans.size() ; i++ )
            out << c.ans[i] ;
        out << endl ;
        out << "==" << setw(12) << "SRTF" << "==" << endl ;
        for ( int i = 0 ; i < d.ans.size() ; i++ )
            out << d.ans[i] ;
        out << endl ;
        out << "==" << setw(12) << "HRRN" << "==" << endl ;
        for ( int i = 0 ; i < e.ans.size() ; i++ )
            out << e.ans[i] ;
        out << endl ;
        out << "==" << setw(12) << "PPRR" << "==" << endl ;
        for ( int i = 0 ; i < f.ans.size() ; i++ )
            out << f.ans[i] ;
        out << endl ;

        out << "===========================================================" << endl << endl ;
        out << "Waiting Time" << endl ;
        out << "ID" << "\t" << "FCFS" << "\t" << "RR" << "\t" << "SJF" << "\t" << "SRTF" << "\t" << "HRRN" << "\t" << "PPRR" << endl ;
        out << "===========================================================" << endl ;
        for ( int i = 0 ; i < a.info.size() ; i++ ) {
            out << a.info[i].id 
            << "\t" << a.info[i].waiting_time << "\t" << b.info[i].waiting_time
            << "\t" << c.info[i].waiting_time << "\t" << d.info[i].waiting_time
            << "\t" << e.info[i].waiting_time << "\t" << f.info[i].waiting_time<< endl ;
        }
        
        out << "===========================================================" << endl << endl ;
        out << "Turnaround Time" << endl ;
        out << "ID" << "\t" << "FCFS" << "\t" << "RR" << "\t" << "SJF" << "\t" << "SRTF" << "\t" << "HRRN" << "\t" << "PPRR" << endl ;
        out << "===========================================================" << endl ;
        for ( int i = 0 ; i < a.info.size() ; i++ ) {
            out << a.info[i].id 
            << "\t" << a.info[i].turnaround_time << "\t" << b.info[i].turnaround_time
            << "\t" << c.info[i].turnaround_time << "\t" << d.info[i].turnaround_time
            << "\t" << e.info[i].turnaround_time << "\t" << f.info[i].turnaround_time<< endl ;
        }
        out << "===========================================================" << endl ;
        out << endl ;

        out.close() ;
    }

    vector<Info> get_data() {
        return data ;
    }

    int get_method() {
        return method ;
    }

    int get_timeslice() {
        return time_slice ;
    }

};

class Cpu_Scheduling {

    char Change(int i ) {
        char x = i + '0' ;
        if ( x >= '0' & x <= '9' ) 
            return x ;
        else 
            return x + 7 ;
    }

    Answer FCFS( vector<Info> data ) {
        // input1_method1
        int time = 0 ;
        vector<Info> q ;
        vector<Info> doing ;
        vector<Info> count ;
        vector<char> ans ;
        int num =  data.size() ;
        while( count.size() != num ) {

            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].arr_time == time) {
                    q.push_back(data[i]) ;
                    sort(q.begin(), q.end(), compareArr_Id);
                }
            }
            //cout << Change(data[0].id) << "      " << data[0].cpu_burst << endl ;
            if ( doing.empty() == true && q.empty() == false ) {
                doing.push_back(q[0]) ;
                doing[0].waiting_time = time - doing[0].arr_time ;
                q.erase(q.begin()) ;
            }
           
            if ( doing.empty() == false && doing[0].arr_time <= time ) {
                doing[0].cpu_burst-- ;
                ans.push_back(Change(doing[0].id)) ;
            }

            if ( doing.empty() == true ) {
                ans.push_back('-') ;
            }

            if ( doing.empty() == false && doing[0].cpu_burst == 0 ) {
                doing[0].turnaround_time = ( time + 1 ) - doing[0].arr_time ;
                count.push_back(doing[0]) ;
                doing.clear() ;
            }

            time++ ;
        }

        sort(count.begin(), count.end(), compareById);

        Answer temp ;
        temp.ans = ans ;
        temp.info = count ;

        return temp ;
    }

    Answer RR( vector<Info> data, int time_slice ) {
        int time = 0 ;
        int exe_time = 0 ;
        vector<Info> q ;
        vector<Info> doing ;
        vector<Info> count ;
        vector<Info> reg ;
        vector<char> ans ;
        int num =  data.size() ;
        while( count.size() != num ) {

            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].arr_time == time) {
                    reg.push_back(data[i]) ;
                }
            }

            if ( reg.empty() == false ) {
                sort(reg.begin(), reg.end(), compareArr_Id);
                for ( int i = 0 ; i < reg.size() ; i++ ){
                    q.push_back(reg[i]) ;
                }
                reg.clear() ;
            }

            if ( doing.empty() == false && exe_time == time_slice ) { // if time is out, clear doing
                exe_time = 0 ;
                q.push_back(doing[0]) ;
                doing.clear() ;
            }

            if ( doing.empty() == true && q.empty() == false ) {
                doing.push_back(q[0]) ;
                q.erase(q.begin()) ;
            }
           
            if ( doing.empty() == false && doing[0].arr_time <= time ) {
                doing[0].cpu_burst-- ;
                exe_time++ ;
                ans.push_back(Change(doing[0].id)) ;
            }

            if ( doing.empty() == true ) {
                ans.push_back('-') ;
            }

            if ( q.empty() == false ) {
                for ( int i = 0 ; i < q.size() ; i++ ) {
                    q[i].waiting_time++ ;
                }
            }

            if ( doing.empty() == false && doing[0].cpu_burst == 0 ) {
                exe_time = 0 ;
                doing[0].turnaround_time = ( time + 1 ) - doing[0].arr_time ;
                count.push_back(doing[0]) ;
                doing.clear() ;
            }

            time++ ;
        }

        sort(count.begin(), count.end(), compareById);

        Answer temp ;
        temp.ans = ans ;
        temp.info = count ;

        return temp ;
    }

    Answer SJF( vector<Info> data ) {
        int time = 0 ;
        vector<Info> q ;
        vector<Info> doing ;
        vector<Info> count ;
        vector<char> ans ;
        int num =  data.size() ;
        while( count.size() != num ) {

            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].arr_time == time) {
                    q.push_back(data[i]) ;
                    sort(q.begin(), q.end(), compareCpu_Arr_Id);
                }
            }
            //cout << Change(data[0].id) << "      " << data[0].cpu_burst << endl ;
            if ( doing.empty() == true && q.empty() == false ) {
                doing.push_back(q[0]) ;
                doing[0].waiting_time = time - doing[0].arr_time ;
                q.erase(q.begin()) ;
            }
           

            if ( doing.empty() == false && doing[0].arr_time <= time ) {
                doing[0].cpu_burst-- ;
                ans.push_back(Change(doing[0].id)) ;
            }

            if ( doing.empty() == true ) {
                ans.push_back('-') ;
            }

            if ( doing.empty() == false && doing[0].cpu_burst == 0 ) {
                doing[0].turnaround_time = ( time + 1 ) - doing[0].arr_time ;
                count.push_back(doing[0]) ;
                doing.clear() ;
            }

            time++ ;
        }

        sort(count.begin(), count.end(), compareById);

        Answer temp ;
        temp.ans = ans ;
        temp.info = count ;

        return temp ;
    }

    Answer SRTF( vector<Info> data ) {
        int time = 0 ;
        vector<Info> q ;
        vector<Info> doing ;
        vector<Info> count ;
        vector<char> ans ;
        int num =  data.size() ;
        while( count.size() != num ) {

            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].arr_time == time) {
                    q.push_back(data[i]) ;
                    sort(q.begin(), q.end(), compareCpu_Arr_Id);
                }
            }

            if ( doing.empty() == true && q.empty() == false ) {
                doing.push_back(q[0]) ;
                q.erase(q.begin()) ;
            }
            else if ( doing.empty() == false && q.empty() == false ) {
                if ( doing[0].cpu_burst > q[0].cpu_burst ) {
                    swap(doing[0], q[0]) ;
                    sort(q.begin(), q.end(), compareCpu_Arr_Id);
                } // 有發現q裡面有多較短工作的
            }
           
            if ( doing.empty() == false && doing[0].arr_time <= time ) {
                doing[0].cpu_burst-- ;
                ans.push_back(Change(doing[0].id)) ;
            }

            if ( doing.empty() == true ) {
                ans.push_back('-') ;
            }

            if ( q.empty() == false ) {
                for ( int i = 0 ; i < q.size() ; i++ ) {
                    q[i].waiting_time++ ;
                }
            }

            if ( doing.empty() == false && doing[0].cpu_burst == 0 ) {
                doing[0].turnaround_time = ( time + 1 ) - doing[0].arr_time ;
                count.push_back(doing[0]) ;
                doing.clear() ;
            }

            time++ ;
        }

        sort(count.begin(), count.end(), compareById);

        Answer temp ;
        temp.ans = ans ;
        temp.info = count ;

        return temp ;
    }

    Answer HRRN( vector<Info> data ) {
        int time = 0 ;
        vector<Info> q ;
        vector<Info> doing ;
        vector<Info> count ;
        vector<char> ans ;
        int num =  data.size() ;
        while( count.size() != num ) {

            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].arr_time == time) {
                    q.push_back(data[i]) ;
                }
            }

            if ( doing.empty() == true && q.empty() == false ) {
                for ( int i = 0 ; i < q.size() ; i++ ) {
                    q[i].rr = 1.0 * ( q[i].waiting_time + q[i].cpu_burst ) / q[i].cpu_burst ;
                }
       
                sort(q.begin(), q.end(), compareByRr_Arr_Id);
                doing.push_back(q[0]) ;
                q.erase(q.begin()) ;

            } //input1_method5

           
            if ( doing.empty() == false && doing[0].arr_time <= time ) {
                doing[0].cpu_burst-- ;
                ans.push_back(Change(doing[0].id)) ;
            }

            if ( doing.empty() == true ) {
                ans.push_back('-') ;
            }

            if ( q.empty() == false ) {
                for ( int i = 0 ; i < q.size() ; i++ ) {
                    q[i].waiting_time++ ;
                }
            }

            if ( doing.empty() == false && doing[0].cpu_burst == 0 ) {
                doing[0].turnaround_time = ( time + 1 ) - doing[0].arr_time ;
                count.push_back(doing[0]) ;
                doing.clear() ;
            }

            time++ ;
        }

        sort(count.begin(), count.end(), compareById);

        Answer temp ;
        temp.ans = ans ;
        temp.info = count ;

        return temp ;
    }

    Answer PPRR( vector<Info> data, int time_slice ) {
        int time = 0 ;
        int exe_time = 0 ;
        int first = 0 ;
        vector<Info> q ;
        vector<Info> doing ;
        vector<Info> count ;
        vector<Info> reg ;
        vector<char> ans ;
        bool newcome = false ;
        int num =  data.size() ;
        while( count.size() != num ) {
            newcome = false ;

            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].arr_time == time) {
                    reg.push_back(data[i]) ;
                    newcome = true ;
                    sort(reg.begin(), reg.end(), compareById) ;
                }
            }

            if ( newcome == true ) {
                for ( int i = 0 ; i < reg.size() ; i++ ) {
                    q.push_back(reg[i]) ;
                }

                reg.clear() ;
            }
            
            if (  doing.empty() == false && ( exe_time == time_slice  || newcome == true ) ) { // if time is out, clear doing
                
                if( exe_time == time_slice ) {
                    // cout << time << "    11111" << endl ;
                    exe_time = 0 ;
                    q.push_back(doing[0]) ;
                    doing.clear() ;
                }
                else {
                    //
                    bool prem = false ;
                    for ( int i = 0 ; q.empty() == false && i < q.size() ; i++) {
                        if ( doing[0].priority > q[i].priority ) {
                            prem = true ;
                        }
                    }

                    if ( prem == true ) {
                        exe_time = 0 ;
                        q.push_back(doing[0]) ;
                        doing.clear() ;
                    }
                }
            }

            stable_sort(q.begin(), q.end(), compareByPri) ;

            if ( doing.empty() == true && q.empty() == false ) {       
                doing.push_back(q[0]) ;
                q.erase(q.begin()) ;
            } //input1_method6
           
            if ( doing.empty() == false && doing[0].arr_time <= time ) {
                doing[0].cpu_burst-- ;
                exe_time++ ;
                ans.push_back(Change(doing[0].id)) ;
            }

            if ( doing.empty() == true ) {
                ans.push_back('-') ;
            }

            if ( q.empty() == false ) {
                for ( int i = 0 ; i < q.size() ; i++ ) {
                    q[i].waiting_time++ ;
                }
            }

            if ( doing.empty() == false && doing[0].cpu_burst == 0 ) {
                exe_time = 0 ;
                doing[0].turnaround_time = ( time + 1 ) - doing[0].arr_time ;
                count.push_back(doing[0]) ;
                doing.clear() ;
                
            }

            time++ ;
        }

        sort(count.begin(), count.end(), compareById);

        Answer temp ;
        temp.ans = ans ;
        temp.info = count ;

        return temp ;
    }

public :
    void task_select() {
        string filename ;
        cout << "Please enter File name :" ;
        cin >> filename ;
        File in ;
        in.read( filename ) ;
        Answer temp ;
        string str ;
        switch(in.get_method()) {
            case 1 :
                temp = FCFS(in.get_data()) ;
                str = "FCFS" ;
                in.Write(temp, str) ;
                break ;
            case 2 : // xxxxxxxx
                temp = RR(in.get_data(), in.get_timeslice()) ;
                str = "RR" ;
                in.Write(temp, str) ;
                break ;
            case 3 :
                temp = SJF(in.get_data()) ;
                str = "SJF" ;
                in.Write(temp, str) ;
                break ;
            case 4 :
                temp = SRTF(in.get_data()) ;
                str = "SRTF" ;
                in.Write(temp, str) ;
                break ;
            case 5 :
                temp = HRRN(in.get_data()) ;
                str = "HRRN" ;
                in.Write(temp, str) ;
                break ;
            case 6 :
                temp = PPRR(in.get_data(), in.get_timeslice()) ;
                str = "PPRR" ;
                in.Write(temp, str) ;
                break ;
            case 7 : //all
                Answer a, b, c, d, e, f ;
                a = FCFS(in.get_data()) ;
                b = RR(in.get_data(), in.get_timeslice()) ;
                c = SJF(in.get_data()) ;
                d = SRTF(in.get_data()) ;
                e = HRRN(in.get_data()) ;
                f = PPRR(in.get_data(), in.get_timeslice()) ;
                in.WriteAll(a, b, c, d, e, f) ;
                break ;
        }

    }
};

int main(){
    Cpu_Scheduling execute ;
    execute.task_select() ;
}