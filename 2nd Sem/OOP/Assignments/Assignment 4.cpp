#include <iostream>
#include <cmath>
using namespace std;

class ComplexNumber
{
private:

	int real, imaginary;

public:

	ComplexNumber(int, int);
	~ComplexNumber();
	void Input();
	void Output();
	bool IsEqual(ComplexNumber);
	ComplexNumber Conjugate();
	ComplexNumber Add(ComplexNumber);
	ComplexNumber Subtract(ComplexNumber);
	ComplexNumber Multiplication(ComplexNumber);
	float Magnitude();

};


ComplexNumber::~ComplexNumber()
{

}


ComplexNumber::ComplexNumber(int real_p, int imaginary_p)
{
	real = real_p;
	imaginary = imaginary_p;
}


void ComplexNumber::Input()
{
	cout << "Enter Real: ";
	cin >> real;

	cout << "Enter Imaginary: ";
	cin >> imaginary;

}


void ComplexNumber::Output()
{
	if (imaginary >= 0)
		cout << real << "+" << imaginary << "i\n";

	else
		cout << real << imaginary << "i\n";

}

// c2 parameter is complex number 2

bool ComplexNumber::IsEqual(ComplexNumber c2)
{
	if (real == c2.real && imaginary == c2.imaginary)
		return true;

	else
		return false;
}


ComplexNumber ComplexNumber::Conjugate()
{
	ComplexNumber temp(0, 0);

	temp.real = real;
	temp.imaginary = imaginary * -1;

	return temp;
}


ComplexNumber ComplexNumber::Add(ComplexNumber c2)
{
	ComplexNumber temp(0, 0);

	temp.real = real + c2.real;
	temp.imaginary = imaginary + c2.imaginary;

	return temp;
}


ComplexNumber ComplexNumber::Subtract(ComplexNumber c2)
{
	ComplexNumber temp(0, 0);

	temp.real = real - c2.real;
	temp.imaginary = imaginary - c2.imaginary;

	return temp;
}

ComplexNumber ComplexNumber::Multiplication(ComplexNumber c2)
{
	ComplexNumber temp(0, 0);

	temp.real = real * c2.real;
	temp.imaginary = real * c2.imaginary;
	temp.imaginary += imaginary * c2.real;
	temp.real += -(imaginary * c2.imaginary);

	return temp;
}


float ComplexNumber::Magnitude()
{
	return sqrt(real * real + imaginary * imaginary);
}



void main()
{
	ComplexNumber c1(0, 0), c2(0, 0);

	cout << "Enter c1 :\n";
	c1.Input();

	cout << "\n";
	

	cout << "Enter c2 :\n";
	c2.Input();


	cout << "\n";


	cout << "c1 = ";
	c1.Output();
	cout << "c2 = ";
	c2.Output();


	cout << "\n";


	if (c1.IsEqual(c2))
		cout << "c1 is equal to c2\n\n";

	else
		cout << "c1 is not equal to c2\n\n";



	cout << "Conjugate of c1 = \t";
	ComplexNumber temp = c1.Conjugate();
	temp.Output();

	cout << "Conjugate of c2 = \t";
	temp = c2.Conjugate();
	temp.Output();

	cout << "\n";



	cout << "c1 + c2 = \t";
	temp = c1.Add(c2);
	temp.Output();

	cout << "c1 - c2 = \t";
	temp = c1.Subtract(c2);
	temp.Output();


	cout << "c1 x c2 = \t";
	temp = c1.Multiplication(c2);
	temp.Output();

	cout << "\n";

	cout << "Magnitude of c1 = \t"<<c1.Magnitude()<<"\n";
	cout << "Magnitude of c2 = \t" << c2.Magnitude() << "\n";


	cout << '\n';
	system("pause");
}