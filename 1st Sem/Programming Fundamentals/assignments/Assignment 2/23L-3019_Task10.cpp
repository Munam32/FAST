#include<iostream>
using namespace std;

int main(){
    float weight,Calories;
    cout<<"Enter your Weight: ";
    cin>>weight;

    char lifestyle;
    cout<<"Enter Life style (A = active , S = Sedentary) : ";
    cin>>lifestyle;

    if (lifestyle=='A'){
        Calories = weight*15;
    }
    else if(lifestyle=='S'){
        Calories = weight*13;
    }

    cout<<"Recommended Calories: "<<Calories<<endl;
    system("pause");

    return 0;
}