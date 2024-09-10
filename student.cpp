#include "student.h"

Student::Student() { // Конструктор пустого студента
	fio = "";
	id = "";
	email = "";
}
Student::Student(const std::string& fio, const std::string& id, const std::string& email) { // Конструктор студента с заранее заданными полями
	this->fio = fio;
	this->id = id;
	this->email = email;
}
Student::Student(const std::string& fio, const std::string& id, const std::string& email, const std::map<std::string, std::vector<double>>& grades){ // Конструктор студента с оценками
	this->fio = fio;
	this->id = id;
	this->email = email;
	this->grades = grades;
}
Student::Student(const Student& other) { // Копирование
	this->grades = other.grades;
	this->fio = other.fio;
	this->id = other.id;
	this->email = other.email;
}
void Student::add_grade(const std::string& subject, double grade) { // Добавляем оценку студенту
	grades[subject].push_back(grade);
}
double Student::get_avg_grade() const { // Среднее значение оценки
	double sum = 0;
	int count = 0;
	for (const auto& subject_grades : grades) {
		for (const auto& grade : subject_grades.second) {
			sum += grade;
			count++;
		}
	}
	if (grades.empty()) return 0.0;
	else return sum / grades.size();
}
double Student::get_grade_by_subject(const std::string& subject) const { // Получение оценки по предмету
	auto it = grades.find(subject);
	if (it != grades.end() && !it->second.empty()) {
		double sum = 0;
		for (const auto& grade : it->second) {
			sum += grade;
		}
		return sum / it->second.size();
	}
	return 0.0;
}
bool Student::operator<(const Student& other) const { // Перегрузка оператора сравнения
	return id < other.id;
}
std::string Student::get_id() const { // Геттеры
	return id;
}
std::string Student::get_fio() const {
	return fio;
}
std::string Student::get_email() const {
	return email;
}
std::map<std::string, std::vector<double>> Student::get_grades() const {
	return grades;
}

void Student::print() const { // Вывод на печать
	std::cout << "Fio: " << fio << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Email: " << email << std::endl;
	std::cout << "Grades: " << std::endl;
	for (const auto& subject_grades : grades) {
		std::cout << " " << subject_grades.first << ": ";
		for (const auto& grade : subject_grades.second) {
			std::cout << grade << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Average grade: " << get_avg_grade() << std::endl;
}
Student::~Student() {}; // Деструктор

std::ostream& operator<<(std::ostream& stream, const Student& student) { // Перегрузка оператора вывода в стандартный поток
	stream << "Fio: " << student.fio << ", ID: " << student.id <<", Email: "<<student.email<< "\nGrades:\n";
	for (const auto& subject_grades : student.grades) {
		stream << " " << subject_grades.first << ": ";
		for (const auto& grade : subject_grades.second) {
			stream << grade << " ";
		}
		stream << "\n";
	}
	stream << "Average grade: " << student.get_avg_grade() << std::endl;
	return stream;
}
