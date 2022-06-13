#include "Statistics.hpp"
#include <map>

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


void Statistics::topTeams(unsigned int numOfTeams)
{
    if (numOfTeams > NUM_TEAMS || numOfTeams == 0)
    {
        throw runtime_error("there are 20 teams at max and 1 team at the minimum");
    }
    unordered_map<string, vector<unsigned int>> teamScore = _schedule.getTeamsScore();
    multimap<unsigned int, string> pointsGame;
    for (const string& name : _schedule.getTeamNames())
    {
        unsigned int points = teamScore[name][IN_PNTS];
        unsigned int wins = teamScore[name][WIN];
        points *= wins;
        pointsGame.insert({points, name});
    }
    cout << "The " << numOfTeams << " teams in the lead are: " << endl;
    int counter = 0;
    for(auto it = pointsGame.rbegin(); it != pointsGame.rend(); ++it)
    {
        if (counter == numOfTeams)
        {
            break;
        }
        cout << "#" << counter + 1 << " : " << it->second;
        cout << "\t(" << teamScore[it->second][WIN] << ")" << endl;
        counter++;
    }
    cout << endl;
}


void Statistics::printTotalGame()
{
    unordered_map<string, vector<unsigned int>> teamScore = _schedule.getTeamsScore();
    
    unsigned int counter = 0;
    vector<vector<string>> table;
    unsigned int countSplits = 1;
    cout << string (MAX_POINTS, '*') << endl;
    cout << string (MAX_POINTS, '*') << endl;
    for (const string& name : _schedule.getTeamNames())
    {
        // reset the table
        
        if (counter == 0)
        {
            table = {{""}, {"win/lose"}, {"score diff"}};
        }
        
        int pointsIn = (int)teamScore[name][IN_PNTS];
        int pointsOut =  (int)teamScore[name][OUT_PNTS];
        table[0].push_back(name);
        table[1].push_back(to_string(pointsIn) + "/" + to_string(pointsOut));
        table[2].push_back(to_string(pointsIn - pointsOut));
        // add the count - hoe many data in row
        counter++;
        
        if (counter == MAX_IN_ROW)
        {
            cout << "Part " << countSplits++ << endl;
            printTable(table);
            cout << endl;
            counter = 0;
        }

    } 
    // if didn't reset than print the last table
    if (counter != 0)
    {
        cout << "Part " << countSplits++ << endl;
        printTable(table);
        cout << endl;
    }

    cout << string (MAX_POINTS, '*') << endl;
    cout << string (MAX_POINTS, '*') << endl << endl;
}

void Statistics::beutifyTable(vector<vector<string>>& table)
{
    unsigned int rows = table.size();
    unsigned int cols = 0;
    // gvet the max len for the cols
    for (unsigned int i = 0; i < rows; i++)
    {
        cols = max((unsigned int)table[i].size(), cols);
    }
    for (unsigned int i = 0; i < rows; i++)
    {
        while (table[i].size() < cols)
        {
            table[i].push_back("");
        }
    }
    for (unsigned int j = 0; j < cols; j++)
    {
        unsigned int maxLen = 0;
        // for each column find the max len of str
        for (unsigned int i = 0; i < rows; i++)
        {
            table[i][j] =  " " + table[i][j] + " ";
            maxLen = max((unsigned int)table[i][j].size(), maxLen);
        }
        // add the spairs
        for (unsigned int i = 0; i < rows; i++)
        {
            table[i][j] += string(maxLen - table[i][j].size(), ' ');
        }
    }

}

void Statistics::printTable(const vector<vector<string>>& tablePrint)
{
    vector<vector<string>> table(tablePrint);
    beutifyTable(table);
    vector<string> lines{};
    for (unsigned int i = 0; i < table.size(); i++)
    {
        string line;
        // set the line with seperator
        for (const string& str: table[i])
        {
            line += str + "|";
        }
        if (!line.empty()) // if line has data remove the last because its '|'
        {
            line.pop_back();
        }
        lines.push_back(line);
        
        // if the line is not the last print seperator
        if (i < table.size() - 1)
        {
            lines.push_back(string(line.size(), '-'));
        }
    }

    for (const string& line: lines)
    {
        cout << line << endl;
    }
    cout << endl;
}