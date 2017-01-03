/* tristate.c --- tri-state logic by katahiromz
 * This file is public domain software (PDS).
 * Copyright (C) 2017 Katayama Hirofumi MZ.
 */
#include "tristate.h"

/****************************************************************************/
/* out-of-line functions */

#ifdef TRISTATE_NO_INLINING
    #undef TRISTATE_INLINE
    #define TRISTATE_INLINE     /* empty */
    #include "tristate_inl.h"
#endif

/****************************************************************************/
/* unit test */

#ifdef TRISTATE_UNITTEST
int main(void)
{
#ifdef __cplusplus
    using namespace std;
#endif
    bool converted, flag;
    TRISTATE value;
    TRISTATE array[3] = { TS_TRUE, TS_FALSE };
    bool unknown_table[3] = { true, false, true };
    bool false_table[3] = { false, false, false };
    bool true_table[3] = { true, true, true };
    TRISTATE tri_unknown_table[3] = { TS_TRUE, TS_FALSE, TS_TRUE };
    TRISTATE tri_false_table[3] = { TS_FALSE, TS_FALSE, TS_FALSE };
    TRISTATE tri_true_table[3] = { TS_TRUE, TS_TRUE, TS_TRUE };

    assert(TS_from_str("true", NULL) == TS_TRUE);
    assert(TS_from_str("false", NULL) == TS_FALSE);
    assert(TS_from_str("unknown", NULL) == TS_UNKNOWN);
    assert(TS_from_str("invalid", NULL) == TS_UNKNOWN);

    assert(TS_from_wstr(L"true", NULL) == TS_TRUE);
    assert(TS_from_wstr(L"false", NULL) == TS_FALSE);
    assert(TS_from_wstr(L"unknown", NULL) == TS_UNKNOWN);
    assert(TS_from_wstr(L"invalid", NULL) == TS_UNKNOWN);

    assert(TS_from_str("true", &converted) == TS_TRUE && converted);
    assert(TS_from_str("false", &converted) == TS_FALSE && converted);
    assert(TS_from_str("unknown", &converted) == TS_UNKNOWN && converted);
    assert(TS_from_str("invalid", &converted) == TS_UNKNOWN && !converted);

    assert(TS_from_wstr(L"true", &converted) == TS_TRUE && converted);
    assert(TS_from_wstr(L"false", &converted) == TS_FALSE && converted);
    assert(TS_from_wstr(L"unknown", &converted) == TS_UNKNOWN && converted);
    assert(TS_from_wstr(L"invalid", &converted) == TS_UNKNOWN && !converted);

    assert(strcmp(TS_to_str(TS_TRUE), "true") == 0);
    assert(strcmp(TS_to_str(TS_FALSE), "false") == 0);
    assert(strcmp(TS_to_str(TS_UNKNOWN), "unknown") == 0);

    assert(wcscmp(TS_to_wstr(TS_TRUE), L"true") == 0);
    assert(wcscmp(TS_to_wstr(TS_FALSE), L"false") == 0);
    assert(wcscmp(TS_to_wstr(TS_UNKNOWN), L"unknown") == 0);

    assert(TS_and(TS_TRUE, TS_TRUE) == TS_TRUE);
    assert(TS_and(TS_TRUE, TS_FALSE) == TS_FALSE);
    assert(TS_and(TS_TRUE, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_and(TS_FALSE, TS_TRUE) == TS_FALSE);
    assert(TS_and(TS_FALSE, TS_FALSE) == TS_FALSE);
    assert(TS_and(TS_FALSE, TS_UNKNOWN) == TS_FALSE);

    assert(TS_and(TS_UNKNOWN, TS_TRUE) == TS_UNKNOWN);
    assert(TS_and(TS_UNKNOWN, TS_FALSE) == TS_FALSE);
    assert(TS_and(TS_UNKNOWN, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_or(TS_TRUE, TS_TRUE) == TS_TRUE);
    assert(TS_or(TS_TRUE, TS_FALSE) == TS_TRUE);
    assert(TS_or(TS_TRUE, TS_UNKNOWN) == TS_TRUE);

    assert(TS_or(TS_FALSE, TS_TRUE) == TS_TRUE);
    assert(TS_or(TS_FALSE, TS_FALSE) == TS_FALSE);
    assert(TS_or(TS_FALSE, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_or(TS_UNKNOWN, TS_TRUE) == TS_TRUE);
    assert(TS_or(TS_UNKNOWN, TS_FALSE) == TS_UNKNOWN);
    assert(TS_or(TS_UNKNOWN, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_not(TS_UNKNOWN) == TS_UNKNOWN);
    assert(TS_not(TS_TRUE) == TS_FALSE);
    assert(TS_not(TS_FALSE) == TS_TRUE);

    assert(array[0] == TS_TRUE);
    assert(array[1] == TS_FALSE);
    assert(array[2] == TS_UNKNOWN);

    assert(TS_TRUE > 0);
    assert(TS_FALSE < 0);
    assert(TS_UNKNOWN == 0);

    assert(TS_TRUE > TS_UNKNOWN);
    assert(TS_FALSE < TS_UNKNOWN);
    assert(TS_UNKNOWN == TS_UNKNOWN);

    flag = false;
    TS_get_totality(&flag, 3, unknown_table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);

    flag = false;
    TS_get_totality(&flag, 3, false_table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, false_table);
    assert(!flag);

    flag = false;
    TS_get_totality(&flag, 3, true_table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, true_table);
    assert(flag);

    TS_get_tri_totality(&value, 3, unknown_table);
    assert(value == TS_UNKNOWN);
    TS_get_tri_totality(&value, 3, false_table);
    assert(value == TS_FALSE);
    TS_get_tri_totality(&value, 3, true_table);
    assert(value == TS_TRUE);

    flag = false;
    TS_get_totality_tri(&flag, 3, tri_unknown_table);
    assert(!flag);
    flag = true;
    TS_get_totality_tri(&flag, 3, tri_unknown_table);
    assert(flag);
    TS_get_totality_tri(&flag, 3, tri_false_table);
    assert(!flag);
    TS_get_totality_tri(&flag, 3, tri_true_table);
    assert(flag);

    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_UNKNOWN);
    TS_get_tri_totality_tri(&value, 3, tri_false_table);
    assert(value == TS_FALSE);
    TS_get_tri_totality_tri(&value, 3, tri_true_table);
    assert(value == TS_TRUE);

    flag = false;
    TS_set_totality(flag, 3, unknown_table);
    flag = false;
    TS_get_totality(&flag, 3, unknown_table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, unknown_table);
    assert(!flag);

    flag = true;
    TS_set_totality(flag, 3, unknown_table);
    flag = false;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);

    value = TS_UNKNOWN;
    TS_set_tri_totality(value, 3, unknown_table);
    flag = false;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);

    value = TS_FALSE;
    TS_set_tri_totality(value, 3, unknown_table);
    flag = false;
    TS_get_totality(&flag, 3, unknown_table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, unknown_table);
    assert(!flag);

    value = TS_TRUE;
    TS_set_tri_totality(value, 3, unknown_table);
    flag = false;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, unknown_table);
    assert(flag);

    TS_set_totality_tri(false, 3, tri_unknown_table);
    flag = false;
    TS_get_totality_tri(&flag, 3, tri_unknown_table);
    assert(!flag);
    flag = true;
    TS_get_totality_tri(&flag, 3, tri_unknown_table);
    assert(!flag);

    TS_set_totality_tri(true, 3, tri_unknown_table);
    flag = false;
    TS_get_totality_tri(&flag, 3, tri_unknown_table);
    assert(flag);
    flag = true;
    TS_get_totality_tri(&flag, 3, tri_unknown_table);
    assert(flag);

    TS_set_tri_totality_tri(TS_UNKNOWN, 3, tri_unknown_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_UNKNOWN);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_UNKNOWN);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_UNKNOWN);

    TS_set_tri_totality_tri(TS_FALSE, 3, tri_unknown_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_FALSE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_FALSE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_FALSE);

    TS_set_tri_totality_tri(TS_TRUE, 3, tri_unknown_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_TRUE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_TRUE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_unknown_table);
    assert(value == TS_TRUE);

    return 0;
} /* main */
#endif  /* def TRISTATE_UNITTEST */

/****************************************************************************/
