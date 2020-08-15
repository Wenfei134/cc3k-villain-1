#include "Dragon.h"
#include "../Items/DragonGold.h"
#include "../Characters/Player.h"
#include "../Characters/Drow.h"
#include "../Characters/Goblin.h"
#include "../Characters/Vampire.h"
#include "../Characters/Shade.h"
#include "../Characters/Troll.h"
#include <cmath>

using namespace std;

Dragon::Dragon():Enemy(150, 30, 25, 'D'){
    dG = nullptr;
}

Dragon::~Dragon(){
}

bool Dragon::onAttacked(Player &p){
    return p.attack(*this);
}

bool Dragon::attack(Drow &p) {
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}  

bool Dragon::onAttacked(Drow &p){
    return baseOnAtk(p);
}

bool Dragon::attack(Goblin &p) {
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}
bool Dragon::onAttacked(Goblin &p){
   return baseOnAtk(p);
}

bool Dragon::attack(Shade &p) {
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}
bool Dragon::onAttacked(Shade &p) {
    return baseOnAtk(p);
}
bool Dragon::attack(Troll &p) {
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}
bool Dragon::onAttacked(Troll &p) {
    return baseOnAtk(p);
}
bool Dragon::attack(Vampire &p) {
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}

bool Dragon::onAttacked(Vampire &p) {
    return baseOnAtk(p);
}


void Dragon::setGold(std::shared_ptr<DragonGold> g){
    dG = g;
}

std::shared_ptr<Gold> Dragon::getGold(){
    return dG;
}

std::shared_ptr<Gold> Dragon::onDeath(){
    dG->setCanCollect(true);
    dG->setDragon(nullptr);
    dG = nullptr;
    return nullptr;
}

