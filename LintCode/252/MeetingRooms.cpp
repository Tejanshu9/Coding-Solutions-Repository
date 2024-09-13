#include <vector>
#include <algorithm>

using namespace std;

// Definition of Interval
class Interval {
public:
    int start, end;
    Interval(int start, int end) : start(start), end(end) {}
};

class Solution {
public:
    /**
     * @param intervals: an array of meeting time intervals
     * @return: if a person could attend all meetings
     */
    bool canAttendMeetings(vector<Interval> &intervals) {
        
        sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
            return a.start < b.start;
        });

       
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start < intervals[i - 1].end) {
                return false; 
            }
        }

        return true; 
    }
};
