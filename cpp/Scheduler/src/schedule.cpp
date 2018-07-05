#include "schedule.h"

std::atomic_int numjobs(0);

bool shortest_job_next( const job & x, const job & y ) 
{
    return x.n_ticks > y.n_ticks;    
}

bool highest_response_ratio_next( const job & x, const job & y )
{
    return ((float)x.wait_t / (float)x.n_ticks) > ((float)y.wait_t / (float)y.n_ticks);
}

bool first_come_first_serve( const job & x, const job & y )
{
    return x.j_id > y.j_id;
}
bool custom_nonsense( const job & x, const job & y )
{
    return (x.n_procs + x.n_ticks + x.j_id - x.wait_t) > (y.n_procs + y.n_ticks + y.j_id - y.wait_t);
}
