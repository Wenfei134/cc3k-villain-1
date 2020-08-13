#include   "Merchant.h"
#include "../Characters/Player.h"
#include "../Items/DragonGold.h"
#include "../Characters/Player.h"
#include "../Characters/Drow.h"
#include "../Characters/Goblin.h"
#include "../Characters/Vampire.h"
#include "../Characters/Shade.h"
#include "../Characters/Troll.h"
#include <cmath>

Merchant::Merchant(): Enemy(30, 70, 5, 'M'){
}

Merchant::~Merchant(){

}

bool Merchant:: isHostile(){
    return hostile;
}

void Merchant::setGold(std::shared_ptr<Gold> g){
    gold = g;
}

std::shared_ptr<Gold> Merchant::onDeath(){
    return gold;
}

bool Merchant::onAttacked(Player &p) {
    return p.attack(*this);
}

bool Merchant::attack(Shade &p){
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}


bool Merchant::attack(Vampire &p){
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}


bool Merchant::attack(Troll &p){
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}


bool Merchant::attack(Drow &p){
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}


bool Merchant::attack(Goblin &p){
    bool toAtk = this->randAtk();
    if (toAtk){
        p.onAttacked(*this);
        return true;
    } else {
        return false;
    }
}

bool Merchant::onAttacked(Goblin &p){
    bool goesThrough = this->randAtk();
    if (goesThrough){
        int damage = ceil((100/(100+ this->getDef()))* p.getAtk());
        this->setHP(this->getHp()-damage);
        return true;
    }
    return false;
}

bool Merchant::onAttacked(Drow &p){
    bool goesThrough = this->randAtk();
    if (goesThrough){
        int damage = ceil((100/(100+ this->getDef()))* p.getAtk());
        this->setHP(this->getHp()-damage);
        return true;
    }
    return false;
}

bool Merchant::onAttacked(Shade &p){
    bool goesThrough = this->randAtk();
    if (goesThrough){
        int damage = ceil((100/(100+ this->getDef()))* p.getAtk());
        this->setHP(this->getHp()-damage);
        return true;
    }
    return false;
}

bool Merchant::onAttacked(Troll &p){
    bool goesThrough = this->randAtk();
    if (goesThrough){
        int damage = ceil((100/(100+ this->getDef()))* p.getAtk());
        this->setHP(this->getHp()-damage);
        return true;
    }
    return false;
}

bool Merchant::onAttacked(Vampire &p){
    bool goesThrough = this->randAtk();
    if (goesThrough){
        int damage = ceil((100/(100+ this->getDef()))* p.getAtk());
        this->setHP(this->getHp()-damage);
        return true;
    }
    return false;
}

