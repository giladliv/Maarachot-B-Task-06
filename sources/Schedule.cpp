#include "Schedule.hpp"

using ball::Schedule;
using ball::Game;

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
    _games.clear();
    _gamesVect.clear();
    for (const string& str: teamsNames)
    {
        _games[str] = unordered_map<unsigned int, Game*>();
    }
    // n - 1 rounds will make each team to play one with outhers, another (n - 1) rounds will make the opposite games
    _numSeasons = 2 * (_league.teamSize() - 1);
    for (unsigned int roundNum = 0; roundNum < _numSeasons; roundNum++)
    {
        _gamesVect.push_back({});
        unsigned int len = teamsNames.size();
        for (unsigned int i = 0; i < len / 2; i++)
        {   
            // if the round is even then the home is the first else is the guest 
            string home = (roundNum % 2 == 0) ? teamsNames[i] : teamsNames[len - 1 - i];
            // if the round is even the guest is the second
            string guest = (roundNum % 2 == 0) ? teamsNames[len - 1 - i] :teamsNames[i];
            _gamesVect[roundNum].push_back(Game(home, guest));
            Game g(home, guest);
            unsigned int ind = _gamesVect[roundNum].size() - 1;
            cout << _gamesVect[roundNum][ind] << endl;
            _games[home][roundNum] = &Game(home, guest);
            _games[guest][roundNum] = &Game(home, guest);
        }
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
            //_gamesVect[i][j].addToBest();
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

Game& Schedule::getGame(const string& str, unsigned int r)
{
    return (*_games[str].at(r));
}


void Schedule::pr()
{
    for (const auto& s: _games)
    {
        cout << s.first <<  " -" << endl;
        cout << string(20, '*') << endl;
        for (const auto& r : _games[s.first] )
        {
            cout << r.first << endl;
            cout << r.second << endl;
        }
        cout << endl << endl;
    }
}