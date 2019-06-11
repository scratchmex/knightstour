#include <stack>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include "knightstour.h"

/* Node functions */

Node::Node(int x, int y, int turn){
    this->x=x; this->y=y; this->turn=turn;
    for(int i=0; i<=7; i++) movedirs[i]=false;
    this->movescount=0;
}

Node::~Node(){
    
}

void Node::setmove(int m){
    if(m<0 || m>7) throw std::invalid_argument("Move out of range");
    this->movedirs[m]=true;
    this->movescount++;
}

bool Node::alreadymoved(int m) const{
    if(m<0 || m>7) throw std::invalid_argument("Move out of range");
    return this->movedirs[m];
}

int Node::getmovescount() const{
    return this->movescount;
}

/* KnightsTour functions */
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
    // s.~stack();
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
    s.push(Node(x0, y0, 1));
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
            // printboard();
            //backtracking
            this->backtrack(currnode);
            continue;
        }

        //ya hicimos todos los movimientos posibles en este nodo, hagamos backtracking
        if(currnode.getmovescount()==8){
            // std::cout<<"allmoves~";
            this->backtrack(currnode);
            continue;
        }
        // printboard();

        //get the move
        int moven=this->getmove(currnode);
        if(moven==-1){
            // std::cout<<"nomove~";
            this->backtrack(currnode);
            continue; //there is no possible move
        }

        int newx=currnode.x+this->moves[moven][0];
        int newy=currnode.y+this->moves[moven][1];
        
        //push the move to current node and to the stack
        Node modified_node=currnode;
        modified_node.setmove(moven);
        s.push(modified_node);

        //make the new move node
        Node move(newx, newy, currnode.turn+1);
        //push the new move to the stack
        s.push(move);//hacer el movimiento
        chessboard[newy][newx]=move.turn;//marcar casilla como visitada del turno siguiente
        // std::cout<<"moving~"; move.print();
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

void KnightsTour::backtrack(const Node& currnode){
    // std::cout<<"backtracking~"; currnode.print();
    chessboard[currnode.y][currnode.x]=notvisited;//reset visited position
}

int KnightsTour::getmove(const Node& currnode){
    //esta heuristica implementa la regla de Warnsdorff's
    //busca el movimiento en donde la casilla tiene el menor grado de movimientos
    int movesgrade[9];//la pos 8 es de control
    std::memset(movesgrade, -1, 9*sizeof(int));
    movesgrade[8]=8; //8 es "infty"
    int bestmoveidx=8;//por default tomemos "infty"
    for(int i=0; i<=7; i++){
        int x=currnode.x+this->moves[i][0];//nueva x
        int y=currnode.y+this->moves[i][1];//nueva y
        if(!this->validcoord(x,y)) continue;
        if(chessboard[y][x]!=notvisited){//no podemos movernos a un lugar ya ocupado
            movesgrade[i]=-1;
            continue;
        }
        movesgrade[i]=this->nodegrade(x, y);
        
        //si el nodo tiene grado -1 o ya se movio hacia alla no se puede mover a ese lugar
        if(movesgrade[i]!=-1 && !currnode.alreadymoved(i) && movesgrade[i]<movesgrade[bestmoveidx]) bestmoveidx=i;
    }
    // std::cout<<"movesgrade[ ";
    // for(int i=0; i<=7; i++) std::cout<<movesgrade[i]<<" ";
    // std::cout<<"]\n";
    // std::cout<<"bestmoveidx: "<<bestmoveidx<<std::endl;
    //no se puede hacer ningun movimiento ya que no se movio el default
    if(bestmoveidx==8) return -1;
    
    return bestmoveidx;
}

int KnightsTour::nodegrade(int x, int y){
    if(!this->validcoord(x,y)) return -1;//no existe tal nodo
    int grade=0;
    for(int i=0; i<=7; i++){
        int possiblex=x+this->moves[i][0];//nueva x
        int possibley=y+this->moves[i][1];//nueva y

        if(!validcoord(possiblex, possibley)) continue;
        if(chessboard[possibley][possiblex]==notvisited){
            // std::cout<<"nodegrade~("<<x<<","<<y<<")->move["<<i<<"]("<<possiblex<<","<<possibley<<")possible\n";
            grade++;
        }
    }
    return grade;
}