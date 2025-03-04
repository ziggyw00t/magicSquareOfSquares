using namespace std;

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector> 
#include <set> 
#include <mutex>
#include <thread>
#include <string>
#include <chrono>

bool g_paused = false ;

bool g_solved = false ;

bool g_status = false ; 
 
//unsigned long long int g_currentTarget = 477204097 ; 

unsigned long long int g_currentTarget = 715806037; 
										 
										 

#define g_max 65000

unsigned long long int g_squares[ g_max ] ;

mutex mtx_target ;
mutex mtx_threadwrite ;

void clearscr() {
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
}

void status(){
	char input = 'a' ;
	while ( input != 'q' ){
		cin >> input;
	}
	g_status = false ; 
	clearscr();
	return ;
}

void menu(){
	string input = "";
		while ( input != "exit" ) {

			if ( g_paused ) 
				cout<< "--- CURRENTLY PAUSED ---" << endl; 
			cout 	<< "OPTIONS:" 	<< endl 
					<< "--pause" 	<< endl 
					<< "--resume" 	<< endl 
					<<"--status (press q+enter to exit)" << endl 
					<< "--exit" << endl
					<< endl << "Your selection: " ;
			cin >> input ; 
			clearscr();
				
			if ( input == "pause" ) { 
				g_paused = true ;
			}
				
			if ( input == "resume" ) {
				g_paused = false ;
			}
			
			if ( input == "status" ) {
				g_status = true ; 
				status();
			}
		}
}

void testPaused(){
	while (g_paused)
		std::this_thread::sleep_for(std::chrono::seconds(5));
}

void printSquare(		unsigned long long int A,
						unsigned long long int B, 
						unsigned long long int C, 
						unsigned long long int D, 
						unsigned long long int E, 
						unsigned long long int F,
						unsigned long long int G,
						unsigned long long int H, 
						unsigned long long int I,
						unsigned long long int target,
						int i, 
						bool solved 
						) {
	if ( solved ) {
		mtx_threadwrite.lock();
		ofstream out("solutions.txt", std::ios::app);
								
		out	<< "Magic square for magic sum: " << target << endl 
			<< endl << A << " " << B << " " << C << endl
			<< endl << D << " " << E << " " << F << endl 
			<< endl << G << " " << H << " " << I << endl
			<< endl << endl ; 
		out.close();
		mtx_threadwrite.unlock();
	}
	
	if ( g_status ) {
		mtx_threadwrite.lock();
		cout << boolalpha; 
		cout	<< "Solved: " << g_solved << endl
				<< "Current target: " << g_currentTarget << endl
				<< "Thread " << i << " is trying magic square for magic sum: " << target << endl 
				<< endl << A << " " << B << " " << C << endl
				<< endl << D << " " << E << " " << F << endl 
				<< endl << G << " " << H << " " << I << endl
				<< endl << endl ; 
		mtx_threadwrite.unlock();
	}
}

bool checkSquare( 	unsigned long long int A, 
					unsigned long long int B,
					unsigned long long int C, 
					unsigned long long int D, 
					unsigned long long int E, 
					unsigned long long int F, 
					unsigned long long int G, 
					unsigned long long int H, 
					unsigned long long int I,
					unsigned long long int target,
					int i, 
					bool solved) {
		
	std::set<unsigned long long int> boxes; 
	
	boxes.insert( A ) ;
	boxes.insert( B ) ; 
	boxes.insert( C ) ; 
	boxes.insert( D ) ; 
	boxes.insert( E ) ; 
	boxes.insert( F ) ; 
	boxes.insert( G ) ; 
	boxes.insert( H ) ; 
	boxes.insert( I ) ;  

	printSquare( A, B, C, D, E, F, G, H, I, target, i, false );
	
	if ( boxes.size() == 9 ) 
		if ( D + E + F == target )
			if ( B + E + H == target ) 
				if ( sqrt( B ) == floor( sqrt( B ) ) ) 
					if ( sqrt( D ) == floor( sqrt( D ) ) ) 
						if ( sqrt( F ) == floor( sqrt( F ) ) ) 
							if ( sqrt( H ) == floor( sqrt( H ) ) ) {
										g_solved = true; 
										printSquare( A, B, C, D, E, F, G, H, I, target, i, true );
										return true ;
										
							}				
									
			
			
	return false ;
}
bool positiveSubtraction( unsigned long long int target, unsigned long long int x, unsigned long long int y ){
	
	// if target - x - y is negative returns false; else returns true 
	
	unsigned long long int z = x + y ; 
	if ( target > z )
		return true;
	else
		return false;

return false ; 
	
}

