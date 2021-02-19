// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


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
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   list<Student> courseStudents; 
   for(int i = 1; i < argc; ++i){
      readRoster(courseStudents, argv[i]);  
      cout << "Read: " << argv[i] << endl;  
   }
   printRoster(courseStudents);

   return 0;

}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last, courseName = fileName.substr(0, fileName.size() - 4);
   bool foundStudent = false;
   while(course >> first >> last) {
      for(auto& student : roster)
         if(student.getName() == first + " " + last) {
		      foundStudent = true;
				student.addCourse(courseName);
			}

   		if(!foundStudent) {
			   Student new_student(first, last);
			   new_student.addCourse(courseName);
			   roster.push_back(new_student);
		   }
   }
   course.close();   
   
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      student.print();
}
