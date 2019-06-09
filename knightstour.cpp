#include <stack>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include "knightstour.h"

KnightsTour::KnightsTour(int bw, int bh, int x0, int y0){
    if(bw<1 || bh<1) throw std::invalid_argument("Less than 1 width or height in a chessboard!!");
    this->bwidth=bw;
    this->bheight=bh;

    this->chessboard=new int*[bheight];
    for(int i=0; i<bheight; i++){
        this->chessboard[i]=new int[bwidth];
        std::memset(this->chessboard[i], this->notvisited, bwidth*sizeof(int));
    }

    if(!validcoord(x0, y0)) throw std::invalid_argument("Invalid initial position!");
    chessboard[y0][x0]=1;
    s.push(Node{x0, y0, 0, 1});
}

KnightsTour::~KnightsTour(){
    s.~stack();
    for(int i=0; i<bheight; i++) delete[] this->chessboard[i];
    delete[] this->chessboard;
}

bool KnightsTour::validcoord(int x, int y){
    if(x<0 || y<0) return false;
    if(x>=this->bwidth || y>=this->bheight) return false;
    return true;
}

void KnightsTour::printboard(){
    std::cout<<"board:\n";
    for(int y=0; y<bheight; y++){
        std::cout<<"| ";
        for(int x=0; x<bwidth; x++) std::cout<<std::setw(3)<<this->chessboard[y][x];
        std::cout<<"|\n";
    }
    std::cout<<std::endl;
}

bool KnightsTour::findpath(){
    while(!s.empty()){
        printboard();
        const Node currnode=s.top();
        s.pop();
        std::cout<<"+turn: "; currnode.print();

        //ya acabamos
        if(currnode.turn==bwidth*bheight){
            std::cout<<"finish~"; currnode.print();
            printboard();
            return true;
        }

        //ya hicimos todos los movimientos posibles en este nodo, hagamos backtracking
        if(currnode.movedir==8){
            chessboard[currnode.y][currnode.x]=notvisited;
            std::cout<<"backtracking~"; currnode.print();
            printboard();
            continue;
        }
        //push the new move
        //movemos direccion pero no movemos ni turno ni coordenadas
        s.push(Node{currnode.x, currnode.y, currnode.movedir+1, currnode.turn});

        //do the current move
        //intenta el movimiento
        int possiblex=currnode.x+this->moves[currnode.movedir][0];//nueva x
        int possibley=currnode.y+this->moves[currnode.movedir][1];//nueva y

        if(!validcoord(possiblex, possibley)){
            std::cout<<"invalidcoords~x,y["<<possiblex<<","<<possibley<<"]\n";
            continue;//son validas
        }
        if(chessboard[possibley][possiblex]!=notvisited){
            std::cout<<"visited~x,y["<<possiblex<<","<<possibley<<"]\n";
            continue;//no se ha visitado
        }

        Node move=Node{possiblex, possibley, 0, currnode.turn+1};
        s.push(move);//hacer el movimiento
        chessboard[possibley][possiblex]=move.turn;//marcar casilla como visitada y aumentar turno
        std::cout<<"moving~"; move.print();
        
        //si no se pudo hacer el movimiento, la siguiente iteracion del while intentara otra direccion
    }
    // std::cout<<"total paths: "<<paths<<std::endl;
    return false;
}