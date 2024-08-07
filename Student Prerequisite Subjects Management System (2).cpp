#include <bits\stdc++.h>

using namespace std;

template <typename T> struct node {
    T data;
    node<T>* next;
};

template <class T> class linkedlist {
    using Node = node<T>*;
    Node head;

public:
    linkedlist() {
        head = nullptr;
    }

    linkedlist(linkedlist<T> &l) {
        if (l.isEmpty()) {
            head = nullptr;
            return;
        }

        for (Node ptr = l.head; ptr != nullptr ; ptr = ptr->next) {
            this->insertyoumis(ptr->data);
        }
    }

    void insertyoumis(T data) {
        Node new_node = new node<T>();
        new_node->data = data;

        if (head == nullptr) {
            head = new_node;
            new_node->next = nullptr;
        } else {
            Node temp;
            temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = nullptr;
        }
    }

    void displayyomnty() {
        if (head == nullptr) {
            cout << " linked list is empty";
        } else {
            Node temp = head;
            while (temp != nullptr) {
                cout << temp->data << ' ';

                temp = temp->next;
            }
        }
    }

    Node getHead() {
        return head;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

class Course {
private:
    string Name;
    string Code;
    int MaxNumberofStudents;
    int Hours;
    linkedlist<Course> prerequired;

public:
    Course() {}
    Course(string name, string code, int maxNumofStds, int hours) {
        Name = name;
        Code = code;
        MaxNumberofStudents = maxNumofStds;
        Hours = hours;
    }

    Course(string name, string code, int maxNumofStds, int chours, linkedlist<Course> prerequiredcrs) {
        Name = name;
        Code = code;
        MaxNumberofStudents = maxNumofStds;
        Hours = chours;
        prerequired = prerequiredcrs;
    }

    string getName() {
        return Name;
    }

    string getCode() {
        return Code;
    }

    int getMaxNumberOfStudents() {
        return MaxNumberofStudents;
    }

    int getHours() {
        return Hours;
    }

    linkedlist<Course> getPrerequired() {
        return prerequired;
    }

    string details() {
        string result;
        result += "Course Name: " + Name + "\n";
        result += "Course Code: " + Code + "\n";
        result += "Course's Maximum number of students: " + to_string(MaxNumberofStudents) + "\n";
        result += "Course's Pre-required Courses: ";
        if (prerequired.isEmpty()) {
            result += "None\n";
        } else {
            for (auto ptr = prerequired.getHead(); ptr != nullptr; ptr = ptr->next) {
                result += ptr->data.Name + "-" + ptr->data.Code;
                if (ptr->next != nullptr && ptr->next->next != nullptr) {
                    result += " || ";
                }
            }
            result += "\n";
        }

        return result;
    }

    friend ostream& operator<<(ostream& out, const Course& crs) {
        out << crs.Name << "-" << crs.Code;
        return out;
    }

    Course(const Course& crs) {
        Name = crs.Name;
        Code = crs.Code;
        MaxNumberofStudents = crs.MaxNumberofStudents;
        Hours = crs.Hours;
        prerequired = crs.prerequired;
    }
};

linkedlist<Course> courses;

class Student {
private:
    string Name;
    string ID;
    string Password;
    int academic_year;
    linkedlist<Course> finished;
    linkedlist<Course> in_progress;
public:
    Student() {}

    Student(string Name, string ID, string Password, int academic, linkedlist<Course> finished = linkedlist<Course>(), linkedlist<Course> in_progress = linkedlist<Course>()) {
        this->Name = Name;
        this->ID = ID;
        this->Password = Password;
        this->academic_year = academic;
        this->finished = finished;
        this->in_progress = in_progress;
    }

    string getName() {
        return Name;
    }

    string getID() {
        return ID;
    }

    void setPassword(string newpass) {
        Password = newpass;
    }

    string getPassword() {
        return Password;
    }

    linkedlist<Course> getFinished() {
        return finished;
    }

    linkedlist<Course> getInprogress() {
        return in_progress;
    }

    void registerforCourse() {
        string crsCode;
        bool found = false;
        Course cs;
        cout << "Please enter the course code of the course you want to register: ";
        cin >> crsCode;

        for (auto ptr = courses.getHead(); ptr != nullptr; ptr = ptr->next) {
            if (ptr->data.getCode() == crsCode) {
                cs = ptr->data;
                found = true;
                break;
            }
        }

        if (found) {
            this->in_progress.insertyoumis(cs);
            cout << "Registered you to the course successfully!" << endl << endl << "Press any key to go back to main menu...";
            system("pause > 0");
        } else {
            cout << "We couldn't find the course you entered the code for...Please try again or check the available courses." << endl << endl << "Press any key to restart..";
            system("pause > 0");
            registerforCourse();
        }
    }

    void viewMyCurrentCourses() {
        cout << "Completed Courses: ";
        if (finished.isEmpty()) {
            cout << "None" << endl;
        } else {
            finished.displayyomnty();
            cout << endl;
        }

        cout << "Courses In Progress: ";
        if (in_progress.isEmpty()) {
            cout << "None" << endl;
        } else {
            in_progress.displayyomnty();
            cout << endl;
        }
    }
};

linkedlist<Student> students;
void studentPage(Student std);

vector<Course> viewAllCourses() { // student and admin
    vector<Course> result(0);

    if (courses.isEmpty()) {
        cout << "There are currently no available courses..." << endl;
    } else {
        cout << "Available courses: ";
        for (auto ptr = courses.getHead(); ptr != nullptr; ptr = ptr->next) {
            cout << ptr->data;

            if (ptr->next != nullptr && ptr->next->next != nullptr) {
                cout << " || ";
            }

            result.push_back(ptr->data);
        }
    }

    return result;
}

void viewCourseDetails(Student std) { // student and admin
    string crsName;

    cout << "Please enter the name of the course you want to view the details for: ";
    cin >> crsName;

    bool found = false;
    auto ptr = courses.getHead();
    for (; ptr != nullptr; ptr = ptr->next) {
        if (ptr->data.getName() == crsName) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << ptr->data.details() << endl;

        system("pause > 0");
        studentPage(std);
    } else {
        cout << "i'm sorry, but we couldn't find a course with this name, would you mind trying again?" << endl;
        system("pause > 0");
        viewCourseDetails(std);
    }
}

void editStudentData(Student std) { // student
    auto ptr = students.getHead();

    while (ptr != nullptr) {
        if (std.getName() == ptr->data.getName()) {
            string pass;
            cout << "Since the only thing that can be changed is the password, please enter a new password: ";
            cin >> pass;

            ptr->data.setPassword(pass);
        }
        ptr = ptr->next;
    }
}

void studentPage(Student std) {
    int choice;

    cout << "Hello, " << std.getName() << "! what would you like to do?" << endl;
    cout << "1- Show all available courses" << endl;
    cout << "2- Show specific course's details" << endl;
    cout << "3- View all my courses" << endl;
    cout << "4- Register for a course" << endl;
    cout << "5- View all his-her courses" << endl;
    cout << "6- Edit his-her data" << endl;

    cout << "Your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            courses.displayyomnty();
            break;
        case 2:
            viewCourseDetails(std);
            break;
        case 3:
            std.viewMyCurrentCourses();
            break;
        case 4:
            std.registerforCourse();
            break;
        case 5:
            viewAllCourses();
            break;
        case 6:
            editStudentData(std);
            break;
        default:
            cout << "You Entered a Wrong Number!" << endl;
    }

}

void adminPage(){
    int choice;

    cout << "Hello, Admin! what would you like to do?" << endl;
    cout << "1- Add new student" << endl;
    cout << "2- Add new course" << endl;
    cout << "3- Enter course prerequisite" << endl; // idk how to do this one
    cout << "4- View list of all students in a specific course" << endl;
    cout << "5- View list of all courses (Finished - Progressed) on a specific Student" << endl;
    cout << "6- Edit all course data" << endl;

    cout << "Your choice: ";
    cin >> choice;

    switch(choice){
        case 1: {
            string name,id,password;
            int academicyear, n;
            linkedlist<Course> finished, is_going;

            cout << "Please enter the student's name: ";
            cin >> name;

            cout << "Please enter the student's ID: ";
            cin >> id;

            cout << "Please enter the student's Password: ";
            cin >> password;

            cout << "Does the student have any finished courses? Enter the number of courses they finished then each name of the course (make sure the course is also available to avoid conflictions): ";
            cin >> n;
            if (n) {
                while (n--) {
                    string crsname, crscode;
                    cout << "Enter the course name and course code: ";
                    cin >> crsname >> crscode;
                    bool found = false;
                    auto ptr = courses.getHead();
                    for (; ptr != nullptr; ptr = ptr->next) {
                        if (ptr->data.getName() == crsname && ptr->data.getCode() == crscode) {
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        finished.insertyoumis(ptr->data);
                    } else {
                        cout << "debug: didn't find course, taken no action.";
                    }
                }
            }

            cout << "Does the student have any ongoing courses? Enter the number of courses they finished then each name of the course (make sure the course is also available to avoid conflictions): ";
            if (n) {
                while (n--) {
                    string crsname, crscode;
                    cout << "Enter the course name and course code: ";
                    cin >> crsname >> crscode;
                    bool found = false;
                    auto ptr = courses.getHead();
                    for (; ptr != nullptr; ptr = ptr->next) {
                        if (ptr->data.getName() == crsname && ptr->data.getCode() == crscode) {
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        is_going.insertyoumis(ptr->data);
                    } else {
                        cout << "debug: didn't find course, taken no action.";
                    }
                }
            }

            cout << "Please enter the academic year: ";
            cin >> academicyear;

            students.insertyoumis({name, id, password, academicyear, finished, is_going});
            cout << "Student added successfully!" << endl;
        } break;
        case 2: {
        string name, code;
        int maxnumber, hours, n;
        linkedlist<Course> predef;

        cout << "Please enter the new course's name: ";
        cin >> name;

        cout << "Please enter the new course's code: ";
        cin >> code;

        cout << "Please enter the maximum number of students for this course: ";
        cin >> maxnumber;

        cout << "Please enter the number of hours for this course: ";
        cin >> hours;

        cout << "Does this course have any prerequirements? Please enter the number of the required courses to be taken to take this course (0 if none) (please make sure that you enter the course name and course codes correctly to avoid conflictions): ";
        cin >> n;

        if (n) {
            while (n--) {
                string crsname, crscode;
                cout << "Enter course name and code: ";
                cin >> crsname >> crscode;

                bool found = false;
                auto ptr = courses.getHead();
                for (; ptr != nullptr; ptr = ptr->next) {
                    if (ptr->data.getName() == crsname && ptr->data.getCode() == crscode) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    predef.insertyoumis(ptr->data);
                } else {
                    cout << "debug: didn't find course, taken no action.";
                }
            }
        }

        courses.insertyoumis({name, code, maxnumber, hours, predef});
            cout << "Course added successfully!" << endl;
        } break;
        case 3:
        {
            string code;
            int n;
            linkedlist<Course> prerequired;

            cout << "Please enter the course code to start searching for it:";
            cin >> code;

            auto ptr = courses.getHead();
            bool found = false;

            for (; ptr != nullptr; ptr = ptr->next) {
                if (ptr->data.getCode() == code) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Couldn't find the course you entered the code for...Please check your input and try again" << endl << endl << "Press any key to go back to main menu...";
                system("pause > 0");
                adminPage();
                return;
            }

            cout << "Please enter the new number of prerequired courses for this course: ";
            cin >> n;

            if (n) {
                while (n--) {
                    string crsname, crscode;
                    cout << "Enter the course name and course code: ";
                    cin >> crsname >> crscode;
                    bool found = false;
                    auto ptr = courses.getHead();
                    for (; ptr != nullptr; ptr = ptr->next) {
                        if (ptr->data.getName() == crsname && ptr->data.getCode() == crscode) {
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        prerequired.insertyoumis(ptr->data);
                    } else {
                        cout << "debug: didn't find course, taken no action.";
                    }
                }
            }

            ptr->data = Course(ptr->data.getName(), ptr->data.getCode(), ptr->data.getMaxNumberOfStudents(), ptr->data.getHours(), prerequired);
            cout << "Course updated successfully!" << endl << endl << "Press any key to go back to main menu...";
            system("pause > 0");
        }
            break;
        case 4:
        {
            string crsname, crscode;

            cout << "Enter the name and code of the specific course you want to show all students registered to for: ";
            cin >> crsname >> crscode;

            bool found = false;
            auto ptr = courses.getHead();
            for (; ptr != nullptr; ptr = ptr->next) {
                if (ptr->data.getName() == crsname && ptr->data.getCode() == crscode) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "couldn't find the course you input. please check your input and try again..." << endl << endl << "Press any key to go back to main menu...";
                system("pause > 0");
                adminPage();
                return;
            }

            Course cs = ptr->data;

            cout << "These are probably the students that are registered to the course you entered (if it's empty it means none): " << endl;
            auto ptr2 = students.getHead();
            for (; ptr2 != nullptr; ptr2 = ptr2->next) {
                auto lastptr = ptr2->data.getInprogress().getHead();
                found = false;

                for (; lastptr != nullptr; lastptr = lastptr->next) {
                    if (lastptr->data.getName() == crsname && lastptr->data.getCode() == crscode) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << ptr2->data.getName() << ' ';
                }
            }
        }
            break;
        case 5: {
            string id;

            cout << "Please enter the ID of the student you want to show all the courses for: ";

            Student std;
            auto ptr = students.getHead();
            bool found = false;

            for (; ptr != nullptr; ptr = ptr->next) {
                if (ptr->data.getID() == id) {
                    found = true;
                    std = ptr->data;
                    break;
                }
            }

            std.viewMyCurrentCourses();
        } break;
        case 6: {
          string name, code;
          int maxnumberofstds, hours, n;
          linkedlist<Course> prerequired;

          cout << "Please enter the course code to start searching for it:";
          cin >> code;

          auto ptr = courses.getHead();
          bool found = false;

          for (; ptr != nullptr; ptr = ptr->next) {
              if (ptr->data.getCode() == code) {
                  found = true;
                  break;
              }
          }

          if (!found) {
              cout << "Couldn't find the course you entered the code for...Please check your input and try again" << endl << endl << "Press any key to go back to main menu...";
              system("pause > 0");
              adminPage();
              return;
          }

          cout << "Please enter all the information of the course as if you are adding it (enter same information if you don't want to change it:" << endl;
          cout << "Course Name: ";
          cin >> name;

          cout << "Course's Maximum number of students: ";
          cin >> maxnumberofstds;

          cout << "Course's hours: ";
          cin >> hours;

          cout << "number of prerequired courses for it: ";
          cin >> n;

          if (n) {
              while (n--) {
                  string crsname, crscode;
                  cout << "Enter the course name and course code: ";
                  cin >> crsname >> crscode;
                  bool found = false;
                  auto ptr = courses.getHead();
                  for (; ptr != nullptr; ptr = ptr->next) {
                      if (ptr->data.getName() == crsname && ptr->data.getCode() == crscode) {
                          found = true;
                          break;
                      }
                  }

                  if (found) {
                      prerequired.insertyoumis(ptr->data);
                  } else {
                      cout << "debug: didn't find course, taken no action.";
                  }
              }
          }

          ptr->data = Course(name, code, maxnumberofstds, hours, prerequired);
          cout << "Course updated successfully!" << endl << endl << "Press any key to go back to main menu...";
          system("pause > 0");
        } break;

        default:
            cout << "You Entered a Wrong Number! try again!" << endl << endl;
    }

    adminPage();
}

void start() {
    int choice;

    cout << "Are you a student or admin?\n1- User\n2- Admin\n Enter Your Choice: ";
    cin >> choice;

    if (choice == 1) {
        string name,password;

        cout << "Enter the User Name: " << endl;
        cin >> name;
        cout << "Enter the Password: " << endl;
        cin >> password;


        auto ptr = students.getHead();
        bool found = false;

        while (ptr != nullptr) {
            if (ptr->data.getName() == name && ptr->data.getPassword() == password) {
                cout << "logged in successfully! press any key to continue";
                system("pause > 0");
                studentPage(ptr->data);
            }
        }
    } else {
        string name,password;

        cout << "Enter the User Name: " << endl;
        cin >> name;
        cout << "Enter the Password: " << endl;
        cin >> password;


        if (name == "admin" && password == "0000") {
            system("cls");
            adminPage();
        }
    }
}

void preDefiniedData(){


    linkedlist<Course> Math0, Math1, Math2, CS;
    linkedlist<Student> Yomi , Kemo;
    Math0.insertyoumis({"Math0", "mth100", 220, 3});
    Math1.insertyoumis({"Math1", "mth101", 220, 3 , Math0});
    Math2.insertyoumis({"Math2", "mth102", 220, 3 , Math1});
    CS.insertyoumis({"Computer Science" , "cs101" , 220 , 3});
    Yomi.insertyoumis({"Youmna Alaa" , "225023" , "Y123123" , 2022 , Math0 , Math1});
    Kemo.insertyoumis({"Akram Mohamed" , "225186" , "123123" , 2022 , CS , Math0});
}

int main() {
    start();
}