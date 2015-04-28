/*
 * Copyright (C) 2015  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QSL_VEC_H
#define QSL_VEC_H

#include "qsl_global.h"
#include <cmath>

namespace Qsl {

class Vec2D
{
public:

    Vec2D() : _x(0.0), _y(0.0) {}
    Vec2D(double x, double y) : _x(x), _y(y) {}

    double x() const { return _x; }
    void setX(double x) { _x = x; }

    double y() const { return _y; }
    void setY(double y) { _y = y; }

    Vec2D operator- () const { return Vec2D(-_x,-_y); }
    Vec2D operator+ (const Vec2D &v) const { return Vec2D(_x+v._x,_y+v._y); }
    Vec2D operator- (const Vec2D &v) const { return Vec2D(_x-v._x,_y-v._y); }
    double operator* (const Vec2D &v) const { return _x*v._x + _y*v._y; }
    Vec2D operator* (double x) const { return Vec2D(_x*x,_y*x); }
    Vec2D operator/ (double x) const { return Vec2D(_x/x,_y/x); }

    double lenSqr() const { return _x*_x + _y*_y; }
    double len() const { return std::sqrt(_x*_x + _y*_y); }

    Vec2D& operator+= (const Vec2D &v) { _x+=v._x; _y+=v._y; return *this; }
    Vec2D& operator-= (const Vec2D &v) { _x-=v._x; _y-=v._y; return *this; }
    Vec2D& operator*= (double x) { _x*=x; _y*=x; return *this; }
    Vec2D& operator/= (double x) { _x/=x; _y/=x; return *this; }

private:

    double _x, _y;
};


class Vec3D
{
public:
    
    Vec3D() : _x(0.0), _y(0.0), _z(0.0) {}
    Vec3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}
    
    double x() const { return _x; }
    void setX(double x) { _x = x; }
    
    double y() const { return _y; }
    void setY(double y) { _y = y; }

    double z() const { return _z; }
    void setZ(double z) { _z = z; }
    
    Vec3D operator- () const { return Vec3D(-_x,-_y,-_z); }
    Vec3D operator+ (const Vec3D &v) const { return Vec3D(_x+v._x,_y+v._y,_z+v._z); }
    Vec3D operator- (const Vec3D &v) const { return Vec3D(_x-v._x,_y-v._y,_z-v._z); }
    double operator* (const Vec3D &v) const { return _x*v._x + _y*v._y + _z*v._z; }
    Vec3D operator* (double x) const { return Vec3D(_x*x,_y*x,_z*x); }
    Vec3D operator/ (double x) const { return Vec3D(_x/x,_y/x,_z/x); }
    
    double lenSqr() const { return _x*_x + _y*_y + _z*_z; }
    double len() const { return std::sqrt(_x*_x + _y*_y + _z*_z); }
    
    Vec3D& operator+= (const Vec3D &v) { _x+=v._x; _y+=v._y; _z+=v._z; return *this; }
    Vec3D& operator-= (const Vec3D &v) { _x-=v._x; _y-=v._y; _z-=v._z; return *this; }
    Vec3D& operator*= (double x) { _x*=x; _y*=x; _z*=x; return *this; }
    Vec3D& operator/= (double x) { _x/=x; _y/=x; _y/=x; return *this; }
    
private:
    
    double _x, _y, _z;
};

inline Vec2D to2D(const Vec3D &v) { return Vec2D(v.x(),v.y()); }
inline Vec3D to3D(const Vec2D &v) { return Vec3D(v.x(),v.y(),0.0); }

} // namespace Qsl

#endif // QSL_VEC_H
