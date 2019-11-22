//
// Created by huc3 on 11/13/2019.
//

#ifndef LAB11_SUPERHERO_H
#define LAB11_SUPERHERO_H

#include <string>
#include <iostream>
using namespace std;
class Superhero {
public:
    Superhero(string heroName, string identity, string power): hero_name(heroName), identity_(identity), power_(power), corrupted(false){};
    string getName() const{
        return hero_name;
    }
    string getPower() const{
        return power_;
    }
    bool operator==(string id){
        return identity_==id;
    }
    bool operator!=(string id){
        return identity_!=id;
    }
    bool operator>(const Superhero& sh){
        if (power_ == "Fire" && sh.power_ == "Wood"){
            return true;
        } else if (power_ == "Wood" && sh.power_ == "Water"){
            return true;
        } else if (power_ == "Water" && sh.power_ == "Fire"){
            return true;
        } else if (power_ == "Speed" && sh.power_ == "Laser"){
            return true;
        } else{
            return false;
        }
    }
    void operator-(){
        if (!corrupted)
            corrupted = true;
        else
            corrupted = false;
    }
    bool isGood(){
        return !corrupted;
    }
    friend ostream&operator<<(ostream& str, const Superhero& sh);
    friend class Team;
private:
    string hero_name;
    string identity_;
    string power_;
    bool corrupted;
};

#endif //LAB11_SUPERHERO_H
