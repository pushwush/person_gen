#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

// Используем битовые поля для минимизации размера
enum tipes { exam, test, course_work };

typedef struct Subject {
    char name_lessons[20];
    uint8_t audience_lecture; 
    uint8_t audience_labs;
    uint8_t sum_hours; 
    enum tipes form;
} My_Subject;

typedef struct Student {
    char surname[20];
    char name[20];
    char patronymic[20];
    uint16_t b_date;
    char group[6];
    My_Subject *num_of_subject;
    uint8_t avarage_disciplines;
} My_Student;

My_Student *student = NULL;
int N = 0;
int max_sub = 20;
int min_sub = 10;

const char *surnames[] = {
    "Иванов", "Петров", "Смирнов", "Кузнецов", "Васильев",
    "Попов", "Сидоров", "Михайлов", "Федоров", "Новиков",
    "Кравцов", "Соловьев", "Чернов", "Морозов", "Кириллов",
    "Егоров", "Костин", "Баранов", "Романов", "Тимофеев",
    "Денисов", "Степанов", "Анатольев", "Викторов", "Максимов",
    "Данилов", "Семёнов", "Валерий", "Кириллов", "Евгений",
    "Романов", "Станиславов", "Дмитрий", "Артем", "Никита"
};

const char *names[] = {
    "Иван", "Петр", "Семен", "Алексей", "Василий",
    "Андрей", "Дмитрий", "Михаил", "Федор", "Николай",
    "Сергей", "Александр", "Владимир", "Игорь", "Кирилл",
    "Егор", "Виктор", "Роман", "Тимофей",
    "Денис", "Станислав", "Анатолий", "Тимур", "Илья",
    "Григорий", "Савелий", "Арсений", "Максим", "Даниил",
    "Семён", "Валерий", "Евгений", "Артем", "Никита"
};

const char *patronymics[] = {
    "Иванович ", "Петрович ", "Семенович ", "Алексеевич ", "Васильевич ",
    "Андреевич ", "Дмитриевич ", "Михайлович ", "Федорович ", "Николаевич ",
    "Сергеевич ", "Александрович ", "Егорович ", "Викторович ", "Романович ",
    "Тимофеевич ", "Денисович ", "Станиславович ", "Анатольевич ", "Максимович ",
    "Данилович ", "Семёнович ", "Валерьевич ", "Кириллович ", "Евгеньевич ",
    "Романович ", "Дмитриевич ", "Артемович ", "Никитич ", "Григорьевич ",
    "Александрович ", "Станиславович ", "Анатольевич ", "Максимович ", "Данилович ",
    "Семёнович ", "Валерьевич ", "Кириллович ", "Евгеньевич ", "Сергеевич ",
    "Андреевич ", "Дмитриевич ", "Михайлович ", "Федорович ", "Николаевич ",
    "Сидорович ", "Игоревич ", "Валентинович ", "Станиславович ", "Тимофеевич ",
    "Евгеньевич ", "Денисович ", "Кириллович ", "Семенович ", "Петрович "
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
    "901", "902", "903", "904", "905"
};

const char *subjects[] = {
    "Математика", "Физика", "Химия", "Биология", "История",
    "География", "Литература", "Информатика", "Экономика", "Философия",
    "Иностранный язык", "Социология", "Психология", "Антропология", "Право",
    "Музыка", "Изобразительное искусство", "Физическая культура", "Экология", "Архитектура",
    "Астрономия", "Геология", "Политология", "Социальная работа", "История искусств",
    "Культурология", "Дизайн", "Этика", "Эстетика", "Теория вероятностей",
    "Статистика", "Филология", "Логика", "Риторика", "Кибернетика",
    "Медицинские науки", "Биохимия", "Генетика", "Эконометрика", "Системный анализ",
    "История науки", "Теория игр", "Менеджмент", "Маркетинг", "Финансовый анализ"
};

