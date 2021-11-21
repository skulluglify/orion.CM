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

    Ex::List<i8> *ll;

    ll = new Ex::List<i8>();

    ll->Push(3);
    ll->Push(6);
    ll->Push(9);
    ll->Push(1);
    ll->Push(5);
    // ll->Push(8);
    // ll->Push(7);

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

    Ex::List<i8> *ls;

    ls = Ye::castInt<Ex::List<i8>>(n);

    LOG(ls)

    ls->Push(12);

    ls->SetItem(4, 64);

    // ls->Remove(0);
    // ls->Remove(4);
    // ls->Remove(1);
    // ls->Remove(2);
    // ls->Remove(4);


    // -------------------

    std::cout << ll->Size() << std::endl;

    for (size_t i = 0; i < ls->Size(); i++) {

        std::cout << (int)(ls->GetItem(i).value) << std::endl;
    }

    Ex::List<i8> *lx;

    lx = &ls->Copy();

    for (size_t i = 0; i < lx->Size(); i++) {

        std::cout << (int)(lx->GetItem(i).value) << std::endl;
    }

    Ex::List<i8> *le;
    Ex::List<i8> *lf;

    le = &ls->Concat(*ls, *lx, *ls);

    LOG((le->Contains(12) ? "ok found it" : "not found anymore"))
    LOG((le->Contains(24) ? "ok found it" : "not found anymore"))

    le->Shift();
    le->Pop();
    le->Remove(4);

    le->Reverse();

    std::cout << "===" << std::endl;

    for (size_t i = 0; i < le->Size(); i++) {

        Ex::ReturnType<i8> rt = le->GetItem(i);

        if (rt.type == Ex::ReturnType<i8>::Status::OK) std::cout << (int)(rt.value) << std::endl;
    }

    std::cout << "===" << std::endl;

    lf = &le->Slice(2, 4);

    std::cout << "===" << std::endl;

    for (size_t i = 0; i < le->Size(); i++) {

        Ex::ReturnType<i8> rt = le->GetItem(i);

        if (rt.type == Ex::ReturnType<i8>::Status::OK) std::cout << (int)(rt.value) << std::endl;
    }

    std::cout << "===" << std::endl;

    std::cout << "===" << std::endl;

    for (size_t i = 0; i < lf->Size(); i++) {

        Ex::ReturnType<i8> rt = lf->GetItem(i);

        if (rt.type == Ex::ReturnType<i8>::Status::OK) std::cout << (int)(rt.value) << std::endl;
    }

    std::cout << "===" << std::endl;


    lf->Reverse();

    std::cout << "===" << std::endl;

    for (size_t i = 0; i < lf->Size(); i++) {

        Ex::ReturnType<i8> rt = lf->GetItem(i);

        if (rt.type == Ex::ReturnType<i8>::Status::OK) std::cout << (int)(rt.value) << std::endl;
    }

    lf->Splice(1, 1, (i8)23, (i8)24, (i8)25);

    lf->Reverse();

    std::cout << "===" << std::endl;

    for (size_t i = 0; i < lf->Size(); i++) {

        Ex::ReturnType<i8> rt = lf->GetItem(i);

        if (rt.type == Ex::ReturnType<i8>::Status::OK) std::cout << (int)(rt.value) << std::endl;
    }

    std::cout << "===" << std::endl;

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
