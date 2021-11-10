#pragma once
#ifndef __ORION_UTILITIES__
#define __ORION_UTILITIES__

#include<iostream>
#include<math.h>

#include"dtype.h"

#ifdef __cplusplus

extern "C++" {

    class Ye {

        private:

            // int to hex
            static char i2h(int n) {

                if (0 <= n && n < 10) return (char)(48 + n);
                // else if (9 < n && n < 16) return (char)(97 + n - 10);
                else if (9 < n && n < 16) return (char)(87 + n);
                return (char)(48);
            }

            // char hex to int
            static int h2i(char c) {

                int n = (int)(c);
                if (48 <= n && n < 58) return n - 48;
                // else if (97 <= n && n < 103) return n - 97 + 10;
                else if (97 <= n && n < 103) return n - 87;
                return 0;
            }

            // 0 - 9 a - z A - Z
             
            // int to alpha
            static char i2a(int n) {

                // 0 - 9
                if (0 <= n && n < 10) return (char)(48 + n);
                // else if (10 <= n && n < 36) return (char)(97 + n - 10);
                else if (10 <= n && n < 36) return (char)(87 + n);
                // else if (36 <= n && n < 62) return (char)(65 + n - 36);
                else if (36 <= n && n < 62) return (char)(29 + n);
                // special character
                else if (62 <= n && n < 64) {
                    if (n == 62) return (char)(43);
                    if (n == 63) return (char)(47);
                }
                return (char)(48);
            }

            // alpha to int
            static int a2i(char c) {

                int n = (int)(c);
                // 0 - 9
                if (48 <= n && n < 58) return n - 48;
                // else if (97 <= n && n < 123) return n - 97 + 10;
                else if (97 <= n && n < 123) return n - 87;
                // else if (65 <= n && n < 91) return n - 65 + 36;
                else if (65 <= n && n < 91) return n - 29;
                // special character
                else if (n == 43) return 62;
                else if (n == 47) return 63;
                return 0;
            }

            // A - Z a - z 0 - 9

            // int to base64
            static char i2b(int n) {

                if (0 <= n && n < 26) return i2a(36 + n);
                // else if (26 <= n && n < 52) return i2a(n - 26 + 10);
                else if (26 <= n && n < 52) return i2a(n - 16);
                else if (52 <= n && n < 62) return i2a(n - 52);
                else if (62 <= n && n < 64) return i2a(n);
                return i2a(36);
            }

            // base64 to int
            static int b2i(char c) {

                int n = (int)(c);
                // if (48 <= n && n < 58) return n - 48 + 52;
                if (48 <= n && n < 58) return 4 + n;
                // else if (97 <= n && n < 123) return n - 97 + 26;
                else if (97 <= n && n < 123) return n - 71;
                else if (65 <= n && n < 91) return n - 65;
                else if (n == 43) return 62;
                else if (n == 47) return 63;
                return 0;
            }

        public:

            template<int N>
            static ui8* int2str(ui64 n) {

                ui8* chars = (ui8*)malloc(N * sizeof(ui8));

                for (int i = 0; i < N; i++) {

                    chars[N -1 -i] = (n >> i * 8) & 255;
                }

                return chars;
            }

            template<int N>
            static ui8* int2hex(ui64 n) {

                ui8* chars = (ui8*)malloc(N * 2 * sizeof(ui8));

                for (int i = 0; i < N; i++) {

                    ui8 x = (n >> i * 8) & 255;
                    int r = N -1 -i;

                    chars[r * 2] = i2h((x >> 4) & 15);
                    chars[r * 2 + 1] = i2h(x & 15);

                }

                return chars;
            }

            template<int N>
            static ui64 str2int(ui8* chars) {

                ui64 n = 0;

                for (int i = 0; i < N; i++) {

                    n += (int)(chars[i]) * pow(256, N -1 -i);
                }

                return n;
            }

            template<int N>
            static ui64 hex2int(ui8* chars) {

                ui64 n = 0;

                for (int i = 0; i < N; i++) {

                    int r = N -1 -i;
                    n += ((h2i(chars[r * 2]) * 16) + h2i(chars[r * 2 + 1])) * pow(256, i);
                }

                return n;
            }

            template<int N>
            static void printStr2Int(ui8* chars) {

                for (int i = 0; i < N; i++) {

                    std::cout << (int)(chars[i]);

                    if (i < 5) std::cout << " ";

                }

                std::cout << std::endl;
            }

            template<int N>
            static ui8* str2hex(ui8* chars) {

                ui8* chexs = (ui8*)malloc((N * 2) * sizeof(ui8));

                for (int i = 0; i < N; i++) {
                    
                    int n = (int)(chars[i]);

                    chexs[i * 2] = i2h((n >> 4) & 15);
                    chexs[i * 2 + 1] = i2h(n & 15);
                }

                return chexs;
            }

            template<int N>
            static ui8* hex2str(ui8* chexs) {

                ui8* chars = (ui8*)malloc(N * sizeof(ui8));

                for (int i = 0; i < N; i++) {

                    int r = N -1 -i;
                    chars[r] = (char)(h2i(chexs[r * 2]) * 16 + h2i(chexs[r * 2 + 1]));

                }

                return chars;
            }

            template<typename T>
            static T* castInt(ui64 n) {

                T* p;
                void* a = (void*)(n);
                p = (T*)(a);

                return p;
            }
    };

}

#endif
#endif
