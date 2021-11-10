#pragma once
#ifndef __ORION_VECTOR__
#define __ORION_VECTOR__

#include<iostream>
#include<string>
#include<array>

#ifdef __cplusplus

extern "C++" {

    template<typename T>
    struct Vec2 {
        T x, y;
    };

    template<typename T>
    struct Vec3 {
        T x, y, z;
    };

    template<typename T>
    struct Vec4 {
        T x, y, z, w;
    };

    template<typename T>
    struct Vector {
        union {
            // Vec4
            Vec4<T> vec4;
            // Vec3
            Vec3<T> vec3;
            // Vec2
            Vec2<T> vec2;
        };
    };

    template<typename T>
    void printVector(const Vector<T> &vector) {

        std::cout << "x: " << vector.vec2.x << std::endl;
        std::cout << "y: " << vector.vec2.y << std::endl;
        std::cout << "z: " << vector.vec3.z << std::endl;
        std::cout << "w: " << vector.vec4.w << std::endl;
    }
}

#endif
#endif
