// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::list;
using std::move;
using std::string;
using std::vector;

void readRoster(list<string> &roster, string fileName);
void printRoster(const list<list<string>> &studentEntries);

int main(int argc, char *argv[]) {

   list<list<string>> studentEntries;

   for (int i = 1; i < argc; ++i) { 

      list<string> classRoster;
      readRoster(classRoster, argv[i]);

      string className = argv[i];

      if (className.substr(className.size() - 4) == ".txt")
         className.erase(className.size() - 4); 


      for (const string studentName_ : classRoster) {
         bool studentAdded = false;
         for (list<string> &existingStudent : studentEntries) {
            if (studentName_ == *existingStudent.begin()) {
               existingStudent.push_back(className);
               studentAdded = true;
               break;
            }
         }

         if (studentAdded == false) {
            list<string> studentList;
            studentList.push_front(studentName_);        
            studentList.push_back(className);            
            studentEntries.push_back(move(studentList)); 
         }
      }
   }

   studentEntries.sort();
   printRoster(studentEntries);
   cout << endl;
}

void readRoster(list<string> &roster, string fileName) {
   ifstream course(fileName); 
   string first, last;
   while (course >> first >> last)
      roster.push_back(first + ' ' + last);
   course.close();
}

void printRoster(const list<list<string>> &studentEntries) {
   size_t mostDigits = 0;
   for (list<string> s1 : studentEntries)
      for (string str : s1)
         if (str.size() > mostDigits)
            mostDigits = str.size();

   cout << "first name, last name: courses " << endl;
   for (list<string> s1 : studentEntries) {
      auto it = s1.begin();
      string studentName = *it;
      string spaceString(mostDigits - studentName.size(), ' ');
      cout << studentName + ':' << spaceString;

      ++it;
      for (it; it != s1.end();) {
         cout << *it << ' ';
         ++it;
      }
      cout << endl;
   }
}
