#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

enum tipes { exam, test, course_work };
typedef struct Subject {
    char *name_lessons; // Динамическая строка для названия дисциплины
    unsigned char audience_lecture; // Номер аудитории (до 255)
    unsigned char audience_labs;    // Номер аудитории (до 255)
    unsigned char sum_hours;        // Количество часов (до 255)
    enum tipes form : 2;            // Формат аттестации (2 бита)
} My_Subject;

typedef struct Student {
    char *name;       // Динамическая строка для имени
    unsigned char b_date;       // Год рождения (смещение от 1900)
    char *group;      // Динамическая строка для группы
    My_Subject *num_of_subject; // Указатель на массив дисциплин
    unsigned char avarage_disciplines; // Количество дисциплин (до 255)
} My_Student;

// Глобальные массивы для хранения данных
const char *full_names[] = {
    "Ivan Ivanov", "Petr Petrov", "Semen Smirnov", "Alexey Kuznetsov", "Vasiliy Vasiliev",
    "Andrey Popov", "Dmitry Sidorov", "Mikhail Mikhailov", "Fedor Fedorov", "Nikolay Novikov",
    "Sergey Kravtsov", "Alexandr Solovyov", "Vladimir Chernov", "Igor Morozov", "Kirill Kirillov",
    "Egor Egorov", "Viktor Kostin", "Alexey Baranov", "Roman Romanov", "Timofey Timofeev",
    "Oleg Golubev", "Dmitriy Dmitriev", "Nikita Nikolaev", "Vladimir Zhukov", "Yuri Makarov",
    "Semyon Zaytsev", "Victor Frolov", "Anton Gusev", "Maksim Vorobyov", "Viktor Kovalev",
    "Boris Belyakov", "Igor Grigoryev", "Leonid Vengerov", "Yuri Semyonov", "Danila Kolesnikov",
    "Vladimir Borisov", "Sergey Lazarev", "Alexey Svetlov", "Oleg Marinov", "Pavel Yakovlev",
    "Valentin Tikhonov", "Dmitriy Gavrilov", "Andrey Pavlov", "Vladimir Sukhov", "Yuri Cherepanov",
    "Petr Sokolov", "Maxim Zelenov", "Igor Krylov", "Oleg Filatov"
};

const char *classrooms[] = {
    "101", "102", "103", "104", "105",
    "201", "202", "203", "204", "205",
    "301", "302", "303", "304", "305",
    "401", "402", "403", "404", "405",
    "501", "502", "503", "504", "505",
    "601", "602", "603", "604", "605",
    "701", "702", "703", "704", "705",
    "801", "802", "803", "804", "805",
    "901", "902", "903", "904", "905",
    "1001", "1002", "1003", "1004", "1005"
};

const char *subjects[] = {
    "Mathematics", "Physics", "Chemistry", "Biology", "History",
    "Geography", "Literature", "Computer Science", "Economics", "Philosophy",
    "Foreign Language", "Sociology", "Psychology", "Anthropology", "Law",
    "Music", "Visual Arts", "Physical Education", "Ecology", "Architecture",
    "Astronomy", "Technology", "Art History", "Ethics", "Logic",
    "Rhetoric", "Cultural Studies", "Journalism", "Probability Theory", "Statistics",
    "Algebra", "Geometry", "Cybernetics", "Programming", "Systems Analysis",
    "Microeconomics", "Macroeconomics", "Financial Management", "Marketing", "Project Management",
    "Design", "Archaeology", "Logistics", "Climatology", "Theater",
    "Film Studies", "Dance", "Sports", "Landscape Design", "Medical Ethics"
};

My_Student *student = NULL;
int N = 0;
int max_sub = 20;
int min_sub = 10;

// Генерация случайного студента
void generate_student(My_Student *student) {
    student->name = strdup(full_names[rand() % 50]);
    student->b_date = 1900 + rand() % 156; // Год от 1900 до 2055
    student->group = strdup(classrooms[rand() % 50]);
    student->avarage_disciplines = rand() % (max_sub - min_sub + 1) + min_sub;

    // Выделение памяти для массива дисциплин
    student->num_of_subject = (My_Subject*)calloc(student->avarage_disciplines, sizeof(My_Subject));
    if (student->num_of_subject == NULL) {
        printf("Ошибка: не удалось выделить память для дисциплин.\n");
        return;
    }

    for (int j = 0; j < student->avarage_disciplines; j++) {
        student->num_of_subject[j].name_lessons = strdup(subjects[rand() % 50]);
        student->num_of_subject[j].audience_lecture = rand() % 255 + 1;
        student->num_of_subject[j].audience_labs = rand() % 255 + 1;
        student->num_of_subject[j].sum_hours = rand() % 255 + 1;
        student->num_of_subject[j].form = rand() % 3;
    }
}

