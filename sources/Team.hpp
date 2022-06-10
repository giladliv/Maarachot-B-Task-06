#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace ball
{
    class Team
    {
        public:
            Team() : Team("", 0) {}
            Team(const string& name, double skill);
            string getName() const;
            double getSkill() const;
            friend ostream& operator<<(ostream& os, const Team& team);
            static void removeSpacesFromEdges(string& s);
            static double strToDouble(const string& str);
            static Team getTemFromInput();

        private:
            string _name;
            double _skill;
    };
    
}
