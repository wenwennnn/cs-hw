#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>

#include <limits.h>
#include <vector>

using namespace std;

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

class state{
    public:
    int x,y;
    int people;
    int depth;
    int h_value;
    array<array<int, SIZE>, SIZE> board;

    state(array<array<int, SIZE>, SIZE> b){
        for(int i=0;i<b.size();i++){
            for(int j=0;j<b[i].size();j++){
                board[i][j]=b[i][j];
            }
        }
        set_h();
    }

    state(int a,int b){
        x=a;
        y=b;

        set_h();
    }

    void set_h()
    {
        int sum=0;

        //
    }

    void update(int newx,int newy,int maxminingPlayer)
    {
        if(maxminingPlayer) board[newx][newy]=1;
        else board[newx][newy]=2;

        depth--;
        x=newx;
        y=newy;

        set_h();
    }
};

int minimax(state node,int depth,int maximiningPlayer)
{
    if(depth==0) return node.h_value;
    
    if(maximiningPlayer){
        int value=INT_MIN;

        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(node.board[i][j]==0){
                    state next=node;
                    next.update(i,j,0);
                    value=max(value,minimax(next,depth-1,0));
                }
            }
        }
    }

    else{
        int value=INT_MAX;
        
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(node.board[i][j]==0){
                    state next=node;
                    next.update(i,j,1);
                    value=max(value,minimax(next,depth-1,1));
                }
            }
        }
    }
}

int alphabeta(state node,int depth,int a,int b,int maximiningPlayer)
{
    if(depth==0) return node.h_value;

    if(maximiningPlayer){
        int value=INT_MIN;
        
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(node.board[i][j]==0){
                    state next=node;
                    next.update(i,j,0);
                    value=max(value,alphabeta(next,depth-1,a,b,0));
                    a=max(a,value);
                    if(a>=b) break;
                }
            }
        }
        return value;
    }

    else{
        int value=INT_MAX;

        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++){
                if(node.board[i][j]==0){
                    state next=node;
                    next.update(i,j,1);
                    value=min(value,alphabeta(next,depth-1,a,b,1));
                    b=min(b,value);
                    if(b<=a) break;
                }
            }
        }
        return value;
    }
}

int player;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    int x, y;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.
        int x = (rand() % SIZE);
        int y = (rand() % SIZE);
        if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}