#include "employees.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

#define MEM_CHUNK_SIZE 0x100

static void
assign_data_set(struct employee *employee, char *data_set)
{
    char *uid_token;
    char *name_token;
    uid_token = strtok(data_set, ",");
    name_token = strtok(NULL, ",");

    strncpy(employee->name, name_token, sizeof(employee->name) - 1);
    employee->uid = strtol(uid_token, NULL, 10);
}

ssize_t
get_employees_info(struct employee **employees, int csv_list_fd)
{
    off_t list_size;
    char *file_buf;
    char **data_sets;
    char *data_set_ptr;
    int data_set_count;
    int data_set_max_elements;

    struct employee *employees_tmp_buf;

    list_size = lseek(csv_list_fd, 0, SEEK_END);
    lseek(csv_list_fd, 0, SEEK_SET);


    file_buf = malloc(list_size + 1);

    if (read(csv_list_fd, file_buf, list_size) < 0) {
        free(file_buf);
        return -1;
    }

    file_buf[list_size] = 0x00;

    data_set_max_elements = MEM_CHUNK_SIZE / sizeof(char *);
    data_sets = malloc(data_set_max_elements * sizeof(char *));

    data_set_ptr = strtok(file_buf, "\n");
    data_sets[0] = data_set_ptr;

    for (data_set_count = 1; data_set_ptr != NULL; ++data_set_count) {
        data_set_ptr = strtok(NULL, "\n");
        data_sets[data_set_count] = data_set_ptr;
    }
    data_set_count--;

    employees_tmp_buf = malloc(sizeof(struct employee) * data_set_count);

    memset(employees_tmp_buf, 0, sizeof(struct employee) * data_set_count);

    /* get each column entry of the tokenized rows */
    for (int i = 0; i < data_set_count; ++i) {
        assign_data_set(&employees_tmp_buf[i], data_sets[i]);
    }

    free(file_buf);

    *employees = employees_tmp_buf;

    return data_set_count;
}

void
delete_employees(struct employee **employees)
{

    free(*employees);
}
