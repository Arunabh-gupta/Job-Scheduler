#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;
class Job // class declaration
{
public:
    ll pid, ts, st = -1, et, dur; // data members
    int imp;
    string orig, inst;
};
istream &operator>>(istream &in, Job *j) // overloading >> for input operations
{
    in >> j->ts >> j->pid >> j->orig >> j->inst >> j->imp >> j->dur;
    j->st = -1;
    return in;
}
ostream &operator<<(ostream &out, const Job *j) // overloading << for output operations
{
    out << "job " << j->ts << " " << j->pid << " " << j->orig << " " << j->inst << " " << j->imp << " " << j->dur;
        return out;
}
struct comparator // functor for given custom priority in priority queue
{
    bool operator()(const Job *j1, const Job *j2) const
    {
        if (j1->imp != j2->imp)
            return j1->imp < j2->imp;
        else if (j1->ts != j2->ts)
            return j1->ts > j2->ts;
        else
            return j1->dur > j2->dur;
    }
};
struct comp // functor for making a min-heap
{
    bool operator()(const ll i, const ll j) const
    {
        return i > j;
    }
};
priority_queue<Job *, vector<Job *>, comparator> q; // global variables declaration
priority_queue<ll, vector<ll>, comp> e_tim;
vector<Job *> jobs;
int main()
{
    // freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(0); // for fast input
    ll limit;
    string s;
    cin >> s >> limit; // input number of CPUs
    ll fre = limit;    // variable to store number of free CPUs at anymoment
    string ch,query;
    ll tim, k, assigned, fin; // declaration of some more variables
    while (cin >> ch)
    { // input lines one by one
        if (ch == "job")
        {                      // if job command
            Job *j = new Job;  // instantiate Job object
            cin >> j;          // input parameters
            q.push(j);         // pushed into waiting queue
            jobs.push_back(j); // pushed into vector of jobs
        }
        else if (ch == "assign")
        { // assign command
            cin >> tim >> k;
            while (!e_tim.empty())
            { // remove all jobs that are over by this time
                if (e_tim.top() <= tim)
                {
                    fre++; // increment the number of free CPUs
                    e_tim.pop();
                }
                else
                    break; // break when all jobs are removed
            }
            assigned = min(min(k, fre), (ll)q.size()); // number of jobs to be assigned
            fre -= assigned;                           // decrease the number of free CPUs
            while (assigned--)
            {
                Job *temp = q.top();  // assign jobs one by one according to priority
                cout << temp << "\n"; // display them
                q.pop();              // remove from waiting queue
                temp->st = tim;       // update start and end time
                temp->et = tim + temp->dur;
                e_tim.push(temp->et); // push end time of the job into e_tim heap
            }
        }
        else
        {
            cin >> tim >> query; // query operation
            ll qll = 0;
            int flag = 0; // to check which query operation is asked
            for (int i = 0; i < query.length(); i++)
            {
                if (!(query[i] >= '0' && query[i] <= '9'))
                { // check if any alphanumeric character is found
                    flag = 1;
                    break; // if found, then update flag and break
                }
                qll = qll * 10 + query[i] - '0'; // else convert to decimal
            }
            if (flag)
            {                                                          // if query for originating system
                priority_queue<Job *, vector<Job *>, comparator> temp; // temporary priority queue
                for (ll i = 0; i < jobs.size(); i++)
                { // iterate all jobs one by one
                    Job *j = jobs[i];
                    if (j->ts > tim) // break if timestamp is greater than query time
                        break;
                    if ((j->st == -1 || j->st > tim) && j->orig == query)
                        temp.push(j); // push the selected job
                }
                while (!temp.empty())
                {
                    cout << temp.top() << "\n"; // display the selected jobs one by one
                    temp.pop();                 // according to priority
                }
            }
            else
            {                                                          // query top k jobs
                priority_queue<Job *, vector<Job *>, comparator> temp; // temporary heap
                for (ll i = 0; i < jobs.size(); i++)
                { // iterate similarly
                    Job *j = jobs[i];
                    if (j->ts > tim)
                        break;
                    if (j->st == -1 || j->st > tim)
                        temp.push(j);
                }
                ll i = min((ll)temp.size(), qll); // check if k is larger than heap size
                while (i--)
                {
                    cout << temp.top() << "\n"; // display top k jobs
                    temp.pop();
                }
            }
        }
    }
    return 0; // return
}
