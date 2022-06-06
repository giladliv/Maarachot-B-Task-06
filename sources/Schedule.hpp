#pragma once

#include <iostream>
#include <string>
#include "Leauge.hpp"

using namespace std;

namespace ball
{
    class Schedule
    {
        public:
            Schedule(Leauge& leauge);
            void createSeason();
            void runAllGames();

        private:
            vector<vector<Game>> _games;
            Leauge& _league;
            random_device _randDev;
            mt19937 _genrator;
            std::normal_distribution<> _distributor;

            unsigned int genHomePoints();
            unsigned int genGuestPoints();
            
            
            
    };
    
}