void testTarget( unsigned long long int i ) {
			
	unsigned long long int target ;
	
	unsigned long long int B, D, F, H ; 

	while ( true  )  {
		
		mtx_target.lock(); 
		target = g_currentTarget; 
		g_currentTarget++;
		mtx_target.unlock(); 
		
		unsigned long long int solutions_found = 0 ; 
		mtx_threadwrite.lock();
		mtx_threadwrite.unlock(); 
		for ( unsigned long long int E = 1 ; E < g_max ; E++ ) {	
			for ( unsigned long long int A = 1 ; A < g_max ; A++ ) {
				if ( g_squares[ E ] + g_squares[ A ] >  target ) break ;
				for ( unsigned long long int I = 1 ; I < g_max ; I++ ) {
					testPaused();
					if ( g_squares[ E ] + g_squares[ A ] + g_squares[ I ] >  target ) break ;
					if ( g_squares[ E ] + g_squares[ A ] + g_squares[ I ] == target ) {	
							for ( unsigned long long int C = 1 ; C < g_max ; C++ ) {
								if ( g_squares[ E ] + g_squares[ C ] > target ) break ;
								for ( unsigned long long int G = 1 ; G < g_max ; G++ ) {
									testPaused();
									if ( g_squares[ E ] + g_squares[ C ] + g_squares[ G ] > target ) break ;
									if ( g_squares[ E ] + g_squares[ C ] + g_squares[ G ] == target ) {
										if ( positiveSubtraction ( target , g_squares[ A ], g_squares[ C ] ) )   			//B
											if ( positiveSubtraction ( target, g_squares[ A ],  g_squares[ G ] ) )     		//D
												if ( positiveSubtraction ( target, g_squares[ C ], g_squares[ I ] ) ) 		//F
													if ( positiveSubtraction( target, g_squares[ G ], g_squares[ I ] ) ) {  //H
														B = target - g_squares[ A ] - g_squares[ C ] ; 
														D = target - g_squares[ A ] - g_squares[ G ] ; 
														F = target - g_squares[ C ] - g_squares[ I ] ; 
														H = target - g_squares[ G ] - g_squares[ I ] ; 
														if ( checkSquare(A, B, C, D, E, F, G, H, I, target, i, true) )
															solutions_found++ ;
									  }
									}
								}
					
							}
					}
			
				}
		
			}

		}
		
		mtx_threadwrite.lock() ;
			ofstream dts("deadtargets.txt", std::ios::app);
			dts << target << endl ;
				dts.close() ; 
		mtx_threadwrite.unlock() ;
	}	
}
		

	


int main (int argc, char* argv[]) {

	//cout 	<< "Starting Target = " << g_currentTarget << endl ; 
	
	for ( unsigned long long int i = 0 ; i < g_max ; i++ ) {
		g_squares[ i ] = i * i ;
	}
		
		// unsigned long long int num_threads = 1 ; 
	
	 int num_threads = std::thread::hardware_concurrency() - 2 ;
		if (num_threads <= 0) {
            num_threads = 1; // Default to 1 if the function returns 0
        } 

        std::vector<std::thread> threads;
        
        for ( int i = 0; i < num_threads; ++i) {
            threads.emplace_back( testTarget, i );
        }
	
        for (auto& thread : threads) {
            thread.detach();
        }

	menu(); 
	
	return 0;
	
}

