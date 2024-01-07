# include <iostream>
using namespace std;
# include <cmath>


int main(){

    double BLength,BWidth,BHeight; // Box sides
    char choice;
    
    cout<<"Enter b for box or s for sphere or p for prism or c for cylinder: ";
    cin>>choice;

    if( choice =='b'){

        cout<<"Enter Length: ";
        cin>>BLength;
        cout<<"Enter Width: ";
        cin>>BWidth;
        cout<<"Enter Height: ";
        cin>>BHeight;

        cout<<"Volume of the Box is: "<<BHeight * BLength * BWidth;
    }
    
    else if(choice =='s'){

        double Radius;

            cout<<"Enter Radius: ";
            cin>>Radius;
            cout<<"Volume Of Sphere: "<< (4/3.0) * (3.141592653589793238462643383279502884197*pow(Radius,3));  // split it or use at one unit e.g: (4/3.0)...

        cout<<"k";
    } 

    else if(choice =='p'){

        double Base,Prism_Height,T_Height; // Prism sides

            cout<<"Enter Length of base of Triangle: ";
            cin>>Base;
            cout<<"Enter Height of Triangle: ";
            cin>>T_Height;
            cout<<"Enter Height of the triangular prism: ";
            cin>>Prism_Height;

            cout<<"Volume of prism: "<< .5 *Base*Prism_Height*T_Height;
    }
    
    else if(choice =='c'){

        double C_Radius,C_Height;   // Cylinder sides

        cout<<"Enter Radius: ";
        cin>>C_Radius;
        cout<<"Enter Height: ";
        cin>>C_Height;
        cout<<"Volume Of Cylinder: "<< 3.141592653589793238462643383279502884197 * pow(C_Radius,2) * C_Height;
    }
    


    return 0;
}