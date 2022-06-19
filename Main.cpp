#include <iostream>
#include "sources/Schedule.hpp"
#include "sources/Statistics.hpp"

using namespace std;
using namespace ball;

void press_any_key();
void part1();
void part2();

void press_any_key()
{
    
}

void part1()
{
    cout << "1st run" << endl;
    press_any_key();

    Leauge leauge;
    Schedule sched(leauge);
    sched.runAllGames();
    cout << leauge << endl << endl;
    cout << sched << endl;
    press_any_key();

    Statistics stats(sched);
    stats.printTotalGame();
    stats.topTeams(5);
    stats.longestWinRow();
    stats.longestLoseRow();
    stats.teamsThatScoredMore();
    stats.printSkillVsPoints();
    press_any_key();
}

void part2()
{
    cout << "2nd run" << endl;
    press_any_key();

    Leauge leauge({Team("milwaukee bucks", 0.51), Team("Boston celtics", 0.61), 
                    Team("Golden state warriors", 0.31), Team("brooklyn nets", 0.41),
                    Team("Chigaco bulls", 0.52), Team("Phoenix suns", 0.63), 
                    Team("Philadelphia 76ers", 0.524)});
    Schedule sched(leauge);
    sched.runAllGames();
    cout << leauge << endl << endl;
    cout << sched << endl;
    press_any_key();

    Statistics stats(sched);
    stats.printTotalGame();
    stats.topTeams(5);
    stats.longestWinRow();
    stats.longestLoseRow();
    stats.teamsThatScoredMore();
    stats.printSkillVsPoints();
    press_any_key();
}

int main()
{
    part1();
    //system("clear");
    //part2();

    //system("clear");
    cout << "\n\nGoodBye" << endl;
    return 0;
}