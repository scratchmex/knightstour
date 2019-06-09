#include "knightstour.h"
#include <stack>
#include <cstring>

KnightsTour::KnightsTour(int bw, int bh, int x0, int y0){
    if(bw<1 || bh<1) throw "Less than 1 width or height in a chessboard!!";
    this->bwidth=bw;
    this->bheight=bh;

    this->chessboard=new int*[bwidth];
    for(int i=0; i<bwidth; i++){
        this->chessboard[i]=new int[bheight];
        std::memset(chessboard[i], this->notvisited, bheight);
    }

    if(!validcoord(x0, y0)) throw "Invalid initial position!";
    s.push(Node{x0, y0, 0});
}

KnightsTour::~KnightsTour(){
    s.~stack();
    for(int i=0; i<bwidth; i++) delete[] this->chessboard[i];
    delete[] this->chessboard;
}

bool KnightsTour::validcoord(int x, int y){
    if(x<0 || y<0) return false;
    if(x>=this->bwidth || y>=this->bheight) return false;
    return true;
}

bool KnightsTour::findpath(){
    while(!s.empty()){
        
    }
}