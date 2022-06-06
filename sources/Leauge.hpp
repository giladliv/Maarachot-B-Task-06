#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include "Game.hpp"

using namespace std;

#define NUM_TEAMS 20
#define NUM_RAND_MAX (RAND_MAX - 1)

namespace ball
{
    class Leauge
    {
        public:
            Leauge();
            void addTeam(const string& name, double skill);
            bool isTeamExists(const string& name);
            unsigned int teamSize();
            vector<string> getTeamsList() const;
            Team& getTeam(const string& name);

        private:
            void setRandomTeams(int num);
            unordered_map<string, Team> _teams;
            vector<string> _teamsNames;
    };
    
}
