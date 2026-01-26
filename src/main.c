#include "plist.h"
#include "main.h"
#include "bottle.h"

static bool execute_step(bool callback, const char *info, const char *error);

int main(void) {
    if (!get_confirmation()) return 0;

    plist_manager_t *manager = plist_manager_new();
    const auto result = execute_step(plist_manager_prepare(manager), LOOPOVER_PREPARE_TEXT, LOOPOVER_PREPARE_ERROR) &&
                        execute_step(plist_manager_load(manager), LOOPOVER_LOAD_TEXT, LOOPOVER_LOAD_ERROR) &&
                        execute_step(plist_manager_modify(manager), LOOPOVER_MODIFY_TEXT, LOOPOVER_MODIFY_ERROR);

    plist_manager_free(manager);
    if (!result) return 1;

    puts(LOOPOVER_SUCCESS_TEXT);

    if (!bottle_list(handle_modify)) {
        puts(LOOPOVER_BOTTLE_ERROR);
        return 1;
    }

    puts(LOOPOVER_SUCCESS_BOTTLE);
    return 0;
}

[[nodiscard]] bool get_confirmation(void) {
    puts("Please close the application if running.");
    puts("This tool will modify application files.");
    puts("Are you sure you want to proceed? [y/n]");

    char answer;
    scanf("%c", &answer);

    return answer == 'y' || answer == 'Y';
}

[[nodiscard]] bool handle_modify(const char *path) {
    printf("Patching %s...\n", path);
    return bottle_modify(path);
}

static bool execute_step(const bool callback, const char *info, const char *error) {
    puts(info);

    if (!callback) {
        puts(error);
    }

    return callback;
}
