HelloThreads.cpp and DistributedCounter1.cpp are updated to use jthread instead of thread.
I like this version better because it is very likely in real life coding that .join() is forgotten, and will result in core dumped if at program termination time threads are not yet destroyed. With jthread we no longer have this problem.
