# Job-Scheduler

## Objective
- To Design a component called “Director” for a system which execute all jobs sent to it. 
- Jobs sent to Director are to be executed on the free CPUs at that time.
- Director has to decide the priority of job on the basis of given conditions.
- Director should be able to process different queries - storing jobs, assigning jobs to CPUs and have a history of total jobs till some timestamp.

## Data structure used and methodology 
- First of all we declared a class Job with the following data members.
  - pid  :  Process ID
  - ts   :  Timestamp
  - st   :  Starting time of the process when its waiting period has ended
  - et   :  Ending time of the process when it frees the CPU
  - dur  :  Working time of the process
  - imp  :  Importance of the process
  - orig :  Name of originating system
  - inst :  Job instruction
- We took two priority queues q and e_tim  and a vector jobs.
  - q that keeps track of the processes that are waiting at any time in accordance with the priorities  given in the problem. 
  - e_tim maintains the ending time of all the jobs currently in the CPU. This helps in calculating the number of free CPUs at any time.
  - jobs stores the list of all the jobs seen so far. This helps in query operations.
- We preferred to store pointers to the actual objects instead of actual objects due to the following reason:
  - Smaller in size leading to time and memory efficient code
  - Reuse of same object in all the vectors and priority queues.
- Job operation 
  - It creates a Job object in the dynamic memory
  - Adds the pointer to that object to the jobs vector
  - Adds it again to the priority queue q of all waiting jobs
  - Time Complexity : log (n) in the number of jobs
- Assign operation 
  - Read the value of time and k 
  - Clear all the jobs finished by time with the help of e_tim  priority queue
  - Calculate the number of free CPUs
  - Clear the same no. of  jobs from q 
  - Update the end time of the jobs assigned
  - Time Complexity : log(n) + log(m) where n is the number of running jobs and m is the number of queued jobs
- 


    
