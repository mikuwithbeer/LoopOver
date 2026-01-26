#ifndef LOOPOVER_BOTTLE_H
#define LOOPOVER_BOTTLE_H

typedef bool (*bottle_modify_callback_t)(const char *path);

[[nodiscard]] bool bottle_modify(const char *path);

[[nodiscard]] bool bottle_list(bottle_modify_callback_t callback);

#endif
