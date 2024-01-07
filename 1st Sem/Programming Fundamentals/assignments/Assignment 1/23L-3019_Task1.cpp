#include <iostream>
using namespace std;

int main(){

   // Total Percentage Of Men = 52
   // Total Literacy Percentage = 48
   // Total Literate Men Percentage = 35 (out of 80000)
   // POP = 80000

   double NumMen,PercentIlliterateMen,LiterateMen,IlliterateMen,Population = 80000;

   NumMen = .52 * Population;
   LiterateMen = .35 * Population;
   IlliterateMen = NumMen - LiterateMen;
 
   double NumWomen,NumLiterateWomen,IlliterateWomen;

      NumWomen = ((100-52)/100.0) * Population;                      // add ".0" in integer arithmetics to preserve float 
      NumLiterateWomen = ((48-35)/100.0) * Population;
      IlliterateWomen = NumWomen - NumLiterateWomen;

      cout<<"Illiterate Men: "<<IlliterateMen<<endl;
      cout<<"Illiterate Women: "<<IlliterateWomen<<endl;
      cout<<"Total Number Of Illiterate Men and Women: "<<IlliterateMen+IlliterateWomen;


   return 0;
}