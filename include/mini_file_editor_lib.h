#ifndef MINI_FILE_EDITOR_LIB_H
#define MINI_FILE_EDITOR_LIB_H
#define MAX_LINE_LENGTH 1024

// Структура для представления строки текста
typedef struct Line {
    char text[MAX_LINE_LENGTH];
    struct Line* next;
    struct Line* prev;
} Line;

// Структура для представления редактора
typedef struct {
    Line* head;
    Line* tail;
    Line* cursor;
    int line_count;
} TextEditor;

// Прототипы функций
TextEditor* create_editor();
void free_editor(TextEditor* editor);
int insert_line(TextEditor* editor, const char* text, int position);
int delete_line(TextEditor* editor, int position);
void print_text(TextEditor* editor);
void save_to_file(TextEditor* editor, const char* filename);
int load_from_file(TextEditor* editor, const char* filename);

#endif
