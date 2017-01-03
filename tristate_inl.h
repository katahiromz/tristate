/* tristate_inl.h --- tri-state logic inlines by katahiromz
 * This file is public domain software (PDS).
 * Copyright (C) 2017 Katayama Hirofumi MZ.
 */

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/

TRISTATE_INLINE bool
TS_is_valid(TRISTATE value)
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
    assert(value == false || value == true);
#endif
    return (value ? TS_TRUE : TS_FALSE);
}

TRISTATE_INLINE void
TS_to_bool(TRISTATE value, bool *flag)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
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
    assert(TS_is_valid(value));
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
    assert(TS_is_valid(value));
#endif
    if (value < 0)
        return L"false";
    if (value > 0)
        return L"true";
    return L"unknown";
}

TRISTATE_INLINE TRISTATE
TS_and(TRISTATE value1, TRISTATE value2)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value1));
    assert(TS_is_valid(value2));
#endif
    if (value1 < 0)
        return value1;
    if (value1 > 0 || value2 < 0)
        return value2;
    return TS_UNKNOWN;
}

TRISTATE_INLINE TRISTATE
TS_or(TRISTATE value1, TRISTATE value2)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value1));
    assert(TS_is_valid(value2));
#endif
    if (value1 > 0)
        return value1;
    if (value1 < 0 || value2 > 0)
        return value2;
    return TS_UNKNOWN;
}

TRISTATE_INLINE TRISTATE
TS_not(TRISTATE value)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
#endif
    return (TRISTATE)-(int)value;
}

TRISTATE_INLINE void
TS_get_totality(bool *value, size_t num, const bool *values)
{
    assert(value != NULL);
    assert(values != NULL);
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
    assert(values != NULL);
    if (sizeof(bool) == 1)
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
    assert(values != NULL);
    bool are_false = true;
    bool are_true = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(*values == false || *values == true);
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
    assert(TS_is_valid(*value));
#endif
}

TRISTATE_INLINE void
TS_set_tri_totality(TRISTATE value, size_t num, bool *values)
{
#ifdef __cplusplus
    using namespace std;
#endif
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
#endif
    assert(values != NULL);
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
    assert(values != NULL);
    bool are_false = true;
    bool are_true = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(*values));
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
    assert(values != NULL);
#ifdef TRISTATE_STRICT
    assert(value == false || value == true);
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
    assert(values != NULL);
    bool are_false = true;
    bool are_true = true;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(*values));
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
    assert(TS_is_valid(*value));
#endif
}

TRISTATE_INLINE void
TS_set_tri_totality_tri(TRISTATE value, size_t num, TRISTATE *values)
{
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
#endif
    if (value == TS_UNKNOWN)
        return;

    TS_reset_tri_totality_tri(value, num, values);
}

TRISTATE_INLINE void
TS_reset_tri_totality_tri(TRISTATE value, size_t num, TRISTATE *values)
{
    assert(values != NULL);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
#endif
    while (num-- > 0)
    {
        *values = value;
        ++values;
    }
}

TRISTATE_INLINE void
TS_each_and(TRISTATE value, size_t num, TRISTATE *values)
{
    assert(values != NULL);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
#endif
    if (value > 0)
    {
        ;
    }
    else if (value < 0)
    {
        TS_set_totality_tri(false, num, values);
    }
    else
    {
        while (num-- > 0)
        {
#ifdef TRISTATE_STRICT
            assert(TS_is_valid(*values));
#endif
            *values = TS_and(*values, value);
#ifdef TRISTATE_STRICT
            assert(TS_is_valid(*values));
#endif
            ++values;
        }
    }
}

TRISTATE_INLINE void
TS_each_or(TRISTATE value, size_t num, TRISTATE *values)
{
    assert(values != NULL);
#ifdef TRISTATE_STRICT
    assert(TS_is_valid(value));
#endif
    if (value > 0)
    {
        TS_set_totality_tri(true, num, values);
    }
    else if (value < 0)
    {
        ;
    }
    else
    {
        while (num-- > 0)
        {
#ifdef TRISTATE_STRICT
            assert(TS_is_valid(*values));
#endif
            *values = TS_or(*values, value);
#ifdef TRISTATE_STRICT
            assert(TS_is_valid(*values));
#endif
            ++values;
        }
    }
}

TRISTATE_INLINE void
TS_each_not(size_t num, TRISTATE *values)
{
    assert(values != NULL);
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(*values));
#endif
        *values = TS_not(*values);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(*values));
#endif
        ++values;
    }
}

TRISTATE_INLINE TRISTATE
TS_connect_and(size_t num, TRISTATE *values)
{
    TRISTATE value = TS_TRUE;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(*values));
#endif
        value = TS_and(value, *values);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(value));
#endif
        if (value < 0)
            break;
        ++values;
    }
    return value;
}

TRISTATE_INLINE TRISTATE
TS_connect_or(size_t num, TRISTATE *values)
{
    TRISTATE value = TS_FALSE;
    while (num-- > 0)
    {
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(*values));
#endif
        value = TS_or(value, *values);
#ifdef TRISTATE_STRICT
        assert(TS_is_valid(value));
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
