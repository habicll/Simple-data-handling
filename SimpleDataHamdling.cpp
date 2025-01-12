#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

class Student {
public:
    int student_id;
    std::string name;
    int year_of_enrollment;

    Student(int id, std::string n, int year) : student_id(id), name(n), year_of_enrollment(year) {}

    void display() const {
        std::cout << "ID: " << student_id << ", Name: " << name << ", Year: " << year_of_enrollment << std::endl;
    }
};

class StudentList {
private:
    std::vector<Student> students;

    std::vector<Student> merge_sort_recursive(std::vector<Student>& arr) {
        if (arr.size() <= 1) return arr;

        size_t mid = arr.size() / 2;
        std::vector<Student> left(arr.begin(), arr.begin() + mid);
        std::vector<Student> right(arr.begin() + mid, arr.end());

        left = merge_sort_recursive(left);
        right = merge_sort_recursive(right);

        return merge(left, right);
    }

    std::vector<Student> merge(const std::vector<Student>& left, const std::vector<Student>& right) {
        std::vector<Student> result;
        size_t i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i].student_id <= right[j].student_id) {
                result.push_back(left[i++]);
            } else {
                result.push_back(right[j++]);
            }
        }
        while (i < left.size()) result.push_back(left[i++]);
        while (j < right.size()) result.push_back(right[j++]);
        return result;
    }

public:
    void add_student(const Student& student) {
        students.push_back(student);
    }

    int find_student(int student_id) {
        int low = 0, high = students.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (students[mid].student_id == student_id) return mid;
            if (students[mid].student_id < student_id) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    void update_student(int student_id, const std::string& new_name, int new_year) {
        int index = find_student(student_id);
        if (index != -1) {
            students[index].name = new_name;
            students[index].year_of_enrollment = new_year;
            std::cout << "Student updated." << std::endl;
        } else {
            std::cout << "Student not found." << std::endl;
        }
    }

    void remove_student(int student_id) {
        int index = find_student(student_id);
        if (index != -1) {
            students.erase(students.begin() + index);
            std::cout << "Student removed." << std::endl;
        } else {
            std::cout << "Student not found." << std::endl;
        }
    }

    void sort_students() {
        students = merge_sort_recursive(students);
        std::cout << "Students sorted by ID." << std::endl;
    }

    void display_all() const {
        for (const auto& student : students) {
            student.display();
        }
    }
};

std::string random_name() {
    const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    for (int i = 0; i < 5; ++i) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return result;
}

bool get_int_input(const std::string& prompt, int& value) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid number." << std::endl;
        return false;
    }
    return true;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    StudentList student_list;

    for (int i = 0; i < 10; ++i) {
        int id = rand() % 9000 + 1000;
        student_list.add_student(Student(id, random_name(), rand() % 8 + 2018));
    }

    int choice;
    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Display all students" << std::endl;
        std::cout << "2. Add student" << std::endl;
        std::cout << "3. Update student" << std::endl;
        std::cout << "4. Remove student" << std::endl;
        std::cout << "5. Sort students by ID" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 6." << std::endl;
            continue;
        }

        if (choice == 1) {
            student_list.display_all();
        } else if (choice == 2) {
            int id, year;
            std::string name;
            if (get_int_input("Enter student ID: ", id) && get_int_input("Enter year of enrollment: ", year)) {
                std::cout << "Enter student name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                student_list.add_student(Student(id, name, year));
            }
        } else if (choice == 3) {
            int id, year;
            std::string name;
            if (get_int_input("Enter student ID to update: ", id) && get_int_input("Enter new year of enrollment: ", year)) {
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                student_list.update_student(id, name, year);
            }
        } else if (choice == 4) {
            int id;
            if (get_int_input("Enter student ID to remove: ", id)) {
                student_list.remove_student(id);
            }
        } else if (choice == 5) {
            student_list.sort_students();
        }
    } while (choice != 6);

    return 0;
}
