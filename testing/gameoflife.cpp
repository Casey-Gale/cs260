#include <iostream>

using namespace std;

class Grid {
    public: 
        int grid[5][5];

        Grid() {
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 5; j++) {
                    grid[i][j] = 0;
                }

            }
        }
        void print() {
            for(int i = 0; i < 5; i++) {
               for(int j = 0; j < 5; j++) {
                    grid[i][j] = 0;
                    cout << grid[i][j] << " ";
                }
                cout << endl;
            }
        }
        void pass_tick();

        
};

void Grid::pass_tick() {
    int sum;
    for(int i = 0; i < 5; i++) {
        sum = 0;
        for(int j = 0; j < 5; j++) {
            // sum horizontal
            if(i == 0) {
                sum += grid[0][j];
                sum += grid[1][j];
            }
            else if(i == 4) {
                sum += grid[3][j];
                sum += grid[4][j];
            }
            else {
                for(int k = i-1; k <= i+1; k++) {
                    sum += grid[k][j];
                }
            }
            // sum vertical


            for(int m = i - 1; m <= i + 1; m++) {
                for(int n = j - 1; n <= j + 1; n++) {
                    // if not trivial
                    if(!(m>=0 && m<5 && n>=0 && n<5)) {
                        
                    }
                }
            }
        }
    }
}

int main() {
    Grid grid;

    grid.print();

    return 0;
}
