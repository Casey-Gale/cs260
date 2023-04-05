#include "marble.h"

Marble::Marble() {
    this->color = "N/A";
}
Marble::Marble(string color) {
    this->color = color;
}
Marble::get_color() {return this->color;}
Marble::set_color(string color) {this->color = color;}
Marble::print() {
    cout << this->color << endl;
}