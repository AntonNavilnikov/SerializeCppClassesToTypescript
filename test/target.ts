class MarketPolicy {
};

class LimitPolicy {
    price: number;
    stop?: number;
};

class Order {
    symbol: string;
    quantity: number;
    isBuy: boolean;
    policy: MarketPolicy | LimitPolicy;
};

class Balance {
    free: number;
    locked: number;
};