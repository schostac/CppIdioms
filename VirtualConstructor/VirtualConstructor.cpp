#include <iostream>
#include <memory>
#include <stdexcept>

/*
 * Virtual constructor.
 * С++ doesn't support virtual constructor, copy and move constructors,
 * only destructor. 
 * Thus, this idiom's used to copy or create a new object wihout knowing 
 * its concrete type; in particular it's used to copy a polymorphic
 * object accessable only via interface (i.e. base pointer).
 */

class Weapon 
{
public:
    virtual ~Weapon() = default;
    virtual std::unique_ptr<Weapon> create() = 0;
    virtual std::unique_ptr<Weapon> clone() = 0;
    virtual void shoot() = 0;
};

class AK47 : public Weapon 
{
    unsigned bullets = 30;
public:
    ~AK47() = default;
    std::unique_ptr<Weapon> create() override {
        return std::make_unique<AK47>();
    }
    std::unique_ptr<Weapon> clone() override {
        return std::make_unique<AK47>(*this);
    }
    void shoot() override { 
        if(bullets) std::cout << "AK-47 shot, bullets: " << --bullets << std::endl;
    }
};

class M16 : public Weapon {
    unsigned bullets = 20;
public:
    ~M16() = default;
    std::unique_ptr<Weapon> create() override {
        return std::make_unique<M16>();
    }
    std::unique_ptr<Weapon> clone() override {
        return std::make_unique<M16>(*this);
    }
    void shoot() override {
        if(bullets) std::cout << "M16 shot, bullets: " << --bullets << std::endl; 
    }
};

class Player {
    std::unique_ptr<Weapon> _weapon;
public:
    Player(std::unique_ptr<Weapon> weapon):_weapon{std::move(weapon)} {
        if(not _weapon) throw std::runtime_error{"null weapon"};
    }
    Player(const Player& rhs):_weapon{rhs._weapon->clone()} {}
    Player(Player&&) = default;
    void shoot() { _weapon->shoot(); }
};

int main()
{
    Player player1(std::make_unique<M16>());
    player1.shoot();
    Player player2(player1);
    player1.shoot();
    player1.shoot();
    player2.shoot();
    return 0;
}
