// sorting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 2/17/2020
//////////////////////////////////
// Modified by Lucas Miller
// 2/28/2021

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

int main(){
   srand(time(nullptr));
   multimap<Variety, string> Fruit;
   int numOfFruits = rand()%100+1;
   for(int i = 0; i <= numOfFruits; ++i)
      Fruit.emplace((static_cast<Variety>(rand() % 3)), colors[rand()%3]);
   
   cout << "Colors of the oranges: ";
   for(auto i = Fruit.lower_bound(Variety::orange); i != Fruit.upper_bound(Variety::orange); ++i)
      cout << i->second << ", ";
   cout << endl;
}

