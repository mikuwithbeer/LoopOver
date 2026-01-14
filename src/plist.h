#ifndef LOOPOVER_FILE_H
#define LOOPOVER_FILE_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct {
    CFURLRef url;
    CFTypeRef properties;
    CFDataRef resource;
} plist_manager_t;

plist_manager_t *plist_manager_new(void);

bool plist_manager_prepare(plist_manager_t *manager);

bool plist_manager_load(plist_manager_t *manager);

void plist_manager_free(plist_manager_t *manager);

#endif //LOOPOVER_FILE_H
