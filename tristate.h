/* tristate.h --- tri-state logic by katahiromz
 * This file is public domain software (PDS).
 * Copyright (C) 2017 Katayama Hirofumi MZ.
 */
#ifndef TRISTATE_H_
#define TRISTATE_H_  19     /* Version 19 */

#if (defined(_MSC_VER) && _MSC_VER > 1000)
    #pragma once
#endif

/****************************************************************************/

#ifdef __cplusplus
    #include <cstring>          /* for strcmp and wcscmp */
    #include <cassert>          /* for assert */
    using std::size_t;
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

bool TS_is_valid_bool(bool value);
bool TS_is_valid_tri(TRISTATE value);

TRISTATE  TS_from_bool(bool value);
void      TS_to_bool(TRISTATE value, bool *flag);
void      TS_to_bool_def(TRISTATE value, bool *flag, bool default_value);

void TS_bool_to_tri(size_t num, const bool *bools, TRISTATE *tris);
void TS_tri_to_bool(size_t num, const TRISTATE *tris, bool *bools);
void TS_tri_to_bool_def(size_t num, const TRISTATE *tris, bool *bools,
                        bool default_value);

TRISTATE TS_from_int(int value);
int      TS_to_int(TRISTATE value);

#ifdef __cplusplus
    TRISTATE TS_from_str(const char *str, bool *converted = NULL);
    TRISTATE TS_from_wstr(const wchar_t *str, bool *converted = NULL);
#else
    TRISTATE TS_from_str(const char *str, bool *converted);
    TRISTATE TS_from_wstr(const wchar_t *str, bool *converted);
#endif

const char *        TS_to_str(TRISTATE value);
const wchar_t *     TS_to_wstr(TRISTATE value);

bool TS_and(bool value1, bool value2);
bool TS_or(bool value1, bool value2);
bool TS_not(bool value);

TRISTATE TS_tri_and(TRISTATE value1, TRISTATE value2);
TRISTATE TS_tri_or (TRISTATE value1, TRISTATE value2);
TRISTATE TS_tri_not(TRISTATE value);

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
#define TS_reset_totality_tri   TS_set_totality_tri

void
TS_get_tri_totality_tri(TRISTATE * value, size_t num, const TRISTATE *values);
void
TS_set_tri_totality_tri(TRISTATE   value, size_t num,       TRISTATE *values);
void
TS_reset_tri_totality_tri(TRISTATE value, size_t num,       TRISTATE *values);

void TS_each_and(bool value, size_t num, bool *values);
void TS_each_or (bool value, size_t num, bool *values);
void TS_each_not(            size_t num, bool *values);

void TS_each_and_tri(bool value, size_t num, TRISTATE *values);
void TS_each_or_tri (bool value, size_t num, TRISTATE *values);
void TS_each_not_tri(            size_t num, TRISTATE *values);

void TS_tri_each_and_tri(TRISTATE value, size_t num, TRISTATE *values);
void TS_tri_each_or_tri (TRISTATE value, size_t num, TRISTATE *values);

bool TS_connect_and(size_t num, const bool *values);
bool TS_connect_or (size_t num, const bool *values);

TRISTATE TS_connect_and_tri(size_t num, const TRISTATE *values);
TRISTATE TS_connect_or_tri (size_t num, const TRISTATE *values);

#ifdef __cplusplus
} // extern "C"
#endif

/****************************************************************************/
/* TriS class */

