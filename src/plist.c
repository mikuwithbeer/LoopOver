#include "plist.h"

plist_manager_t *plist_manager_new(void) {
    return calloc(1, sizeof(plist_manager_t));
}

bool plist_manager_prepare(plist_manager_t *manager) {
    const auto home = getenv("HOME");
    if (home == nullptr) return false;

    char raw_path[PATH_MAX] = {};
    snprintf(raw_path, PATH_MAX, "%s/Library/Preferences/com.codeweavers.CrossOver.plist", home);

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

    if (!status || manager->resource == nullptr) return false;

    CFErrorRef error = nullptr;
    manager->properties = CFPropertyListCreateWithData(
        kCFAllocatorDefault,
        manager->resource,
        kCFPropertyListMutableContainersAndLeaves,
        nullptr,
        &error
    );

    return error == nullptr;
}

bool plist_manager_modify(const plist_manager_t *manager) {
    const auto yesterday = CFAbsoluteTimeGetCurrent() - 86'400.0;
    const auto key = CFSTR("FirstRunDate");

    const auto today = CFDateCreate(nullptr, yesterday);
    if (today == nullptr) return false;

    CFDictionarySetValue(manager->properties, key, today);
    CFRelease(today);

    CFErrorRef error = nullptr;
    const auto output = CFPropertyListCreateData(
        kCFAllocatorDefault,
        manager->properties,
        kCFPropertyListXMLFormat_v1_0,
        0,
        &error
    );

    if (output == nullptr) {
        if (error != nullptr) CFRelease(error);
        return false;
    }

    SInt32 error_code = 0;
    const bool status = CFURLWriteDataAndPropertiesToResource(
        manager->url,
        output,
        nullptr,
        &error_code
    );

    CFRelease(output);
    return status;
}

void plist_manager_free(plist_manager_t *manager) {
    if (manager == nullptr) [[clang::unlikely]] return;

    if (manager->resource != nullptr) CFRelease(manager->resource);
    if (manager->properties != nullptr) CFRelease(manager->properties);
    if (manager->url != nullptr) CFRelease(manager->url);

    free(manager);
}
