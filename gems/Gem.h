#pragma once
#include "Enums.h"

class Gem {
public:
    Gem();
    Gem(GemColor color);

    GemColor getColor() const { return m_color; }
    void setColor(GemColor color) { m_color = color; }

    BonusType getBonus() const { return m_bonus; }
    void setBonus(BonusType bonus) { m_bonus = bonus; }

    bool isEmpty() const { return m_color == GemColor::Empty; }
    void clear();

private:
    GemColor m_color;
    BonusType m_bonus;
};
