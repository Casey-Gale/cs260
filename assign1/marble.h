#ifndef MARBLE
#define MARBLE

#include <string>

class Marble {
    private:
        std::string color;
    public: 
        Marble();
        Marble(std::string);
        std::string get_color();
        void set_color(std::string);
        void print();
};

#endif