
#ifndef PROCESSARGS_EXPORT_H
#define PROCESSARGS_EXPORT_H

#ifdef PROCESSARGS_STATIC_DEFINE
#  define PROCESSARGS_EXPORT
#  define PROCESSARGS_NO_EXPORT
#else
#  ifndef PROCESSARGS_EXPORT
#    ifdef processArgs_EXPORTS
        /* We are building this library */
#      define PROCESSARGS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PROCESSARGS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PROCESSARGS_NO_EXPORT
#    define PROCESSARGS_NO_EXPORT 
#  endif
#endif

#ifndef PROCESSARGS_DEPRECATED
#  define PROCESSARGS_DEPRECATED __declspec(deprecated)
#endif

#ifndef PROCESSARGS_DEPRECATED_EXPORT
#  define PROCESSARGS_DEPRECATED_EXPORT PROCESSARGS_EXPORT PROCESSARGS_DEPRECATED
#endif

#ifndef PROCESSARGS_DEPRECATED_NO_EXPORT
#  define PROCESSARGS_DEPRECATED_NO_EXPORT PROCESSARGS_NO_EXPORT PROCESSARGS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PROCESSARGS_NO_DEPRECATED
#    define PROCESSARGS_NO_DEPRECATED
#  endif
#endif

#endif /* PROCESSARGS_EXPORT_H */
