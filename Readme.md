# Readers-Writers Problem
The readers-writers problem is a classical problem of process synchronization,  It deals with the situation where multiple threads of execution (processes or threads) need to access a shared resource, where some threads only read from the resource, while others may also write to it. 
## Problem
 In this system, multiple redears are allowed to read files simutaneously but while a writer is writing(editing) a file, no reader is allowed to read and no writer is allowed to write. This whole process needs synchronization.The goal is to ensure that all threads can access the resource without interfering with each other.

### Classical Solution
 In the classical solution, Either readers are given priority over writers or vice versa. This creates the problem of **starvation**.
 In this, we have following data structures to implement **readers-first** solution.

```
//Declarations and initializations
semaphore rw mutex = 1;
semaphore mutex = 1;
int read_count = 0;
```

The semaphores mutex and rw mutex are initialized to 1; read_count is
initialized to 0 which basically counts number of readers present currently. The semaphore rw_mutex is common to both reader and writer. 

### Writer implementation
```
do {
wait(rw_mutex);

//write

signal(rw_mutex);
} while (true);
```

### Reader implementation
```
do { 

wait(mutex);
read_count++;
if (read_count == 1){
wait(rw_mutex);
   }
signal(mutex);

//reading

wait(mutex);
read_count--;
if (read_count == 0){
     signal(rw_mutex);
     //rw_mutex released only if no readers present
     }
signal(mutex);
} while (true);
```

Source for classical(starved) solution: _Operating Systems Concpts~ Abraham Silberschatz_

### How starvation occurs in classical solution:
   Notice that when read_count is greater than 0 (i.e. even if one reader is present), rw_mutex is not released by readers. Thus if a writer is waiting for writing and new readers keep on coming, writer will never get chance to write and hence will starve.


 Now we present how starvation can be avoided. A generic idea is proposed below and **exact details of implementation are given in form of comments in the pseudocode.**
 ## Starve Free Readers-Writers Problem

In the starve-free solution, the `newSem `semaphore is used in addition to the `readSem` and `write_mutex` semaphore. This must be acquired before any reader or writer  acquires the `rw_mutex` or before entrance of any reader in its critical section. This eliminates the risk of starvation as if writer comes before readers, he will have the `newSem` and thus he won't be waiting for readers.

Even if the order of arrival is reader-> writer-> reader with some readers present in Critical section, as writer has `newSem` readers are denied the access to it.Hence when all readers leave the critical section, writer will be the first to acquire the semaphore `rw_mutex`  (because he arrived before and thus at the front of waiting queue of `rw_mutex`).Now he can perform writing and thus synchronization without starvation proceeds as both readers and writers have same preference.

