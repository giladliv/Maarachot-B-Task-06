#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include "Schedule.hpp"

using namespace std;

constexpr unsigned int MAX_IN_ROW = 5;


namespace ball
{
    class Statistics
    {
        public:
            Statistics(Schedule& schedule);
            ~Statistics();
            void printTotalGame();
            void topTeams(unsigned int numOfTeams);
            void longestWinRow();
            void longestLoseRow();
            void teamsThatScoredMore();
            void teamsThatScoredLess();
            void printSkillVsPoints();
            static void beutifyTable(vector<vector<string>>& table);
            static void printTable(const vector<vector<string>>& table);
            

        private:
            Schedule& _schedule;
            unordered_map<string, vector<bool>> getWinnings();
            void longestWinLoserRunner(bool checkForWin);
            void printScoresOverMoreLess(bool isMore);
            

    };
    
}
