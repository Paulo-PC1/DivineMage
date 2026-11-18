#pragma once
#include "potions/potion/potion.hpp"

class HealthPotion : public Potion {
public:
    explicit HealthPotion(int healAmount = 30);

    bool canApply(const Actor &target) const override;  // só se a vida não estiver cheia
    void apply(Actor &target) const override;           // target.heal(_healAmount)

private:
    int _healAmount;
};