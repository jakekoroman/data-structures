#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
	char *data;
	size_t size;
    
	char *gap_start;
	char *gap_end;
	size_t gap_size;
    int unsigned cursor;
} Buffer;

#define BUFFER_CAP 1024
#define GAP_CAP 4

void
grow_buffer(Buffer *buffer)
{
    assert(buffer->gap_end == buffer->gap_start);
    assert(buffer->size + buffer->gap_size <= BUFFER_CAP);
    for (int i = buffer->size - 1;
         i >= buffer->cursor - 1;
         --i)
    {
        int idx = i + (buffer->gap_size);
        buffer->data[idx] = buffer->data[i];
    }
    
    buffer->gap_end += buffer->gap_size;
}

void
insert_char(Buffer *buffer, char ch)
{
    // make sure there is room in the gap
    if (buffer->gap_start == buffer->gap_end)
    {
        grow_buffer(buffer);
    }
    *buffer->gap_start++ = ch;
    buffer->size++;
    buffer->cursor++;
}

void
visualize_gap(Buffer *buffer, int gap_size)
{
    int n = buffer->size + gap_size;
    char result[n];
    for (int i = 0;
         i < n;
         ++i)
    {
        if (&buffer->data[i] >= buffer->gap_start && &buffer->data[i] < buffer->gap_end)
        {
            result[i] = '*';
        }
        else
        {
            result[i] = buffer->data[i];
        }
    }
    result[n] = '\0';
    printf("%s\n", result);
}

void
move_gap_to_cursor(Buffer *buffer)
{
    // NOTE(jake): when moving to the left
    if (&buffer->data[buffer->cursor - 1] < buffer->gap_start)
    {
        while (&buffer->data[buffer->cursor - 1] != buffer->gap_start)
        {
            buffer->gap_end--;
            *buffer->gap_end = *(buffer->gap_start - 1);
            buffer->gap_start--;
        }
    }
    // NOTE(jake): when moving to the right
    else
    {
        while (&buffer->data[buffer->cursor - 1] != buffer->gap_start)
        {
            *buffer->gap_start++ = *buffer->gap_end++;
        }
    }
}

void
backspace_buffer(Buffer *buffer)
{
    assert(buffer->gap_start - 1 >= buffer->data);
    buffer->gap_start--;
    buffer->size--;
    buffer->cursor--;
}

void
print_buffer(Buffer *buffer)
{
    printf("buffer->data      -> %p : %s\n"
           "buffer->gap_start -> %p\n"
           "buffer->gap_end   -> %p\n"
           "buffer->size      -> %ld\n"
           "buffer->cursor    -> %d\n",
           buffer->data, buffer->data, buffer->gap_start, buffer->gap_end, buffer->size, buffer->cursor);
    
    int gap_size = buffer->gap_end - buffer->gap_start;
    visualize_gap(buffer, gap_size);
    printf("-----------------------\n");
}

int
main(int argc, char **argv)
{
	Buffer buffer = {0};
	buffer.data = malloc(sizeof(char) * BUFFER_CAP);
    buffer.cursor = 1;
    assert(buffer.data);
    
    buffer.gap_size = GAP_CAP;
    buffer.gap_start = buffer.data;
    buffer.gap_end = buffer.data + buffer.gap_size;
    
    print_buffer(&buffer);
    
    insert_char(&buffer, 'a');
    insert_char(&buffer, 'b');
    insert_char(&buffer, 'c');
    insert_char(&buffer, 'd');
    
    print_buffer(&buffer);
    
    insert_char(&buffer, 'e');
    
    print_buffer(&buffer);
    
    buffer.cursor = 1;
    // NOTE(jake): gap should only be moved when inserting or deleting
    move_gap_to_cursor(&buffer);
    print_buffer(&buffer);
    
    insert_char(&buffer, 'f');
    print_buffer(&buffer);
    
    buffer.cursor += 3;
    move_gap_to_cursor(&buffer);
    insert_char(&buffer, 'g');
    insert_char(&buffer, 'h');
    insert_char(&buffer, 'i');
    insert_char(&buffer, 'j');
    print_buffer(&buffer);
    
    backspace_buffer(&buffer);
    backspace_buffer(&buffer);
    backspace_buffer(&buffer);
    backspace_buffer(&buffer);
    print_buffer(&buffer);
    
    buffer.cursor = buffer.size + 1;
    move_gap_to_cursor(&buffer);
    print_buffer(&buffer);
    
    buffer.cursor--;
    move_gap_to_cursor(&buffer);
    print_buffer(&buffer);
    
    free(buffer.data);
    return 0;
}
