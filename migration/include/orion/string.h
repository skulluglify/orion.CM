#pragma once
#ifndef ORION_STRING_H
#define ORION_STRING_H

#include<string>

#include"dtype.h"
#include"debug.h"
#include"array.h"

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

                    return 0xD8000000 + ((n & 0xFFC00) << 6) +
                    0xDC00 + (n & 0x3FF);
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

        VirtualChar(void) {

            data = 0;
            type = TypeChar::UTF_8;
        
        }

        VirtualChar(u32& n) {

            VirtualChar();

            data = n;

            if (n < 0x80) type = TypeChar::UTF_8;
            else if (n < 0x10000) type = TypeChar::UTF_16;
            else type = TypeChar::UTF_32;
        
        }

        ~VirtualChar() {}

    };

    class String {

        private:

            typedef Ex::List<VirtualChar> xlist;
            typedef Ex::List<u8> utf8buffer;
            typedef Ex::List<u16> utf16buffer;
            typedef Ex::List<u32> utf32buffer;

            xlist buffer; 
        
        // private

        public:

            String(void) {}
            
            String(const char*) {}

            String(std::string) {}

            ~String() {}

            void push(u32& data) {

                VirtualChar virtchar(data);
                // LOG(sizeof(virtchar))
                buffer.push(virtchar);
            }

            auto& utf8encode(void) {

                utf8buffer& ulist = *(new utf8buffer);
                VirtualChar virtchar;
                CodeCVT::UTF8 cvt;
                TypeChar utf8 = UTF_8;

                u8 v;
                u32 n;

                for (u64 i = 0; i < buffer.size(); i++) {


                    virtchar = buffer[i];

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


                    virtchar = buffer[i];

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

                utf32buffer& ulist = *(new utf32buffer);
                VirtualChar virtchar;
                // CodeCVT::UTF32 cvt;
                // TypeChar utf8 = UTF_8;
                // TypeChar utf16 = UTF_16;
                // TypeChar utf32 = UTF_32;

                for (u64 i = 0; i < buffer.size(); i++) {


                    virtchar = buffer[i];

                    // if (virtchar.type == utf8 || virtchar.type == utf16 || virtchar.type == utf32) ulist.push(virtchar.data);
                    // else ulist.push(cvt.fromCodePoint(virtchar.data));
                    ulist.push(virtchar.data); // always 32
                }

                return ulist;
            }

        // public
    };


}
#endif

#endif
