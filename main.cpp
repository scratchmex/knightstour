#include <iostream>
#include "knightstour.h"

using namespace std;

int main(int argn, char* argv[]){
    int bwidth, bheight;
    if(argn==2+1){
        bwidth=atoi(argv[1]), bheight=atoi(argv[2]);
    }
    else{
        cout<<"+Enter board parameters+"<<endl;
        cout<<"Board width: ";
        cin>>bwidth; cout<<endl;

        cout<<"Board height: ";
        cin>>bheight; cout<<endl;
    }

    KnightsTour tour(bwidth, bheight);
    cout<<"The tour is possible?: "<<tour.isthereapath()<<endl;

    return 0;
}