#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <sys/types.h>
#include <fcntl.h>

#define UID_LENGTH 10

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 256
#endif /* MAX_NAME_LENGTH */

struct employee {
    long int uid;
    char name[MAX_NAME_LENGTH];
};

ssize_t get_employees_info(struct employee **employees, int csv_list_fd);
void delete_employees(struct employee **employees);

#endif /* EMPLOYEES_H */
