#ifndef RUNQUEUE_H
#define RUNQUEUE_H 1

#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include "schedule.h"

static bool run_comp( const job & x, const job & y ) {
    return x.run_t > y.run_t;
}

class RunQueue : public std::priority_queue<job, std::vector<job>, bool(*)(const job&, const job&)>
{
    typedef std::priority_queue<job, std::vector<job>, bool(*)(const job&, const job&)> parent;

    public:
        RunQueue( ) : parent(&run_comp) {}

        friend std::ostream& operator<<( std::ostream& out, RunQueue& RQ ) {
            for( job j : RQ.c ) {
                out << j;
            }
            return out;
        }

        job top_pop( ) {
            job ret = parent::top();
            parent::pop();
            return ret;
        }

        void tick( ) {
            for( job & j : this->c ) {
                j.run_t--;
            }
            std::make_heap(c.begin(), c.end(), comp);
        } 
};
#endif
