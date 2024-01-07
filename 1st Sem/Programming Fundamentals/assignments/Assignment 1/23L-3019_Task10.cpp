// -6 -12 8 13 11 6 7 2 -6 -9 -10 11 10 9 2

#include <iostream>
#include <cmath>
using namespace std;

int main(){

    double mean,Standard_Deviation,sum,sum_x2,DistMean1,DistMean2,DistMean3,DistMean4,DistMean5,DistMean6,DistMean7,DistMean8,DistMean9,DistMean10,DistMean11,DistMean12,DistMean13,DistMean14,DistMean15;
    double sumDist; 

    sum = -6-12+8+13+11+6+7+2-6-9-10+11+10+9+2;
    mean = sum/ 15.0;

    DistMean1 = pow((-6-mean),2);
    DistMean2 = pow((-12-mean),2);
    DistMean3 = pow((8-mean),2);
    DistMean4 = pow((13-mean),2);
    DistMean5 = pow((11-mean),2);
    DistMean6 = pow((6-mean),2);
    DistMean7 = pow((7-mean),2);
    DistMean8 = pow((2-mean),2);
    DistMean9 = pow((-6-mean),2);
    DistMean10 = pow((-9-mean),2);
    DistMean11= pow((-10-mean),2);
    DistMean12= pow((11-mean),2);
    DistMean13 = pow((10-mean),2);
    DistMean14 = pow((9-mean),2);
    DistMean15 = pow(2-mean,2);

    sumDist = DistMean1 + DistMean2 + DistMean3 + DistMean4 + DistMean5 + DistMean6 + DistMean7 + DistMean8 + DistMean9 + DistMean10 + DistMean11 + DistMean12 + DistMean13 + DistMean14 + DistMean15;
    Standard_Deviation = sqrt(sumDist/15.0);

    cout<<"Mean: "<<mean<<endl;
    cout<<"Standard Deviation: "<<Standard_Deviation;           

    return 0;
}