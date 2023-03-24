/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define TODO(msg_const_str) printf("TODO:\t" msg_const_str "\n")
#include "employees.h"


#define CSV_FILE_MODE (S_IRUSR | S_IWUSR)

int
main(int argc, char **argv)
{
    int id_list;
    int employee_list;
    int shift_info;
    int log_fd;
    int employee_count;
    struct employee *employees;

    if ((log_fd = open("logfile.log", O_RDWR)) < 0) {
        if ((log_fd = open("logfile.log", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0) {
            return EXIT_FAILURE;
        }
    }


    /* open csv files */
    if ((id_list = open("id_list.csv", O_RDWR)) < 0) {
        dprintf(log_fd, "creating new id_list.csv\n");

        if ((id_list = open("id_list.csv", O_CREAT | O_RDWR, CSV_FILE_MODE)) < 0) {
            dprintf(log_fd, "failed to open id_list.csv:\t%s\n", strerror(errno));

            return EXIT_FAILURE;
        }
    }

    if ((employee_list = open("employee_list.csv", O_RDWR)) < 0) {
        dprintf(log_fd, "creating new employee_list.csv\n");

        if ((employee_list = open("employee_list.csv", O_CREAT | O_RDWR, CSV_FILE_MODE)) < 0) {
            dprintf(log_fd, "failed to open employee_list.csv:\t%s\n", strerror(errno));

            return EXIT_FAILURE;
        }
    }


    /* parse the employee csv file */
    employee_count = get_employees_info(&employees, employee_list);

    if (employee_count < 0) {
        dprintf(log_fd, "failed to read employees file\n");

        close(log_fd);
        return EXIT_FAILURE;
    }

    dprintf(log_fd, "current employee count: %d\n", employee_count);


    for (int i = 0; i < employee_count; ++i) {
        printf("employees[%d].name = %s\n", i, employees[i].name);
        printf("employees[%d].uid = %d\n", i, employees[i].uid);
    }

    delete_employees(&employees);

    close(employee_list);
    close(id_list);
    close(log_fd);

    return EXIT_SUCCESS;
}
