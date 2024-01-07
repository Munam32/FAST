#include <iostream>
using namespace std;

// assuming all months are having 30 days

int main() {

    int month,day,year;

    cout<<"Enter Day: ";
    cin>>day;
    cout<<"Enter Month: ";
    cin>>month;
    cout<<"Enter Year: ";
    cin>>year;

    if((day>=1 && day<=30) && (month>=1 && month<=12)){

        if(year % 4 == 0){

            if(month==2 && day==28){
                day++;
            }
            else if(day==29 && month ==2){
                month++;
                day=1;
            }
            else if(day == 30 && month ==12){
                month = 1;
                day = 1;
                year++;
            }
            else if(day==30){
                day = 1;
                month++;
            }
            else{
                day++;
            }
        }

        else{

            if(month==2 && day<=27){
                day++;
            }
            else if(day == 28 && month == 2){
                day = 1;
                month++;
            }
            else if(month == 12 && day==30){
                year++;
                day=1;
                month=1;
            }
            else if(day==30 && (month==1 || (month>=3 && month<=12)) ){
                day=1;
                month++; 
            }
            else if(month==1 || (month>=3 && month<=12)){
                day++;
            }
        }
        
    }
    
    
    cout<<day<<"-"<<month<<"-"<<year;

    cout<<endl;
    system("pause");
    return 0;
}