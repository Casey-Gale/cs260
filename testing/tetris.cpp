#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

const int x_max = 8;
const int y_max = 10;

class Node
{
    public:
        int x;
        int y;
        Node* next;

        Node() {x = 0; y = 0; next = nullptr;}
        Node(int new_x, int new_y) {x = new_x; y = new_y; next = nullptr;}
};


//abstract Block class for representing any general block in the game
//x represents a taken spot labeled x
//c represents center of the block
class Block {
    private:
        int x_coord;
        int y_coord;
        int rotation; //represents 90 * rotation degrees transformation
        char display_char;
    public:
        Block() {
            this->x_coord = 0;
            this->y_coord = 0;
            this->rotation = 0;
            this->display_char = '?';
        }
        void set_x(const int new_x) {this->x_coord = new_x;}
        void set_y(const int new_y) {this->y_coord = new_y;}
        void set_rotation(const int new_rotation) {this->rotation = new_rotation % 4;}
        void set_display_char(const char new_char) {this->display_char = new_char;}
        int get_x() const {return this->x_coord;}
        int get_y() const {return this->y_coord;}
        int get_rotation() const {return this->rotation;}
        char get_display_char() const {return this->display_char;}
        virtual Node* get_spaces() = 0;
};

//probably can inherit this to a mirrored version
// 1
// 2 c
// 3 4
class L_Block : public Block {
    public:
        L_Block() {set_display_char('L');}
        L_Block(int x, int y, int rot);
        Node* get_spaces();
};
L_Block::L_Block(const int x, const int y, const int rot) {
    set_x(x);
    set_y(y);
    set_rotation(rot);
    set_display_char('L');
}
Node* L_Block::get_spaces() {
    Node* head;
    if(get_rotation() == 0) {
        head = new Node(get_x() - 1, get_y() - 1); //1
        Node* current = head;
        current->next = new Node(get_x() - 1, get_y()); //2
        current = current->next;
        current->next = new Node(get_x() - 1, get_y() + 1); //3
        current = current->next;
        current->next = new Node(get_x(), get_y() + 1); //4
    }
    else if(get_rotation() == 1) {
        head = new Node(get_x() - 1, get_y() + 1); //1
        Node* current = head;
        current->next = new Node(get_x(), get_y() + 1); //2
        current = current->next;
        current->next = new Node(get_x() + 1, get_y() + 1); //3
        current = current->next;
        current->next = new Node(get_x() + 1, get_y()); //4
    }
    else if(get_rotation() == 2) {
        head = new Node(get_x() + 1, get_y() + 1); //1
        Node* current = head;
        current->next = new Node(get_x() + 1, get_y()); //2
        current = current->next;
        current->next = new Node(get_x() + 1, get_y() - 1); //3
        current = current->next;
        current->next = new Node(get_x(), get_y() - 1); //4
    }
    else {
        head = new Node(get_x() + 1, get_y() - 1); //1
        Node* current = head;
        current->next = new Node(get_x(), get_y() - 1); //2
        current = current->next;
        current->next = new Node(get_x() - 1, get_y() - 1); //3
        current = current->next;
        current->next = new Node(get_x() - 1, get_y()); //4
    }
    return head;
}

//maybe a vector for storing all blocks

using namespace std;

//prints the grid according to global variables x_max and y_max
void print(vector<vector<char>>& grid) {
    for(int j = 0; j < y_max; j++) {
        for(int i = 0; i < x_max; i++) {
            cout << grid.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    //resizes grid to desired size
    vector<vector<char>> grid;
    grid.resize(x_max);
    for (int i = 0; i < x_max; i++)
    {
        grid.at(i).resize(y_max);
    }

    //sets the whole grid to 'o'
    for(int j = 0; j < y_max; j++) {
        for(int i = 0; i < x_max; i++) {
            grid.at(i).at(j) = 'o';
        }
    }

    print(grid);
    
    //gets all coordinates of an L block
    Block* b = new L_Block(4, 4, 100);
    Node* head = b->get_spaces();
    Node* current = head;
    //should print coordinates and change all coordinates of the L block to an 'L'
    while (current != nullptr)
    {
        cout << "(" << current->x << ", " << current->y << ")" << endl;
        grid.at(current->x).at(current->y) = b->get_display_char();
        current = current->next;
    }
    cout << endl;

    print(grid);

    return 0;
}

//TODO: add block falling down
        //  this requires adding a check to see that the block can fall down (is empty space below the block in every column? 
        //  would the block be falling out of bounds of the grid?)