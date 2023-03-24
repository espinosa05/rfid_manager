# rfid employee manager

this software is intended to be used as a tool for managing employees' workhours<br>
with an rfid scanner.<br>
Everytime an unknown id is scanned an email is sent to the administrator and he can choose to add the id<br>
by appending it to the employees.csv file with the name of the new owner of the rfid chip.<br>
If an employee is to be deleted, the line containing his name has to be removed from the employees.csv file

# basic overview (API)

```c
ERR_MSG_ASSERT(cond, msg)
```
&nbsp;&nbsp;is a macro that checks for a condition and throws an error if the condition is not met
```c
ssize_t get_employee_info(struct employee **employees, int csv_file);
```

parses the employee.csv file and packages the information into the struct employee array.<br>
```c
struct employee {<br>
char *uid;
char *msg;
}<br>
```

