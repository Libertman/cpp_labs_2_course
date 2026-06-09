#pragma once
#include "Enums.h"
#include <memory>

class Gem {
public:
    virtual ~Gem() = default;

    virtual GemColor getColor() const = 0;
    virtual void setColor(GemColor color) = 0;
    virtual BonusType getBonusType() const = 0;

    virtual bool isEmpty() const { return getColor() == GemColor::Empty; }
};

class BaseGem : public Gem {
    protected:
        GemColor m_color;
    public:
        BaseGem(GemColor color);
        GemColor getColor() const override { return m_color; }
        void setColor(GemColor color) override { m_color = color; }
};

class NormalGem : public BaseGem {
    public:
        using BaseGem::BaseGem;
        BonusType getBonusType() const override { return BonusType::None; }
};

class RecolorGem : public BaseGem {
    public:
        using BaseGem::BaseGem;
        BonusType getBonusType() const override { return BonusType::Recolor; }
};

class BombGem : public BaseGem {
    public:
        using BaseGem::BaseGem;
        BonusType getBonusType() const override { return BonusType::Bomb; }
};

class GemFactory {
    public:
        static std::unique_ptr<Gem> createGem(GemColor color, BonusType bonus = BonusType::None);
    };