#include "Statistics.hpp"

using ball::Statistics;

Statistics::Statistics(Schedule& schedule) : _schedule(schedule)
{
}

Statistics::~Statistics()
{
}

unordered_map<string, vector<bool>> Statistics::getWinnings()
{
    _schedule.throwIfNotCreated();
    const vector<vector<Game>>& games = _schedule.getGames();
    unordered_map<string, vector<bool>> winTable;
    
    // reset the names
    for (const string& name : _schedule.getTeamNames())
    {
        winTable[name] = {};
    }

    string winner;
    string loser;
    for (unsigned int i = 0; i < games.size(); i++)
    {
        for (const Game& game: games[i])
        {
            winner = game.getWinner();
            loser = game.getLoser();
            //cout << "w:  " << winner << "  ,  l:  " << loser << endl; 
            winTable[winner].push_back(true);
            winTable[loser].push_back(false);
        }
    }
    return (winTable);
}

void Statistics::longestWinRow()
{
    longestWinLoserRunner(true);
}

void Statistics::longestLoseRow()
{
    longestWinLoserRunner(false);
}

void Statistics::longestWinLoserRunner(bool checkForWin)
{
    unordered_map<string, vector<bool>> winTable = getWinnings();
    unordered_map<string, unsigned int> numOfLongest;
    unsigned int maxRow = 0;
    bool dataBreaker = !checkForWin;
    for (const auto& winPair : winTable)
    {
        const string& name = winPair.first;
        const vector<bool>& winsVect = winPair.second;
        numOfLongest[name] = 0;
        unsigned int counter = 0;
        for (auto it = winsVect.begin(); it != winsVect.end(); )
        {
            // find the next occorence of the opposite - if win then search for false
            // if lose search for win (lose)
            auto findIt = find(it, winsVect.end(), dataBreaker);
            counter = findIt - it;
            numOfLongest[name] = max(counter, numOfLongest[name]);
            maxRow = max(maxRow, counter);
            
            // set the iterator for over the first that found - if the end - leave it be
            it = (findIt != winsVect.end()) ? findIt + 1 : findIt;
        }
    }

    cout << "the longest number of " << (checkForWin ? "winning" : "losing");
    cout << " games in a row is:  " << maxRow << "  games" << endl;
    cout << "the teams are: " << endl;
    for (const auto& winPair: numOfLongest)
    {
        if (winPair.second == maxRow)
        {
            cout << winPair.first << endl;
        }
    }
}