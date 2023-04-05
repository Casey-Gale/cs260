#include "marble.h"
#include <iostream>

Marble::Marble() {
    this->color = "N/A";
}
Marble::Marble(std::string color) {
    this->color = color;
}
std::string Marble::get_color() {return this->color;}
void Marble::set_color(std::string color) {this->color = color;}
void Marble::print() {
    std::cout << this->color << std::endl;
}