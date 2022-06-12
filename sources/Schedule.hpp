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
            const vector<vector<Game>>& getGames() const;
            void throwIfNotCreated() const;
            vector<string> getTeamNames();

        private:
            vector<vector<Game>> _games;
            Leauge& _league;
            random_device _randDev;
            mt19937 _genrator;
            std::normal_distribution<> _distributor;
            bool _isSeasonPointsSet;
            //unordered_map<string, vector<Game*>> _gMap;

            unsigned int genHomePoints();
            unsigned int genGuestPoints();
            
            //void addTeamsToMap(const string& strTeam1, const string& strTeam2);
            void setGamePoints(Game& game);
            
            
            
    };
    
}
