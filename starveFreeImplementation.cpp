// names for most of the variables, functions have been insipred by the classical solution .

class semaphore
{ // we accomodate binary and counting semaphores in same class.

public:
    long long availableResources;

    semaphore(int n)
    { // here n is the number of instances of resource 
        availableResources = n;// initially availableResources will be equal to num of instances.
    }

    void signal()
    {            // standard V(S) method
        availableResources++; // availableResources of semaphore is incremented as signal is called.
        return;
    }

    void wait()
    { // standard P(S) method
        while (availableResources <= 0)
        {
            ; // do nothing as semaphore is acquired by some other process
        }
        availableResources--;
    }
};

//___________________________________________________________________________________________________________

// INITIALIZATION and variable declaration for starve free reader-writer problem

long long numOfResources = 1; // can be varied but then semaphore type may change

// rw_mutex and readSem are standard semaphores in classical solution of readers writers problem

semaphore rw_mutex(numOfResources); // instantiating rw_mutex semaphore

int rdCnt = 0; // maintains readers count

semaphore readSem(numOfResources);

//  The above three data structures are the same as above in the classical solution

semaphore newSem(numOfResources); // The new semaphore is used at begining of both processes
                                  // which both try to acquire at begining.
                                  // both the redears and writers have equal priority for acquiring

//___________________________________________________________________________________________________________

//  Starve free writers implementation
void starveFreeWriter(int PID)
{

    newSem.wait();
    //  the writer also waits for the entry mutex first can be acquired also when reader is in critical section

    rw_mutex.wait();

    newSem.signal();
    //  once the writer is ready to enter the critical section it frees the newSem
    //   This newSem semaphore can be acquired by anyone arriving first
    // ***** CRITICAL SECTION ***** //

    //  the critical section can be accessed by a writer only if they have acquired the rw_mutex

    rw_mutex.signal();
}

//____________________________________________________________________________________________________________

//  STARVE-FREE READER CODE
void starveFreeReader(int PID)
{ // PID is process id of the reader
    //  called everytime a new reader arrives

    newSem.wait();
    //  can be acquired by writers/readers with equal priority with mutual exclusion

    readSem.wait(); // to implement mutual exclusion so that race condition doesnt happen  for rdCnt

    ++rdCnt;

    if (rdCnt == 1)
    { // it would be the first reader

        rw_mutex.wait();
    }

    readSem.signal(); // now readers that have acquired the newSem can access the rdCnt

    newSem.signal();
    //  Once the reader is ready to enter the critical section, it frees the newSem semaphore
    //  This newSem semaphore can be acquired by any reader arriving first

    // ***** CRITICAL SECTION ***** //

    readSem.wait(); // mutual exclusion for rdCnt;
    --rdCnt;
    readSem.signal();

    if (rdCnt == 0)
    {
        rw_mutex.signal();
        // the last reader frees the rw_mutex
    }
}

// starvation problem has been taken care of and none would starve. Thus, a starve-free approach to the Reader-Writer problem.

int main()
{
    while (true)
    {
        int PID; // PID is process id of a process
        starveFreeWriter(PID);
        starveFreeReader(PID);
    }
    return 0;
}
