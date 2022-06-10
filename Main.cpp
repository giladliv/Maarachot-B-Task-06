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
    cout << sched._gamesVect[0][0] << endl;
    cout << sched._games["f"].at(0) << endl;
    unordered_map<string, unordered_map<int, Team>> m;
    m["hello"] = {};
    Team a("a", 0.6);
    Team b("b", 0.6);
    m["hello"][1] = Team("7", 0.8);
    
    return 0;
}