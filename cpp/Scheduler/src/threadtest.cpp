#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <functional>
#include "system.h"

namespace ms = my_system;

void user( int n = 10 ) {
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count(); 
    unsigned seed2 = seed1 * 2; 
    auto procs = std::bind(
                    std::uniform_int_distribution<int>(1,ms::total_procs),
                    std::default_random_engine(seed1) 
                 ); 
    auto ticks = std::bind(
                    std::uniform_int_distribution<int>(1,100),
                    std::default_random_engine(seed2) 
                 ); 
    for( int i = 0; i < n; i++ ) {
        ms::submit_job("user job", ticks(), procs() );
    }
}


int main()
{
    using std::thread;
    thread users[10];
    
    for( unsigned i = 0; i < 10; i++ ) {
        users[i] = thread( user, 10 );
    }   

    ms::tick();
    while( ! ms::is_done() ) {
        ms::tick();
    }
    for( auto &t : users )  t.join();


    return 0;
}
