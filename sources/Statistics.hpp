#pragma once

#include <iostream>
#include <string>
#include "Schedule.hpp"

using namespace std;

namespace ball
{
    class Statistics
    {
        public:
            Statistics(Schedule& schedule);
            ~Statistics();
            // void topTeams();
            void longestWinRow();
            void longestLoseRow();
            //void teamsThatScoredMore();

        private:
            Schedule& _schedule;
            unordered_map<string, vector<bool>> getWinnings();
            void longestWinLoserRunner(bool checkForWin);
            

    };
    
}
