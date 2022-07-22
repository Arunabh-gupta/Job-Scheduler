## Explanation

The question was a simple scheduler problem with different processes having different priorities working on a real-time system.

To begin with, we declared the class to represent the Jobs. It had the following data members:

- pid : Process ID
- ts : Timestamp
- st : Starting time of the process when its waiting period has ended
- et : Ending time of the process when it frees the CPU
- dur : Working time of the process
- imp : Importance of the process
- orig : Name of originating system
- inst : Job instruction

The problem was solved using a priority queue "q" that keeps track of the
processes that are waiting at any time in accordance with the priorities
given in the problem. Another priority queue "e_tim" maintains the ending time
of all processes currently in the CPU. Apart from that, a vector "jobs" stores
all the jobs already given for historical analysis.

Our basic approach was to read the lines one after another and then depending upon
the choice, different task was to be carried out:

"job" : It was the easiest of the tasks. We just had to dynamically allocate a Job
object in heap memory and then input all the parameters of the Job. Then,
we pushed the pointer to both "q" and "jobs".
Time Complexity : log(n) where n is total number of jobs
log(n) factor due to priority queue

"assign" : Here, we read the value of time and "k" and then cleared all the jobs
that must have finished by that time, thus calculating the number of free
CPUs by that time. We did that with the help of "e_tim" priority queue.
After that, we determined the number of jobs to be assigned and cleared
the same number of jobs from the "q". It was during this time that we updated
the start time and end time of the jobs. We also pushed the end time of the
job into "e_tim".
Time Complexity : log(n) + log(m) where n is the number of running jobs and
m is the number of queued jobs

"query origin" : After all the task done by "assign" and "job", all we had to do here
is to iterate over all the jobs in the "jobs" vector, and select all queued
jobs originating from the given system. Then, we pushed them into a temporary
priority queue and displayed them in order of decreasing priority.
Time Complexity : n log(n) where n is number of waiting jobs.

"query k" : Its operation was also similar to above query. We pushed all the queued
jobs into a temporary priority queue and then displayed the top "k".
Time Complexity : n log(n) where n is number of waiting jobs.

