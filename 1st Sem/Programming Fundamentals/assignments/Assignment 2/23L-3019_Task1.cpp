# include <iostream>
#include <cstdlib>
using namespace std;

int main(){

    int choice;

    cout<<"Problem calling Program (1)"<<endl;
    cout<<"Guessing Game (2)"<<endl;
    cout<<"Calendar Calculator (3)"<<endl;
    cout<<"Age Calculator (4)"<<endl;
    cout<<"Integer sign guess (5)"<<endl;
    cout<<"Multiple Checker (6)"<<endl;
    cout<<"Vowel checker (7)"<<endl;
    cout<<"Average Checker (8)"<<endl;
    cout<<"Auto Insurance Program (9)"<<endl;
    cout<<"Calories Calculator (10)"<<endl<<endl;
    cout<<"Enter Your Choice (1/2/3/4/5/6/7/8/9/10) : ";
    cin>>choice;

    if(choice>=1 && choice <=10){
        
        if(choice==1)
            system("23L-3019_Task1.exe");

        else if(choice ==2)
            system("23l-3019_Task2.exe");

        else if(choice==3)
            system("23l-3019_Task3.exe");
        
        else if(choice==4)
            system("23l-3019_Task4.exe");

        else if(choice==5)
            system("23l-3019_Task5.exe");
        
        else if(choice==6)
            system("23l-3019_Task6.exe");
        
        else if(choice==7)
            system("23l-3019_Task7.exe");

        else if(choice ==8)
            system("23l-3019_Task8.exe");

        else if(choice==9)
            system("23l-3019_Task9.exe");

        else if(choice==10)
            system("23l-3019_Task10.exe");
    
    }
    return 0;
}

