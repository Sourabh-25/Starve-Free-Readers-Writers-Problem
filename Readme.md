# Readers-Writers Problem
The readers-writers problem is a classical problem of process synchronization, it relates to a data set such as a file that is shared between more than one process at a time. Among these various processes, some are Readers - which can only read the data set; they do not perform any updates, some are Writers - can both read and write in the data sets.
## Problem
 In this system, multiple redears are allowed to read files simutaneously but while a writer is writing(editing) a file, no reader is allowed to read and no writer is allowed to write. This whole process needs synchronization.

### Classical Solution
 In the classical solution, Either readers are given priority over writers or vice versa. This creates the problem of **starvation**.
 
 Now we present how starvation can be avoided. A generic idea is proposed below and **exact details of implementation are given in form of comments in the pseudocode.**
 ## Starve Free Readers-Writers Problem

In the starve-free solution, the `newSem `semaphore is used in addition to the `read_mutex` and `write_mutex` semaphore. This is first required to be obained before anyone (the reader or the writer) accesses the `rw_mutex` or before anyone (any reader) enters the critcal section directly. This solves the problem of starvation as if readers keep coming one after another, then this won't starve the writers as it used to in first readers problem.

 Here, if a writer comes in between two readers, and even if some readers are still present in the critical section,the writer would have already acquired the `newSem` and thus the reader can't acquire it and thus after the existing readers exit the critical section, the writer that was waiting would be the first to acquire `rw_mutex` (as it will be at front in the queue of `rw_mutex`) and thus acquires it. Now the writer can enter the critical section and the same process would repeat. Thus readers and writers are now at equal priority and none would starve. Doing this also preserves the advantage of readers not having to acquire the `rw_mutex` everytime, when some other reader is already present. Thus an effiecient and starve-free solution to the Reader-Writer problem.