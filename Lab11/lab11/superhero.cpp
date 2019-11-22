//
// Created by huc3 on 11/13/2019.
//

#include "superhero.h"

ostream&operator<<(ostream& str, const Superhero& sh){
    if(!sh.corrupted) {
        str << "Superhero " << sh.hero_name << " has power " << sh.power_<<endl;
    }
    return str;
}