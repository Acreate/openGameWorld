
#ifndef TYPEFILE_EXPORT_H
#define TYPEFILE_EXPORT_H

#ifdef TYPEFILE_STATIC_DEFINE
#  define TYPEFILE_EXPORT
#  define TYPEFILE_NO_EXPORT
#else
#  ifndef TYPEFILE_EXPORT
#    ifdef typeFile_EXPORTS
        /* We are building this library */
#      define TYPEFILE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define TYPEFILE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef TYPEFILE_NO_EXPORT
#    define TYPEFILE_NO_EXPORT 
#  endif
#endif

#ifndef TYPEFILE_DEPRECATED
#  define TYPEFILE_DEPRECATED __declspec(deprecated)
#endif

#ifndef TYPEFILE_DEPRECATED_EXPORT
#  define TYPEFILE_DEPRECATED_EXPORT TYPEFILE_EXPORT TYPEFILE_DEPRECATED
#endif

#ifndef TYPEFILE_DEPRECATED_NO_EXPORT
#  define TYPEFILE_DEPRECATED_NO_EXPORT TYPEFILE_NO_EXPORT TYPEFILE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TYPEFILE_NO_DEPRECATED
#    define TYPEFILE_NO_DEPRECATED
#  endif
#endif

#endif /* TYPEFILE_EXPORT_H */
