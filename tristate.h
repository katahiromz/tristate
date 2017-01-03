/* tristate.h --- tri-state logic by katahiromz
 * This file is public domain software (PDS).
 * Copyright (C) 2017 Katayama Hirofumi MZ.
 */
#ifndef TRISTATE_H_
#define TRISTATE_H_  11 /* Version 11 */

#if (defined(_MSC_VER) && _MSC_VER > 1000)
    #pragma once
#endif

/****************************************************************************/

#ifdef __cplusplus
    #include <cstring>          /* for strcmp and wcscmp */
    #include <cassert>          /* for assert */
#else
    #include <string.h>         /* for strcmp and wcscmp */
    #include <assert.h>         /* for assert */

    #ifndef __bool_true_false_are_defined
        #include <stdbool.h>    /* for bool, true, false */
    #endif
#endif

/****************************************************************************/
/* TRISTATE */

typedef enum TRISTATE
{
    TS_UNKNOWN = 0,     /* unknown value (default) */
    TS_FALSE = -1,      /* false value */
    TS_TRUE = 1         /* true value */
} TRISTATE, *PTRISTATE;

typedef const TRISTATE *PCTRISTATE;

/****************************************************************************/
/* TRISTATE functions */

#ifdef __cplusplus
extern "C" {
#endif

bool TS_is_valid(TRISTATE value);

TRISTATE    TS_from_bool(bool value);
void        TS_to_bool(TRISTATE value, bool *flag);

#ifdef __cplusplus
    TRISTATE TS_from_str(const char *str, bool *converted = NULL);
    TRISTATE TS_from_wstr(const wchar_t *str, bool *converted = NULL);
#else
    TRISTATE TS_from_str(const char *str, bool *converted);
    TRISTATE TS_from_wstr(const wchar_t *str, bool *converted);
#endif

const char *        TS_to_str(TRISTATE value);
const wchar_t *     TS_to_wstr(TRISTATE value);

TRISTATE TS_and(TRISTATE value1, TRISTATE value2);
TRISTATE TS_or (TRISTATE value1, TRISTATE value2);
TRISTATE TS_not(TRISTATE value);

#if defined(UNICODE) || defined(_UNICODE)
    #define TS_from_tstr    TS_from_wstr
    #define TS_to_tstr      TS_to_wstr
#else
    #define TS_from_tstr    TS_from_str
    #define TS_to_tstr      TS_to_str
#endif

void TS_get_totality(bool *value, size_t num, const bool *values);
void TS_set_totality(bool  value, size_t num,       bool *values);

void TS_get_tri_totality(TRISTATE *value, size_t num, const bool *values);
void TS_set_tri_totality(TRISTATE  value, size_t num,       bool *values);

void TS_get_totality_tri(bool *value, size_t num, const TRISTATE *values);
void TS_set_totality_tri(bool  value, size_t num,       TRISTATE *values);
#define TS_reset_totality_tri TS_set_totality_tri

void
TS_get_tri_totality_tri(TRISTATE * value, size_t num, const TRISTATE *values);
void
TS_set_tri_totality_tri(TRISTATE   value, size_t num,       TRISTATE *values);
void
TS_reset_tri_totality_tri(TRISTATE value, size_t num,       TRISTATE *values);

void TS_each_and(TRISTATE value, size_t num, TRISTATE *values);
void TS_each_or (TRISTATE value, size_t num, TRISTATE *values);
void TS_each_not(                size_t num, TRISTATE *values);

TRISTATE TS_connect_and(size_t num, TRISTATE *values);
TRISTATE TS_connect_or (size_t num, TRISTATE *values);

#ifdef __cplusplus
} // extern "C"
#endif

/****************************************************************************/
/* inline functions */

#ifndef TRISTATE_NO_INLINING
    #undef TRISTATE_INLINE
    #define TRISTATE_INLINE     inline
    #include "tristate_inl.h"
#endif

/****************************************************************************/

#endif  /* ndef TRISTATE_H_ */

/****************************************************************************/
