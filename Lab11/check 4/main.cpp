#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
typedef std::set<std::pair<std::string,std::string> > set_of_word_pairs;
bool common(const std::string &a, const std::string &b) {
for (int i = 0; i < a.size(); i++)
for (int j = 0; j < b.size(); j++)
if (a[i] == b[j]) return true;
return false;
}

void common(set_of_word_pairs &answer, const std::vector<std::string>& words, int a, int b) {
pair<string, string> wp;
if(a==words.size()-1){
    return;
}
if(common(words[a], words[b])){
    answer.insert(make_pair(words[a], words[b]));
}
if(b==words.size()-1){
    common(answer, words, a+1,a+2);
} else{
    common(answer, words, a,b+1);
}

}

void common(set_of_word_pairs &answer, const std::vector<std::string>& words, int a) {
common(answer, words,a,a+1);
}

set_of_word_pairs common(const std::vector<std::string>& words) {
set_of_word_pairs swp;
common(swp,words,0);
    return swp;
}

int main() {
    vector<string> w
    return 0;
}