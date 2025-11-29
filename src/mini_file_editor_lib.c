#include "mini_file_editor_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create new editor
TextEditor* create_editor() {
    TextEditor* editor = (TextEditor*)malloc(sizeof(TextEditor));
    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;
    editor->line_count = 0;
    return editor;
}

// free editor memory
void free_editor(TextEditor* editor) {
    Line* current = editor->head;
    while (current != NULL) {
        Line* next = current->next;
        free(current);
        current = next;
    }
    free(editor);
}

// paste text to each position 
int insert_line(TextEditor* editor, const char* text, int position) {
    if (position < 0 || position > editor->line_count) {
        return -1; // not valied position
    }

    Line* new_line = (Line*)malloc(sizeof(Line));
    strncpy(new_line->text, text, MAX_LINE_LENGTH);
    new_line->text[MAX_LINE_LENGTH - 1] = '\0';

    if (editor->line_count == 0) {
        // first string
        new_line->next = NULL;
        new_line->prev = NULL;
        editor->head = new_line;
        editor->tail = new_line;
    } else if (position == 0) {
        // paste to start
        new_line->next = editor->head;
        new_line->prev = NULL;
        editor->head->prev = new_line;
        editor->head = new_line;
    } else if (position == editor->line_count) {
        // paste to end
        new_line->next = NULL;
        new_line->prev = editor->tail;
        editor->tail->next = new_line;
        editor->tail = new_line;
    } else {
        // paste in middle
        Line* current = editor->head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        new_line->next = current;
        new_line->prev = current->prev;
        current->prev->next = new_line;
        current->prev = new_line;
    }

    editor->line_count++;
    return 0;
}

// remove string in position 
int delete_line(TextEditor* editor, int position) {
    if (position < 0 || position >= editor->line_count) {
        return -1; // not valied position
    }

    Line* to_delete;

    if (position == 0) {
        // remove remove first string
        to_delete = editor->head;
        editor->head = to_delete->next;
        if (editor->head != NULL) {
            editor->head->prev = NULL;
        } else {
            editor->tail = NULL;
        }
    } else if (position == editor->line_count - 1) {
        // remove end string
        to_delete = editor->tail;
        editor->tail = to_delete->prev;
        editor->tail->next = NULL;
    } else {
        // remove middle string 
        to_delete = editor->head;
        for (int i = 0; i < position; i++) {
            to_delete = to_delete->next;
        }
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
    }

    free(to_delete);
    editor->line_count--;
    return 0;
}

// print all text
void print_text(TextEditor* editor) {
    Line* current = editor->head;
    int line_num = 1;
    while (current != NULL) {
        printf("%d: %s\n", line_num++, current->text);
        current = current->next;
    }
}

// save to file
void save_to_file(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error open file");
        return;
    }

    Line* current = editor->head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->text);
        current = current->next;
    }

    fclose(file);
    printf("text saved to  %s\n", filename);
}

// load from file 
int load_from_file(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error open file");
        return -1;
    }
    
    // clear current contnet
    Line* current = editor->head;
    while (current != NULL) {
        Line* next = current->next;
        free(current);
        current = next;
    }
    editor->head = NULL;
    editor->tail = NULL;
    editor->line_count = 0;

    // read from file
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        // remove new string symbol
        buffer[strcspn(buffer, "\n")] = '\0';
        insert_line(editor, buffer, editor->line_count);
    }

    fclose(file);
    printf("Text loaded from %s\n", filename);
    return 0;
}

// use example main.c
/*
#include "editor.h"

int main() {
    TextEditor* editor = create_editor();
    
    insert_line(editor, "first string", 0);
    insert_line(editor, "second string", 1);
    insert_line(editor, "new string between string", 1);
    
    printf("text after paste:\n");
    print_text(editor);
    
    delete_line(editor, 0);
    printf("\nafter delete first string:\n");
    print_text(editor);
    
    save_to_file(editor, "text.txt");
    load_from_file(editor, "text.txt");
    
    free_editor(editor);
    return 0;
}
*/
