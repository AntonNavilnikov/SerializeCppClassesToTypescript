#ifndef order_hpp
#define order_hpp

#include <optional>
#include <string>
#include <variant>

namespace ClassesToSerialize {

struct MarketPolicy {};

struct LimitPolicy {
    double price;
    std::optional<double> stop;
};

typedef std::variant<MarketPolicy, LimitPolicy> PolicyVariant;

struct Order {
    std::string symbol;
    double quantity;
    bool is_buy;
    PolicyVariant policy;
};

}; // namespace ClassesToSerialize

#endif