
#ifndef TYPESQL_EXPORT_H
#define TYPESQL_EXPORT_H

#ifdef TYPESQL_STATIC_DEFINE
#  define TYPESQL_EXPORT
#  define TYPESQL_NO_EXPORT
#else
#  ifndef TYPESQL_EXPORT
#    ifdef typeSql_EXPORTS
        /* We are building this library */
#      define TYPESQL_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define TYPESQL_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef TYPESQL_NO_EXPORT
#    define TYPESQL_NO_EXPORT 
#  endif
#endif

#ifndef TYPESQL_DEPRECATED
#  define TYPESQL_DEPRECATED __declspec(deprecated)
#endif

#ifndef TYPESQL_DEPRECATED_EXPORT
#  define TYPESQL_DEPRECATED_EXPORT TYPESQL_EXPORT TYPESQL_DEPRECATED
#endif

#ifndef TYPESQL_DEPRECATED_NO_EXPORT
#  define TYPESQL_DEPRECATED_NO_EXPORT TYPESQL_NO_EXPORT TYPESQL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TYPESQL_NO_DEPRECATED
#    define TYPESQL_NO_DEPRECATED
#  endif
#endif

#endif /* TYPESQL_EXPORT_H */
