#include "bottle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

bool bottle_modify(const char *path) {
    const auto file = fopen(path, "r");
    if (file == nullptr) return false;

    char temp_path[LOOPOVER_BOTTLE_PATH_MAX] = {};
    snprintf(temp_path, sizeof(temp_path), "%s.tmp", path);

    const auto temp_file = fopen(temp_path, "w");
    if (temp_file == nullptr) {
        fclose(file);
        return false;
    }

    auto line_found = false;
    auto skip_lines = 0;

    char buffer[LOOPOVER_BOTTLE_BUFFER_SIZE] = {};
    while (fgets(buffer, LOOPOVER_BOTTLE_BUFFER_SIZE, file)) {
        if (skip_lines > 0) [[clang::unlikely]] {
            skip_lines--;
            continue;
        }

        const auto result = strstr(buffer, LOOPOVER_BOTTLE_LOOKUP);
        if (result != nullptr) [[clang::unlikely]] {
            skip_lines = LOOPOVER_BOTTLE_PASS_COUNT;
            line_found = true;
            continue;
        }

        fputs(buffer, temp_file);
    }

    fclose(file);

    const bool flush_result = fflush(temp_file) != 0;
    fclose(temp_file);

    if (flush_result) return false;

    if (line_found) {
        if (rename(temp_path, path) != 0) return false;
    } else {
        remove(temp_path);
    }

    return true;
}

bool bottle_list(const bottle_modify_callback_t callback) {
    const auto home = getenv("HOME");
    if (home == nullptr) return false;

    char bottles_path[LOOPOVER_BOTTLE_PATH_MAX] = {};
    snprintf(bottles_path, LOOPOVER_BOTTLE_PATH_MAX, "%s/Library/Application Support/CrossOver/Bottles", home);

    const auto dir = opendir(bottles_path);
    if (dir == nullptr) return false;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') continue;

        char reg_path[LOOPOVER_BOTTLE_PATH_MAX] = {};
        snprintf(reg_path, LOOPOVER_BOTTLE_PATH_MAX, "%s/%s/system.reg", bottles_path, entry->d_name);

        if (!callback(reg_path)) {
            closedir(dir);
            return false;
        }
    }

    closedir(dir);
    return true;
}
