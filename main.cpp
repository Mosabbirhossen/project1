#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
protected:
    string name;

public:
    Person(const string& name) : name(name) {}

    virtual void display() const = 0;

    string getName() const {
        return name;
    }
};

class Student : public Person {
private:
    int borderNo;
    string department;
    string password;
    bool meals[31];

public:
    Student(const string& name, int borderNo, const string& department)
        : Person(name), borderNo(borderNo), department(department) {
        for (int i = 0; i < 31; ++i) {
            meals[i] = true;
        }
    }

    int getBorderNo() const {
        return borderNo;
    }

    string getDepartment() const {
        return department;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    bool authenticate(const string& inputPassword) const {
        return password == inputPassword;
    }

    void turnOffMeal(int day) {
        if (day >= 1 && day <= 31) {
            meals[day - 1] = false;
            cout << "Meal turned off for Day " << day << endl;
        }
    }

    void turnOnMeal(int day) {
        if (day >= 1 && day <= 31) {
            meals[day - 1] = true;
            cout << "Meal turned on for Day " << day << endl;
        }
    }

    void displayMealStatus() const {
        cout << "Meal Status for " << name << " (Border No: " << borderNo << ", Department: " << department << "):\n";
        for (int i = 0; i < 31; ++i) {
            cout << "Day " << (i + 1) << ": " << (meals[i] ? "ON" : "Off") << endl;
        }
        cout << endl;
    }

    void display() const override {
        cout << "Student: " << name << " (Border No: " << borderNo << ", Department: " << department << ")" << endl;
    }
};

class Menu {
private:
    vector<string> dishes;

public:
    void addDish(const string& dish) {
        dishes.push_back(dish);
    }

    void display() const {
        cout << "Menu:\n";
        for (const string& dish : dishes) {
            cout << "- " << dish << "\n";
        }
        cout << endl;
    }
};

class DiningHall {
private:
    string name;
    Menu menu;
    vector<Person*> people;

public:
    DiningHall(const string& name) : name(name) {}

    void addPerson(Person* person) {
        people.push_back(person);
    }

    void displayPeople() const {
        cout << "People in " << name << "\n";
        for (const Person* person : people) {
            person->display();
        }
        cout << endl;
    }

    void setMenu(const Menu& newMenu) {
        menu = newMenu;
    }

    Person* findPersonByName(const string& name) {
        for (Person* person : people) {
            if (person->getName() == name) {
                return person;
            }
        }
        return nullptr;
    }

    void displayMenu() const {
        cout << "Welcome to " << name << "\n";
        menu.display();
    }
};

int main() {
    DiningHall lalanShahHall("Lalan Shah Hall");

    string name;
    int borderNo;
    string department;

    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter border number: ";
    cin >> borderNo;

    cin.ignore();

    cout << "Enter department Name: ";
    getline(cin, department);

    Student* student = new Student(name, borderNo, department);
    lalanShahHall.addPerson(student);

    Menu menu;
    menu.addDish("Rice");
    menu.addDish("Lentils");
    menu.addDish("Vegetables");
    menu.addDish("Chicken");
    menu.addDish("Fish");
    lalanShahHall.setMenu(menu);

    lalanShahHall.displayPeople();

    int enteredBorderNo;
    string password;
    string confirmPassword;

    cout << "Student Login\n";
    cout << "Enter your border number: ";
    cin >> enteredBorderNo;

    Person* person = lalanShahHall.findPersonByName(name);

    if (person) {
        Student* studentPtr = dynamic_cast<Student*>(person);

        do {
            cout << "Enter your new password: ";
            cin >> password;
            cout << "Confirm password: ";
            cin >> confirmPassword;
            if (password != confirmPassword) {
                cout << "Passwords do not match. Please try again.\n";
            }
        } while (password != confirmPassword);

        studentPtr->setPassword(password);
        cout << "Log in to the Student Management System of Lalan Shah Hall successfully!\n\n";

        lalanShahHall.displayMenu();

        studentPtr->displayMealStatus();

        int choice;
        while (true) {
            cout << "Enter your choice:\n";
            cout << "1. Turn off meal for a specific day\n";
            cout << "2. Turn on meal for a specific day\n";
            cout << "3. Exit\n";
            cout << "Choice: ";
            cin >> choice;

            if (choice == 1 || choice == 2) {
                int day;
                cout << "Enter the day (1-31): ";
                cin >> day;

                if (choice == 1) {
                    studentPtr->turnOffMeal(day);
                }
                else if (choice == 2) {
                    studentPtr->turnOnMeal(day);
                }
            }
            else if (choice == 3) {
                break;
            }
            else {
                cout << "Invalid choice!\n";
            }

            studentPtr->displayMealStatus();
        }
    }
    else {
        cout << "Person not found.\n";
    }

    delete student;

    return 0;
}

