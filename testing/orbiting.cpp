#include <iostream>
#include <cmath>

using namespace std;

float pi = 3.14159;

class planet {
    public: 
        float radius;
        float angle;
        float speed;
        planet(float r, float a, float s) {radius = r; angle = a; speed = s;}
};

float distance_between(planet* planet1, planet* planet2);
float average_distance_between(planet* planet1, planet* planet2);
int gcd(int, int);
int lcm(int, int);

// *******************************************************
// MAIN
// *******************************************************
int main() {
    //        radius    pi*angle    speed
    planet p1(500,      0,          5);
    planet p2(500,      0,          2);
    // cout << "instantaneous distance between planets: " << distance_between(&p1, &p2);
    cout << "average distance between planets: " << average_distance_between(&p1, &p2) << endl;

    // cout << "GCD(21, 42) == " << gcd(21, 42);
    // cout << "LCM(4, 14) == " << lcm(4, 14);

    return 0;
}

float distance_between(planet* planet1, planet* planet2) {
    float x1 = planet1->radius * cos(planet1->angle * pi);
    float y1 = planet1->radius * sin(planet1->angle * pi);
    float x2 = planet2->radius * cos(planet2->angle * pi);
    float y2 = planet2->radius * sin(planet2->angle * pi);
    
    float delta_x = x1 - x2;
    float delta_y = y1 - y2;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

float average_distance_between(planet* planet1, planet* planet2) {
    float max_time = 10;
    float time_step = .1;
    float time = 0;
    float distance = 0;
    float num_steps = 0;
    float angle1 = planet1->angle;
    float angle2 = planet2->angle;
    while(time < max_time) {
        planet1->angle = planet1->speed * time + angle1;
        planet2->angle = planet2->speed * time + angle2;
        distance += distance_between(planet1, planet2);
        num_steps++;
        time += time_step;
    }
    planet1->angle = angle1;
    planet2->angle = angle2;
    return distance / num_steps; // gives average distance
}

int gcd(int a, int b) {
    // checks if one is zero, then returns the other integer if true
    if(a * b == 0) {
        return a + b; 
    }
    // otherwise, apply the euclidean algorithm for GCD
    if(a > b) {
        return gcd((a-b), b);
    }
    return gcd((b-a), a);
}

int lcm(int a, int b) {
    int g = gcd(a, b);
    return ((a/g)*b);
}

// i want to find the average distance between two orbiting planets with different speeds. 
// they orbit around the same sun, and their gravitational effects on each other are negligible. 
// i assume every speed is a rational multiple of pi
