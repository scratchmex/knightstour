#include <iostream>
#include "knightstour.h"

using namespace std;

int main(int argn, char* argv[]){
    int bwidth, bheight, x0, y0;
    if(argn==4+1){
        bwidth=atoi(argv[1]), bheight=atoi(argv[2]);
        x0=atoi(argv[3]), y0=atoi(argv[4]);
    }
    else{
        cout<<"+Enter board parameters+"<<endl;
        cout<<"Board width: ";
        cin>>bwidth; cout<<endl;

        cout<<"Board height: ";
        cin>>bheight; cout<<endl;

        cout<<"+Enter initial knight coords+. (0,0) is top left."<<endl;
        cout<<"x0: ";
        cin>>x0; cout<<endl;

        cout<<"y0: ";
        cin>>y0; cout<<endl;
    }

    KnightsTour tour(bwidth, bheight, x0, y0);
    cout<<"The tour is possible?: "<<tour.findpath()<<endl;

    return 0;
}