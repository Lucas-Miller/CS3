// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018
//
// Modified by Lucas Miller
// 2/23/2021

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::map;
using std::pair;

class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;

   string getName() const {return firstName_ + ' ' + lastName_;};

   void addCourse(string course_name){ classes_.push_back(course_name);}
   
  void print() const {
     cout << firstName_ + ' ' + lastName_ << " ";
     for(auto& className : classes_)
         cout << className << ' ';
      cout << endl;
  }

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
   list<string> classes_;
};

// reading a list from a fileName
void readRoster(map<Student, list<string>>& , string fileName);  
// printing a list out
void printRoster(const map<Student, list<string>>&); 

int main(int argc, char* argv[]){
   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // map of courses of students
   map<Student, list<string>> students; 
   for(int i = 1; i < argc; ++i){
      readRoster(students, argv[i]);  
      cout << "Read: " << argv[i] << endl;  
   }
   printRoster(students);

   return 0;
}

void readRoster(map<Student, list<string>>& roster , string fileName){
   ifstream course(fileName);
   string first, last, courseName = fileName.substr(0, fileName.size() - 4);
   
   while(course >> first >> last) {
      auto it = roster.find(Student(first, last));
      if(it == roster.end()) 
         roster.insert(pair<Student, list<string>> (Student(first, last), list<string>({courseName})));
      else 
         (it->second).push_back(courseName);
   }
   course.close();  
   
}

// printing a list out
void printRoster(const map<Student, list<string>>& roster){
   for(auto it = roster.cbegin(); it != roster.cend(); ++it) {
      cout << (it->first).getName() << " ";
      for(string course : it->second) 
         cout << course << " ";

      cout << endl;
   }
}

