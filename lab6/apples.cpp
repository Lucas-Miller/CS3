// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 10/03/2018


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



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
   for(int i=0; i < crate.size(); ++i)
      crate[i].weight += toGrow;

   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   
   for(auto it=crate.begin(); it != crate.end(); )
      if(it->weight < minAccept)
	 it = crate.erase(it);
      else
	 ++it;
	 
   cout << "removed " << size - crate.size() << " elements" << endl;


   // bubble sort, replace with sort()
   bool swapped;
   do{
      swapped = false;
      for(int i=0; i < crate.size()-1; ++i)
	 if(crate[i].weight > crate[i+1].weight){
	    std::swap(crate[i], crate[i+1]);
	    swapped = true;
	 }
   }while(swapped);


   // moving all red apples from crate to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Apples> peck;
   for(auto it=crate.begin(); it != crate.end();)
      if(it->color == "red"){
	 peck.push_front(std::move(*it));
	 it=crate.erase(it);
      }else
	 ++it;

   // for_each() possibly
   cout << "apples in the create"<< endl;
   for(const auto &e: crate) {
      e.print(); 
   }

   cout << endl;

   // for_each() possibly
   cout << "apples in the peck"<< endl;
   for(const auto &e: peck) {
      e.print();
   } 


   // prints every "space" apple in the peck
   // 
   const int space=3; 
   cout << "\nevery " << space << "\'d apple in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
   auto it=peck.cbegin(); int i = 0;   
   while(it != peck.cend()){
      if(i == space){
	 it->print();
	 i=0;
      }
      ++i; 
      ++it;
   }


   // putting all small green apples in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0; 
   for(auto it=crate.begin(); it != crate.end();)
      if(it->weight < weightToJam){
	 jamWeight += it->weight;
	 it=crate.erase(it);
      }else
	 ++it;

   cout << "Weight of jam is: " << jamWeight << endl;

}

