#pragma once

#include <iostream>
#include <string>
#include "Leauge.hpp"

using namespace std;

constexpr unsigned int GAP = 20;
constexpr unsigned int IN_PNTS = 0;
constexpr unsigned int OUT_PNTS = 1;
constexpr unsigned int WIN = 2;
constexpr unsigned int LOSE = 3;

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
            unordered_map<string, vector<unsigned int>> getTeamsScore();
            Leauge& getLeuage(){ return _league; }
            unsigned int getTotalRounds() const { return _totalRoundNum; }

        private:
            vector<vector<Game>> _games;
            Leauge& _league;
            random_device _randDev;
            mt19937 _genrator;
            std::normal_distribution<> _distributor;
            bool _isSeasonPointsSet;
            unsigned int _totalRoundNum;

            unsigned int genHomePoints();
            unsigned int genGuestPoints();
            
            //void addTeamsToMap(const string& strTeam1, const string& strTeam2);
            void setGamePoints(Game& game);
            
            
            
    };
    
}
