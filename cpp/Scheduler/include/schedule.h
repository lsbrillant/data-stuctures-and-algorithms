#ifndef SCHEDULE_H
#define SCHEDULE_H 1 

#include <queue>
#include <vector>
#include <string>
#include <atomic>
#include <iostream>

/* using std::atomic_int for mutual exclusion in a multithreaded enviroment */
extern std::atomic_int numjobs;
struct job 
{
    std::string job_description;
    int n_procs;
    int n_ticks;
    int j_id;
    int wait_t;
    int run_t;
    
    job( std::string desc, int ticks, int procs=1 ) : 
        job_description{ desc }, 
            n_procs{ procs }, 
                n_ticks{ ticks }, 
                    j_id{ ++numjobs }, 
                        wait_t{ 0 },
                            run_t{ ticks } { }

    friend std::ostream & operator<<( std::ostream& out, job & j ){
        out << "Job: " << j.j_id 
            << "\n\tdescription: " << j.job_description 
            << "\n\tprocs: " << j.n_procs 
            << "\n\tticks: " << j.n_ticks
            << "\n\twait time: " << j.wait_t << "\n";
        return out;
    }
};


bool shortest_job_next( const job & x, const job & y ); 
//{
//    return x.n_ticks > y.n_ticks;    
//}

bool highest_response_ratio_next( const job & x, const job & y );
//{
//    return ((float)x.wait_t / (float)x.n_ticks) > ((float)y.wait_t / (float)y.n_ticks);
//}

bool first_come_first_serve( const job & x, const job & y );
//{
//    return x.j_id > y.j_id;
//}
bool custom_nonsense( const job & x, const job & y );
//{
//    return (x.n_procs + x.n_ticks + x.j_id - x.wait_t) > (y.n_procs + y.n_ticks + y.j_id - y.wait_t);
//}
#endif
