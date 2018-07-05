threadtest: schedule.o system.o threadtest.o
	g++ schedule.o system.o threadtest.o -o threadtest -pthread -std=c++11

threadtest.o: src/threadtest.cpp include/system.h
	g++ -c src/threadtest.cpp -pthread -I include -std=c++11

schedule.o: src/schedule.cpp include/schedule.h
	g++ -c src/schedule.cpp -I include -std=c++11

system.o: include/schedule.h include/system.h include/runqueue.h include/waitqueue.h src/system.cpp
	g++ -c src/system.cpp -I include -std=c++11

clean:
	rm schedule.o system.o threadtest.o threadtest

