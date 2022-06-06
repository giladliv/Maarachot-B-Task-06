#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace ball
{
    class Team
    {
        public:
            Team(const string& name, double skill);
            string getName() const;
            double getSkill() const;

        private:
            string _name;
            double _skill;
    };
    
}
