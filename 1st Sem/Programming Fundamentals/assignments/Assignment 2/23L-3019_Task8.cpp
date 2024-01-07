#include <iostream>
using namespace std;

int main() {
    float num1,num2,num3,num4,num5,num6,num7,num8,num9,num10;

    cout<<"Enter Number: ";
    cin>>num1;
    cout<<"Enter Number: ";
    cin>>num2;
    cout<<"Enter Number: ";
    cin>>num3;
    cout<<"Enter Number: ";
    cin>>num4;
    cout<<"Enter Number: ";
    cin>>num5;
    cout<<"Enter Number: ";
    cin>>num6;
    cout<<"Enter Number: ";
    cin>>num7;
    cout<<"Enter Number: ";
    cin>>num8;
    cout<<"Enter Number: ";
    cin>>num9;
    cout<<"Enter Number: ";
    cin>>num10;

    float avg;
    int avg_up=0,avg_down=0;

    avg = (num1+num2+num3+num4+num5+num6+num7+num8+num9+num10)/10;

    cout<<"Average: "<<avg<<endl;

    if (num1>avg) avg_up++;
    else avg_down++;

    if (num2>avg) avg_up++;
    else avg_down++;

    if (num3>avg) avg_up++;
    else avg_down++;

    if (num4>avg) avg_up++;
    else avg_down++;

    if (num5>avg) avg_up++;
    else avg_down++;

    if (num6>avg) avg_up++;
    else avg_down++;

    if (num7>avg) avg_up++;
    else avg_down++;

    if (num8>avg) avg_up++;
    else avg_down++;

    if (num9>avg) avg_up++;
    else avg_down++;

    if (num10>avg) avg_up++;
    else avg_down++;

    cout<<avg_up<<" numbers are above average\n";
    cout<<avg_down<<" numbers are below average\n";
    
    system("pause");
    return 0;
}