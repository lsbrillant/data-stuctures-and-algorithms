#include "system.h"
//#include "schedule.h"


int main()
{
    my_system::submit_job("test1", 4, 1);
    my_system::submit_job("testy", 4, 101);
    my_system::submit_job("test2",5,20);
    my_system::submit_job("test3", 73, 3);
    my_system::submit_job("test4",30,70);
    my_system::submit_job("test5", 4, 1);
    my_system::submit_job("test6",5,20);
    my_system::submit_job("test7", 73, 3);
    my_system::submit_job("test8",30,70);

    
    my_system::tick();
    while( ! my_system::is_done() ) {
        my_system::tick();
    }

    return 0;
}
