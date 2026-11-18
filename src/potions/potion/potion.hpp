#pragma once

class Actor;  // declaração antecipada: só usamos referência

class Potion {
public:
    virtual ~Potion() = default;
    virtual bool canApply(const Actor &target) const = 0;  // a regra de uso é de CADA poção
    virtual void apply(Actor &target) const = 0;
};