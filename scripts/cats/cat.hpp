#ifndef CAT_H
#define CAT_H

#include <iostream>

struct catName {
    unsigned short prefix;
    unsigned short suffix;
    bool spec_suffix_hidden;
};


class Cat {
    public:
        unsigned short id;
        unsigned int seed;
        unsigned short moons;
        catName name;
        unsigned short gender;
        std::string backstory;
        std::string skill;
        int mentor;

        
        Cat();
        ~Cat();

    private:
};


#endif