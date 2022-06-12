#include "Game.hpp"

using ball::Game;
using ball::Team;

Game::Game(Team& home, Team& guest): _home(home), _guest(guest)
{
    if (&home == &guest || home.getName() == guest.getName())
    {
        throw runtime_error("cannot have the same team as host and guest");
    }
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

ostream& ball::operator<<(ostream& os, const Game& game)
{
    os << "home: " << game._home.getName() << " , points:"  << game.getHomePoints() << endl;
    os << "vs." << endl;
    os << "guest: " << game._guest.getName() << " , points:"  << game.getGuestPoints() << endl;
    return os;
}

const Team& Game::getHomeTeam()
{
    return _home;
}

const Team& Game::getGuestTeam()
{
    return _guest;
}

string Game::getWinner()
{
    throwIfGameNotReady();
    // home leads - return home name
    if (_homePoints > _guestPoints)
    {
        return _home.getName();
    }
    // guest leads return guest name
    if (_homePoints < _guestPoints)
    {
        return _guest.getName();
    }
    
    // if home's skill is better than guest - return its name, else the guest is the winner
    return ((_home.getSkill() >= _guest.getSkill()) ? _home.getName() : _guest.getName());
}

string Game::getLoser()
{
    // if home is not the winner than home is the loser
    // else is the guest
    return (getWinner() != _home.getName() ? _home.getName() : _guest.getName());

}

void Game::throwIfGameNotReady()
{
    if (_homePoints < MIN_HOME_POINTS || _homePoints > MAX_POINTS ||
        _guestPoints < MIN_GUEST_POINTS || _guestPoints > MAX_POINTS)
    {
        throw runtime_error("the game is not ready - please set points to home and guest");
    }
}

