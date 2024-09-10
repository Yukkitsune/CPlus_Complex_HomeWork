#include "group.h" // Подключаем необходимыые библиотеки

int main()
{
    Group group1("Group 1"); // Создаем две группы с названием
    Group group2("Group 2");
    Group* current_group = &group1; //  Указатель на одну из двух групп ( по умолчанию группа 1)
    bool run = true;
    while (run) { // Меню программы
        std::cout << "Choose an option: " << std::endl;
        std::cout << "1. Add student to current group" << std::endl;
        std::cout << "2. Add grade to student" << std::endl;
        std::cout << "3. Average grade by subject" << std::endl;
        std::cout << "4. Find student" << std::endl;
        std::cout << "5. Edit student" << std::endl;
        std::cout << "6. Remove student" << std::endl;
        std::cout << "7. Save data to file" << std::endl;
        std::cout << "8. Load from file" << std::endl;
        std::cout << "9. Sort students by field and print students" << std::endl;
        std::cout << "10. Print all student from current group" << std::endl;
        std::cout << "11. Change current group" << std::endl;
        std::cout << "12. Merge Group 1 and Group 2" << std::endl;
        std::cout << "13. Exit" << std::endl;
        int choice; // Выбор пользователя
        std::cin >> choice;
        switch (choice) {
        case 1: {
            std::string fio, id, email; // Добавляем нового студента в группу
            std::cout << "Enter student Fio: ";
            std::cin.ignore();
            std::getline(std::cin,fio);
            std::cout << "Enter student ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter student Email: ";
            std::getline(std::cin, email);
            Student student(fio, id, email);
            (*current_group).add_student(student);
            break;
        }
        case 2: {
            std::string id, subject; // Добавляем оценку студенту по id, иначе исключение
            double grade;
            std::cout << "Enter student's ID: ";
            std::cin.ignore();
            std::getline(std::cin, id);
            Student student;
            if (current_group->find_student_by_ID(id, student)) {
                std::cout << "Enter subject: ";
                std::getline(std::cin, subject);
                std::cout << "Enter grade: ";
                std::cin >> grade;
                student.add_grade(subject, grade);
                current_group->edit_student(id, student);
            }
            else {
                std::cout << "Student not found" << std::endl;
            }
            break;
        }
        case 3: {
            std::string id, subject; // Средняя оценка по предмету по id, иначе исключение
            std::cout << "Enter ID of the student: ";
            std::cin.ignore();
            std::getline(std::cin, id);
            std::cout << "Enter subject: ";
            std::getline(std::cin, subject);
            Student student;
            if (current_group->find_student_by_ID(id, student)) {
                double avg_grade = student.get_grade_by_subject(subject);
                std::cout << "Average grade for " << subject << ": " << avg_grade << std::endl;
            }
            else {
                std::cout << "Student not found" << std::endl;
            }
            break;

        }
        case 4: {
            std::string id; // Поиск студента в группе по его id
            std::cout << "Enter ID: ";
            std::cin.ignore();
            std::getline(std::cin, id);
            Student student;
            if (current_group->find_student_by_ID(id, student)) {
                student.print();
            }
            else {
                std::cout << "Student not found" << std::endl;
            }
            break;
        }
        case 5: {
            std::string id; // Редактирование студента
            std::cout << "Enter student's ID to edit the student: ";
            std::cin.ignore();
            std::getline(std::cin, id);
            Student student;
            if (current_group->find_student_by_ID(id, student)) {
                std::string newFio, newId, newEmail;
                std::cout << "Enter new Fio: ";
                std::getline(std::cin, newFio);
                std::cout << "Enter new ID: ";
                std::getline(std::cin, newId);
                std::cout << "Enter new Email: ";
                std::getline(std::cin, newEmail);
                student = Student(newFio, newId,newEmail, student.get_grades());
                current_group->edit_student(id, student);
            }
            else {
                std::cout << "Student not found" << std::endl;
            }
            break;
        }
        case 6: { // Удаление студента из группы
            std::string id;
            std::cout << "Enter student's ID to remove the student: ";
            std::cin.ignore();
            std::getline(std::cin, id);
            current_group->remove_student(id);
            break;
        }
        case 7: { // Сохранение группы в файл
            std::string file;
            std::cout << "Enter name of the file to save: ";
            std::cin.ignore();
            std::getline(std::cin, file);
            std::thread saveThread([current_group, file]() {
                current_group->save_to_file(file);
                });
            saveThread.join();
            break;
        }
        case 8: {
            std::string file; // Загрузка данных о студентах из файла
            std::cout << "Enter name of the file to load: ";
            std::cin.ignore();
            std::getline(std::cin, file);
            std::thread loadThread([current_group, file]() {
                current_group->load_from_file(file);
                });
            loadThread.join();
            break;
        }
        case 9: {
            std::string field; // Сортировка студентов по полю
            std::cout << "Enter field to sort students (fio or id or avg_grade): ";
            std::cin.ignore();
            std::getline(std::cin, field);
            current_group->sort_print_by_field(field);
            break;
        }
        case 10: { // Печать всех студентов группы
            current_group->print_students();
            break;
        }
        case 11: { // Изменение учебной группы
            int group_choice;
            std::cout << "Choose group (1 or 2): ";
            std::cin >> group_choice;
            if (group_choice == 1) {
                current_group = &group1;
            }
            else if (group_choice == 2) {
                current_group = &group2;
            }
            else {
                std::cout << "Invalid group choice" << std::endl;
            }
            break;
        }
        case 12: { // Статистика по соединенным группам
            Group merged_group = group1 + group2;
            std::cout << "Merged group:\n";
            merged_group.print_students();
            break;
        }
        case 13: { // Остановка программы
            run = false;
            break;
        }
        default: { // Некорректный ввод пользователя
            std::cout << "Wrong choice. Please choose an option again.\n";
            break;
        }
        }
    }
    return 0;
}
