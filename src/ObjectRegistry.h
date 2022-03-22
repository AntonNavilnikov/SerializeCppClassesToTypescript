#pragma once

#include "ClassDescriptor.h"
#include <vector>

class ObjectRegistry {
private:
    ObjectRegistry() {};
    ~ObjectRegistry() {
        for (auto desc : descriptors)
            delete desc;
    };
    std::vector<ClassDescriptor*> descriptors;

public:
    static ObjectRegistry &instance() {
        static ObjectRegistry _instance;
        return _instance;
    }
    
    ClassDescriptor* append(const std::string& cls_name);
    std::string render();

private:
    void renderClass(const ClassDescriptor* const class_decs, std::string& output);
};
