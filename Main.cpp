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
    //cout << leauge << endl << endl;
    //cout << sched << endl;
    cout << sched._gamesVect[0][0] << endl;
    sched.pr();
    unordered_map<string, unordered_map<unsigned int, Game>> m{};
    
    Team a("a", 0.6);
    Team b("b", 0.6);
    m["hello"].emplace(1, Game("7", "0.8"));
    cout << m["hello"].at(1) << endl;

    return 0;
}