#pragma once

#include <string>
#include <vector>

struct ClassDescriptorProperty {
    ClassDescriptorProperty(const std::string& _key, const std::string& _type, bool _optional)
        : key(_key), type(_type), optional(_optional) {}

    std::string key;
    std::string type;
    bool optional = false;
};

struct ClassDescriptor {
    explicit ClassDescriptor(const std::string& cls_name) :name(cls_name) {}

    std::string name;
    std::vector<ClassDescriptorProperty> properties;
};