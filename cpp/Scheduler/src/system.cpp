#include <mutex>
#include <iostream>
#include "system.h"
#include "runqueue.h"
#include "waitqueue.h"

namespace my_system 
{   
    std::atomic_int total_procs(100);
    bool(*schedule)(const job&, const job&) = &shortest_job_next;
    
    namespace {
        std::atomic_int numticks(0);
        std::mutex mtx;
        std::atomic_int available_procs(static_cast<int>(my_system::total_procs));
        RunQueue run_queue = RunQueue( );
        WaitQueue wait_queue = WaitQueue( my_system::schedule );

        void run_job( const job & j ) {
            my_system::available_procs -= j.n_procs;
            my_system::run_queue.push(j);
        }
    }
    void submit_job( job& j ) {
        my_system::mtx.lock();
        my_system::wait_queue.push( j );
        my_system::mtx.unlock();
    }
    void submit_job( std::string s, int t, int p ) {
        my_system::mtx.lock();
        my_system::wait_queue.emplace(s,t,p);
        my_system::mtx.unlock(); 
    }
    
    void tick( ) {
        my_system::mtx.lock();
        std::cout << "Tick # " << numticks++ << std::endl; 
        my_system::run_queue.tick();
        if( !my_system::run_queue.empty() && my_system::run_queue.top().run_t == 0 )
            std::cout << "Jobs completed this tick:" << std::endl; 
        while( !my_system::run_queue.empty() && my_system::run_queue.top().run_t == 0 ) {
            my_system::available_procs += my_system::run_queue.top().n_procs;
            
            auto tmp = my_system::run_queue.top_pop();
            std::cout << tmp << std::endl;
        }
        if( !my_system::wait_queue.empty() ) {
            std::vector<job> tmp = my_system::wait_queue.best_job_by_procs(static_cast<int>(my_system::available_procs));
            if(!tmp.empty()) {
                std::cout << "Jobs started running this tick:" << std::endl; 
                for( job j : tmp ) {
                    my_system::run_job(j);
                    std::cout << j << std::endl;
                }
            }
        }        
        my_system::wait_queue.tick();

        my_system::mtx.unlock(); 
    } 
    
    bool is_done( ) {
        return my_system::run_queue.empty();
    }  
}
