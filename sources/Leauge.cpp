#include "Leauge.hpp"

using ball::Leauge;
using ball::Game;
using ball::Team;

Leauge::Leauge(const vector<Team>& teams)
{
    if (teams.size() > NUM_TEAMS)
    {
        throw runtime_error("number of leagues must be positive integer and between 0 and " + to_string(NUM_TEAMS));
    }
    for (const Team& team: teams)
    {
        addTeam(team);
    }
    setRandomTeams(NUM_TEAMS - teams.size());
}

Leauge::Leauge(unsigned int numOfInput)
{
    if (numOfInput < 0 || numOfInput > NUM_TEAMS)
    {
        throw runtime_error("number of leagues must be positive integer and between 0 and " + to_string(NUM_TEAMS));
    }
    setLeaugesFromOuter(numOfInput);
    setRandomTeams(NUM_TEAMS - numOfInput);
}

void Leauge::setRandomTeams(unsigned int num)
{
    double skillRandNum = 0;
    string strName;
    srand(time(NULL));
    if (num < 0 || num > NUM_TEAMS)
    {
        throw runtime_error("number of leagues must be positive integer and between 0 and " + to_string(NUM_TEAMS));
    }
    for (char ch = 'a'; ch <= 'z' && teamSize() < num; ch++)
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
    if (_teams.size() == NUM_TEAMS)
    {
        throw runtime_error("reached to the max of teams");
    }
    if (isTeamExists(name))
    {
        throw runtime_error("cannot add a team with the same name");
    }
    _teams[name] = Team(name, skill);
    _teamsNames.push_back(name);
}

void Leauge::addTeam(const string& name, const string& skill)
{
    double skillNum = Team::strToDouble(skill);
    addTeam(name, skillNum);
}

void Leauge::addTeam(const Team& team)
{
    addTeam(team.getName(), team.getSkill());
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
    return _teamsNames; //vector<string>(_teamsNames.begin(), _teamsNames.end());
}

Team& Leauge::getTeam(const string& name)
{
    if (!isTeamExists(name))
    {
        throw runtime_error("the team doesn't exist, please try another one");
    }
    return _teams[name];
}

ostream& ball::operator<<(ostream& os, const Leauge& leauge)
{
    for (const string& name: leauge._teamsNames)
    {
        os << leauge._teams.find(name)->second << endl;
    }
    return os;
}

void Leauge::setLeaugesFromOuter(unsigned int numOfLeaeges)
{
    if (numOfLeaeges < 0 || numOfLeaeges > NUM_TEAMS)
    {
        throw runtime_error("number of leagues must be positive integer and between 0 and " + to_string(NUM_TEAMS));
    }

    for (int i = 1; i <= numOfLeaeges; i++)
    {
        try
        {
            cout << "Team #" << i << endl;
            addTeam(Team::getTemFromInput());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            // take a step back - there will no change because of the adding at the end of the loop
            fflush(stdin);
            i--;
        }
    }
}

void Leauge::removeSpacesFromEdges(string& s)
{
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\n'))
    {
        // erase the 1st char
        s.erase(0, 1);
    }

    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\n'))
    {
        s.pop_back();
    }
}
