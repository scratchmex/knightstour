#include <stack>

class Node{
    private:
        bool movedirs[8];//0...7
        int movescount;

    public:
        Node(int x, int y, int turn);
        int x;
        int y;
        int turn;
        void print() const{
            std::cout<<"Node{"<<x<<","<<y<<",[ ";
            for(int i=0; i<=7; i++) std::cout<<movedirs[i]<<" ";
            std::cout<<"]"<<","<<turn<<"}\n";
        }
        void setmove(int m);
        bool alreadymoved(int m) const;
        int getmovescount() const;
};

class KnightsTour{
    private:
        //arriba derecha y orden contrario a las manecillas del reloj
        int moves[8][2]={{2,-1}, {2,1},//derecha
                        {1,2}, {-1,2},//abajo
                        {-2,1}, {-2,-1},//izquierda
                        {-1,-2}, {1,-2}};//arriba
        std::stack<Node> s;
        int** chessboard;
        const int notvisited=0;
        int bwidth, bheight;
        void backtrack(const Node& currnode);
        int getmove(const Node& currnode);//0...7
        int nodegrade(int x, int y);
    
    public:
        KnightsTour(int bwidth, int bheight);
        ~KnightsTour();
        bool validcoord(int x, int y);
        void printboard();
        int findpath(int x0, int y0, bool count);
        bool isthereapath();
        int countpaths();
};