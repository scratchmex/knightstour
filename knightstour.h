#include <stack>

struct Node{
    unsigned int x;
    unsigned int y;
    int currentmove;//0...7
};

class KnightsTour{
    private:
        //arriba derecha y orden contrario a las manecillas del reloj
        int moves[8][2]={{2,1}, {2,-1},//derecha
                        {1,-2}, {-1,-2},//abajo
                        {-2,-1}, {-2,1},//izquierda
                        {-1,2}, {1,2}};//arriba
        std::stack<Node> s;
        int** chessboard;
        const int notvisited=-1;
        unsigned int bwidth, bheight;
    
    public:
        KnightsTour(int bwidth, int bheight, int x0, int y0);
        ~KnightsTour();
        bool validcoord(int x, int y);
        bool findpath();
};