#include "Rational.h"

void Rational::fractionReduction()
{
		long long gcd ;
	if (numerator == 0)
		return;
	
	gcd = GCD((numerator>0)?numerator:(-numerator), denominator);
	numerator /= gcd;
	denominator /= gcd;
}

Rational::Rational() : numerator(0), denominator(1)
{
}

Rational::Rational(const long double &d)
{
	long part = static_cast<long>(d);
	long double buf = d;
	numerator = part;
	buf -= part;

	while ((buf - static_cast<long>(buf)) != 0)
	{
		buf *= 10;
	}
	denominator = buf;
	if (denominator == 0)
		denominator++;
}

Rational::Rational(long long inputNumerator, unsigned long long inputDenominator = 1) : numerator(inputNumerator), denominator(inputDenominator)
{
}

long double Rational::getValue()
{
	return numerator * 1.0 / denominator;
}

Rational& Rational::operator=(const Rational& d)
{
	if (this == &d)
		return *this;
	this->numerator = d.numerator;
	this->denominator = d.denominator;
	return *this;
}
Rational& Rational::operator=(const long double& d)
{
	long part = static_cast<long>(d);
	long double buf = d;
	numerator = part;
	buf -= part;
	
	while ((buf - static_cast<long>(buf)) != 0)
	{
		buf *= 10;
	}
	denominator = buf;
	if (denominator == 0)
		denominator++;
	return *this;
}
Rational& operator+=(Rational &d1, const Rational& d2)
{
	d1 = d1 + d2;
	return d1;
}
Rational& operator-=(Rational& d1, const Rational& d2)
{
	d1 = d1 - d2;
	return d1;
}
std::istream& operator>>(std::istream& in, Rational& input)
{
	std::string buf;
	long long numerator = 0;
	unsigned long long denominator = 0;

	in >> buf;
	bool flagSlash = false, flagDot = false, sign = false;
	for (int i = 0; i < buf.size(); ++i)
	{
		if (buf[i] == '.')
		{
			if (flagSlash)
				exit(-1);
			flagDot = true;
		}
		else if (buf[i] == '/')
		{
			if (flagDot)
				exit(-1);
			flagSlash = true;
			continue;
		}
		else if (buf[i] == '-')
		{
			sign = true;
		}
		else if (buf[i] >= '0' && buf[i] <= '9')
		{
			buf[i] -= '0';
			if (!flagSlash && !flagDot)
			{
				numerator *= 10;
				numerator += buf[i];
			}
				
			else
			{
				denominator *= 10;
				denominator += buf[i];
			}
				
		}
		else
			exit(-2);
	}
	if (!denominator)
		denominator = 1;
	Rational ans((true)?(-numerator):numerator, denominator);
	input = ans;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& output)
{
	out << output.numerator << '/' << output.denominator;
	return out;
}

unsigned long long GCD(unsigned long long n1, unsigned long long n2)
{
	return (n2 == 0) ? n1 : GCD(n2, n1 % n2);
}

Rational& Rational::operator--()
{
	numerator = numerator - denominator;
	fractionReduction();
	return *this;
}

Rational& Rational::operator++()
{
	numerator = numerator + denominator;
	fractionReduction();
	return *this;
}

Rational Rational::operator--(int)
{
	Rational temp(this->numerator, this->denominator);
	--(*this);
	return temp;
}

Rational Rational::operator++(int)
{
	Rational temp(this->numerator, this->denominator);
	++(*this);
	return temp;
}

Rational::operator long double()
{
	return getValue();
}

Rational operator+(const Rational& d1, const Rational& d2)
{
	Rational ans;
	ans.numerator = d1.numerator*d2.denominator + d2.numerator*d1.denominator;
	ans.denominator = d1.denominator * d2.denominator;
	ans.fractionReduction();
	return ans;
}

Rational operator-(const Rational& d1, const Rational& d2)
{
	Rational ans;
	ans.numerator = d1.numerator * d2.denominator - d2.numerator * d1.denominator;
	ans.denominator = d1.denominator * d2.denominator;
	ans.fractionReduction();
	return ans;
}

Rational operator*(const Rational& d1, const Rational& d2)
{
	Rational ans;
	ans.numerator = d1.numerator * d2.numerator;
	ans.denominator = d1.denominator * d2.denominator;
	ans.fractionReduction();
	return ans;
}

Rational operator/(const Rational& d1, const Rational& d2)
{
	Rational ans;
	if (d2.numerator == 0)
		exit(-3);
	ans.numerator = d1.numerator * d2.denominator;
	long long den = (d1.denominator * d2.numerator);
	if (den < 0)
	{
		den *= (-1);
		ans.numerator += (-1);
	}
	ans.denominator = den;
	ans.fractionReduction();
	return ans;
}

bool operator==(const Rational& a, const Rational& b)
{
	return (a.numerator == b.numerator && a.denominator == b.denominator);
}

