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
            Game& getGame(const string& str, unsigned int round);
            vector<vector<Game>> _gamesVect;
            unordered_map<string, unordered_map<unsigned int, Game*>> _games;
            vector<unordered_map<string, Game>> _gMap;
            void pr();


        private:
            
            Leauge& _league;

            random_device _randDev;
            mt19937 _genrator;
            std::normal_distribution<> _distributor;
            bool _isSeasonPointsSet;
            unsigned int _numSeasons;

            unsigned int genHomePoints();
            unsigned int genGuestPoints();
            void throwIfNotCreated();
            void addGameToSchedule(const string& strTeam1, const string& strTeam2, unsigned int r);
            
            
            
            
    };
    
}
