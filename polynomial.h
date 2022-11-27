#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>
using std::istream;
using std::ostream;
using std::string;

class Polynomial{
	size_t _degree;
	float* _coefficients;
public:
	Polynomial(size_t);
	Polynomial(size_t, const float*);
	Polynomial(const Polynomial&);
	~Polynomial();
	const Polynomial operator+(const Polynomial&)const; //modified for extra (extra) credit
	const Polynomial operator-(const Polynomial&)const; //modified for extra (extra) credit
	const Polynomial operator-()const; //modified for extra (extra) credit
	const Polynomial operator*(const Polynomial&)const; //modified for extra (extra) credit
	const Polynomial operator/(const Polynomial&)const; //modified for extra (extra) credit
	const Polynomial operator()()const; //modified for extra (extra) credit
	float operator()(double)const; //modified for extra (extra) credit
	float operator()(double, double)const; //modified for extra (extra) credit
	const Polynomial& operator=(const Polynomial&);
	string ToString()const;
	bool Equals(const Polynomial&)const;
	ostream& Write(ostream&)const;
	istream& Read(istream&);

};



#endif
