/*
    Title:      Lab 1 – polynomial.cpp
    Purpose:    implements the polynomial class methods
    Author:     Karena Qian (Co-Author)
    Date:       April 16, 2022
*/
#include "polynomial.h"

#include <iostream>
#include <string>
//#include <sstream>
#include <iomanip>
//#include <cfloat>
#include <cmath>

using std::istream;
using std::ostream;
using std::string;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::showpos;

/**
* Constructor
* It creates a new empty Polynomial from given degree.
* @param degree the degree of new empty Polynomial
*/
Polynomial::Polynomial(size_t degree) : _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = 0.0;
	}
}
/**
* Constructor
* It constructs a new Polynomial from given degree and coefficients.
* @param degree the degree of new Polynomial
* @param coefficients the coefficients of new Polynomial
*/
Polynomial::Polynomial(size_t degree, const float* coefficients): _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = coefficients[i];
	}
}
/**
* Copy Constructor
* It creates a deep copy of given Polynomial.
* @param polynomial the Polynomial to be copied
*/
Polynomial::Polynomial(const Polynomial& polynomial): _degree(polynomial._degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = polynomial._coefficients[i];
	}
}
/**
* Destructor
* It deallocates all allocated memory.
*/
Polynomial::~Polynomial(){
	delete[] _coefficients;
}
/**
* operator+ (originally Sum)
* It returns the sum of two Polynomials, using polynomial summation.
* @param rhs the Polynomial to be added to this
* @returns a new Polynomial representing the Polynomial sum
*/
const Polynomial Polynomial::operator+(const Polynomial& rhs)const{ //originally Sum, changed for extra (extra) credit
    size_t smaller;
    size_t larger;
    Polynomial bigPoly(0);
    //identifies the smaller and bigger polynomials
    if(_degree > rhs._degree){
        bigPoly = *this;
        larger = _degree;
        smaller = rhs._degree;
    }
    else{
        bigPoly = rhs;
        larger = rhs._degree;
        smaller = _degree;
    }
    Polynomial p(larger);
    for(size_t i = 0; i <= larger; i++){
        if(i <= smaller) {
            p._coefficients[i] = _coefficients[i] + rhs._coefficients[i];
        }
        else{
            p._coefficients[i] = bigPoly._coefficients[i];
        }
    }
	return p;
}
/**
* operator- (originally Subtract)
* It returns the difference between two Polynomials, using polynomial subtraction.
* @param rhs the Polynomial to be subtracted with this
* @returns a new Polynomial representing the Polynomial difference
*/
const Polynomial Polynomial::operator-(const Polynomial& rhs)const{ //originally Subtract, changed for extra (extra) credit
    if(_degree < rhs._degree) {
        return rhs + (-*this);
    }
    else{
        return *this + (-rhs);
    }
}
/**
* operator- (originally Minus)
* It returns this with negated coefficients.
* @returns a new Polynomial representing the negative version of this
*/
const Polynomial Polynomial::operator-()const{ //originally Minus, changed for extra (extra) credit
	Polynomial retVal(*this);
	for (size_t i = 0; i < _degree + 1; i++) {
		retVal._coefficients[i] *= -1;
	}
	return retVal;
}
/**
* operator* (originally Multiply)
* It returns the product of two Polynomials, using polynomial multiplication.
* @param rhs the Polynomial to be multiplied with this
* @returns a new Polynomial representing the Polynomial product
*/
const Polynomial Polynomial::operator*(const Polynomial& rhs)const{ //originally Multiply, changed for extra (extra) credit
    Polynomial p(_degree + rhs._degree);
    for(size_t i = 0; i <= _degree; i++){
        for(size_t j = 0; j <= rhs._degree; j++){
            p._coefficients[j + i] += _coefficients[i] * rhs._coefficients[j];
        }
    }
    return p;
}
/**
* operator/ (originally Divide)
* It returns the quotient of two Polynomials, using polynomial long division.
* @param rhs the Polynomial to be divided with this
* @returns a new Polynomial representing the Polynomial quotient
*/
const Polynomial Polynomial::operator/(const Polynomial& rhs)const{ //originally Divide, changed for extra (extra) credit
    unsigned int newDegree; //degree for new Polynomial
    Polynomial copy(0); //copy of bigger Polynomial (for long division manipulation)
    double denominator;
    //identifies the smaller and bigger polynomials
    if(_degree < rhs._degree){
        newDegree = rhs._degree - _degree;
        copy = rhs;
        denominator = _coefficients[_degree];
    }
    else{
        newDegree = _degree - rhs._degree;
        copy = *this;
        denominator = rhs._coefficients[rhs._degree];
    }
    Polynomial p(newDegree);
    double numerator = copy._coefficients[copy._degree];
    size_t copyIndex = copy._degree; //keeps track of target coefficient of copy
    for(size_t i = p._degree + 1; i > 0; i--){
        p._coefficients[i - 1] = static_cast<float>(numerator / denominator);
        size_t index = copyIndex; //for keeping track of target coefficients of copy
        for(size_t j = rhs._degree + 1; j > 0; j--) {
            copy._coefficients[index] -= rhs._coefficients[j - 1] * p._coefficients[i - 1];
            index--;
        }
        copyIndex--;
        numerator = copy._coefficients[copyIndex];
    }
	return p;
}
/**
* operator() (originally Derive)
* It returns the derivative of Polynomial this.
* @returns a new Polynomial representing the derivative of this
*/
const Polynomial Polynomial::operator()()const{ //originally Derive, changed for extra (extra) credit
    Polynomial p(_degree - 1);
    for(size_t i = 1; i <= _degree; i++){
        p._coefficients[i - 1] = _coefficients[i] * static_cast<float>(i);
    }
	return p;
}
/**
* operator() (originally Evaluate)
* It evaluates Polynomial this by the given parameter and returns the answer.
* @param x the parameter to evaluate this with
* @returns the evaluated answer from Polynomial this
*/
float Polynomial::operator()(double x)const{ //originally Evaluate, changed for extra (extra) credit
    float sum = 0;
    for(size_t i = 0; i <= _degree; i++){
        sum += static_cast<float>(_coefficients[i] * pow(x, static_cast<double>(i)));
    }
	return sum;
}
/**
* operator() (originally Integrate)
* It returns the integral of Polynomial this between given starting and ending parameters
* @param start starting parameter of integral
* @param end ending parameter of integral
* @returns the evaluated integral of Polynomial this
*/
float Polynomial::operator()(double start, double end)const{ //originally Integrate, changed for extra (extra) credit
    float diff = 0;
    for(size_t i = 0; i <= _degree; i++){
        diff += static_cast<float>((_coefficients[i]/static_cast<float>(i + 1)) * pow(end, static_cast<double>(i + 1)));
    }
    for(size_t i = 0; i <= _degree; i++){
        diff -= static_cast<float>((_coefficients[i]/static_cast<float>(i + 1)) * pow(start, static_cast<double>(i + 1)));
    }
    return diff;
}
/**
* operator=
* It assigns Polynomial rhs to Polynomial.
* @param rhs the Polynomial to be assigned to this
* @returns *this
*/
const Polynomial& Polynomial::operator=(const Polynomial& rhs){
	if (&rhs == this){
		return *this;
	}
	if (_degree != rhs._degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = rhs._degree;
		_coefficients = new float[_degree + 1];
	}
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = rhs._coefficients[i];
	}
	return *this;
}
/**
* Equals
* It checks if Polynomial this is equals to Polynomial rhs.
* @param rhs the Polynomial to be compared with this
* @returns true if this and rhs are equal, false if not
*/
bool Polynomial::Equals(const Polynomial& rhs)const{
	if (_degree != rhs._degree){
		return false;
	}
	for (size_t i=0; i < _degree; i++){
		if (abs(_coefficients[i] - rhs._coefficients[i]) > 0.0001){
			return false;
		}
	}
	return true;
}
/**
* ToString
* It creates and returns a string representation of the Polynomial.
* @returns the string representation of the Polynomial
*/
string Polynomial::ToString()const{
	stringstream ss;
	for (size_t i = _degree; i > 0; i--) {
		ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
	}
	ss << showpos << fixed << setprecision(2) << _coefficients[0];
	return ss.str();
}
/**
* Write
* It writes a string representation of the Polynomial to give ostream.
* @param output ostream to write to
* @returns output
*/
ostream& Polynomial::Write(ostream& output)const{
	output << _degree << " ";
	for (size_t i = 0; i < _degree + 1; i++) {
		output << _coefficients[i] << " ";
	}
	return output;
}
/**
* Read
* It reads information from a Polynomial from given istream
* @param input istream to read from
* @returns input
*/
istream& Polynomial::Read(istream& input){
	size_t degree;
	input >> degree;
	if (input.fail()){
		return input;
	}
	float* coefficients = new float[degree + 1];
	for (size_t i = 0; i < degree + 1; i++) {
		input >> coefficients[i];
		if (input.fail()){
			delete[] coefficients;
			return input;
		}
	}

	if (degree != _degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = degree;
		_coefficients = coefficients;
	}else{
		for (size_t i = 0; i < _degree + 1; i++) {
			_coefficients[i] = coefficients[i];
		}
		delete[] coefficients;
	}
	return input;
}
