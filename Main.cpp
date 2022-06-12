#include <iostream>
#include "sources/Schedule.hpp"
#include "sources/Statistics.hpp"

using namespace std;
using namespace ball;


int main()
{
    cout << "me" << endl;
    Leauge leauge(false);
    Schedule sched(leauge);
    sched.runAllGames();
    //cout << leauge << endl << endl;
    cout << sched << endl;

    Statistics stats(sched);
    stats.longestWinRow();
    stats.longestLoseRow();
    return 0;
}