/* Author:       Nicholas Stafford
                   - based on code from Mikhail Nesterenko 3/11/2014
   Program:    roster.cpp
   Class:      cs44001
   Due Date:   2/15/18
   
   Description: Displays a list of students and the classes they are enrolled in.
   the same student will be in multiple classes
   assume all students have different names
   
   Arguments: Takes files as arguments when executable is called
                 each input file name is the name of the class (.txt extension permitted)
		 each input file contains student names ordered like so:
		 firstname1 lastname1
		 firstname2 lastname2
		 firstname3 lastname3
		 ...
		 
		 Does NOT take dropouts.txt. dropout is not implemented. 
*/

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

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);
// printing a list out
void printStudents(const list<list<string>>& studentEntries_);

int main(int argc, char* argv[]) {
  
  if (argc <= 1) {
    cout << "usage: " << argv[0]
	 << " list of courses" << endl; exit(1);
  }
  
  /*	studentEntries is a list of lists of strings
          the lists contain the students information in the following order
	    linked list's 1st element should be students name
	    linked list's 2nd element should be the students last name
	    linked list's 3rd, 4th... elements should be the courses student is enrolled in
  */
  list<list<string>> studentEntries;
  
  // search through each class file for students
  for (int i = 1; i < argc; ++i) { // start at one to avoid argv[0] 
    
    // create a roster of all students in the class
    list<string> classRoster;
    readRoster(classRoster, argv[i]);
    
    string className = argv[i];
    
		// if classname file ends in ".txt" remove this from the class name
    if (className.substr(className.size() - 4) == ".txt")
      className.erase(className.size() - 4); // erase last 4 characters. 
    
    // for each student in the class
    for (const string studentName_ : classRoster) {
      //check if studentEntries contains that student
      
      bool studentAdded = false;
      // find out if student already exists
      for (list<string> &existingStudent : studentEntries) {
	if (studentName_ == *existingStudent.begin()) {
	  existingStudent.push_back(className);
	  studentAdded = true;
	  break;
	}
			}
      // if student is not already in studentEntries add new list
      if (studentAdded == false) {
	list<string> studentList;
	studentList.push_front(studentName_); // add studentName to studentList
	studentList.push_back(className); // removed move
	studentEntries.push_back(move(studentList)); // possible change to move
      }
    }
  }
  // uncomment if you want alphabetically, comment out if you want by className (approximatly)
  studentEntries.sort(); 
  
  printStudents(studentEntries);
  cout << endl;
}

void readRoster(list<string>& roster, string fileName) {
  //   ifstream course(fileName.c_str());
  ifstream course(fileName); // I am trying it
  
  string first, last;
  while (course >> first >> last)
    // add new string to list
    roster.push_back(first + ' ' + last);
  course.close();
}

// printing a list of lists out
void printStudents(const list<list<string>>& studentEntries_) {
  // for neatness create a spacer so classes start at the same location
  size_t mostDigits = 0;
  for (list<string> sl : studentEntries_) {
    for (string str : sl)
      if (str.size() > mostDigits) 
	mostDigits = str.size();
  }
  
  cout << "first name, last name:  courses " << endl;
  for (list<string> sl : studentEntries_) {
    auto it = sl.begin();
    string studentName_ = *it;
    string spaceString(mostDigits - studentName_.size(), ' ');
    cout << studentName_ + ": " << spaceString;
    
    ++it;
    for (it; it != sl.end();) { // for the rest of the strings in sl (the classes)
      cout << *it << " ";
      ++it;
    }
    cout << endl;
  }
}
