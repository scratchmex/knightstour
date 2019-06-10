#include <stack>

struct Node{
    int x;
    int y;
    int movedir;//0...7
    int turn;
    void print() const{
        std::cout<<"Node{"<<x<<","<<y<<","<<movedir<<","<<turn<<"}\n";
    }
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
        const int notvisited=0;
        int bwidth, bheight;
    
    public:
        KnightsTour(int bwidth, int bheight);
        ~KnightsTour();
        bool validcoord(int x, int y);
        void printboard();
        int findpath(int x0, int y0, bool count);
        bool isthereapath();
        int countpaths();
};