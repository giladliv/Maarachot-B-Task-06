#include "doctest.h"
#include "sources/Statistics.hpp"

using namespace std;
using namespace ball;


TEST_CASE("CHEACK TEAM")
{
    CHECK_THROWS(Team("Harry Potter", -1.0));
    CHECK_THROWS(Team("Harry Potter", -0.5));
    CHECK_THROWS(Team("Harry Potter", 1.1));
    CHECK_THROWS(Team("Harry Potter", 100));
    CHECK_NOTHROW(Team("Harry Potter", 0.5));
    CHECK_NOTHROW(Team("Harry Potter", 1));
}

TEST_CASE("CHECK LUEAGE")
{
    CHECK_THROWS(Leauge({Team("Voldemort", 0.5), Team("Voldemort", 0.5)}));
    CHECK_THROWS(Leauge({Team("Voldemort", 0.5), Team("Voldemort", 0.6)}));
    CHECK_NOTHROW(Leauge());
    CHECK_NOTHROW(Leauge({Team("Harry", 0.5), Team("Ron", 0.5)}));

    vector<Team> teams;
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        teams.push_back(Team(string() + ch, 0.5));
    }
    CHECK_THROWS(Leauge(teams));
    
    Leauge l;
    char letter = 'a';
    for (const string& str: l.getTeamsList())
    {
        CHECK_EQ(str, string() + letter++);
    }
    vector<string> names{"Harry", "Ron", "Hermione", "Luna", "Neville", "Dumbledore"};
    teams.clear();

    for (const string& str: names)
    {
        teams.push_back(Team(str, 0.5));
    }

    Leauge league{teams};
    unsigned int len = NUM_TEAMS - names.size();
    letter = 'a';
    for (int i = 0; i < len; i++)
    { 
        names.push_back(string() + letter++);
    }

    for (const string& str: league.getTeamsList())
    {
        CHECK_EQ(str, string() + letter++);
    }
}

TEST_CASE("check statistics")
{
    Leauge leauge;
    Schedule schedule(leauge);
    Statistics stats(schedule);
    // did not ran the games
    CHECK_THROWS(stats.printTotalGame());
    CHECK_THROWS(stats.printTotalGame());
    CHECK_THROWS(stats.topTeams(5));
    CHECK_THROWS(stats.longestWinRow());
    CHECK_THROWS(stats.longestLoseRow());
    CHECK_THROWS(stats.teamsThatScoredMore());
    CHECK_THROWS(stats.printSkillVsPoints());
}