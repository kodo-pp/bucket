#ifndef RAWIO_H
#define RAWIO_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bool enterRawMode(void);
bool exitRawMode(void);
void get_term_size(int *, int *);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* end of include guard: RAWIO_H */
