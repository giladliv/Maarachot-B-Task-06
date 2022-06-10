#include "Schedule.hpp"

using ball::Schedule;

constexpr double AVG = 2.0;
constexpr double DSTR = 6.0;

Schedule::Schedule(Leauge& leauge) : _league(leauge), _isSeasonPointsSet(false), _numSeasons(0)
{
    _genrator = mt19937{_randDev()};
    // this it the best distribution for the ranges
    _distributor = std::normal_distribution<>{ (MIN_GUEST_POINTS / AVG), (MIN_GUEST_POINTS / DSTR)};

    createSeason();

    //me
}

/**
 * @brief according to the Round Robin tournnament creates the vector of season that contains each round
 * 
 */
void Schedule::createSeason()
{
    if (_league.teamSize() != NUM_TEAMS)
    {
        throw runtime_error("not enough teams in leauge - make sure its " + to_string(NUM_TEAMS));
    }
    
    vector<string> teamsNames = _league.getTeamsList();
    _gamesVect.clear();
    _games.clear();

    // n - 1 rounds will make each team to play one with outhers, another (n - 1) rounds will make the opposite games
    _numSeasons = 2 * (_league.teamSize() - 1);
    for (unsigned int roundNum = 0; roundNum < _numSeasons; roundNum++)
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
        _gamesVect.push_back(gamesOfRound);
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
        points = MIN_GUEST_POINTS + (unsigned int)_distributor(_genrator);
    } while (points < MIN_HOME_POINTS || points > MAX_POINTS);
    return points;
}

unsigned int Schedule::genGuestPoints()
{
    unsigned int points = 0;
    do
    {
        // add 50 to number between 0-50
        points = MIN_GUEST_POINTS + (unsigned int)_distributor(_genrator);
    } while (points < MIN_GUEST_POINTS || points > MAX_POINTS);
    return points;
}

void Schedule::runAllGames()
{
    for (unsigned int i = 0; i < _gamesVect.size(); i++)
    {
        for (unsigned int j = 0; j < _gamesVect[i].size(); j++)
        {
            _gamesVect[i][j].setHomePoints(genHomePoints());
            _gamesVect[i][j].setGuestPoints(genGuestPoints());
            _gamesVect[i][j].addToBest();
        }
    }
    _isSeasonPointsSet = true;
}

ostream& ball::operator<<(ostream& os, const Schedule& schedule)
{
    for (unsigned int i = 0; i < schedule._gamesVect.size(); i++)
    {
        os << "Round " << (i+1) << endl;
        os << string(GAP, '*') << endl;
        for (unsigned int j = 0; j < schedule._gamesVect[i].size(); j++)
        {
            os << schedule._gamesVect[i][j] << endl;
        }

        os << string(GAP, '*') << endl << endl;
    }
    return os;
}

void Schedule::throwIfNotCreated()
{
    if (!_isSeasonPointsSet)
    {
        throw runtime_error("the games hasn't been given their points");
    }
}