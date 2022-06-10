#pragma once

#include <iostream>
#include <string>
#include "Leauge.hpp"

using namespace std;

constexpr unsigned int GAP = 20;

namespace ball
{
    class Schedule
    {
        public:
            Schedule(Leauge& leauge);
            void createSeason();
            void runAllGames();
            friend ostream& operator<<(ostream& os, const Schedule& schedule);
            


        private:
            vector<vector<Game>> _gamesVect;
            unordered_map<string, unordered_map<int, Game&>> _games;
            Leauge& _league;
            random_device _randDev;
            mt19937 _genrator;
            std::normal_distribution<> _distributor;
            bool _isSeasonPointsSet;
            unsigned int _numSeasons;

            unsigned int genHomePoints();
            unsigned int genGuestPoints();
            void throwIfNotCreated();
            
            
            
    };
    
}
