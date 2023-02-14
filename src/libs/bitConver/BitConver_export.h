
#ifndef BITCONVER_EXPORT_H
#define BITCONVER_EXPORT_H

#ifdef BITCONVER_STATIC_DEFINE
#  define BITCONVER_EXPORT
#  define BITCONVER_NO_EXPORT
#else
#  ifndef BITCONVER_EXPORT
#    ifdef bitConver_EXPORTS
        /* We are building this library */
#      define BITCONVER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define BITCONVER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef BITCONVER_NO_EXPORT
#    define BITCONVER_NO_EXPORT 
#  endif
#endif

#ifndef BITCONVER_DEPRECATED
#  define BITCONVER_DEPRECATED __declspec(deprecated)
#endif

#ifndef BITCONVER_DEPRECATED_EXPORT
#  define BITCONVER_DEPRECATED_EXPORT BITCONVER_EXPORT BITCONVER_DEPRECATED
#endif

#ifndef BITCONVER_DEPRECATED_NO_EXPORT
#  define BITCONVER_DEPRECATED_NO_EXPORT BITCONVER_NO_EXPORT BITCONVER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BITCONVER_NO_DEPRECATED
#    define BITCONVER_NO_DEPRECATED
#  endif
#endif

#endif /* BITCONVER_EXPORT_H */
