#ifndef MINI_FILE_EDITOR_LIB_H
#define MINI_FILE_EDITOR_LIB_H
#define MAX_LINE_LENGTH 1024

typedef struct Line {
    char text[MAX_LINE_LENGTH];
    struct Line* next;
    struct Line* prev;
} Line;

typedef struct {
    Line* head;
    Line* tail;
    Line* cursor;
    int line_count;
} TextEditor;

TextEditor* create_editor();
void free_editor(TextEditor* editor);
int insert_line(TextEditor* editor, const char* text, int position);
int delete_line(TextEditor* editor, int position);
void print_text(TextEditor* editor);
void save_to_file(TextEditor* editor, const char* filename);
int load_from_file(TextEditor* editor, const char* filename);

#endif
