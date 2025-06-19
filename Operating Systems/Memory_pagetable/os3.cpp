#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std ;

class File {
    int method ;
    int page_frame ;
    vector<int> data ;
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

        in >> method >> page_frame ;
        
        string line;
        in.ignore() ; // skip '/n'

        while ( getline( in, line ) ) {
            for ( char c : line ) {
                data.push_back( c - '0' ); // 將字符轉換為整數並存入vector
            }
        }

        in.close() ;
    }

    void create_file( string name ) { 
        filename = "out_" + name + ".txt" ;
        ofstream out( filename ) ;
    }

    void write_title( string title ) {
        ofstream out ;
        out.open( filename , ios::app ) ;
        out << "--------------" << title << "-----------------------" << endl ;
        out.close() ;
    }

    void write_pages( int page, vector<int> q, bool Isfault ) {
        ofstream out ;
        out.open( filename , ios::app ) ;
        out << page << "\t";
        for ( int i = 0 ; i < q.size() ; i++ )
            out << q[i] ;
        
        if( Isfault == false ) {
            out << "\t" << "F" ;
        }
        out << endl ;
        out.close() ;
    }

    void write_page_FRF( int faults, int replaces, int frames ) {
        ofstream out ;
        out.open( filename , ios::app ) ;
        out << "Page Fault = " << faults << "  Page Replaces = " << replaces << "  Page Frames = " << frames << endl ;
        out.close() ;
    }

    void write_line() {
        ofstream out ;
        out.open( filename , ios::app ) ;
        out << endl ;
        out.close() ;
    }

    vector<int> get_data() {
        return data ;
    }

    int get_method() {
        return method ;
    }

    int get_pageframe() {
        return page_frame ;
    }

};

class Page_Replacement {

    File file ;
    bool isAll ;

    vector<int> q2v( queue<int> q ) {
        vector<int> temp ;
        while ( q.empty() == false ) {
            temp.push_back( q.front() );
            q.pop();
        }

        reverse( temp.begin(), temp.end() ) ;
        return temp ;
    }

    queue<int> erase_exit( queue<int> q, int exit ) {
        queue<int> temp ;
            while ( q.empty() == false ) {
                if ( q.front() != exit )
                    temp.push( q.front() ) ;
                
                q.pop() ;
            }

            return temp ;
    }

    queue<int> queue_reorder( queue<int> q, int page ) {
        queue<int> temp ;
            while ( q.empty() == false ) {
                if ( q.front() != page )
                    temp.push( q.front() ) ;
                
                q.pop() ;
            }

            temp.push( page ) ;

            return temp ;
    }


    void FIFO( vector<int> data, int frames, string filename ) { //input1_method1
        if ( isAll == false ) file.create_file( filename );

        unordered_set<int> memory; // in memeory
        queue<int> q;
        int faults = 0, replaces = 0 ;
        
        file.write_title( "FIFO" ) ;
        
        for ( int page : data ) {
            if ( memory.find(page) == memory.end() ) { // can't find, return end()
                faults++;
                
                if ( memory.size() == frames ) { // is full
                    memory.erase( q.front() );
                    q.pop() ;
                    replaces++;
                }
                
                memory.insert( page );
                q.push( page );
                
                file.write_pages( page, q2v(q), false ) ;
            } 
            else {
               file.write_pages( page, q2v(q), true ) ;
            }
        }

        file.write_page_FRF( faults, replaces, frames ) ;
    }

    void LRU( vector<int> data, int frames, string filename ) { //input1_method2
        if ( isAll == false ) file.create_file( filename );

        unordered_set<int> memory; // in memeory
        vector<int> q;
        int faults = 0, replaces = 0 ;
        
        file.write_title( "LRU" ) ;
        
        for ( int page : data ) {
            if ( memory.find(page) == memory.end() ) { // can't find, return end()
                faults++;
                
                if ( memory.size() == frames ) { // is full
                    memory.erase( q.back() );
                    q.pop_back() ;
                    replaces++;
                }
                
                memory.insert( page );
                q.insert( q.begin(), page );
                
                file.write_pages( page, q, false ) ;
            } 
            else {
                for ( int i = 0 ; i < q.size() ; i++ ) {
                    if ( page == q[i] ) {
                        q.erase( q.begin() + i ) ;
                        q.insert( q.begin(), page );
                    }
                }

                file.write_pages( page, q, true ) ;
            }
        }

        file.write_page_FRF( faults, replaces, frames ) ;
    }

