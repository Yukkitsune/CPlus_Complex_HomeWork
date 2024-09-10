#include "group.h"

Group::Group(const Group& group_2) { // Конструктор копирования
    std::lock_guard<std::mutex> lock(group_2.mtx);
    students = group_2.students;
    group_name = group_2.group_name;
}

Group::Group(const std::string& name) { // Конструктор с названием группы
    this->group_name = name;
}

Group::~Group() {}; // Деструктор

void Group::set_group_name(const std::string& name) { // Сеттер названия группы
    std::lock_guard<std::mutex> lock(mtx);
    group_name = name;
}

std::string Group::get_group_name() const { // Геттер названия группы
    std::lock_guard<std::mutex> lock(mtx);
    return group_name;
}
void Group::add_student(const Student& student) { // Добавление студента в группу
    std::lock_guard<std::mutex> lock(mtx);
    students.insert(student);
}

bool Group::find_student_by_ID(const std::string& id, Student& student) { // Поиск по id
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& it : students) {
        if (it.get_id() == id) {
            student = it;
            return true;
        }
    }
    return false;
}

void Group::edit_student(const std::string& id, const Student& new_student) { // Изменение параметров студента
    std::lock_guard<std::mutex> lock(mtx);
    auto it = students.find(Student("", id,""));
    if (it != students.end()) {
        students.erase(it);
        students.insert(new_student);
    }
}

void Group::remove_student(const std::string& id) { // Удаление из группы
    std::lock_guard<std::mutex> lock(mtx);
    auto it = students.find(Student("", id,""));
    if (it != students.end()) {
        students.erase(it);
    }
}

void Group::save_to_file(const std::string& file) { // Сохранение в файл
    std::lock_guard<std::mutex> lock(mtx);
    try {
        std::ofstream fout(file);
        if (!fout.is_open()) throw std::runtime_error("Failed to open file for saving");
        fout << "Group name: " << group_name << "\n";
        for (const auto& student : students) {
            fout << student.get_id() << ", " << student.get_fio();
            for (const auto& subject_grades : student.get_grades()) {
                fout << ", " << subject_grades.first;
                for (const auto& grade : subject_grades.second) {
                    fout << ", " << grade;
                }
            }
            fout << "\n";
        }
    }
    catch (const std::exception& error) {
        std::cerr << "Something went wrong: " << error.what() << std::endl;
    }
}

void Group::load_from_file(const std::string& file) { // Чтение из файла
    std::lock_guard<std::mutex> lock(mtx);
    try {
        std::ifstream fin(file);
        if (!fin.is_open()) throw std::runtime_error("Failed to open file for loading");
        students.clear();
        std::string line, group_name_line;
        std::getline(fin, group_name_line);
        group_name = group_name_line.substr(group_name_line.find(":") + 2);
        while (std::getline(fin, line)) {
            std::stringstream ss(line);
            std::string id, fio, email;
            std::getline(ss, id, ',');
            std::getline(ss, fio, ',');
            std::getline(ss, email, ',');

            std::map<std::string, std::vector<double>> grades;
            std::string subject;
            while (std::getline(ss, subject, ',')) {
                std::vector<double> grades_vector;
                std::string grade_str;
                while (std::getline(ss, grade_str, ',')) {
                    try {
                        grades_vector.push_back(std::stod(grade_str));
                    }
                    catch (const std::invalid_argument&) {
                        break;
                    }
                }
                grades[subject] = grades_vector;
            }
            students.insert(Student(fio, id, email, grades));
        }
    }
    catch (const std::exception& error) {
        std::cerr << "Something went wrong: " << error.what() << std::endl;
    }
}

void Group::sort_print_by_field(const std::string& field) { // Сортировка по полю и вывод на печать
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<Student> sorted(students.begin(), students.end());

    if (field == "fio") { // Сортировка по фио
        std::sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) { return a.get_fio() < b.get_fio(); });
    }
    else if (field == "id") { // Сортировка по id
        std::sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) { return a.get_id() < b.get_id(); });
    }
    else if (field == "avg_grade") { // Сортировка по средней оценке
        std::sort(sorted.begin(), sorted.end(),
            [](const Student& a, const Student& b) { return a.get_avg_grade() < b.get_avg_grade(); });
    }
    for (const auto& student : sorted) { // Вывод отсортированных студентов
        student.print();
    }
}

void Group::print_students() const { // Вывод всех студентов
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Group name: " << group_name << std::endl;
    for (const auto& student : students) {
        student.print();
    }
}

Group Group::operator+(const Student& student) const { // Перегрузка оператора сложения для добавления студента в группу
    Group new_group(*this);
    new_group.add_student(student);
    return new_group;
}
Group Group::operator+(const Group& other) const { // Перегрузка оператора сложения для двух групп
    Group new_group = *this;
    std::lock_guard<std::mutex> lock1(mtx);
    std::lock_guard<std::mutex> lock2(other.mtx);
    new_group.students.insert(other.students.begin(), other.students.end());
    return new_group;
}

void Group::add_students_to_group(const std::vector<Student>& students,  Group& group) { // Добавление студента в группу
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto& student : students) {
        group.add_student(student);
    }
}

std::ostream& operator<<(std::ostream& stream, Group& group) { // Перегрузка оператора вывода в стандартный поток
    std::lock_guard<std::mutex> lock(group.mtx);
    stream << "Group name: " << group.get_group_name() << "\n";
    for (const auto& student : group.students) {
        stream << student;
    }
    return stream;
}
