#pragma once
#ifndef ORION_OBJECT_H
#define ORION_OBJECT_H

#include<string>

#include"dtype.h"
#include"debug.h"
#include"array.h"

#ifdef __cplusplus
extern "C++" {

    // pass
    namespace Ex {

        template<typename T>
        class Dict {

            private:

                struct Item {

                    std::string key = "";
                    T& value = *(new T);

                    Item(void) {

                        // re initialized
                        key = "";
                        value = *(new T);
                    }
                    ~Item() {}
                };

                typedef Se::List<Item*> ListItem;
                typedef Se::List<const char*> ListKey;

                ListItem& _Dict_data_items = *(new ListItem);

            public:

                Dict(void) {

                    // re initialized
                    _Dict_data_items = *(new ListItem);
                }

                ~Dict() {}

                void setitem(const char* key, const T& value) {

                    Item* item = nullptr;

                    for (u64 i = 0; i < _Dict_data_items.size(); i++) {

                        item = _Dict_data_items[i];
                        if (item->key == key) {
                            item->value = value;
                            break;
                        }
                    }

                    // if not found? goto garbage
                }

                T& getitem(const char* key) {

                    Item* item = nullptr;
                    
                    bool finding;

                    finding = false;

                    for (u64 i = 0; i < _Dict_data_items.size(); i++) {

                        item = _Dict_data_items[i];
                        if (item->key == key) {
                            finding = true;
                            break;
                        }
                    }

                    if (!finding) return (new Item)->value; // garbage

                    return item->value;
                }
                
                T& operator[] (const char* key) {
                    
                    Item* item = nullptr;

                    bool finding;

                    finding = false;

                    for (u64 i = 0; i < _Dict_data_items.size(); i++) {

                        item = _Dict_data_items[i];
                        if (item->key == key) {
                            finding = true;
                            break;
                        }
                    }

                    if (!finding) {
                    
                        item = new Item;
                        item->key = key;
                        _Dict_data_items.push(item);
                    }

                    return item->value;

                }

                bool find(const char* key) {

                    Item* item;

                    item = new Item;

                    for (u64 i = 0; i < _Dict_data_items.size(); i++) {

                        item = _Dict_data_items[i];
                        if (item->key == key) return true;
                    }

                    return false;
                }

                auto& keys(void) {

                    Item* item = nullptr;
                    ListKey& listkeys = *(new ListKey);

                    for (u64 i = 0; i < _Dict_data_items.size(); i++) {

                        item = _Dict_data_items[i];
                        listkeys.push(item->key.c_str());
                    }

                    return listkeys;
                }
            
            // public
        };
    };

}
#endif

#endif
