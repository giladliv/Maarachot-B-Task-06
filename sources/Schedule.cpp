#include "Schedule.hpp"

using ball::Schedule;

Schedule::Schedule(Leauge& leauge) : _league(leauge)
{
    createSeason();
    _genrator = mt19937{_randDev()};
    // this it the best distribution for the ranges
    _distributor = std::normal_distribution<>{ MIN_GUEST_POINTS / 2, MIN_GUEST_POINTS / 6};
}

/**
 * @brief according to the Round Robin tournnament creates the vector of season that contains each round
 * 
 */
void Schedule::createSeason()
{
    vector<string> teamsNames = _league.getTeamsList();
    _games.clear();
    for (unsigned int roundNum = 0; roundNum < _league.teamSize(); roundNum++)
    {
        vector<Game> gamesOfRound;
        unsigned int len = teamsNames.size();
        for (unsigned int i = 0; i < len / 2; i++)
        {
            // take a team and its mirror
            Team& team1 = _league.getTeam(teamsNames[i]);
            Team& team2 = _league.getTeam(teamsNames[len - 1 - i]);
            
            // if the round is even then the home is the first else is the guest 
            Team& home = (roundNum % 2 == 0) ? team1 : team2;
            // if the round is even the guest is the second
            Team& guest = (roundNum % 2 == 0) ? team2 : team1;
            gamesOfRound.push_back(Game(home, guest));
        }
        _games.push_back(gamesOfRound);
        //get the last team
        string lastTeam = teamsNames.back();
        // remove it from vector
        teamsNames.pop_back();
        // put it to the second var in the team
        teamsNames.insert(teamsNames.begin() + 1, lastTeam);

    }
}

unsigned int Schedule::genHomePoints()
{
    unsigned int points = 0;
    do
    {
        // add 50 to number between 0-50
        points = MIN_GUEST_POINTS + _distributor(_genrator);
    } while (points < MIN_HOME_POINTS || points > MAX_POINTS);
    return points;
}

unsigned int Schedule::genGuestPoints()
{
    unsigned int points = 0;
    do
    {
        // add 50 to number between 0-50
        points = MIN_GUEST_POINTS + _distributor(_genrator);
    } while (points < MIN_GUEST_POINTS || points > MAX_POINTS);
    return points;
}

void Schedule::runAllGames()
{
    for (unsigned int i = 0; i < _games.size(); i++)
    {
        for (unsigned int j = 0; j < _games[i].size(); j++)
        {
            _games[i][j].setHomePoints(genHomePoints());
            _games[i][j].setGuestPoints(genGuestPoints());
            _games[i][j].addToBest();
        }
    }
}
