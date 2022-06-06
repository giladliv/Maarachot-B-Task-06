#include "Leauge.hpp"

using ball::Leauge;
using ball::Game;
using ball::Team;

Leauge::Leauge()
{
    setRandomTeams(NUM_TEAMS);
}


void Leauge::setRandomTeams(int num)
{
    double skillRandNum = 0;
    string strName;
    for (char ch = 'a'; ch <= 'z' && teamSize() < num && teamSize() < NUM_TEAMS; ch++)
    {
        strName = ch;
        if (!isTeamExists(strName))
        {
            // rand a number with its number 0 <= n <= 1
            skillRandNum = (double)(rand() % RAND_MAX) / (double)(NUM_RAND_MAX);
            addTeam(strName, skillRandNum);
        }   
    }
}

void Leauge::addTeam(const string& name, double skill)
{
    if (isTeamExists(name))
    {
        throw runtime_error("cannot add a team with the same name");
    }
    _teams[name] = Team(name, skill);
    _teamsNames.push_back(name);
}

bool Leauge::isTeamExists(const string& name)
{
    return (_teams.count(name) != 0);
}

unsigned int Leauge::teamSize()
{
    return _teams.size();
}

vector<string> Leauge::getTeamsList() const
{
    return _teamsNames;
}

Team& Leauge::getTeam(const string& name)
{
    if (!isTeamExists(name))
    {
        throw runtime_error("the team doesn't exist, please try another one");
    }
    return _teams[name];
}

