#ifndef UTIL_H
#define UTIL_H


#if DEBUG_LEVEL >= 1 
#define dprintf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define dprintf(...)
#endif

#if DEBUG_LEVEL >= 2 
#define d2printf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define d2printf(...)
#endif

#if DEBUG_LEVEL >= 3 
#define d3printf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define d3printf(...)
#endif

#if DEBUG_LEVEL >= 4 
#define d4printf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define d4printf(...)
#endif

#if DEBUG_LEVEL >= 5
#define d5printf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define d5printf(...)
#endif


#endif
