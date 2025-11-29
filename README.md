# mini_file_editor_lib


A minimalist library for managing text in files,
written as a small learning project to learn how to use "Cmake" and create static libraries.
and so that on the basis of this library I could write my own small text editors in my programs

## Use example
```c
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
```
