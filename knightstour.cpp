#include <stack>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include "knightstour.h"

KnightsTour::KnightsTour(int bw, int bh){
    if(bw<1 || bh<1) throw std::invalid_argument("Less than 1 width or height in a chessboard!!");
    this->bwidth=bw;
    this->bheight=bh;

    this->chessboard=new int*[bheight];
    for(int i=0; i<bheight; i++){
        this->chessboard[i]=new int[bwidth];
        std::memset(this->chessboard[i], this->notvisited, bwidth*sizeof(int));
    }
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

int KnightsTour::findpath(int x0, int y0, bool count=false){
    if(!validcoord(x0, y0)) throw std::invalid_argument("Invalid initial position!");
    chessboard[y0][x0]=1;
    s.push(Node{x0, y0, 0, 1});
    int paths=0;

    while(!s.empty()){
        const Node currnode=s.top();
        s.pop();
        // std::cout<<"+turn: "; currnode.print();

        //ya acabamos
        if(currnode.turn==bwidth*bheight){
            // std::cout<<"finish~"; currnode.print();
            paths++;
    
            if(count==false){
                printboard();
                return paths;
            }

            chessboard[currnode.y][currnode.x]=notvisited; //backtracking
            continue;
        }

        //ya hicimos todos los movimientos posibles en este nodo, hagamos backtracking
        if(currnode.movedir==8){
            chessboard[currnode.y][currnode.x]=notvisited;
            // std::cout<<"backtracking~"; currnode.print();
            continue;
        }
        // printboard();
        
        //push the new move
        //movemos direccion pero no movemos ni turno ni coordenadas
        s.push(Node{currnode.x, currnode.y, currnode.movedir+1, currnode.turn});

        //do the current move
        //intenta el movimiento
        int possiblex=currnode.x+this->moves[currnode.movedir][0];//nueva x
        int possibley=currnode.y+this->moves[currnode.movedir][1];//nueva y

        if(!validcoord(possiblex, possibley)){
            // std::cout<<"invalidcoords~x,y["<<possiblex<<","<<possibley<<"]\n";
            continue;//son validas
        }
        if(chessboard[possibley][possiblex]!=notvisited){
            // std::cout<<"visited~x,y["<<possiblex<<","<<possibley<<"]\n";
            continue;//no se ha visitado
        }

        Node move=Node{possiblex, possibley, 0, currnode.turn+1};
        s.push(move);//hacer el movimiento
        chessboard[possibley][possiblex]=move.turn;//marcar casilla como visitada y aumentar turno
        // std::cout<<"moving~"; move.print();
        
        //si no se pudo hacer el movimiento, la siguiente iteracion del while intentara otra direccion
    }
    return paths;
}

bool KnightsTour::isthereapath(){
    for(int y=0; y<bheight; y++) for(int x=0; x<bwidth; x++)
        if(findpath(x, y)!=0) return true;
    return false;
}

int KnightsTour::countpaths(){
    int totalpaths=0;
    for(int y=0; y<bheight; y++) for(int x=0; x<bwidth; x++)
        totalpaths+=findpath(x, y, true);
    return totalpaths;
}