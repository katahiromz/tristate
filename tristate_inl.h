
/* tristate_inl.h --- tri-state logic inlines by katahiromz
 * This file is public domain software (PDS).
 * Copyright (C) 2017 Katayama Hirofumi MZ.
 */

#ifndef TRISTATE_H_
    #error You should #include "tristate.h" rather than "tristate_inl.h".
#endif

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/

TRISTATE_INLINE bool
TS_is_valid_bool(bool value)
{
    return (value == false || value == true);
}

TRISTATE_INLINE bool
TS_is_valid_tri(TRISTATE value)
{
    switch (value)
    {
    case TS_TRUE: case TS_FALSE: case TS_UNKNOWN:
        return true;
    default:
        return false;
    }
}

TRISTATE_INLINE TRISTATE
TS_from_bool(bool value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    return (value ? TS_TRUE : TS_FALSE);
}

TRISTATE_INLINE void
TS_to_bool(TRISTATE value, bool *flag)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    if (value < 0)
    {
        assert(flag != NULL);
        *flag = false;
    }
    else if (value > 0)
    {
        assert(flag != NULL);
        *flag = true;
    }
}

TRISTATE_INLINE void
TS_to_bool_def(TRISTATE value, bool *flag, bool default_value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
    assert(TS_is_valid_bool(default_value));
#endif
    assert(flag != NULL);
    if (value < 0)
    {
        *flag = false;
    }
    else if (value > 0)
    {
        *flag = true;
    }
    else
    {
        *flag = default_value;
    }
}

TRISTATE_INLINE bool
TS_and(bool value1, bool value2)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value1));
    assert(TS_is_valid_bool(value2));
#endif
    return value1 && value2;
}

TRISTATE_INLINE bool
TS_or(bool value1, bool value2)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value1));
    assert(TS_is_valid_bool(value2));
#endif
    return value1 || value2;
}

TRISTATE_INLINE bool
TS_not(bool value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    return !value;
}

TRISTATE_INLINE void
TS_bool_to_tri(size_t num, const bool *bools, TRISTATE *tris)
{
    assert(bools != NULL || num == 0);
    assert(tris != NULL || num == 0);
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*bools));
#endif
        *tris = TS_from_bool(*bools);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*tris));
#endif
        ++bools;
        ++tris;
    }
}

TRISTATE_INLINE void
TS_tri_to_bool(size_t num, const TRISTATE *tris, bool *bools)
{
    assert(tris != NULL || num == 0);
    assert(bools != NULL || num == 0);
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*tris));
#endif
        TS_to_bool(*tris, bools);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*bools));
#endif
        ++tris;
        ++bools;
    }
}

TRISTATE_INLINE void
TS_tri_to_bool_def(size_t num, const TRISTATE *tris, bool *bools,
                   bool default_value)
{
    assert(tris != NULL || num == 0);
    assert(bools != NULL || num == 0);
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*tris));
#endif
        TS_to_bool_def(*tris, bools, default_value);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*bools));
#endif
        ++tris;
        ++bools;
    }
}

TRISTATE_INLINE TRISTATE
TS_from_int(int value)
{
#ifdef TRISTATE_STRICT
    if (value < 0)
        return TS_FALSE;
    if (value > 0)
        return TS_TRUE;
    return TS_UNKNOWN;
#else
    return (TRISTATE)value;
#endif
}

TRISTATE_INLINE int
TS_to_int(TRISTATE value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
    if (value < 0)
        return -1;
    if (value > 0)
        return 1;
    return 0;
#else
    return (int)value;
#endif
}

TRISTATE_INLINE TRISTATE
TS_from_str(const char *str, bool *converted)
{
#ifdef __cplusplus
    using namespace std;
#endif
    if (strcmp(str, "false") == 0)
    {
        if (converted)
            *converted = true;
        return TS_FALSE;
    }
    if (strcmp(str, "true") == 0)
    {
        if (converted)
            *converted = true;
        return TS_TRUE;
    }
    if (strcmp(str, "unknown") == 0)
    {
        if (converted)
            *converted = true;
        return TS_UNKNOWN;
    }
    if (converted)
        *converted = false;
    return TS_UNKNOWN;
}

