#ifndef LOOPOVER_BOTTLE_H
#define LOOPOVER_BOTTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef bool (*bottle_modify_callback_t)(const char *path);

bool bottle_modify(const char *path);

bool bottle_list(bottle_modify_callback_t callback);

#endif //LOOPOVER_BOTTLE_H
