# Dining Philosophers
Code Description:
The following code is a modification of the dining philosophers problem that deals with allocation of resources in a way such that
no deadlocks occur throughout. In our version, we deal with resource allocation of two kinds of resources: (1)Forks and (2)Bowls
In my implementation, I treat the pair of bowls as a single entity, as both the bowls need to be allocated together to the philosopher.
The given code utilises the pthread library for execution of the semaphore and performs resource allocation in the infinite loop.
The code provides a deadlock free solution to custom number of philosophers.

## Files
1) A4.c (blocking version)
2) A42.c (non blocking version)

## Code Implementation
The structure for the semaphore my_semaphore has been implemented using the pthread library. The semaphore structure consists of the following:
-The semaphore value
-The mutex lock corresponding to the semaphore
-The conditional variable of the semaphore

The semaphore is declared using the my_semaphore structure. The semaphore contains the following primitive functions for 
execution:

1. Wait()
2. Signal()
3. Signal_printvalue()

*The wait() is invoked when a philosopher enters and the signal() is invoked when philosopher utilises the resource.
By careful utilisation of wait() and signal() function on the counting semaphore deadlocks are avoided.*

a) Blocking Version

* First the semaphore value is acquired
* Then the value of the semaphore is modified under the critical section of the code.
* The semaphore performs blocking wait using pthread_cond_wait(). It performs a conditional wait on the semaphore till it is required to block all the other
threads that access the value of the sempahore.
* It peforms blocking signal() operation using pthread_cond_signal(). This function performs a conditional signal operation on the sempahore 
when the value of the semaphore is acquired.


b) Non-Blocking Version

* First the semaphore value is acquired
* Then the value of the semaphore is modified under the critical section of the code.
* The semaphore performs non blocking wait. The semaphore value is simply modified on the critical section of the code. The mutex is unlocked upon successful modification.
The semaphore does not block any secondary threads. Hence by performing a non blocking wait, mulitiple threads perform blocking in a synchronized fashion.
It performs a conditional wait on the semaphore till it is acquired to block all the other
threads that access the value of the sempahore.
* It peforms signal() operation using pthread_cond_signal(). This function performs a conditional signal operation on the sempahore 
when the value of the semaphore is acquired.
