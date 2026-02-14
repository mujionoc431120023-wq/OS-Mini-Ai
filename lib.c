/* Stub implementations for kernel */
#include <stddef.h>
#include <stdint.h>

void *malloc(size_t size) {
    static char heap[16384];
    static size_t pos = 0;
    if (pos + size > sizeof(heap)) return NULL;
    void *p = &heap[pos];
    pos += size;
    return p;
}

void *calloc(size_t n, size_t size) {
    void *p = malloc(n * size);
    if (p) {
        char *cp = p;
        for (size_t i = 0; i < n * size; i++) cp[i] = 0;
    }
    return p;
}

void free(void *p) { (void)p; }

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < n; i++) d[i] = s[i];
    return dest;
}

void *__memcpy_chk(void *dest, const void *src, size_t n, size_t objsize) {
    return memcpy(dest, src, n);
}

void *memset(void *s, int c, size_t n) {
    char *p = s;
    for (size_t i = 0; i < n; i++) p[i] = c;
    return s;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return *s1 - *s2;
        s1++; s2++;
    }
    return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (!s1[i] || s1[i] != s2[i]) return s1[i] - s2[i];
    }
    return 0;
}

char *strcpy(char *dest, const char *src) {
    char *d = dest;
    while (*src) { *d++ = *src++; }
    *d = 0;
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    while (i < n && src[i]) { dest[i] = src[i]; i++; }
    while (i < n) { dest[i++] = 0; }
    return dest;
}

size_t strlen(const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

int abs(int x) { return x < 0 ? -x : x; }

void *memmove(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    if (d < s) {
        for (size_t i = 0; i < n; i++) d[i] = s[i];
    } else {
        for (size_t i = n; i > 0; i--) d[i-1] = s[i-1];
    }
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const char *a = s1, *b = s2;
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }
    return 0;
}

void *memchr(const void *s, int c, size_t n) {
    const char *p = s;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == c) return (void*)(p + i);
    }
    return NULL;
}

char *strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d) d++;
    while (*src) *d++ = *src++;
    *d = 0;
    return dest;
}

char *strchr(const char *s, int c) {
    while (*s) {
        if (*s == c) return (char*)s;
        s++;
    }
    return NULL;
}

char *strrchr(const char *s, int c) {
    const char *found = NULL;
    while (*s) {
        if (*s == c) found = s;
        s++;
    }
    return (char*)found;
}

char *strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    while (*haystack) {
        const char *h = haystack, *n = needle;
        while (*h && *n && *h == *n) { h++; n++; }
        if (!*n) return (char*)haystack;
        haystack++;
    }
    return NULL;
}

size_t strspn(const char *s, const char *accept) {
    size_t n = 0;
    while (*s && strchr(accept, *s)) { s++; n++; }
    return n;
}

size_t strcspn(const char *s, const char *reject) {
    size_t n = 0;
    while (*s && !strchr(reject, *s)) { s++; n++; }
    return n;
}

char *strpbrk(const char *s, const char *breakset) {
    while (*s) {
        if (strchr(breakset, *s)) return (char*)s;
        s++;
    }
    return NULL;
}

char *strtok_r(char *s, const char *delim, char **saveptr) {
    if (!s) s = *saveptr;
    if (!s) return NULL;
    s += strspn(s, delim);
    if (!*s) { *saveptr = NULL; return NULL; }
    char *token = s;
    s += strcspn(s, delim);
    if (*s) { *s = 0; *saveptr = s + 1; }
    else { *saveptr = NULL; }
    return token;
}

