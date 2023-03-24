#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>

#define ERR_MSG_ASSERT(cond, msg)                           \
    if (!(cond)) {                                          \
        dprintf(STDERR_FILENO, "assertion failed: %s\n"     \
                "error message: %s\n", #cond, msg);         \
        }


#endif /* UTILS_H */
