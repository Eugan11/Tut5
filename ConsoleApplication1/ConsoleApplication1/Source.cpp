
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Shape
{
protected:
	string name;
	int numsides;
	float *dims;
public:
	//default constructor
	Shape(string nm = "unspecified shape", int num_sides = 0)
	{
		setName(nm);
		setNum(num_sides);
	}

	static const float PI; //for use in circle

	//abstract base class due to pure virtual fn call--MUST be overridden in derived class
	virtual float getArea(/*float *dims*/) = 0;

	//other accessors from defult constructor
	virtual string setName(string nm)
	{
		name = nm;
	}

	virtual int setNum(int ns)
	{
		numsides = ns;
	}

	virtual string getName()
	{
		return name;
	}

	virtual void printName() const
	{
		cout << "This shape is a " << name << endl;
	}

	void setDims(float *sizes)
	{
		dims = sizes;
		numsides = sizeof(sizes) / sizeof(float);
	}

};

const float Shape::PI = M_PI;	//math.h PI implementation

class Triangle : public Shape
{
public:
	//default constructor
	Triangle(string nm = "Triangle", int sides = 3);

	//other constructor overwrite for sizing
	Triangle(float *sizes)
	{
		setName("Triangle");
		setDims(sizes);
	}

	virtual float getArea(/*float **/) override //overriding pure virtual base functions
	{
		//http://www.mathopenref.com/heronsformula.html
		float a = *(dims);
		float b = *(dims + 1);
		float c = *(dims + 2);
		float s = (a + b + c) / 2;

		return sqrt(s*(s - a)*(s - b)*(s - c));
	}
};

class Circle : public Shape
{
public:
	//default constructor (name only)
	Circle(int numsides = 0, string nm = "Circle");
	Circle(float *r)
	{
		setName("Circle");
		setDims(r);
	}

	virtual float getArea(/*float **/) override
	{
		return PI*(pow((*dims), 2));
	}
};

class Rectangle :public Shape
{
public:
	//default constructor
	Rectangle(string nm = "Rectangle", int numsides = 4);
	Rectangle(float *dims)
	{
		setName("Rectangle");
		setDims(dims);
	}

	virtual float getArea(/*float **/) override
	{
		float a = (*dims);
		float b = (*dims) + 1;
		return a*b;
	}
};

int main()
{
	//these dimensions allow areas to be fully calculated
	float triDimensions[] = { 5, 12, 13 };
	float rectDimensions[] = { 5, 15 };
	float circRad = 2;

	//instantiate object from derived classes only due to abstract base class
	Triangle A;
	A.setDims(triDimensions);
	Rectangle B; //testing default constructor
	B.setDims(rectDimensions);
	Circle C(2);
	C.setDims(&circRad);

	cout << "Shape 1 is: " << endl;
	A.printName();
	cout << "Shape 2 is: " << endl;
	B.printName();
	cout << "Shape 3 is: " << endl;
	C.printName();

	Shape *myShapes[] = { &A, &B, &C },
		**shapePtr = myShapes;

	cout << endl << "The areas of the shapes are: " << endl;

	for (int i = 0; i<3; ++i)
	{
		cout << "The area of Shape " << 1 + i << " is: " << (*(shapePtr + i))->getArea() << endl;
	}

}