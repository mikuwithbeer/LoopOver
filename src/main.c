#include "plist.h"
#include "bottle.h"

#define PREPARE_TEXT "Preparing the state..."
#define LOAD_TEXT "Loading the state..."
#define MODIFY_TEXT "Modifying the state..."

#define PREPARE_ERROR "Failed to prepare the state :("
#define LOAD_ERROR "Failed to load the state :("
#define MODIFY_ERROR "Failed to modify the state :("

#define SUCCESS_TEXT "Modified the state successfully!"

#define SUCCESS_BOTTLE "Patched the bottles successfully!"
#define BOTTLE_ERROR "Failed patching the bottle :("

#define RUN_SAFELY(callback, start_msg, error_msg) \
    do { \
        puts(start_msg); \
        if (callback(manager) == false) { \
            puts(error_msg); \
            plist_manager_free(manager); \
            return 1; \
        } \
    } while (0)

bool warn_user(void) {
    puts("Please close the application if running.");
    puts("This tool will modify application files.");
    puts("Are you sure you want to proceed? [y/n]");

    char answer;
    scanf("%c", &answer);

    return answer == 'y' || answer == 'Y';
}

bool modify_handler(const char *path) {
    printf("Patching %s...\n", path);
    return bottle_modify(path);
}

int main(void) {
    if (warn_user() == false) {
        return 0;
    }

    plist_manager_t *manager = plist_manager_new();

    RUN_SAFELY(plist_manager_prepare, PREPARE_TEXT, PREPARE_ERROR);
    RUN_SAFELY(plist_manager_load, LOAD_TEXT, LOAD_ERROR);
    RUN_SAFELY(plist_manager_modify, MODIFY_TEXT, MODIFY_ERROR);

    puts(SUCCESS_TEXT);
    plist_manager_free(manager);

    if (bottle_list(modify_handler)) {
        puts(SUCCESS_BOTTLE);
    } else {
        puts(BOTTLE_ERROR);
    }

    return 0;
}
