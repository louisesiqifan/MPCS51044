all: HelloThreads DistributedCounterTest1

HelloThreads: HelloThreads.cpp
	g++ -std=c++20 HelloThreads.cpp -o HelloThreads -lpthread

DistributedCounterTest1: DistributedCounterTest1.cpp DistributedCounter1.h
	g++ -std=c++20 DistributedCounterTest1.cpp -o DistributedCounterTest1 -lpthread
