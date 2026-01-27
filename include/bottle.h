#ifndef LOOPOVER_BOTTLE_H
#define LOOPOVER_BOTTLE_H

constexpr int LOOPOVER_BOTTLE_PATH_MAX = 1024;
constexpr int LOOPOVER_BOTTLE_BUFFER_SIZE = LOOPOVER_BOTTLE_PATH_MAX << 2;
constexpr int LOOPOVER_BOTTLE_PASS_COUNT = 5;

constexpr char LOOPOVER_BOTTLE_LOOKUP[] = "[Software\\\\CodeWeavers\\\\CrossOver\\\\cxoffice]";

typedef bool (*bottle_modify_callback_t)(const char *path);

[[nodiscard]] bool bottle_modify(const char *path);

[[nodiscard]] bool bottle_list(bottle_modify_callback_t callback);

#endif
