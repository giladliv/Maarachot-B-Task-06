#include "Team.hpp"

using ball::Team;

Team::Team(const string& name, double skill)
{
    _name = name;
    if (skill < 0 || skill > 1)
    {
        throw runtime_error("skill must be a floating number between 0 and 1");
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


ostream& ball::operator<<(ostream& os, const Team& team)
{
    os << "Name: " << team.getName() << endl;
    os << "Skill: " << team.getSkill();
    return os;
}

void Team::removeSpacesFromEdges(string& s)
{
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\n'))
    {
        // erase the 1st char
        s.erase(0, 1);
    }

    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\n'))
    {
        s.pop_back();
    }
}

double Team::strToDouble(const string& str)
{
    double skill = 0.0;
    try
    {
        size_t s = 0;
        string strCpy = str;
        removeSpacesFromEdges(strCpy);
        skill = stod(strCpy, &s);
        cout << "(" << s << ")" << endl;
        // if the size of parsering is not good then it is noit good input
        if (s != strCpy.size())
        {
            throw runtime_error("");
        }
    }
    catch(const std::exception& e)
    {
        throw runtime_error("input isn't double");
    }

    return skill;
}

Team Team::getTemFromInput()
{
    cout << "Enter here the name of the team: ";
    string name;
    getline(cin, name, '\n');
    
    cout << "Enter skill factor (between 0 and 1): ";
    string skillStr;
    getline(cin, skillStr, '\n');
    
    double skill = strToDouble(skillStr);

    return Team(name, skill);
}