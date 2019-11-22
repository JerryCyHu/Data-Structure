#include <cassert>
#include "superhero.h"
#include "team.h"
using namespace std;
bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0) 
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->identity_;
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

void Team::operator-=(const Superhero &a) {
    for (list<Superhero>::iterator i = superheroes.begin(); i != superheroes.end() ; ++i) {
        if(i->getName()==a.getName()){
            i = superheroes.erase(i);
        }
    }
}

void Team::operator+=(const Superhero &a) {
    bool add = true;
    for (list<Superhero>::iterator i = superheroes.begin(); i != superheroes.end() ; ++i) {
        if(i->getName()==a.getName()){
            add = false;
        }
    }
    if (add){
        superheroes.push_back(a);
    }
}

Team operator+(const Team &a, const Team &b){
    Team t;
    for (list<Superhero>::const_iterator i = a.superheroes.begin(); i != a.superheroes.end() ; ++i) {
        t.superheroes.push_back(*i);
    }
    for (list<Superhero>::const_iterator i = b.superheroes.begin(); i != b.superheroes.end() ; ++i) {
        bool add = true;
        for (list<Superhero>::const_iterator ii = a.superheroes.begin(); ii != a.superheroes.end() ; ++ii) {
            if (i->getName()==ii->getName()){
                add = false;
            }
        }
        if (add){
            t.superheroes.push_back(*i);
        }
    }
    return t;
}

Team operator+(const Team &a, const Superhero &b){
    Team t;
    for (list<Superhero>::const_iterator i = a.superheroes.begin(); i != a.superheroes.end() ; ++i) {
        t.superheroes.push_back(*i);
    }
    t.superheroes.push_back(b);
    return t;
}

Team operator+(const Superhero &a, const Superhero &b){
    Team t;
    t+=a;
    t+=b;
    return t;
}