TRISTATE_INLINE TRISTATE
TS_from_wstr(const wchar_t *str, bool *converted)
{
#ifdef __cplusplus
    using namespace std;
#endif
    if (wcscmp(str, L"false") == 0)
    {
        if (converted)
            *converted = true;
        return TS_FALSE;
    }
    if (wcscmp(str, L"true") == 0)
    {
        if (converted)
            *converted = true;
        return TS_TRUE;
    }
    if (wcscmp(str, L"unknown") == 0)
    {
        if (converted)
            *converted = true;
        return TS_UNKNOWN;
    }
    if (converted)
        *converted = false;
    return TS_UNKNOWN;
}

TRISTATE_INLINE const char *
TS_to_str(TRISTATE value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    if (value < 0)
        return "false";
    if (value > 0)
        return "true";
    return "unknown";
}

TRISTATE_INLINE const wchar_t *
TS_to_wstr(TRISTATE value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    if (value < 0)
        return L"false";
    if (value > 0)
        return L"true";
    return L"unknown";
}

TRISTATE_INLINE TRISTATE
TS_tri_and(TRISTATE value1, TRISTATE value2)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value1));
    assert(TS_is_valid_tri(value2));
#endif
    if (value1 < 0)
        return value1;
    if (value1 > 0 || value2 < 0)
        return value2;
    return TS_UNKNOWN;
}

TRISTATE_INLINE TRISTATE
TS_tri_or(TRISTATE value1, TRISTATE value2)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value1));
    assert(TS_is_valid_tri(value2));
#endif
    if (value1 > 0)
        return value1;
    if (value1 < 0 || value2 > 0)
        return value2;
    return TS_UNKNOWN;
}

TRISTATE_INLINE TRISTATE
TS_tri_not(TRISTATE value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    return (TRISTATE)-(int)value;
}

TRISTATE_INLINE void
TS_get_totality(bool *value, size_t num, const bool *values)
{
    assert(value != NULL);
    assert(values != NULL || num == 0);
    TRISTATE state;
    TS_get_tri_totality(&state, num, values);
    if (state < 0)
        *value = false;
    if (state > 0)
        *value = true;
}

TRISTATE_INLINE void
TS_set_totality(bool value, size_t num, bool *values)
{
#ifdef __cplusplus
    using namespace std;
#endif
    assert(values != NULL || num == 0);
    if (sizeof(bool) == 1 || !value)
    {
        memset(values, value, num * sizeof(bool));
    }
    else
    {
        while (num-- > 0)
        {
            *values = value;
            ++values;
        }
    }
}

TRISTATE_INLINE void
TS_get_tri_totality(TRISTATE *value, size_t num, const bool *values)
{
    assert(value != NULL);
    assert(values != NULL || num == 0);
    bool are_false = true;
    bool are_true = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*values));
#endif
        if (*values)
            are_false = false;
        else
            are_true = false;
        ++values;
    }
    if (are_false == are_true)
        *value = TS_UNKNOWN;
    else if (are_false)
        *value = TS_FALSE;
    else if (are_true)
        *value = TS_TRUE;
    else
        *value = TS_UNKNOWN;
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(*value));
#endif
}

TRISTATE_INLINE void
TS_set_tri_totality(TRISTATE value, size_t num, bool *values)
{
#ifdef __cplusplus
    using namespace std;
#endif
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    assert(values != NULL || num == 0);
    if (value < 0)
    {
        TS_set_totality(false, num, values);
    }
    else if (value > 0)
    {
        TS_set_totality(true, num, values);
    }
}

TRISTATE_INLINE void
TS_get_totality_tri(bool *value, size_t num, const TRISTATE *values)
{
    assert(value != NULL);
    assert(values != NULL || num == 0);
    bool are_false = true;
    bool are_true = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        if (*values < 0)
            are_true = false;
        else if (*values > 0)
            are_false = false;
        ++values;
    }
    if (are_false == are_true)
        ;
    else if (are_false)
        *value = false;
    else if (are_true)
        *value = true;
}

TRISTATE_INLINE void
TS_set_totality_tri(bool value, size_t num, TRISTATE *values)
{
    assert(values != NULL || num == 0);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    const TRISTATE state = TS_from_bool(value);
    while (num-- > 0)
    {
        *values = state;
        ++values;
    }
}

