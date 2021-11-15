#include<iostream>
#include<string>
#include<array>

#include"include/orion/vector.h"
#include"include/orion/array.h"
#include"include/orion/dtype.h"
#include"include/orion/utils.h"
  
int main(int argc, const char** argv) {

    (void)argc;
    (void)argv;

    // for (int i = 0; i < argc; i++) {

        // std::cout << *(argv + i) << std::endl;
    // }

    // LOG(sizeof(i8))
    // LOG(sizeof(i16))
    // LOG(sizeof(i32))
    // LOG(sizeof(i64))

    // LOG(sizeof(ui8))
    // LOG(sizeof(ui16))
    // LOG(sizeof(ui32))
    // LOG(sizeof(ui64))

    // LOG(sizeof(f32))
    // LOG(sizeof(f64))
    // LOG(sizeof(f128))

    Vector<f32> *vec;
    vec = new Vector<f32>();

    Vec2<f32> &vec2 = vec->vec2;
    Vec3<f32> &vec3 = vec->vec3;
    Vec4<f32> &vec4 = vec->vec4;

    vec2.x = 12.00f;
    vec2.y = 8.00f;
    vec3.z = 6.00f;
    vec4.w = 500.00f;

    printVector<f32>(*vec);

    Yo::LinkedList<i8> *ll;

    ll = new Yo::LinkedList<i8>();

    ll->push(3);
    ll->push(6);
    ll->push(9);
    // ll->push(1);
    // ll->push(5);
    // ll->push(8);
    // ll->push(7);

    std::cout << (size_t)(ll) << std::endl;

    ui8* t = Ye::int2str<6>((ui64)(ll));
    ui64 n = Ye::str2int<6>(t);


    std::cout << Ye::int2hex<6>((ui64)(ll)) << std::endl;
    std::cout << Ye::hex2int<6>(Ye::int2hex<6>((ui64)(ll))) << std::endl;

    std::cout << n << std::endl;


    std::cout << ll << std::endl;

    ui8* h = Ye::str2hex<6>(t);
    ui8* s = Ye::hex2str<6>(h);

    std::cout << h << std::endl;

    Ye::printStr2Int<6>(s);

    // int to mem to cast

    Yo::LinkedList<i8> *ls;

    ls = Ye::castInt<Yo::LinkedList<i8>>(n);

    LOG(ls)

    ls->push(12);


    // -------------------

    std::cout << ll->size() << std::endl;

    for (size_t i = 0; i < ls->size(); i++) {

        std::cout << (int)(ls->get(i)) << std::endl;
    }

    Ye::printStr2Int<6>(t);

    // std::cout << Ye::a2i('0') << std::endl;
    // std::cout << Ye::a2i('9') << std::endl;
    // std::cout << Ye::a2i('a') << std::endl;
    // std::cout << Ye::a2i('z') << std::endl;
    // std::cout << Ye::a2i('A') << std::endl;
    // std::cout << Ye::a2i('Z') << std::endl;

    // std::cout << Ye::a2i('+') << std::endl;
    // std::cout << Ye::a2i('/') << std::endl;
    // std::cout << Ye::i2a(62) << std::endl;
    // std::cout << Ye::i2a(63) << std::endl;

    // std::cout << Ye::i2b(0) << std::endl;
    // std::cout << Ye::i2b(25) << std::endl;
    // std::cout << Ye::i2b(26) << std::endl;
    // std::cout << Ye::i2b(51) << std::endl;
    // std::cout << Ye::i2b(52) << std::endl;
    // std::cout << Ye::i2b(61) << std::endl;
    // std::cout << Ye::i2b(62) << std::endl;
    // std::cout << Ye::i2b(63) << std::endl;

    // std::cout << Ye::b2i('A') << std::endl;
    // std::cout << Ye::b2i('Z') << std::endl;
    // std::cout << Ye::b2i('a') << std::endl;
    // std::cout << Ye::b2i('z') << std::endl;
    // std::cout << Ye::b2i('0') << std::endl;
    // std::cout << Ye::b2i('9') << std::endl;
    // std::cout << Ye::b2i('+') << std::endl;
    // std::cout << Ye::b2i('/') << std::endl;

    return 0;
}
