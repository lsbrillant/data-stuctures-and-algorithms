#ifndef MY_SYSTEM_H
#define MY_SYSTEM_H 1

#include <atomic>
#include <string>
#include "schedule.h"

namespace my_system 
{
    extern std::atomic_int total_procs;
    extern bool(*schedule)(const job&, const job&);
    
    void submit_job( job& );
    void submit_job( std::string, int, int );
    
    void tick( );
    bool is_done( ); 
}
#endif
