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
    if (converted)
        *converted = false;
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
    return TS_UNKNOWN;
}

TRISTATE_INLINE TRISTATE
TS_from_wstr(const wchar_t *str, bool *converted)
{
#ifdef __cplusplus
    using namespace std;
#endif
    if (converted)
        *converted = false;
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

TRISTATE_INLINE TRISTATE
TS_get_totality(size_t count, const bool *values)
{
    bool are_true = true;
    bool are_false = true;
    while (count-- > 0)
    {
        if (*values)
            are_false = false;
        else
            are_true = false;
        ++values;
    }
    if (are_false == are_true)
        return TS_UNKNOWN;
    if (are_true)
        return TS_TRUE;
    return TS_FALSE;
}

TRISTATE_INLINE void
TS_set_totality(size_t count, bool *values, TRISTATE value)
{
#ifdef __cplusplus
    using namespace std;
#endif
    if (value < 0)
    {
        if (sizeof(bool) == 1)
        {
            memset(values, false, count * sizeof(bool));
        }
        else
        {
            while (count-- > 0)
            {
                *values = false;
                ++values;
            }
        }
    }
    else if (value > 0)
    {
        if (sizeof(bool) == 1)
        {
            memset(values, true, count * sizeof(bool));
        }
        else
        {
            while (count-- > 0)
            {
                *values = true;
                ++values;
            }
        }
    }
}

/****************************************************************************/

#ifdef __cplusplus
} // extern "C"
#endif

/****************************************************************************/
