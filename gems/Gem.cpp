#include "Gem.h"
#include <memory>

BaseGem::BaseGem(GemColor color) : m_color(color) {}

std::unique_ptr<Gem> GemFactory::createGem(GemColor color, BonusType bonus) {
    switch (bonus) {
    case BonusType::Recolor:
        return std::make_unique<RecolorGem>(color);
    case BonusType::Bomb:
        return std::make_unique<BombGem>(color);
    default:
        return std::make_unique<NormalGem>(color);
    }
}
