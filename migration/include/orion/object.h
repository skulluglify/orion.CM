#pragma once
#ifndef ORION_OBJECT_H
#define ORION_OBJECT_H

#include<string>

#include"dtype.h"
#include"debug.h"
#include"array.h"

#ifdef __cplusplus
extern "C++" {

    namespace Ex {

        template<typename T>
        class Dict {

            private:

                struct Item {

                    std::string key = "";
                    T& value = *(new T);

                    struct Item* next;

                    Item(void) {

                        // re-initialized
                        key = "";
                        value = *(new T);
                    }
                    ~Item() {}
                };

                typedef Ex::List<const char*> ListKey;

                Item* first; // like head
                Item* last; // like tail
            
            // private

            public:

                Dict(void) {

                    // re-initialized
                    first = nullptr;
                    last = nullptr;
                }

                ~Dict() {}

                void set(const char* key, const T& value) { // unique

                    Item* item;
                    item = new Item;
                    item->key = key;
                    item->value = value;

                    if (!find(key)) {

                        if (first == nullptr) {

                            first = item;
                            last = item;

                        } else {

                            last->next = item;
                            last = item;

                        }
                    }
                }

                void setitem(const char* key, const T& value) {

                    Item* item = nullptr;

                    item = first;

                    while (item != nullptr) {

                        if (item->key == key) item->value = value;
                        item = item->next;
                    }
                }

                T& getitem(const char* key) {

                    Item* item = nullptr;
                    
                    bool finding;

                    finding = false;

                    item = first;

                    while (item != nullptr) {

                        if (item->key == key) {
                            finding = true;
                            break;
                        }
                        item = item->next;
                    }

                    if (!finding) return (new Item)->value; // garbage

                    return item->value;
                }
                
                T& operator[] (const char* key) { // set auto
                    
                    Item* item = nullptr;

                    bool finding;

                    item = first;
                    finding = false;

                    if (item == nullptr) {

                        item = new Item;
                        item->key = key;
                        first = item;
                        last = item;
                        
                    } else {

                        while (item != nullptr) {

                            if (item->key == key) {
                                finding = true;
                                break;
                            }
                            item = item->next;
                        }

                        if (!finding) {
                        
                            item = new Item;
                            item->key = key;
                            last->next = item;
                            last = item;
                        }
                    }

                    return item->value;
                }

                bool find(const char* key) {

                    Item* item;

                    item = new Item;

                    item = first;

                    while (item != nullptr) {

                        if (item->key == key) return true;
                        item = item->next;
                    }

                    return false;
                }

                auto& keys(void) {

                    Item* item = nullptr;
                    ListKey& list = *(new ListKey);

                    item = first;

                    while (item != nullptr) {

                        list.push(item->key.c_str());
                        item = item->next;
                    }

                    return list;
                }
            
            // public
        };
    };

}
#endif

#endif
