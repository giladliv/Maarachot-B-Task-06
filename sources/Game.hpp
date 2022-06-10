#pragma once

#include <iostream>
#include <string>
#include "Team.hpp"

using namespace std;

constexpr unsigned int MIN_HOME_POINTS = 55;
constexpr unsigned int MIN_GUEST_POINTS = 50;
constexpr unsigned int MAX_POINTS = 100;
constexpr unsigned int BONUS_POINTS = 10;

namespace ball
{
    class Game
    {
        public:
            Game(Team& home, Team& guest);
            void setHomePoints(unsigned int points);
            void setGuestPoints(unsigned int points);
            unsigned int getHomePoints() const;
            unsigned int getGuestPoints() const;
            void addToBest();
            friend ostream& operator<<(ostream& os, const Game& game);
            bool isGameSet() const;

        private:
            Team& _home;
            Team& _guest;
            unsigned int _homePoints;
            unsigned int _guestPoints;
            

    };
    
}
