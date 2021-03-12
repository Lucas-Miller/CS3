// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 10/03/2018
//////////////////////////////////
// Modified by Lucas Miller
// 2/28/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};

bool less_than(const Apples& a, const double& maxWeight){ return a.weight < maxWeight;};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
   std::generate(crate.begin(), crate.end(), [=]() {
      Apples a; 
		a.weight = minWeight + static_cast<double>(rand()) / RAND_MAX*(maxWeight - minWeight);
		a.color = rand() % 2 == 1 ? "green" : "red"; 
		return a;});

 
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   int cnt = std::count_if(crate.cbegin(), crate.cend(), [toFind](Apples a) {return a.weight > toFind;});


   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find_if()
   cout << "at positions ";
   auto itr = std::find_if(crate.cbegin(), crate.cend(), [toFind](Apples a) {return a.weight > toFind;});
   while(itr != crate.cend()) {
      cout << itr - crate.cbegin() << ", ";
      itr = std::find_if((itr + 1), crate.cend(), [toFind](Apples a) {return a.weight > toFind;});
   }
   cout << endl;

   // max_element()
   itr = std::max_element(crate.cbegin(), crate.cend(), [](Apples a, Apples b) {return a.weight > b.weight;});
   cout << "Heaviest apple weighs: " << itr->weight << " oz" << endl;



   // for_each() or accumulate()
   double sum;
   std::for_each(crate.cbegin(), crate.cend(), [&sum](Apples a) {sum += a.weight;});
   cout << "Total apple weight is: " << sum << " oz" << endl;

   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   std::transform(crate.begin(),crate.end(), crate.begin(), [toGrow](Apples a){Apples temp; 
                                                                                 temp.color = a.color;
                                                                                 temp.weight = a.weight + toGrow;
                                                                                 return temp;
                                                                                 });

   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   crate.erase(std::remove_if(crate.begin(), crate.end(), [minAccept](Apples &a){return a.weight < minAccept;}), crate.end());


   // bubble sort, replace with sort()
   std::sort(crate.begin(), crate.end(), [](Apples a, Apples b){return a.weight < b.weight;});

   // moving all red apples from crate to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Apples> peck;
   std::remove_copy_if(crate.begin(), crate.end(), std::back_inserter(peck), [](Apples &a){return a.color != "red";});

   auto toRemove = std::remove_if(crate.begin(), crate.end(), [](Apples &a){return a.color == "red";});
   crate.erase(toRemove, crate.end());

   // for_each() possibly
   cout << "apples in the create"<< endl;
   std::for_each(crate.begin(), crate.end(), [](Apples a){if(a.color != "")a.print();});
   cout << endl;

   // for_each() possibly
   cout << "apples in the peck"<< endl;
   std::for_each(peck.begin(), peck.end(), [](Apples a){if(a.color != "")a.print();});


   // prints every "space" apple in the peck
   // 
   const int space=3; 
   cout << "\nevery " << space << "\'d apple in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
   int i = 1;
   auto deqitr = peck.begin();
   while(deqitr != peck.end()){
      if(deqitr->color != "" && i%3 == 0)deqitr->print();
      std::advance(deqitr, 1);
      ++i;
   }

   class Jam {
      private:
         double jam_weight = 0;
      public:
         Jam(){};
         void operator()(vector<Apples> jamCrate, double max_weight) {
            for(auto &itr : jamCrate) {
               if(itr.weight < max_weight)
                  jam_weight += itr.weight;
            }
         }

         double get_weight() {return jam_weight;};
   };

   // putting all small green apples in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0; 

   using namespace std::placeholders; 
   auto binder = std::bind(less_than, _1, weightToJam);

   int appleCount = 0;
   auto iterator = crate.begin();
   while (std::count_if(crate.begin(), crate.end(), binder) != appleCount)
       if (iterator->weight < weightToJam) {
         jamWeight += iterator->weight;
	      ++appleCount;
	   }

   auto removeIt = std::remove_if(crate.begin(), crate.end(), binder);
   crate.erase(removeIt, crate.end());

   cout << "Weight of jam is: " << jamWeight << endl;
}