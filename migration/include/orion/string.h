#pragma once
#ifndef ORION_STRING_H
#define ORION_STRING_H

#include<iostream>
#include<string>
#include<bitset>

#include"dtype.h"
#include"debug.h"
#include"array.h"

#define BS(x) std::cout << std::bitset<8>(x) << std::endl;

#ifdef __cplusplus
extern "C++" {

    enum TypeChar {

        UTF_8,
        UTF_16,
        UTF_32,

    };

    // < 0x80     utf8
    // < 0x10000  utf16
    //            utf32

    namespace CodeCVT {

        struct UTF8 {

            u32 codePointAt(u32 n) { // uchar to oct

                if      (n < 0x100    ) return n;
                else if (n < 0x10000  ) return                             ((n & 0x1F00) >> 2) + (n & 0x3F);
                else if (n < 0x1000000) return     ((n & 0xF0000 ) >> 4) + ((n & 0x3F00) >> 2) + (n & 0x3F);
                // < 0x100000000
                else return ((n & 0x7000000) >> 6) + ((n & 0x3F0000) >> 4) + ((n & 0x3F00) >> 2) + (n & 0x3F);
            }

            u32 fromCodePoint(u32 n) { // oct to uchar

                // 0o77       0x3f
                // 0o7700     0xfc0
                // 0o770000   0x3f000
                // 0o77000000 0xfc0000

                if      (n < 0x80   ) return n;
                else if (n < 0x800  ) return                                                       0xC000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
                else if (n < 0x10000) return                     0xE00000 + ((n & 0x3f000) << 4) + 0x8000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
                // < 0x200000
                else return 0xF0000000 + ((n & 0xfc0000) << 6) + 0x800000 + ((n & 0x3f000) << 4) + 0x8000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
            }

        };

        struct UTF16 {

            u32 codePointAt(u32 n) { // uchar to oct

                if (n < 0x10000) return n;
                else {

                    n = ((n & 0x3FF0000) >> 6) + (n & 0x3FF);

                    return n + 0x10000;
                }
            }

            u32 fromCodePoint(u32 n) { // oct to uchar

                if (n < 0x10000) return n;
                else {

                    n = n - 0x10000;

                    return 0xD8000000 + ((n & 0xFFC00) << 6) + 0xDC00 + (n & 0x3FF);
                }
            }
        };

        struct UTF32 {

            u32 codePointAt(u32 n) { // uchar to oct

                return n;
            }

            u32 fromCodePoint(u32 n) { // oct to uchar

                return n;
            }
        };
    };

    struct VirtualChar {

        u32 data;
        TypeChar type;

        void init(u32& n) {

            data = n;
            
            if (n < 0x80) type = TypeChar::UTF_8;
            else if (n < 0x10000) type = TypeChar::UTF_16;
            else type = TypeChar::UTF_32;
        
        }

        VirtualChar(void) {

            data = 0;
            type = TypeChar::UTF_8;
        
        }

        VirtualChar(u32& n) {

            VirtualChar();
            init(n);

        }

        ~VirtualChar() {}

    };

    typedef Ex::List<VirtualChar> xlist;
    typedef Ex::List<u8> utf8buffer;
    typedef Ex::List<u16> utf16buffer;
    typedef Ex::List<u32> utf32buffer;

    class vchar {

        // mark
        // 01001011
        // 1 0 1 3
        // 2 1 2 4
        // 2 bytes
        // 1 bytes
        // 2 bytes
        // 4 bytes

        private:

            utf8buffer buffer;

            // utf32buffer cache;

            u64 count;
            
            u64 mark;
            u8 pack;

        public:

            vchar(void) {

                count = 0;

                mark = 0;
                pack = 4;

            }
            ~vchar() {}

            void push(u32& data) {

                u8 r;
                // u8 m;

                r = 4;

                if (pack == 0) pack = 4;

                // 256        1 bytes 0x100
                // 65536      2 bytes 0x10000
                // 16777216   3 bytes 0x1000000
                // 4294967296 4 bytes 0x100000000

                if      (data < 0x100)       r = 1; 
                else if (data < 0x10000)     r = 2; 
                else if (data < 0x1000000)   r = 3; 
                // else if (data < 0x100000000) r = 4; 
                // else r = 4;

                if (pack == 4) {
                
                    // create mark
                    u8& m = *(new u8);

                    m = 0x55;

                    buffer.push(m);
                    mark = buffer.size() -1;
                }

                // get mark
                u8& m = buffer[mark];

                // 0xFF & (0x03 << 6)

                u8 ir;

                u8 i;
                u8 R;
                u8 L;

                i = 0;
                R = 0;
                L = 0;

                ir = ((pack - 1) * 2);

                i = 6 - ir;

                R = ((1 << ir) - 1);

                L = ((1 << i) - 1) << (8 - i); // 6 - i + 2

                m &= (L | R);

                // 00111111
                // 11001111
                // 11110011
                // 11111100

                m |= (r - 1) << ir;


                if (r > 3) buffer.push((data >> 24) & 0xFF);
                if (r > 2) buffer.push((data >> 16) & 0xFF);
                if (r > 1) buffer.push((data >> 8) & 0xFF);
                if (r > 0) buffer.push(data & 0xFF);

                // count += r;
                count++;

                pack--;
            }

            u64 size(void) {

                return count;
            }

            auto& getBuffer(void) {

                return buffer;
            }

            auto& utf32encode(void) {

                u8 p;
                u8 r;
                u8 m;
                u32 c;

                bool h;

                utf32buffer& temp = *(new utf32buffer);
                
                p = 4;
                r = 0;
                m = 0;
                c = 0;

                h = true;

                u64 i;
                i = 0;

                while (true) {

                    // get mark
                    if (h) {
                        
                        m = buffer[i];
                        h = false;
                        i++;
                        continue;
                    }


                    // get range
                    r = (m >> ((p - 1) * 2)) & 0x03;
                    r = r + 1;

                    for (u8 j = 0; j < r; j++) {

                        c += buffer[i + j] << ((r - j - 1) * 8);

                        // i++;
                    }

                    u32 t;
                    t = c;

                    if (r > 1 && t == 0x00) break;

                    temp.push(t);
                    c = 0;

                    // update pack
                    p = (p != 1 ? p - 1 : 4);

                    if (p == 4) h = true;

                    // update pos
                    // i++;
                    i = i + r;
                }

                return temp;
            }
    };

    class String {

        private:


            utf32buffer buffer; 
        
        // private

        public:

            String(void) {}
            
            String(const char*) {}

            String(std::string) {}

            String(utf32buffer& raw) {

                buffer = raw.copy();
            }

            ~String() {}

            void push(u32& data) {

                // VirtualChar virtchar(data);
                // LOG(sizeof(virtchar))
                buffer.push(data);
            }

            auto& utf8encode(void) {

                utf8buffer& ulist = *(new utf8buffer);
                VirtualChar virtchar;
                CodeCVT::UTF8 cvt;
                TypeChar utf8 = UTF_8;

                u8 v;
                u32 n;

                for (u64 i = 0; i < buffer.size(); i++) {


                    virtchar.init(buffer[i]);

                    if (virtchar.type == utf8) ulist.push(virtchar.data);
                    else {

                        n = cvt.fromCodePoint(virtchar.data);

                        u8 p = 32;

                        do {

                            p = p - 8;

                            v = (n >> p) & 0xFF;

                            if (v != 0x00) ulist.push(v);

                        } while (p != 0x00);
                    }
                }

                return ulist;
            }

            auto& utf16encode(void) {

                utf16buffer& ulist = *(new utf16buffer);
                VirtualChar virtchar;
                CodeCVT::UTF16 cvt;
                TypeChar utf8 = UTF_8;
                TypeChar utf16 = UTF_16;

                u32 n;

                for (u64 i = 0; i < buffer.size(); i++) {


                    virtchar.init(buffer[i]);

                    if (virtchar.type == utf8 || virtchar.type == utf16) ulist.push(virtchar.data);
                    else {
                        n = cvt.fromCodePoint(virtchar.data);
                        ulist.push((n >> 16) & 0xFFFF);
                        ulist.push(n & 0xFFFF);
                    }
                }

                return ulist;
            }

            auto& utf32encode(void) {

                // utf32buffer& ulist = *(new utf32buffer);
                // VirtualChar virtchar;
                // // CodeCVT::UTF32 cvt;
                // // TypeChar utf8 = UTF_8;
                // // TypeChar utf16 = UTF_16;
                // // TypeChar utf32 = UTF_32;

                // for (u64 i = 0; i < buffer.size(); i++) {


                //     virtchar.init(buffer[i]);

                //     // if (virtchar.type == utf8 || virtchar.type == utf16 || virtchar.type == utf32) ulist.push(virtchar.data);
                //     // else ulist.push(cvt.fromCodePoint(virtchar.data));
                //     ulist.push(virtchar.data); // always 32
                // }

                // return ulist;

                return buffer.copy();
            }

            void utf8decode(utf8buffer raw) {

                // 10  000000 0x80 0xC0
                // 110  00000 0xC0 0xE0
                // 1110  0000 0xE0 0xF0
                // 11110  000 0xF0 0xF8

                u8 b;
                u32 r;
                u32 d;

                CodeCVT::UTF8 cvt;
                
                b = 0;
                r = 1;
                d = 0;

                for (u64 i = 0; i < raw.size(); i++) {

                    b = raw[i];

                    if      ((b & 0xE0) == 0xC0) r = 2;
                    else if ((b & 0xF0) == 0xE0) r = 3;
                    else if ((b & 0xF8) == 0xF0) r = 4;
                    else {

                        if ((b & 0xC0) != 0x80) r = 1;
                    }

                    if      (r == 4) d += b << 24;
                    else if (r == 3) d += b << 16;
                    else if (r == 2) d += b << 8;
                    else if (r == 1) {

                        d += b;

                        buffer.push(cvt.codePointAt(d));

                        d = 0;
                    }

                    r--;
                }
            }

            void utf16decode(utf16buffer raw) {
                
                u16 b;
                u32 r;
                u32 d;

                CodeCVT::UTF16 cvt;
                
                b = 0;
                r = 1;
                d = 0;

                for (u64 i = 0; i < raw.size(); i++) {

                    b = raw[i];

                    if ((b & 0xFC00) == 0xD800) r = 2;
                    else r = 1;

                    if      (r == 2) d += b << 16;
                    else if (r == 1) {

                        d += b;

                        buffer.push(cvt.codePointAt(d));

                        d = 0;
                    }

                    r--;
                }
            }

            void utf32decode(utf32buffer raw) {

                CodeCVT::UTF32 cvt;

                for (u64 i = 0; i < raw.size(); i++) {

                    buffer.push(cvt.codePointAt(raw[i]));
                }
            }

        // public
    };


}
#endif

#endif
