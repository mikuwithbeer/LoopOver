#include "plist.h"

plist_manager_t *plist_manager_new(void) {
    plist_manager_t *manager = calloc(1, sizeof(plist_manager_t));
    return manager;
}

bool plist_manager_prepare(plist_manager_t *manager) {
    constexpr int PATH_MAX_SIZE = 1024;
    char raw_path[PATH_MAX_SIZE] = {};

    const auto home = getenv("HOME");
    if (home == nullptr) {
        return false;
    }

    snprintf(raw_path, PATH_MAX_SIZE, "%s/Library/Preferences/com.codeweavers.CrossOver.plist", home);

    const auto file_path = CFStringCreateWithCString(kCFAllocatorDefault, raw_path, kCFStringEncodingUTF8);
    const auto file_url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, file_path, kCFURLPOSIXPathStyle, false);

    manager->url = file_url;
    CFRelease(file_path);

    return true;
}

bool plist_manager_load(plist_manager_t *manager) {
    SInt32 error_code = 0;
    const bool status = CFURLCreateDataAndPropertiesFromResource(
        kCFAllocatorDefault,
        manager->url,
        &manager->resource,
        nullptr,
        nullptr,
        &error_code
    );

    if (!status || manager->resource == nullptr) {
        if (manager->url) {
            CFRelease(manager->url);
        }

        return false;
    }

    CFErrorRef error = nullptr;
    manager->properties = CFPropertyListCreateWithData(
        kCFAllocatorDefault,
        manager->resource,
        kCFPropertyListMutableContainersAndLeaves,
        nullptr,
        &error
    );

    if (error != nullptr) {
        return false;
    }

    return true;
}

void plist_manager_free(plist_manager_t *manager) {
    CFRelease(manager->resource);
    CFRelease(manager->properties);
    CFRelease(manager->url);

    free(manager);
}
