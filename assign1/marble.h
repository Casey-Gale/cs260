#ifndef MARBLE
#define MARBLE

#include <string>

class Marble {
    private:
        string color;
    public: 
        Marble();
        Marble(string);
        string get_color();
        void set_color(string);
        void print();
};

#endif