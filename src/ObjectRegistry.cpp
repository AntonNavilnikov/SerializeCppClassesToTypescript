#include "ObjectRegistry.h"

#include <algorithm>

static std::string snakeToCamel(const std::string& snake);

ClassDescriptor* ObjectRegistry::append(const std::string& cls_name) {
    auto found_desc = std::find_if(descriptors.begin(), descriptors.end(), [cls_name](auto desc) {
        return desc->name == cls_name;
    });
    if (found_desc != descriptors.end())
        return *found_desc;
    descriptors.push_back(new ClassDescriptor(cls_name));
    return descriptors.back();
};

std::string ObjectRegistry::render() {
    if (descriptors.empty())
        return "";
    std::string output;
    renderClass(descriptors[0], output);
    for (int i = 1; i < descriptors.size(); ++i) {
        output += "\n\n";
        renderClass(descriptors[i], output);
    }
    return output;
};

void ObjectRegistry::renderClass(const ClassDescriptor* const class_decs, std::string& output) {
    output += "class " + class_decs->name + " {\n";
    if (!class_decs->properties.empty()) {
        for (auto& class_property : class_decs->properties) {
            output += "    " +
                snakeToCamel(class_property.key) +
                (class_property.optional ? "?" : "") +": "+
                class_property.type + ";\n";
        }
    }
    output += "};";
}

static std::string snakeToCamel(const std::string& snake) {
    std::string camel;
    bool make_uppercase = false;
    for (auto& symbol : snake) {
        if (symbol == '_') {
            make_uppercase = true;
            continue;
        }
        if (make_uppercase)
            camel += toupper(symbol);
        else
            camel += symbol;
        make_uppercase = false;
    }
    return camel;
}
