#include "bottle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

constexpr int PATH_MAX = 1024;
constexpr int BUFFER_SIZE = PATH_MAX * 4;
constexpr int LINES_TO_REMOVE = 5;

constexpr char TARGET_PREFIX[] = "[Software\\\\CodeWeavers\\\\CrossOver\\\\cxoffice]";

bool bottle_modify(const char *path) {
    const auto file = fopen(path, "r");
    if (file == nullptr) return false;

    char temp_path[PATH_MAX];
    snprintf(temp_path, sizeof(temp_path), "%s.tmp", path);

    const auto temp_file = fopen(temp_path, "w");
    if (temp_file == nullptr) {
        fclose(file);
        return false;
    }

    auto line_found = false;
    auto skip_lines = 0;

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        if (skip_lines > 0) {
            skip_lines--;
            continue;
        }

        const auto result = strstr(buffer, TARGET_PREFIX);
        if (result != nullptr) {
            skip_lines = LINES_TO_REMOVE;
            line_found = true;

            continue;
        }

        fputs(buffer, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    if (line_found) {
        if (remove(path) != 0) return false;
        if (rename(temp_path, path) != 0) return false;
    } else {
        remove(temp_path);
    }

    return true;
}

bool bottle_list(const bottle_modify_callback_t callback) {
    const auto home = getenv("HOME");
    if (home == nullptr) return false;

    char bottles_path[PATH_MAX] = {};
    snprintf(bottles_path, sizeof(bottles_path), "%s/Library/Application Support/CrossOver/Bottles", home);

    const auto dir = opendir(bottles_path);
    if (dir == nullptr) return false;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') continue;

        char reg_path[PATH_MAX] = {};
        snprintf(reg_path, sizeof(reg_path), "%s/%s/system.reg", bottles_path, entry->d_name);

        if (!callback(reg_path)) {
            closedir(dir);
            return false;
        }
    }

    closedir(dir);
    return true;
}
