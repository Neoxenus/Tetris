#include <iostream>
#include <string>

unsigned long long GCD(unsigned long long n1, unsigned long long n2);

class Rational
{
	long long numerator;
	unsigned long long denominator;
	


	void fractionReduction();
	
public:
	Rational();
	Rational(const long double&);
	Rational(long long numerator, unsigned long long denominator);

	long double getValue();


	Rational& operator= (const Rational& d);
	Rational& operator= (const long double& d);
	friend Rational& operator+= (Rational&, const Rational& );
	friend Rational& operator-= (Rational&, const Rational& );
	Rational& operator-- ();
	Rational& operator++ ();
	Rational operator-- (int);
	Rational operator++ (int);
	operator long double();
	friend Rational operator+ (const Rational&, const Rational&);
	friend Rational operator- (const Rational&, const Rational&);
	friend Rational operator* (const Rational&, const Rational&);
	friend Rational operator/ (const Rational&, const Rational&);

	friend bool operator== (const Rational& a, const Rational& b);
	friend std::istream& operator>> (std::istream& in, Rational& input);
	friend std::ostream& operator<< (std::ostream& out, const Rational& output);
};