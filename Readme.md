# Readers-Writers Problem
The readers-writers problem is a classical problem of process synchronization, it relates to a data set such as a file that is shared between more than one process at a time. Among these various processes, some are Readers - which can only read the data set; they do not perform any updates, some are Writers - can both read and write in the data sets.
## Problem
 In this system, multiple redears are allowed to read files simutaneously but while a writer is writing(editing) a file, no reader is allowed to read and no writer is allowed to write. This whole process needs synchronization.

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
initialized to 0 which basically counts number of readers present currently. The semaphore rw mutex is common to both reader and writer. 

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

Source for classical solution: _Operating Systems Concpts~ Abraham Silberschatz_

### How starvation occurs in classical solution:
   Notice that when read_count is greater than 0 (i.e. even if one reader is present), rw_mutex is not released by readers. Thus if a writer is waiting for writing and new readers keep on coming, writer will never get chance to write and hence will starve.


 Now we present how starvation can be avoided. A generic idea is proposed below and **exact details of implementation are given in form of comments in the pseudocode.**
 ## Starve Free Readers-Writers Problem

In the starve-free solution, the `newSem `semaphore is used in addition to the `read_mutex` and `write_mutex` semaphore. This is first required to be obained before anyone (the reader or the writer) accesses the `rw_mutex` or before anyone (any reader) enters the critcal section directly. This solves the problem of starvation as if readers keep coming one after another, then this won't starve the writers as it used to in first readers problem.

 Here, if a writer comes in between two readers, and even if some readers are still present in the critical section,the writer would have already acquired the `newSem` and thus the reader can't acquire it and thus after the existing readers exit the critical section, the writer that was waiting would be the first to acquire `rw_mutex` (as it will be at front in the queue of `rw_mutex`) and thus acquires it. Now the writer can enter the critical section and the same process would repeat. Thus readers and writers are now at equal priority and none would starve. Doing this also preserves the advantage of readers not having to acquire the `rw_mutex` everytime, when some other reader is already present. Thus an effiecient and starve-free solution to the Reader-Writer problem.