TRISTATE_INLINE void
TS_get_tri_totality_tri(TRISTATE *value, size_t num, const TRISTATE *values)
{
    assert(value != NULL);
    assert(values != NULL || num == 0);
    bool are_false = true;
    bool are_true = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        if (*values < 0)
            are_true = false;
        else if (*values > 0)
            are_false = false;
        ++values;
    }
    if (are_false == are_true)
        *value = TS_UNKNOWN;
    else if (are_false)
        *value = TS_FALSE;
    else if (are_true)
        *value = TS_TRUE;
    else
        *value = TS_UNKNOWN;
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(*value));
#endif
}

TRISTATE_INLINE void
TS_set_tri_totality_tri(TRISTATE value, size_t num, TRISTATE *values)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    if (value == TS_UNKNOWN)
        return;

    TS_reset_tri_totality_tri(value, num, values);
}

TRISTATE_INLINE void
TS_reset_tri_totality_tri(TRISTATE value, size_t num, TRISTATE *values)
{
    assert(values != NULL || num == 0);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    while (num-- > 0)
    {
        *values = value;
        ++values;
    }
}

TRISTATE_INLINE void
TS_each_and(bool value, size_t num, bool *values)
{
    assert(values != NULL || num == 0);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    if (value)
        return;
    TS_set_totality(false, num, values);
}

TRISTATE_INLINE void
TS_each_or (bool value, size_t num, bool *values)
{
    assert(values != NULL || num == 0);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    if (!value)
        return;
    TS_set_totality(true, num, values);
}

TRISTATE_INLINE void
TS_each_not(size_t num, bool *values)
{
    assert(values != NULL || num == 0);
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*values));
#endif
        *values = !*values;
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*values));
#endif
        ++values;
    }
}

TRISTATE_INLINE void
TS_each_and_tri(bool value, size_t num, TRISTATE *values)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    assert(values != NULL || num == 0);

    if (value)
        return;

    TS_set_totality_tri(false, num, values);
}

TRISTATE_INLINE void
TS_each_or_tri(bool value, size_t num, TRISTATE *values)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_bool(value));
#endif
    assert(values != NULL || num == 0);

    if (!value)
        return;

    TS_set_totality_tri(true, num, values);
}

TRISTATE_INLINE void
TS_tri_each_and_tri(TRISTATE value, size_t num, TRISTATE *values)
{
    assert(values != NULL || num == 0);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    if (value > 0)
        return;

    if (value < 0)
    {
        TS_set_totality_tri(false, num, values);
        return;
    }

    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        *values = TS_tri_and(*values, value);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        ++values;
    }
}

TRISTATE_INLINE void
TS_tri_each_or_tri(TRISTATE value, size_t num, TRISTATE *values)
{
    assert(values != NULL || num == 0);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid_tri(value));
#endif
    if (value > 0)
    {
        TS_set_totality_tri(true, num, values);
        return;
    }

    if (value < 0)
        return;

    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        *values = TS_tri_or(*values, value);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        ++values;
    }
}

TRISTATE_INLINE void
TS_each_not_tri(size_t num, TRISTATE *values)
{
    assert(values != NULL || num == 0);
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        *values = TS_tri_not(*values);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        ++values;
    }
}

TRISTATE_INLINE bool
TS_connect_and(size_t num, const bool *values)
{
    bool value = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*values));
#endif
        value = *values;
        if (!value)
            break;
        ++values;
    }
    return value;
}

TRISTATE_INLINE bool
TS_connect_or(size_t num, const bool *values)
{
    bool value = false;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_bool(*values));
#endif
        value = *values;
        if (value)
            break;
        ++values;
    }
    return value;
}

TRISTATE_INLINE TRISTATE
TS_connect_and_tri(size_t num, const TRISTATE *values)
{
    TRISTATE value = TS_TRUE;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        value = TS_tri_and(value, *values);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(value));
#endif
        if (value < 0)
            break;
        ++values;
    }
    return value;
}

TRISTATE_INLINE TRISTATE
TS_connect_or_tri(size_t num, const TRISTATE *values)
{
    TRISTATE value = TS_FALSE;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(*values));
#endif
        value = TS_tri_or(value, *values);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid_tri(value));
#endif
        if (value > 0)
            break;
        ++values;
    }
    return value;
}

/****************************************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

/****************************************************************************/
