# include <iostream>
using namespace std;

int main(){
    char light;
    cout<<"Enter Colour of Lights(r=red , y=yellow, g=green) : ";
    cin>>light;

    if (light == 'r') cout<<"Stop the Car\n";
    else if(light=='y') cout<<"Ready your car\n";
    else if(light =='g') cout<<"You can go\n";
    else cout<<"Enter a valid character\n";
    system("pause");
    return 0;
}