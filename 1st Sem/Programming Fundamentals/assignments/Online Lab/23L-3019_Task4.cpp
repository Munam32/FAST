# include <iostream>
using namespace std;
int main(){
    int marks;
    cout<<"Enter Marks: ";
    cin>>marks;

    if (marks>=0 && marks<=100){

        if(marks>=90) cout<<"Grade A";
        else if(marks>=75) cout<<"Grade B";
        else if(marks>=60) cout<<"Grade C";
        else if(marks>=45) cout<<"Grade D";
        else cout<<"Grade F";
    }
    else cout<<"Invalid Input";


    cout<<endl;
    system("pause");
}