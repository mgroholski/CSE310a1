// ASU CSE310 Spring 2022 Assignment #1
// Name: Matthew Groholski  
// ASU ID: 1218442420
// ASU Email address: mgrohols@asu.edu
// Description: Linked List

#include <iostream>
#include <iomanip>          //used to control the format of the output
#include <string>

using namespace std;

//Student represents a student information
struct Student
{
    string firstName, lastName;
    int id;
    double gpa;
    struct Student* next;
};

//class LinkedList will contains a linked list of Students. This is class definition
class LinkedList
{
    private:
        struct Student* head;

    public:
        LinkedList();
        ~LinkedList();
        bool findStudent(int studentId);
        bool addStudent(string firstName, string lastName, int studentId, double gpa);
        bool removeById(int studentId);
        bool removeByName(string firstName, string lastName);
        bool changeStudentName(int studentId, string newFullName);
        bool updateStudentGpa(int studentId, double newGpa);
        void printStudentListByLastName(string oneLastName);
        void printStudentList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = nullptr;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	int count = 0;

    while (head != nullptr) {
        count++;
        Student* current = head;
        head = head->next;
        delete current;
    }

    cout<< "The number of deleted student is: " << count <<"\n";
}

//A function to identify if the parameterized Student is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findStudent(int studentId){
	Student* current = head;

    while(current != nullptr) {
        if (current->id == studentId)
            return true;
        current = current->next;
    }

    return false;
}

//This function creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Students by their names, i.e.
//first by last name, then by first name. Note: each Student has a unique id, but
//may have the same first and last name with another Student. In case two Students have same names
//they should be inserted according to the increasing order of their IDs.
//Return true if it is successfully inserted and false in case of failures.
bool LinkedList::addStudent(string firstName, string lastName, int studentId, double gpa){
    //Checks if student with ID already exists
    if (findStudent(studentId)) {
        cout << "Duplicated student. Not added" << endl;
        return false;
    }
    
    //Creates student
    Student* newStudent = new Student();
    newStudent->firstName = firstName;
    newStudent->lastName = lastName;
    newStudent->id = studentId;
    newStudent->gpa = gpa;

    //Finds placement
    //Checks if list is empty  
    if (head == nullptr){
        head = newStudent;
        return true;
    }


    Student* current = head, *previous = current;

    while (current != nullptr) {
        if (newStudent->lastName.compare(current->lastName) < 0) {
            if (head == current) {
                head = newStudent;
                newStudent->next = current;
            } else {
                previous->next = newStudent;
                newStudent->next = current;
            }
            return true;
        } else if (newStudent->lastName.compare(current->lastName) == 0) {
            if (newStudent->firstName.compare(current->firstName) < 0) {
                if (head == current) {
                    head = newStudent;
                    newStudent->next = current;
                } else {
                    previous->next = newStudent;
                    newStudent->next = current;
                }
                return true;
            } else if (newStudent->firstName.compare(current->firstName) == 0) {
                if (newStudent->id < current->id) {
                if (head == current) {
                    head = newStudent;
                    newStudent->next = current;
                } else {
                    previous->next = newStudent;
                    newStudent->next = current;
                }
                    return true;
                }
            }
        }
        previous = current;
        current = current->next;
    }
    previous->next = newStudent;
    return true;
}

//Removes the specified student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int studentId)
 {
	Student* current = head, *previous = current;

    while (current != nullptr){
        //Checks if correct node
        if (current->id == studentId) {
            //Checks which case nodes falls into
            if (current == head) {
                head = current->next;
                delete current;
            } else {
                previous->next = current->next;
                delete current;
            }
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
 }

//Removes the given Student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Students with
//the same first and last name should be removed from the list.
bool LinkedList::removeByName(string firstName, string lastName)
{
	Student* current = head, *previous = current;
    bool removed = false;

    while (current != nullptr) {
        //Checks if matching name
        if (current->lastName.compare(lastName) == 0 && current->firstName.compare(firstName) == 0) {
            //Checks if beginning
            if (current == head) {
                head = current->next;
                delete current;
                current = head;
            } else {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
            removed = true;
            continue;
        }

        previous = current;
        current = current->next;
    }

    if (!removed)
        cout << "No such student name found." << endl;

    return removed;
}

//Modifies the data of the given Student. Return true if it modifies successfully and
//false otherwise. Note: after changing a Student name, the linked list must still be
//in correct alphabetical order.
bool LinkedList::changeStudentName(int studentId, string newFullName){
    //Checks if student exists
    if (!findStudent(studentId))
        return false;
    
    //formats string
    string name[2];
    for (int i = 0, j = 0; i < newFullName.length(); i++) {
        if (newFullName[i] == ' ') {
            j++;
            continue;
        }

        name[j] += newFullName[i];
    }

    //Finds correct student
    Student* current = head;

    while (current->id != studentId) 
        current = current->next;

    double gpa = current->gpa;

    if (!removeById(studentId))
        return false;

    if (!addStudent(name[0], name[1], studentId, gpa))
        return false;
    return true;
}

bool LinkedList::updateStudentGpa(int studentId, double newGpa)
{
    if (!findStudent(studentId)) {
        cout << "Student is NOT inside the list, cannot change gpa." << endl;
        return false;
    }

    Student* current = head;
    while (current->id != studentId)
        current = current->next;
    current->gpa = newGpa;

    return true;
}

//Prints all students in the list with the same last name.
void LinkedList::printStudentListByLastName(string oneLastName)
{
    if(head == NULL)
    {
		cout << "The list is empty\n";
		return;
	}

	Student* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->lastName.compare(oneLastName) == 0) {
            cout << left    << setw(12) << current->firstName
            << left    << setw(12) << current->lastName
            << right   << setw(8) << current->id
            << setw(10) << fixed << setprecision(2) << current->gpa << "\n";
            found = true;
        }

        current = current->next;
    }

    if (!found)
        cout << "No students with the specified last name found." << endl;

}

//Prints all students in the linked list starting from the head node.
void LinkedList::printStudentList()
{
 	if(head == NULL)
    {
		cout << "The list is empty\n";
		return;
	}

    Student* temp = head;
    while (temp!= nullptr){
        cout << left    << setw(12) << temp->firstName
        << left    << setw(12) << temp->lastName
        << right   << setw(8) << temp->id
        << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
        temp=temp->next;
    }
}