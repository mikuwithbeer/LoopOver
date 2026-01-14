#include "plist.h"

#define PREPARE_TEXT "Preparing the state..."
#define LOAD_TEXT "Loading the state..."
#define MODIFY_TEXT "Modifying the state..."

#define PREPARE_ERROR "Failed to prepare the state :("
#define LOAD_ERROR "Failed to load the state :("
#define MODIFY_ERROR "Failed to modify the state :("

#define SUCCESS_TEXT "Applied the patch successfully!"

#define RUN_SAFELY(callback, start_msg, error_msg) \
    do { \
        puts(start_msg); \
        if (callback(manager) == false) { \
            puts(error_msg); \
            plist_manager_free(manager); \
            return 1; \
        } \
    } while (0)

int main(void) {
    plist_manager_t *manager = plist_manager_new();

    RUN_SAFELY(plist_manager_prepare, PREPARE_TEXT, PREPARE_ERROR);
    RUN_SAFELY(plist_manager_load, LOAD_TEXT, LOAD_ERROR);
    RUN_SAFELY(plist_manager_modify, MODIFY_TEXT, MODIFY_ERROR);

    puts(SUCCESS_TEXT);
    plist_manager_free(manager);

    return 0;
}
