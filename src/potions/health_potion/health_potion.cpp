// DivineMage - Shooter/src/potions/health_potion/health_potion.cpp
#include "potions/health_potion/health_potion.hpp" // Inclui o cabeçalho da classe HealthPotion
#include "entities/actor/actor.hpp" // Precisa da definição COMPLETA de Actor (o potion.hpp só tem a declaração antecipada)

// Construtor: guarda quanto a poção cura
HealthPotion::HealthPotion(int healAmount) :
    _healAmount(healAmount)
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// A regra desta poção: só pode ser usada se a vida NÃO estiver cheia
bool HealthPotion::canApply(const Actor &target) const
{
    return target.getHealth() < target.getMaxHealth();
}

// O efeito desta poção: cura (o Actor::heal já garante que a vida não passa do máximo)
void HealthPotion::apply(Actor &target) const
{
    target.heal(_healAmount);
}