    void LFU( vector<int> data, int frames, string filename ) { //input1_method3  選最近最久沒被使用到的page換掉
        if ( isAll == false ) file.create_file( filename );

        unordered_set<int> memory ; // In memory
        unordered_map<int, int> freq ;
        queue<int> q ; 
        int faults = 0, replaces = 0 ;

        file.write_title("Least Frequently Used Page Replacement");

        for ( int page : data ) {
            if ( memory.find(page) == memory.end() ) { // Page not in memory
                faults++ ;
                if ( memory.size() == frames ) { // Memory is full
                    // Find the page with the least frequency
                    int exit = q.front() ;
                    queue<int> temp = q ;
                    while ( q.empty() == false ) {
                        if ( freq[q.front()] < freq[exit] ) {
                            exit = q.front() ;
                        }
                        q.pop() ;
                    }
                    q = temp ;
                    
                    memory.erase( exit ) ;
                    freq.erase( exit ) ;
                    q = erase_exit( q, exit ) ;
                    
                    replaces++ ;
                }

                memory.insert( page ) ;
                freq[page] = 1 ;
                q.push( page ) ;
                file.write_pages( page, q2v(q), false ) ;
            }
            else {
                freq[page]++ ;
                file.write_pages( page, q2v(q), true ) ;
            }
        }

        file.write_page_FRF( faults, replaces, frames ) ;
    }

    void MFU( vector<int> data, int frames, string filename ) { //input1_method4
        if ( isAll == false ) file.create_file( filename );

        unordered_set<int> memory; // In memory
        unordered_map<int, int> freq; // Frequency of pages
        queue<int> q; // FIFO queue for replacement policy
        int faults = 0, replaces = 0 ;

        file.write_title("Most Frequently Used Page Replacement ");

                for ( int page : data ) {
            if ( memory.find(page) == memory.end() ) { // Page not in memory
                faults++ ;
                if ( memory.size() == frames ) { // Memory is full
                    // Find the page with the least frequency
                    int exit = q.front() ;
                    queue<int> temp = q ;
                    while ( q.empty() == false ) {
                        if ( freq[q.front()] > freq[exit] ) {
                            exit = q.front() ;
                        }
                        q.pop() ;
                    }
                    q = temp ;
                    
                    memory.erase( exit ) ;
                    freq.erase( exit ) ;
                    q = erase_exit( q, exit ) ;
                    
                    replaces++ ;
                }

                memory.insert( page ) ;
                freq[page] = 1 ;
                q.push( page ) ;
                file.write_pages( page, q2v(q), false ) ;
            }
            else {
                freq[page]++ ;
                file.write_pages( page, q2v(q), true ) ;
            }
        }

        file.write_page_FRF( faults, replaces, frames ) ;
    }


    void LFU_LRU( vector<int> data, int frames, string filename ) { //input1_method5
        if ( isAll == false ) file.create_file( filename );

        unordered_set<int> memory; // In memory
        unordered_map<int, int> freq; // Frequency of pages
        queue<int> q ;

        int faults = 0, replaces = 0;

        file.write_title("Least Frequently Used LRU Page Replacement");

        for ( int page : data ) {
            if ( memory.find(page) == memory.end() ) { // Page not in memory
                faults++ ;
                if ( memory.size() == frames ) { // Memory is full
                    int exit = q.front() ;
                    queue<int> temp = q ;
                    while ( q.empty() == false ) {
                        if ( freq[q.front()] < freq[exit] ) {
                            exit = q.front() ;
                        }
                        q.pop() ;
                    }
                    q = temp ;

                    memory.erase( exit ) ;
                    freq.erase( exit ) ;
                    q = erase_exit( q, exit ) ;
                    
                    replaces++ ;
                }

                memory.insert( page ) ;
                freq[page] = 1 ;
                q.push( page ) ;
                file.write_pages( page, q2v(q), false ) ;
            }
            else {
                freq[page]++ ;
                q = queue_reorder( q, page ) ;
                file.write_pages( page, q2v(q), true ) ;
            }
        }

        file.write_page_FRF( faults, replaces, frames ) ;
    }

    void ALL( File in, string filename ) { //input1_method6
        isAll = true ;
        file.create_file( filename );
        FIFO( in.get_data(), in.get_pageframe(), filename ) ;
        file.write_line() ;
        LRU( in.get_data(), in.get_pageframe(), filename ) ;
        file.write_line() ;
        LFU( in.get_data(), in.get_pageframe(), filename ) ;
        file.write_line() ;
        MFU( in.get_data(), in.get_pageframe(), filename ) ;
        file.write_line() ;
        LFU_LRU( in.get_data(), in.get_pageframe(), filename ) ;
    }

public :
    void task_select() {
        string filename ;
        cout << "Please enter File name :" ;
        cin >> filename ;
        File in ;
        in.read( filename ) ;
        
        switch( in.get_method() ) {
            case 1 :
                FIFO( in.get_data(), in.get_pageframe(), filename ) ;
                break ;
            case 2 : // xxxxxxxx
                LRU( in.get_data(), in.get_pageframe(), filename ) ;
                break ;
            case 3 :
                LFU( in.get_data(), in.get_pageframe(), filename ) ;
                break ;
            case 4 :
                MFU( in.get_data(), in.get_pageframe(), filename ) ;
                break ;
            case 5 :
                LFU_LRU( in.get_data(), in.get_pageframe(), filename ) ;
                break ;
            case 6 :
                ALL( in, filename ) ;
                break ;
        }
    }
} ;

int main(){
    Page_Replacement execute ;
    execute.task_select() ;
}