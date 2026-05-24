#include "Gem.h"

Gem::Gem() : m_color(GemColor::Empty), m_bonus(BonusType::None) {}

Gem::Gem(GemColor color) : m_color(color), m_bonus(BonusType::None) {}

void Gem::clear() {
    m_color = GemColor::Empty;
    m_bonus = BonusType::None;
}