#include <iostream>
using namespace std;

int main(){
    char b1=' ',b2=' ',b3=' ',b4=' ',b5=' ',b6=' ',b7=' ',b8=' ',b9=' ';
    int choice;
    bool flag1=true;



    cout<<"       1 | 2 | 3 "<<endl;
    cout<<"       4 | 5 | 6 "<<endl;
    cout<<"       7 | 8 | 9 "<<"\n";
    cout<<"Enter The numbers as shown above to place your mark"<<endl;
    
    for(;;){

        if (flag1==true){
            cout<<"Enter Postion Player 1 (X): ";
            cin.fail();
            cin>>choice;



            
            if(choice>=1 && choice <=9){

                if( (choice==1 && b1!=' ') || (choice==2 && b2!=' ') || (choice==3 && b3!=' ') || (choice==4 && b4!=' ') || (choice==5 && b5!=' ') || (choice==6 && b6!=' ') || (choice==7 && b7!=' ') || (choice==8 && b8!=' ') || (choice==9 && b9!=' ') ){
                    continue;
                }

                if(choice==1){
                    b1='X';

                }
                else if(choice == 2){
                    b2='X';
                }
                else if(choice == 3){
                    b3='X';
                }
                else if(choice == 4){
                    b4='X';
                }
                else if(choice == 5){
                    b5='X';
                }
                else if(choice == 6){
                    b6='X';
                }
                else if(choice == 7){
                    b7='X';
                }
                else if(choice == 8){
                    b8='X';
                }
                else{
                    b9='X';
                }
            }
            else{
                cin.ignore();
                continue;
            }

            if( (b1=='X' && b2=='X' && b3=='X') || (b4=='X' && b5=='X' && b6=='X') || (b7=='X' && b8=='X' && b9=='X') || (b1=='X' && b5=='X' && b9=='X') || (b3=='X' && b5=='X' && b7=='X') || (b1=='X' && b4=='X' && b7=='X') || (b2=='X' && b5=='X' && b8=='X') || (b3=='X' && b6=='X' && b9=='X') ){   
                cout<<endl;
                cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
                cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
                cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
                cout<<endl;
                
                cout<<"Player 1 wins";
                break;
            }
            else if((b1=='O' && b2=='O' && b3=='O') || (b4=='O' && b5=='O' && b6=='O') || (b7=='O' && b8=='O' && b9=='O') || (b1=='O' && b5=='O' && b9=='O') || (b3=='O' && b5=='O' && b7=='O') || (b1=='O' && b4=='O' && b7=='O') || (b2=='O' && b5=='O' && b8=='O') || (b3=='O' && b6=='O' && b9=='O') ){
                cout<<endl;
                cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
                cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
                cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
                cout<<endl;
                
                cout<<"Player 2 wins";
                break;
            }
            else if(b1!=' ' && b2!=' ' && b3!=' ' && b4!=' ' && b5!=' ' && b6!=' ' && b7!=' ' && b8!=' ' && b9!=' '){
                cout<<endl;
                cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
                cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
                cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
                cout<<endl;
                
                cout<<"Tie--Restart game for a rematch";
                break;
            } 

            cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
            cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
            cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
        }

        cout<<"Enter Postion Player 2 (O): ";
        cin>>choice;


        if(choice>=1 && choice <=9){

            if( (choice==1 && b1!=' ') || (choice==2 && b2!=' ') || (choice==3 && b3!=' ') || (choice==4 && b4!=' ') || (choice==5 && b5!=' ') || (choice==6 && b6!=' ') || (choice==7 && b7!=' ') || (choice==8 && b8!=' ') || (choice==9 && b9!=' ') ){
                    flag1=false;
                    continue;
                }

            if(choice==1 && b1==' '){
                b1='O';
            }
            else if(choice == 2 && b2==' '){
                b2='O';
            }
            else if(choice == 3 && b3==' '){
                b3='O';
            }
            else if(choice == 4 && b4==' '){
                b4='O';
            }
            else if(choice == 5 && b5==' '){
                b5='O';
            }
            else if(choice == 6 && b6==' '){
                b6='O';
            }
            else if(choice == 7 && b7==' '){
                b7='O';
            }
            else if(choice == 8 && b8==' '){
                b8='O';
            }
            else if(b9==' '){
                b9='O';
            }
        }
        else{
            flag1=false;
            continue;
            
        }


        if( (b1=='X' && b2=='X' && b3=='X') || (b4=='X' && b5=='X' && b6=='X') || (b7=='X' && b8=='X' && b9=='X') || (b1=='X' && b5=='X' && b9=='X') || (b3=='X' && b5=='X' && b7=='X') || (b1=='X' && b4=='X' && b7=='X') || (b2=='X' && b5=='X' && b8=='X') || (b3=='X' && b6=='X' && b9=='X') ){   
            cout<<endl;
            cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
            cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
            cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
            cout<<endl;
            
            cout<<"Player 1 wins";
            break;
        }
        else if((b1=='O' && b2=='O' && b3=='O') || (b4=='O' && b5=='O' && b6=='O') || (b7=='O' && b8=='O' && b9=='O') || (b1=='O' && b5=='O' && b9=='O') || (b3=='O' && b5=='O' && b7=='O') || (b1=='O' && b4=='O' && b7=='O') || (b2=='O' && b5=='O' && b8=='O') || (b3=='O' && b6=='O' && b9=='O') ){
            cout<<endl;
            cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
            cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
            cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
            cout<<endl;

            cout<<"Player 2 wins";
            break;
        }
        else if(b1!=' ' && b2!=' ' && b3!=' ' && b4!=' ' && b5!=' ' && b6!=' ' && b7!=' ' && b8!=' ' && b9!=' '){
            cout<<endl;
            cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
            cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
            cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n";
            cout<<endl;

            cout<<"Tie--Restart game for a rematch";
            break;
        }

        cout<<"        " <<b1<<" | "<<b2<<" | "<<b3<<endl;
        cout<<"        " <<b4<<" | "<<b5<<" | "<<b6<<endl;
        cout<<"        " <<b7<<" | "<<b8<<" | "<<b9<<"\n"; 
        
        flag1=true;

    }

    cout<<endl;
    system("pause");
    return 0;
}


