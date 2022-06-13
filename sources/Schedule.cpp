#include "Schedule.hpp"


using ball::Schedule;
using ball::Game;

constexpr double AVG = 2.0;
constexpr double DSTR = 6.0;

Schedule::Schedule(Leauge& leauge) : _league(leauge), _isSeasonPointsSet(false), _totalRoundNum(0)
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
    vector<string> teamsNames = _league.getTeamsList();
    _games.clear();
    if (_league.teamSize() != NUM_TEAMS)
    {
        throw runtime_error("not enough teams in leauge - make sure its " + to_string(NUM_TEAMS));
    }
    // n - 1 rounds will make each team to play one with outhers, another (n - 1) rounds will make the opposite games
    _totalRoundNum = 2 * (_league.teamSize() - 1);
    for (unsigned int roundNum = 0; roundNum < _totalRoundNum; roundNum++)
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
    _isSeasonPointsSet = false;
    for (unsigned int i = 0; i < _games.size(); i++)
    {
        for (unsigned int j = 0; j < _games[i].size(); j++)
        {
            setGamePoints(_games[i][j]);
        }
    }
    _isSeasonPointsSet = true;
}

const vector<vector<Game>>& Schedule::getGames() const
{
    return _games;
}

ostream& ball::operator<<(ostream& os, const Schedule& schedule)
{
    for (unsigned int i = 0; i < schedule._games.size(); i++)
    {
        os << "Round " << (i+1) << endl;
        os << string(GAP, '*') << endl;
        for (unsigned int j = 0; j < schedule._games[i].size(); j++)
        {
            os << schedule._games[i][j] << endl;
        }

        os << string(GAP, '*') << endl << endl;
    }
    return os;
}

void Schedule::throwIfNotCreated() const
{
    if (!_isSeasonPointsSet)
    {
        throw runtime_error("the games hasn't been given their points");
    }
}

void Schedule::setGamePoints(Game& game)
{
    // generate nuber of points
    unsigned int homePoints = genHomePoints();
    unsigned int guestPoints = genGuestPoints();

    // if the home team has more talent so it gets bonus points
    // cannot be over 100
    if (game.getHomeTeam().getSkill() >= game.getGuestTeam().getSkill())
    {
        homePoints = min(homePoints + BONUS_POINTS, (unsigned int)MAX_POINTS);
    }
    else
    {
        guestPoints = min(guestPoints + BONUS_POINTS, (unsigned int)MAX_POINTS);
    }
    // set the points to the teams
    game.setHomePoints(homePoints);
    game.setGuestPoints(guestPoints);
}

vector<string> Schedule::getTeamNames()
{
    return _league.getTeamsList();
}

unordered_map<string, vector<unsigned int>> Schedule::getTeamsScore()
{
    unordered_map<string, vector<unsigned int>> teamScore;
    
    for(const string& name: getTeamNames())
    {
        teamScore[name] = vector<unsigned int>{4, 0};
    }

    string winner;
    string loser;
    for (unsigned int i = 0; i < _games.size(); i++)
    {
        for (const Game& game: _games[i])
        {
            winner = game.getWinner();
            loser = game.getLoser();
            // for the winner:
            teamScore[winner][IN_PNTS] += game.getPointsOfTeam(winner);
            teamScore[winner][OUT_PNTS] += game.getPointsOfTeam(loser);
            
            // set the points to the loser
            teamScore[loser][IN_PNTS] += game.getPointsOfTeam(loser);
            teamScore[loser][OUT_PNTS] += game.getPointsOfTeam(winner);
            
            // set the winning number wo winner and losing to loser
            teamScore[winner][WIN] += 1;
            teamScore[loser][LOSE] += 1;
        }
    }

    return (teamScore);
}