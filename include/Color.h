#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    double r, g, b;

    // Constructors
    Color();
    Color(double r_, double g_, double b_);

    // Operator overloads
    Color operator+(const Color& c) const;
    Color& operator+=(const Color& c);
    Color operator*(double s) const;
    Color operator*(const Color& c) const;
    Color& operator*=(double s);
};

#endif // COLOR_H
