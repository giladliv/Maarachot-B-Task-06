#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include "Game.hpp"


using namespace std;

constexpr unsigned int NUM_TEAMS = 6;
constexpr unsigned int NUM_RAND_MAX = RAND_MAX - 1;

namespace ball
{
    class Leauge
    {
        public:
            Leauge(const vector<Team>& teams = {});
            Leauge(unsigned int numOfInput);
            void addTeam(const string& name, double skill);
            void addTeam(const string& name, const string& skill);
            void addTeam(const Team& team);
            bool isTeamExists(const string& name);
            unsigned int teamSize();
            vector<string> getTeamsList() const;
            Team& getTeam(const string& name);
            friend ostream& operator<<(ostream& os, const Leauge& leauge);
            static void removeSpacesFromEdges(string& s);

        private:
            void setRandomTeams(unsigned int num);
            void setLeaugesFromOuter(unsigned int numOfLeaeges);
            unordered_map<string, Team> _teams;
            vector<string> _teamsNames;
    };
    
}
