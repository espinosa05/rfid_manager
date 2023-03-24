#include "employees.h"
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MEM_CHUNK_SIZE 0x80

ssize_t
get_employees_info(struct employee **employees, int csv_list_fd)
{
    off_t list_size;
    char *file_buf;
    char **data_sets;
    char *data_set_ptr;
    int data_set_count;
    int data_set_max_elements;


    list_size = lseek(csv_list_fd, 0, SEEK_END);
    lseek(csv_list_fd, 0, SEEK_SET);

    ERR_MSG_ASSERT();

    file_buf = malloc(list_size);

    if (read(csv_list_fd, file_buf, list_size) < 0) {
        free(file_buf);
        return -1;
    }

    data_set_max_elements = MEM_CHUNK_SIZE / sizeof(char *);
    data_sets = malloc(data_set_max_elements);

    data_set_ptr = strtok(file_buf, "\n");

    for (data_set_count = 0; data_set_ptr != NULL; ++data_set_count) {

        data_set_ptr = strtok(file_buf, "\n");
        /* the last element is set to NULL */
        data_sets[data_set_count] = data_set_ptr;
    }
    --data_set_count;
    *employees = malloc(sizeof(struct employee) * data_set_count);

    /* get each column entry of the tokenized rows */
    for (int i = 0; i < data_set_count; ++i) {
        *employees[i]->uid = strtok(data_sets[i], ",");
        ERR_MSG_ASSERT(*employees[i]->uid != NULL, "unexpected end of file");
        *employees[i]->name = strtok(data_sets[i], ",");
        ERR_MSG_ASSERT(*employees[i]->name != NULL, "unexpected end of file");
    }
}

void
delete_employees(struct employee **employees)
{

    free(*employees);
}