// Генерация N студентов
void generait(int N) {
    srand(time(NULL));
    student = (My_Student*)calloc(N, sizeof(My_Student));
    if (student == NULL) {
        printf("Ошибка: не удалось выделить память для студентов.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        generate_student(&student[i]);
    }
}

// Вывод информации о студентах
void print_stud(int n) {
    if (student == NULL) {
        printf("Нет записи\n");
        return;
    }
    if (n > N) {
        printf("Максимальное значение: %d\n", N);
        n = N;
    }
    for (int i = 0; i < n; i++) {
        printf("Имя студента: %s, группа студента: %s, год рождения: %d\n", student[i].name, student[i].group, student[i].b_date);
        for (int j = 0; j < student[i].avarage_disciplines; j++) {
            printf("Предмет %d: %s, Лекционная комната: %d, Лабораторная комната: %d, Часы: %d, Форма сдачи: %d\n",
                   j + 1, student[i].num_of_subject[j].name_lessons, student[i].num_of_subject[j].audience_lecture,
                   student[i].num_of_subject[j].audience_labs, student[i].num_of_subject[j].sum_hours, student[i].num_of_subject[j].form);
        }
        printf("\n");
    }
}

// Вычисление размера занимаемой памяти
void size() {
    if (student == NULL) {
        printf("Ошибка: нет данных\n");
        return;
    }

    size_t total_size = N * sizeof(My_Student); // Основная структура студентов

    for (int i = 0; i < N; i++) {
        total_size += student[i].avarage_disciplines * sizeof(My_Subject); // Память для дисциплин
        total_size += strlen(student[i].name) + 1; // Память для имени
        total_size += strlen(student[i].group) + 1; // Память для группы
        for (int j = 0; j < student[i].avarage_disciplines; j++) {
            total_size += strlen(student[i].num_of_subject[j].name_lessons) + 1; // Память для названия дисциплины
        }
    }

    // Вывод в удобочитаемом формате
    if (total_size < 1024) {
        printf("Size: %zu B\n", total_size);
    } else if (total_size < 1048576) {
        printf("Size: %.2f KB\n", total_size / 1024.0);
    } else if (total_size < 1073741824) {
        printf("Size: %.2f MB\n", total_size / 1048576.0);
    } else {
        printf("Size: %.2f GB\n", total_size / 1073741824.0);
    }
}

// Очистка памяти
void clean() {
    if (student == NULL) {
        return;
    }
    for (int i = 0; i < N; i++) {
        free(student[i].name);
        free(student[i].group);
        for (int j = 0; j < student[i].avarage_disciplines; j++) {
            free(student[i].num_of_subject[j].name_lessons);
        }
        free(student[i].num_of_subject);
    }
    free(student);
    student = NULL;
}

// Функция для проверки доступной памяти
int check_memory(int N) {
    size_t required_memory = N * sizeof(My_Student); // Память для студентов
    for (int i = 0; i < N; i++) {
        int disciplines = rand() % (max_sub - min_sub + 1) + min_sub;
        required_memory += disciplines * sizeof(My_Subject); // Память для дисциплин
    }

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    size_t free_memory = memInfo.ullAvailPhys; // Доступная физическая память в байтах

    if (required_memory > free_memory) {
        printf("Ошибка: недостаточно памяти для генерации данных. Требуется: %.2f MB, доступно: %.2f MB\n",
               required_memory / 1048576.0, free_memory / 1048576.0);
        return 0;
    }
    return 1;
}

// Функция для расчета максимального количества студентов
void check_max_students() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    size_t free_memory = memInfo.ullAvailPhys; // Доступная память в байтах

    size_t min_student_size = sizeof(My_Student) + min_sub * sizeof(My_Subject);  // Минимум
    size_t max_student_size = sizeof(My_Student) + max_sub * sizeof(My_Subject);  // Максимум

    size_t max_students_min = free_memory / min_student_size;
    size_t max_students_max = free_memory / max_student_size;

    printf("Доступная память: %.2f GB\n", free_memory / 1073741824.0);
    printf("Максимум студентов (минимум размера): %zu\n", max_students_min);
    printf("Максимум студентов (максимум размера): %zu\n", max_students_max);
}

int main(void) {
    char command[100];
    printf("gen N - generate N students\n"
           "min N - changes min_disciplines to number N (initially min_disciplines = 10)\n"
           "max N - changes max_disciplines to number N (initially max_disciplines = 20)\n"
           "get - get size (B, KB, MB, GB)\n"
           "print N - print N students\n"
           "clean - memory clearing\n"
           "max_students - check maximum number of students that can be generated\n"
           "exit - finish the program\n\n");

    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);

        if (strcmp(command, "exit\n") == 0) {
            break;
        } else if (strncmp(command, "gen ", 4) == 0) {
            N = atoi(command + 4);
            if (check_memory(N)) {
                generait(N);
            } else {
                printf("Недостаточно памяти для генерации %d студентов.\n", N);
            }
        } else if (strncmp(command, "min ", 4) == 0) {
            min_sub = atoi(command + 4);
        } else if (strncmp(command, "max ", 4) == 0) {
            max_sub = atoi(command + 4);
        } else if (strncmp(command, "get\n", 4) == 0) {
            size();
        } else if (strncmp(command, "print ", 6) == 0) {
            int n = atoi(command + 6);
            print_stud(n);
        } else if (strncmp(command, "clean\n", 6) == 0) {
            clean();
        } else if (strncmp(command, "max_students\n", 13) == 0) {
            check_max_students();
        } else {
            printf("Неизвестная команда\n");
        }
    }

    return 0;
}