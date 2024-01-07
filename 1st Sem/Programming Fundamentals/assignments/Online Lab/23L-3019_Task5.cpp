# include<iostream>
using namespace std;

int main(){

    float x,y;
    cout<<"Enter x-coordinate: ";
    cin>>x;
    cout<<"Enter y-coordinate: ";
    cin>>y;

    if(x==0 && y==0) cout<<"Lies on Origin";
    else if(x==0 || y==0) cout<<"Lies on the line of origin";
    else if(x>0 && y>0) cout<<"First Quadrant";
    else if(x>0 && y<0) cout<<"Fourth Quadrant";
    else if(x<0 && y>0) cout<<"Second Quadrant";
    else if(x<0 && y<0) cout<<"Third Quadrant";

    cout<<endl;
    system("pause");
    return 0;
}