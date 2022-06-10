#include <iostream>
#include "Schedule.hpp"

using namespace std;
using namespace ball;


int main()
{
    cout << "me" << endl;
    Leauge leauge;
    Schedule sched(leauge);
    sched.runAllGames();
    cout << leauge << endl << endl;
    cout << sched << endl;
    return 0;
}