#ifndef WAITQUEUE_H
#define WAITQUEUE_H 1

#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include "schedule.h"

class WaitQueue : public std::priority_queue<job, std::vector<job>, bool(*)(const job&, const job&)>
{
    typedef std::priority_queue<job, std::vector<job>, bool(*)(const job&, const job&)> parent;

    public:
        WaitQueue( bool(*comp)(const job&, const job&) ) : parent(comp) {}

        friend std::ostream& operator<<( std::ostream& out, WaitQueue& WQ ) {
            for( job j : WQ.c ) {
                out << j;
            }
            return out;
        }
        job top_pop( ) {
            job ret = parent::top();
            parent::pop();
            return ret;
        }
        std::vector<job> best_job_by_procs( int numprocs ) {
            std::vector<job> ret;
            std::sort_heap(c.begin(), c.end(), comp);
            for( int i = c.size()-1; i >= 0; i-- ) {
                if( c[i].n_procs <= numprocs ) {
                    ret.push_back(c[i]);
                    numprocs -= c[i].n_procs;
                    c.erase(c.begin()+i);
                }
            } 
            std::make_heap(c.begin(), c.end(), comp);
            return ret;
        }
        void tick( ) {
            for( job & j : c ) {
                j.wait_t++;
            }
            std::make_heap(c.begin(), c.end(), comp);
        } 
};
#endif
