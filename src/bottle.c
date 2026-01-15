#include "bottle.h"

#include <sys/syslimits.h>


bool bottle_modify(const char *path) {
    return true;
}

bool bottle_list(const bottle_modify_callback_t callback) {
    const char *home = getenv("HOME");
    if (home == nullptr) {
        return false;
    }

    char bottles_path[PATH_MAX];
    snprintf(bottles_path, sizeof(bottles_path), "%s/Library/Application Support/CrossOver/Bottles", home);

    DIR *dir = opendir(bottles_path);
    if (dir == nullptr) {
        return false;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (entry->d_name[0] == '.') {
            continue;
        }

        char reg_path[PATH_MAX];
        snprintf(reg_path, sizeof(reg_path), "%s/%s/system.reg", bottles_path, entry->d_name);

        callback(reg_path);
    }

    closedir(dir);
    return true;
}
