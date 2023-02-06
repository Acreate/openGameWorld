
#ifndef PROCESSPATH_EXPORT_H
#define PROCESSPATH_EXPORT_H

#ifdef PROCESSPATH_STATIC_DEFINE
#  define PROCESSPATH_EXPORT
#  define PROCESSPATH_NO_EXPORT
#else
#  ifndef PROCESSPATH_EXPORT
#    ifdef processPath_EXPORTS
        /* We are building this library */
#      define PROCESSPATH_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PROCESSPATH_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PROCESSPATH_NO_EXPORT
#    define PROCESSPATH_NO_EXPORT 
#  endif
#endif

#ifndef PROCESSPATH_DEPRECATED
#  define PROCESSPATH_DEPRECATED __declspec(deprecated)
#endif

#ifndef PROCESSPATH_DEPRECATED_EXPORT
#  define PROCESSPATH_DEPRECATED_EXPORT PROCESSPATH_EXPORT PROCESSPATH_DEPRECATED
#endif

#ifndef PROCESSPATH_DEPRECATED_NO_EXPORT
#  define PROCESSPATH_DEPRECATED_NO_EXPORT PROCESSPATH_NO_EXPORT PROCESSPATH_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PROCESSPATH_NO_DEPRECATED
#    define PROCESSPATH_NO_DEPRECATED
#  endif
#endif

#endif /* PROCESSPATH_EXPORT_H */
