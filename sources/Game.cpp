#include "Game.hpp"

using ball::Game;
using ball::Team;

Game::Game(Team& home, Team& guest): _home(home), _guest(guest)
{
    _homePoints = 0;
    _guestPoints = 0;
}

void Game::setHomePoints(unsigned int points)
{
    if (points < MIN_HOME_POINTS || points > MAX_POINTS)
    {
        throw runtime_error("the point of home team must be between 55 and 100");
    }
    _homePoints = points;
}

void Game::setGuestPoints(unsigned int points)
{
    if (points < MIN_GUEST_POINTS || points > MAX_POINTS)
    {
        throw runtime_error("the point of guest team must be between 50 and 100");
    }
    _guestPoints = points;
}

unsigned int Game::getHomePoints() const
{
    return (_homePoints);
}

unsigned int Game::getGuestPoints() const
{
    return (_guestPoints);
}

void Game::addToBest()
{
    if (_home.getSkill() >= _guest.getSkill())
    {
        _homePoints = min(_homePoints + 10, (unsigned int)MAX_POINTS);
    }
    else
    {
        _guestPoints = min(_guestPoints + 10, (unsigned int)MAX_POINTS);
    }
}