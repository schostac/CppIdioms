#include <iostream>
#include <type_traits>

/*
 * Curiously recurring template pattern (CRTP) or static polymorphism.
 * Class X derives from a class template instantiation using itself as 
 * template argument. It achieves a similar effect to the use 
 * of virtual functions, without the cost of dynamic polymorphism. 
 * It's faster than dynamic polymorphism (provided inlining isn't disabled)
 */

template<typename SpecificWeapon>
class Weapon {
public:
    void shoot() { implementation().shoot(); }
private:
    SpecificWeapon& implementation() {
        static_assert(std::is_base_of<Weapon, SpecificWeapon>::value);
        return *static_cast<SpecificWeapon*>(this);
    }
};

class M16 : public Weapon<M16> {
public:
    void shoot() { std::cout << "M16" << std::endl; }
};

class AK47 : public Weapon<AK47> {
public:
    void shoot() { std::cout << "AK-47" << std::endl; }
};

template<typename SpecificWeapon>
void run(Weapon<SpecificWeapon> & weapon) {
    weapon.shoot();
}

int main()
{
    M16 m16;
    run(m16);

    AK47 ak47;
    run(ak47);

    return 0;
}