#ifdef __cplusplus
    #include <string>   // for std::string, std::wstring, ...
    class TriS
    {
    public:
        static const TriS   T;  /* true value */
        static const TriS   F;  /* false value */
        static const TriS   U;  /* unknown value */

        TriS()
            : m_value(TS_UNKNOWN) { }
        TriS(TRISTATE value)
            : m_value(value) { }
        TriS(const TriS& value)
            : m_value(value.m_value) { }
        TriS(bool value)
            : m_value(value ? TS_TRUE : TS_FALSE) { }
        TriS(int value)
            : m_value(TS_from_int(value)) { }
        TriS(const char *str)
            : m_value(TS_from_str(str)) { }
        TriS(const wchar_t *wstr)
            : m_value(TS_from_wstr(wstr)) { }
        TriS(const char *str, bool *converted)
            : m_value(TS_from_str(str, converted)) { }
        TriS(const wchar_t *wstr, bool *converted)
            : m_value(TS_from_wstr(wstr, converted)) { }

        bool is_valid() const {
            return TS_is_valid_tri(m_value);
        }
        operator bool() const {
            bool flag = false;
            TS_to_bool(m_value, &flag);
            return flag;
        }
        TRISTATE get_value() const {
            return m_value;
        }
        void set_value(TRISTATE value) {
            m_value = value;
        }

        std::string str() const   { return TS_to_str(m_value); }
        std::wstring wstr() const { return TS_to_wstr(m_value); }

#if defined(UNICODE) || defined(_UNICODE)
        std::wstring tstr() const { return wstr(); }
#else
        std::string tstr() const  { return str(); }
#endif

        TriS& operator=(bool value) {
            m_value = TS_from_bool(value);
            return *this;
        }
        TriS& operator=(int value) {
            m_value = TS_from_int(value);
            return *this;
        }
        TriS& operator=(TRISTATE value) {
            m_value = value;
            return *this;
        }
        TriS& operator=(const TriS& value) {
            m_value = value.m_value;
            return *this;
        }

        inline friend bool
        operator==(const TriS& value1, const TriS& value2) {
            return value1.m_value == value2.m_value;
        }
        inline friend bool
        operator!=(const TriS& value1, const TriS& value2) {
            return value1.m_value != value2.m_value;
        }
        inline friend bool
        operator>(const TriS& value1, const TriS& value2) {
            return value1.m_value > value2.m_value;
        }
        inline friend bool
        operator<(const TriS& value1, const TriS& value2) {
            return value1.m_value < value2.m_value;
        }
        inline friend bool
        operator>=(const TriS& value1, const TriS& value2) {
            return value1.m_value >= value2.m_value;
        }
        inline friend bool
        operator<=(const TriS& value1, const TriS& value2) {
            return value1.m_value <= value2.m_value;
        }

        inline friend bool
        operator==(const TriS& value1, int value2) {
            return value1.m_value == TS_from_int(value2);
        }
        inline friend bool
        operator!=(const TriS& value1, int value2) {
            return value1.m_value != TS_from_int(value2);
        }
        inline friend bool
        operator>(const TriS& value1, int value2) {
            return value1.m_value > TS_from_int(value2);
        }
        inline friend bool
        operator<(const TriS& value1, int value2) {
            return value1.m_value < TS_from_int(value2);
        }
        inline friend bool
        operator>=(const TriS& value1, int value2) {
            return value1.m_value >= TS_from_int(value2);
        }
        inline friend bool
        operator<=(const TriS& value1, int value2) {
            return value1.m_value <= TS_from_int(value2);
        }

        inline friend bool
        operator==(const TriS& value1, bool value2) {
            return value1.m_value == TS_from_bool(value2);
        }
        inline friend bool
        operator!=(const TriS& value1, bool value2) {
            return value1.m_value != TS_from_bool(value2);
        }
        inline friend bool
        operator>(const TriS& value1, bool value2) {
            return value1.m_value > TS_from_bool(value2);
        }
        inline friend bool
        operator<(const TriS& value1, bool value2) {
            return value1.m_value < TS_from_bool(value2);
        }
        inline friend bool
        operator>=(const TriS& value1, bool value2) {
            return value1.m_value >= TS_from_bool(value2);
        }
        inline friend bool
        operator<=(const TriS& value1, bool value2) {
            return value1.m_value <= TS_from_bool(value2);
        }

        inline friend bool
        operator==(int value1, const TriS& value2) {
            return TS_from_int(value1) == value2.m_value;
        }
        inline friend bool
        operator!=(int value1, const TriS& value2) {
            return TS_from_int(value1) != value2.m_value;
        }
        inline friend bool
        operator>(int value1, const TriS& value2) {
            return TS_from_int(value1) > value2.m_value;
        }
        inline friend bool
        operator<(int value1, const TriS& value2) {
            return TS_from_int(value1) < value2.m_value;
        }
        inline friend bool
        operator>=(int value1, const TriS& value2) {
            return TS_from_int(value1) >= value2.m_value;
        }
        inline friend bool
        operator<=(int value1, const TriS& value2) {
            return TS_from_int(value1) <= value2.m_value;
        }

        inline friend bool
        operator==(bool value1, const TriS& value2) {
            return TS_from_bool(value1) == value2.m_value;
        }
        inline friend bool
        operator!=(bool value1, const TriS& value2) {
            return TS_from_bool(value1) != value2.m_value;
        }
        inline friend bool
        operator>(bool value1, const TriS& value2) {
            return TS_from_bool(value1) > value2.m_value;
        }
        inline friend bool
        operator<(bool value1, const TriS& value2) {
            return TS_from_bool(value1) < value2.m_value;
        }
        inline friend bool
        operator>=(bool value1, const TriS& value2) {
            return TS_from_bool(value1) >= value2.m_value;
        }
        inline friend bool
        operator<=(bool value1, const TriS& value2) {
            return TS_from_bool(value1) <= value2.m_value;
        }

        inline friend TriS
        operator&&(const TriS& value1, const TriS& value2) {
            return TS_tri_and(value1.m_value, value2.m_value);
        }
        inline friend TriS
        operator&&(const TriS& value1, int value2) {
            return TS_tri_and(value1.m_value, TS_from_int(value2));
        }
        inline friend TriS
        operator&&(const TriS& value1, bool value2) {
            return TS_tri_and(value1.m_value, TS_from_bool(value2));
        }
        inline friend TriS
        operator&&(int value1, const TriS& value2) {
            return TS_tri_and(TS_from_int(value1), value2.m_value);
        }
        inline friend TriS
        operator&&(bool value1, const TriS& value2) {
            return TS_tri_and(TS_from_bool(value1), value2.m_value);
        }

        inline friend TriS
        operator||(const TriS& value1, const TriS& value2) {
            return TS_tri_or(value1.m_value, value2.m_value);
        }
        inline friend TriS
        operator||(const TriS& value1, int value2) {
            return TS_tri_or(value1.m_value, TS_from_int(value2));
        }
        inline friend TriS
        operator||(const TriS& value1, bool value2) {
            return TS_tri_or(value1.m_value, TS_from_bool(value2));
        }
        inline friend TriS
        operator||(int value1, const TriS& value2) {
            return TS_tri_or(TS_from_int(value1), value2.m_value);
        }
        inline friend TriS
        operator||(bool value1, const TriS& value2) {
            return TS_tri_or(TS_from_bool(value1), value2.m_value);
        }

        inline friend TriS
        operator!(const TriS& value) {
            return TS_tri_not(value.m_value);
        }

    protected:
        TRISTATE m_value;
    }; // class TriS

    /*static*/ const TriS   TriS::T(TS_TRUE);
    /*static*/ const TriS   TriS::F(TS_FALSE);
    /*static*/ const TriS   TriS::U(TS_UNKNOWN);
#endif  /* def __cplusplus */

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
