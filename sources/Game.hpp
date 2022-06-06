#pragma once

#include <iostream>
#include <string>
#include "Team.hpp"

using namespace std;

#define MIN_HOME_POINTS 55
#define MIN_GUEST_POINTS 50
#define MAX_POINTS 100

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

        private:
            Team& _home;
            Team& _guest;
            unsigned int _homePoints;
            unsigned int _guestPoints;

    };
    
}
