#include "plist.h"

int main(void) {
    plist_manager_t *manager = plist_manager_new();
    plist_manager_prepare(manager);
    plist_manager_load(manager);
    plist_manager_modify(manager);
    plist_manager_free(manager);

    return 0;
}
