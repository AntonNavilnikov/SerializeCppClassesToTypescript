#pragma once

#include "balance.hpp"
#include "order.hpp"

#include <string>
#include <optional>
#include <variant>
#include <algorithm>

using ClassesToSerialize::Balance;
using ClassesToSerialize::LimitPolicy;
using ClassesToSerialize::MarketPolicy;
using ClassesToSerialize::Order;

struct ClassDescriptor;

template <typename T> 
class Binder {
public:
    explicit Binder(std::string cls_name) {
        class_desc = ObjectRegistry::instance().append(cls_name);
    };

    template <typename ClassName, typename Attribute>
    void set(std::string name, Attribute ClassName::* attribute) {
        std::string member_type_name = getTypeName<Attribute>();
        addProperty(name, member_type_name);
    };
    
    template <typename ClassName, typename Attribute>
    void set(std::string name, std::optional<Attribute> ClassName::* attribute) {
        std::string member_type_name = getTypeName<Attribute>();
        addProperty(name, member_type_name, true);
    }
    
    template <typename ClassName, typename... Attribute>
    void set(std::string name, std::variant<Attribute...> ClassName::* attribute) {
        std::vector<std::string> variants;
        (variants.push_back(getTypeName<Attribute>()), ...);
        if (variants.empty())
            return;
        std::string member_type_name = variants[0];
        for (int i = 1; i < variants.size(); ++i) {
            member_type_name += " | " + variants[i];
        }
        addProperty(name, member_type_name);
    }

private:
    template<typename T>
    std::string getTypeName() {
        return static_assert("UNDEFINED");
    }

    template<>
    std::string getTypeName<bool>() {
        return "boolean";
    }

    template<>
    std::string getTypeName<double>() {
        return "number";
    }

    template<>
    std::string getTypeName<std::string>() {
        return "string";
    }

    template<>
    std::string getTypeName<LimitPolicy>() {
        return "LimitPolicy";
    }

    template<>
    std::string getTypeName<MarketPolicy>() {
        return "MarketPolicy";
    }

    void addProperty(const std::string& key, const std::string& type, bool optional = false) {
        if (!class_desc)
            return;
        auto found_prop = std::find_if(class_desc->properties.begin(), class_desc->properties.end(), [key](auto prop) {
            return prop.key == key;
        });
        if (found_prop != class_desc->properties.end()) {
            found_prop->type = type;
            found_prop->optional = optional;
        }
        else {
            class_desc->properties.push_back(std::move(ClassDescriptorProperty(
                key,
                type,
                optional
            )));
        }
    }

    ClassDescriptor* class_desc;
};