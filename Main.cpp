#include <iostream>
#include "sources/Schedule.hpp"

using namespace std;
using namespace ball;


int main()
{
    cout << "me" << endl;
    Leauge leauge(false);
    Schedule sched(leauge);
    sched.runAllGames();
    cout << leauge << endl << endl;
    cout << sched << endl;
    cout << sched.getGame("c", 0) << endl;
    cout << sched.getGame("b", 0) << endl;

    return 0;
}