void generait(int N) {
    srand(time(NULL));
    student = (My_Student*)calloc(N, sizeof(My_Student));
    if (student == NULL) {
        printf("Ошибка: не удалось выделить память для студентов.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        My_Student *current_student = &student[i];

        // Заполнение полей фамилии, имени и отчества
        strncpy(current_student->surname, surnames[rand() % (sizeof(surnames) / sizeof(surnames[0]))], sizeof(current_student->surname) - 1);
        current_student->surname[sizeof(current_student->surname) - 1] = '\0';

        strncpy(current_student->name, names[rand() % (sizeof(names) / sizeof(names[0]))], sizeof(current_student->name) - 1);
        current_student->name[sizeof(current_student->name) - 1] = '\0';

        strncpy(current_student->patronymic, patronymics[rand() % (sizeof(patronymics) / sizeof(patronymics[0]))], sizeof(current_student->patronymic) - 1);
        current_student->patronymic[sizeof(current_student->patronymic) - 1] = '\0';

        current_student->b_date = 2006 + rand() % 2;

        strncpy(current_student->group, classrooms[rand() % (sizeof(classrooms) / sizeof(classrooms[0]))], sizeof(current_student->group) - 1);
        current_student->group[sizeof(current_student->group) - 1] = '\0';

        current_student->avarage_disciplines = rand() % (max_sub - min_sub + 1) + min_sub;

        current_student->num_of_subject = (My_Subject*)calloc(current_student->avarage_disciplines, sizeof(My_Subject));
        if (current_student->num_of_subject == NULL) {
            printf("Ошибка: не удалось выделить память для дисциплин студента %d.\n", i);
            return;
        }

        for (int j = 0; j < current_student->avarage_disciplines; j++) {
            My_Subject *current_subject = &current_student->num_of_subject[j];

            strncpy(current_subject->name_lessons, subjects[rand() % (sizeof(subjects) / sizeof(subjects[0]))], sizeof(current_subject->name_lessons) - 1);
            current_subject->name_lessons[sizeof(current_subject->name_lessons) - 1] = '\0';

            current_subject->audience_lecture = rand() % 255 + 1;
            current_subject->audience_labs = rand() % 255 + 1;
            current_subject->sum_hours = rand() % 255 + 1;
            current_subject->form = rand() % 3;
        }
    }
}

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
        My_Student *current_student = &student[i];
        printf("Студент: %s %s %s Группа: %s, Год рождения: %d\n",
               current_student->surname, current_student->name, current_student->patronymic,
               current_student->group, current_student->b_date);
        for (int j = 0; j < current_student->avarage_disciplines; j++) {
            My_Subject *current_subject = &current_student->num_of_subject[j];
            printf("Предмет %d: %s, Лекционная комната: %d, Лабораторная комната: %d, Часы: %d, Форма сдачи: %d\n",
                   j + 1, current_subject->name_lessons, current_subject->audience_lecture,
                   current_subject->audience_labs, current_subject->sum_hours, current_subject->form);
        }
        printf("\n");
    }
}

void size() {
    if (student == NULL) {
        printf("Ошибка: нет данных\n");
        return;
    }
    size_t total_size = N * sizeof(My_Student);
    for (int i = 0; i < N; i++) {
        My_Student *current_student = &student[i];
        total_size += current_student->avarage_disciplines * sizeof(My_Subject);
    }

    if (total_size < 1024) {
        printf("Size: %zu B\n", total_size);
    }
    else if (total_size < 1048576) {
        printf("Size: %.2f KB\n", total_size / 1024.0);
    }
    else if (total_size < 1073741824) {
        printf("Size: %.2f MB\n", total_size / 1048576.0);
    }
    else {
        printf("Size: %.2f GB\n", total_size / 1073741824.0);
    }
}

void clean() {
    if (student == NULL) {
        return;
    }
    for (int i = 0; i < N; i++) {
        My_Student *current_student = &student[i];
        free(current_student->num_of_subject);
    }
    free(student);
    student = NULL;
}

// Функция для проверки доступной памяти
int check_memory(int N) {
    size_t required_memory = N * sizeof(My_Student);
    for (int i = 0; i < N; i++) {
        int disciplines = rand() % (max_sub - min_sub + 1) + min_sub;
        required_memory += disciplines * sizeof(My_Subject);
    }

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    size_t free_memory = memInfo.ullAvailPhys;

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

    size_t free_memory = memInfo.ullAvailPhys;

    size_t min_student_size = sizeof(My_Student) + min_sub * sizeof(My_Subject);
    size_t max_student_size = sizeof(My_Student) + max_sub * sizeof(My_Subject);

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

    clean(); // Очистка памяти перед выходом
    return 0;
}
