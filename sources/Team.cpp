#include "Team.hpp"

using ball::Team;

Team::Team(const string& name, double skill)
{
    _name = name;
    if (skill < 0 || skill > 1)
    {
        throw runtime_error("must be between 0 and 1");
    }
    _skill = skill;
}

string Team::getName() const
{
    return (_name);
}

double Team::getSkill() const
{
    return(_skill);
}

