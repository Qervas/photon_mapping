#include "Color.h"

Color::Color() : r(0), g(0), b(0) {}
Color::Color(double r_, double g_, double b_) : r(r_), g(g_), b(b_) {}

Color Color::operator+(const Color& c) const {
    return Color(r + c.r, g + c.g, b + c.b);
}

Color& Color::operator+=(const Color& c) {
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

Color Color::operator*(double s) const {
    return Color(r * s, g * s, b * s);
}

Color Color::operator*(const Color& c) const {
    return Color(r * c.r, g * c.g, b * c.b);
}

Color& Color::operator*=(double s) {
    r *= s;
    g *= s;
    b *= s;
    return *this;
}
