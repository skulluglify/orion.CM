#include<iostream>
#include"include/orion/core.h"

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    typedef Ex::Dict<std::string> Dict;

    Dict obj;

    LOG((obj["name"]))

    obj["name"] = "ahmad asy syafiq";

    LOG((obj["name"]))

    obj["name"] = "udin";

    LOG((obj["name"]))

    obj["age"] = "19";

    LOG((obj["name"]))
    LOG((obj["age"]))

    LOG((obj["name"]))
    LOG((obj["age"]))

    obj.set("pet", "cat");
    obj.set("pet", "dog");
    LOG(obj.getitem("pet"))
    obj.setitem("pet", "furry");

    auto& keys = obj.keys();

    for (u64 i = 0; i < keys.size(); i++) {

        LOG((keys[i]) << " = " << obj[keys[i]])
    }

    LOG((obj.find("name")))
    LOG((obj.find("address")))
    LOG((obj.find("address")))

    return 0;
}
