#pragma once

#include "ThirdParty/hedley.h"

#ifdef HEDLEY_MSVC_VERSION
#include <Windows.h>
#include <processthreadsapi.h>
#include <string>


inline void *platform_thread_self() {
    return GetCurrentThread();
}

inline void platform_set_thread_name(void *platform_thread_self, const char *name) {
    size_t len = strlen(name);
    std::wstring wst(len + 1, '#');
    size_t num_convert;
    mbstowcs_s(&num_convert, &wst[0], len + 1, name, len + 1);
    SetThreadDescription(platform_thread_self, &wst[0]);
}

inline void platform_get_thread_name(void *platform_thread_self, char *buf, size_t bufsize) {
    wchar_t *wbuf;
    GetThreadDescription(platform_thread_self, &wbuf);
    size_t num_convert;
    wcstombs_s(&num_convert, buf, bufsize, wbuf, bufsize);
    LocalFree(wbuf);
}

#else
#ifdef HEDLEY_GNUC_VERSION
#include <thread>

inline auto platform_thread_self() {
    return pthread_self();
}

inline void platform_set_thread_name(decltype(platform_thread_self()) id, const char *name) {
    pthread_setname_np(id, name);
}

inline void platform_get_thread_name(decltype(platform_thread_self()) id, char *buf, size_t bufsize) {
    pthread_getname_np(id, buf, bufsize);
}
#endif
#endif

