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
    bool table[3];
    const bool unknown_table[3] = { true, false, true };
    const bool false_table[3] = { false, false, false };
    const bool true_table[3] = { true, true, true };
    TRISTATE tri_table[3];
    const TRISTATE tri_unknown_table[3] = { TS_TRUE, TS_FALSE, TS_UNKNOWN };
    const TRISTATE tri_false_table[3] = { TS_FALSE, TS_FALSE, TS_FALSE };
    const TRISTATE tri_true_table[3] = { TS_TRUE, TS_TRUE, TS_TRUE };
    const TRISTATE array[3] = { TS_TRUE, TS_FALSE };

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

    assert(TS_tri_and(TS_TRUE, TS_TRUE) == TS_TRUE);
    assert(TS_tri_and(TS_TRUE, TS_FALSE) == TS_FALSE);
    assert(TS_tri_and(TS_TRUE, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_tri_and(TS_FALSE, TS_TRUE) == TS_FALSE);
    assert(TS_tri_and(TS_FALSE, TS_FALSE) == TS_FALSE);
    assert(TS_tri_and(TS_FALSE, TS_UNKNOWN) == TS_FALSE);

    assert(TS_tri_and(TS_UNKNOWN, TS_TRUE) == TS_UNKNOWN);
    assert(TS_tri_and(TS_UNKNOWN, TS_FALSE) == TS_FALSE);
    assert(TS_tri_and(TS_UNKNOWN, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_tri_or(TS_TRUE, TS_TRUE) == TS_TRUE);
    assert(TS_tri_or(TS_TRUE, TS_FALSE) == TS_TRUE);
    assert(TS_tri_or(TS_TRUE, TS_UNKNOWN) == TS_TRUE);

    assert(TS_tri_or(TS_FALSE, TS_TRUE) == TS_TRUE);
    assert(TS_tri_or(TS_FALSE, TS_FALSE) == TS_FALSE);
    assert(TS_tri_or(TS_FALSE, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_tri_or(TS_UNKNOWN, TS_TRUE) == TS_TRUE);
    assert(TS_tri_or(TS_UNKNOWN, TS_FALSE) == TS_UNKNOWN);
    assert(TS_tri_or(TS_UNKNOWN, TS_UNKNOWN) == TS_UNKNOWN);

    assert(TS_tri_not(TS_UNKNOWN) == TS_UNKNOWN);
    assert(TS_tri_not(TS_TRUE) == TS_FALSE);
    assert(TS_tri_not(TS_FALSE) == TS_TRUE);

    assert(array[0] == TS_TRUE);
    assert(array[1] == TS_FALSE);
    assert(array[2] == TS_UNKNOWN);

    assert(TS_TRUE > 0);        /* positive */
    assert(TS_FALSE < 0);       /* negative */
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
    TS_set_totality(flag, 3, table);
    flag = false;
    TS_get_totality(&flag, 3, table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, table);
    assert(!flag);

    flag = true;
    TS_set_totality(flag, 3, table);
    flag = false;
    TS_get_totality(&flag, 3, table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, table);
    assert(flag);

    TS_set_tri_totality(TS_FALSE, 3, table);
    TS_set_tri_totality(TS_UNKNOWN, 3, table);
    flag = false;
    TS_get_totality(&flag, 3, table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, table);
    assert(!flag);

    TS_set_tri_totality(TS_TRUE, 3, table);
    TS_set_tri_totality(TS_UNKNOWN, 3, table);
    flag = false;
    TS_get_totality(&flag, 3, table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, table);
    assert(flag);

    TS_set_tri_totality(TS_FALSE, 3, table);
    flag = false;
    TS_get_totality(&flag, 3, table);
    assert(!flag);
    flag = true;
    TS_get_totality(&flag, 3, table);
    assert(!flag);

    TS_set_tri_totality(TS_TRUE, 3, table);
    flag = false;
    TS_get_totality(&flag, 3, table);
    assert(flag);
    flag = true;
    TS_get_totality(&flag, 3, table);
    assert(flag);

    TS_set_totality_tri(false, 3, tri_table);
    flag = false;
    TS_get_totality_tri(&flag, 3, tri_table);
    assert(!flag);
    flag = true;
    TS_get_totality_tri(&flag, 3, tri_table);
    assert(!flag);

    TS_set_totality_tri(true, 3, tri_table);
    flag = false;
    TS_get_totality_tri(&flag, 3, tri_table);
    assert(flag);
    flag = true;
    TS_get_totality_tri(&flag, 3, tri_table);
    assert(flag);

    TS_set_tri_totality_tri(TS_FALSE, 3, tri_table);
    TS_set_tri_totality_tri(TS_UNKNOWN, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);

    TS_set_tri_totality_tri(TS_TRUE, 3, tri_table);
    TS_set_tri_totality_tri(TS_UNKNOWN, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);

    TS_set_tri_totality_tri(TS_FALSE, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);

    TS_set_tri_totality_tri(TS_TRUE, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);

    TS_reset_tri_totality_tri(TS_UNKNOWN, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_UNKNOWN);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_UNKNOWN);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_UNKNOWN);

    TS_reset_tri_totality_tri(TS_FALSE, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_FALSE);

    TS_reset_tri_totality_tri(TS_TRUE, 3, tri_table);
    value = TS_UNKNOWN;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);
    value = TS_FALSE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);
    value = TS_TRUE;
    TS_get_tri_totality_tri(&value, 3, tri_table);
    assert(value == TS_TRUE);

    table[0] = true;
    table[1] = false;
    table[2] = true;
    TS_each_and(true, 3, table);
    assert(table[0] == true);
    assert(table[1] == false);
    assert(table[2] == true);

    table[0] = true;
    table[1] = false;
    table[2] = true;
    TS_each_and(false, 3, table);
    assert(table[0] == false);
    assert(table[1] == false);
    assert(table[2] == false);

    table[0] = true;
    table[1] = false;
    table[2] = true;
    TS_each_or(true, 3, table);
    assert(table[0] == true);
    assert(table[1] == true);
    assert(table[2] == true);

    table[0] = true;
    table[1] = false;
    table[2] = true;
    TS_each_or(false, 3, table);
    assert(table[0] == true);
    assert(table[1] == false);
    assert(table[2] == true);

    table[0] = true;
    table[1] = false;
    table[2] = true;
    TS_each_not(3, table);
    assert(table[0] == false);
    assert(table[1] == true);
    assert(table[2] == false);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_each_and_tri(false, 3, tri_table);
    assert(tri_table[0] == TS_FALSE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_FALSE);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_each_and_tri(true, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_UNKNOWN);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_each_or_tri(false, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_UNKNOWN);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_each_or_tri(true, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_TRUE);
    assert(tri_table[2] == TS_TRUE);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_tri_each_and_tri(TS_UNKNOWN, 3, tri_table);
    assert(tri_table[0] == TS_UNKNOWN);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_UNKNOWN);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_tri_each_and_tri(TS_FALSE, 3, tri_table);
    assert(tri_table[0] == TS_FALSE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_FALSE);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_tri_each_and_tri(TS_TRUE, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_UNKNOWN);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_tri_each_or_tri(TS_UNKNOWN, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_UNKNOWN);
    assert(tri_table[2] == TS_UNKNOWN);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_tri_each_or_tri(TS_FALSE, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_UNKNOWN);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    TS_tri_each_or_tri(TS_TRUE, 3, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_TRUE);
    assert(tri_table[2] == TS_TRUE);

    table[0] = false;
    table[1] = false;
    table[2] = false;
    flag = TS_connect_and(3, table);
    assert(!flag);

    table[0] = true;
    table[1] = true;
    table[2] = true;
    flag = TS_connect_and(3, table);
    assert(flag);

    table[0] = false;
    table[1] = true;
    table[2] = true;
    flag = TS_connect_and(3, table);
    assert(!flag);

    table[0] = true;
    table[1] = false;
    table[2] = false;
    flag = TS_connect_and(3, table);
    assert(!flag);

    table[0] = false;
    table[1] = false;
    table[2] = false;
    flag = TS_connect_or(3, table);
    assert(!flag);

    table[0] = true;
    table[1] = true;
    table[2] = true;
    flag = TS_connect_or(3, table);
    assert(flag);

    table[0] = false;
    table[1] = true;
    table[2] = true;
    flag = TS_connect_or(3, table);
    assert(flag);

    table[0] = true;
    table[1] = false;
    table[2] = false;
    flag = TS_connect_or(3, table);
    assert(flag);

    tri_table[0] = TS_UNKNOWN;
    tri_table[1] = TS_UNKNOWN;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_and_tri(3, tri_table);
    assert(value == 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_FALSE;
    value = TS_connect_and_tri(3, tri_table);
    assert(value < 0);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_TRUE;
    tri_table[2] = TS_TRUE;
    value = TS_connect_and_tri(3, tri_table);
    assert(value > 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_TRUE;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_and_tri(3, tri_table);
    assert(value < 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_TRUE;
    tri_table[2] = TS_TRUE;
    value = TS_connect_and_tri(3, tri_table);
    assert(value < 0);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_FALSE;
    value = TS_connect_and_tri(3, tri_table);
    assert(value < 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_UNKNOWN;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_and_tri(3, tri_table);
    assert(value < 0);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_UNKNOWN;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_and_tri(3, tri_table);
    assert(value == 0);

    tri_table[0] = TS_UNKNOWN;
    tri_table[1] = TS_UNKNOWN;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_or_tri(3, tri_table);
    assert(value == 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_FALSE;
    value = TS_connect_or_tri(3, tri_table);
    assert(value < 0);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_TRUE;
    tri_table[2] = TS_TRUE;
    value = TS_connect_or_tri(3, tri_table);
    assert(value > 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_TRUE;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_or_tri(3, tri_table);
    assert(value > 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_TRUE;
    tri_table[2] = TS_TRUE;
    value = TS_connect_or_tri(3, tri_table);
    assert(value > 0);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_FALSE;
    value = TS_connect_or_tri(3, tri_table);
    assert(value > 0);

    tri_table[0] = TS_FALSE;
    tri_table[1] = TS_UNKNOWN;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_or_tri(3, tri_table);
    assert(value == 0);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_UNKNOWN;
    tri_table[2] = TS_UNKNOWN;
    value = TS_connect_or_tri(3, tri_table);
    assert(value > 0);

    assert(TS_from_bool(false) == TS_FALSE);
    assert(TS_from_bool(true) == TS_TRUE);

    flag = false;
    TS_to_bool(TS_UNKNOWN, &flag);
    assert(!flag);
    flag = true;
    TS_to_bool(TS_UNKNOWN, &flag);
    assert(flag);

    flag = false;
    TS_to_bool(TS_FALSE, &flag);
    assert(!flag);
    flag = true;
    TS_to_bool(TS_FALSE, &flag);
    assert(!flag);

    flag = false;
    TS_to_bool(TS_TRUE, &flag);
    assert(flag);
    flag = true;
    TS_to_bool(TS_TRUE, &flag);
    assert(flag);

    flag = false;
    TS_to_bool_def(TS_UNKNOWN, &flag, false);
    assert(!flag);
    flag = false;
    TS_to_bool_def(TS_UNKNOWN, &flag, true);
    assert(flag);

    flag = true;
    TS_to_bool_def(TS_UNKNOWN, &flag, false);
    assert(!flag);
    flag = true;
    TS_to_bool_def(TS_UNKNOWN, &flag, true);
    assert(flag);

    tri_table[0] = TS_TRUE;
    tri_table[1] = TS_FALSE;
    tri_table[2] = TS_UNKNOWN;
    table[2] = false;
    TS_tri_to_bool(3, tri_table, table);
    assert(table[0] == true);
    assert(table[1] == false);
    assert(table[2] == false);
    table[2] = true;
    TS_tri_to_bool(3, tri_table, table);
    assert(table[0] == true);
    assert(table[1] == false);
    assert(table[2] == true);

    table[2] = true;
    TS_tri_to_bool_def(3, tri_table, table, false);
    assert(table[0] == true);
    assert(table[1] == false);
    assert(table[2] == false);
    table[2] = true;
    TS_tri_to_bool_def(3, tri_table, table, true);
    assert(table[0] == true);
    assert(table[1] == false);
    assert(table[2] == true);

    table[0] = true;
    table[1] = false;
    table[2] = false;
    TS_bool_to_tri(3, table, tri_table);
    assert(tri_table[0] == TS_TRUE);
    assert(tri_table[1] == TS_FALSE);
    assert(tri_table[2] == TS_FALSE);

    table[0] = false;
    table[1] = true;
    table[2] = true;
    TS_bool_to_tri(3, table, tri_table);
    assert(tri_table[0] == TS_FALSE);
    assert(tri_table[1] == TS_TRUE);
    assert(tri_table[2] == TS_TRUE);

    assert(!TS_and(false, false));
    assert(!TS_and(false, true));
    assert(!TS_and(true, false));
    assert(TS_and(true, true));

    assert(!TS_or(false, false));
    assert(TS_or(false, true));
    assert(TS_or(true, false));
    assert(TS_or(true, true));

    assert(!TS_not(true));
    assert(TS_not(false));

#ifdef __cplusplus
    assert((TriState)false == TriState::F);
    assert((TriState)true == TriState::T);
    assert((TriState)TS_FALSE == TriState::F);
    assert((TriState)TS_TRUE == TriState::T);
    assert((TriState)TS_UNKNOWN == TriState::U);
    assert((TriState)"false" == TriState::F);
    assert((TriState)"true" == TriState::T);
    assert((TriState)"unknown" == TriState::U);
    assert((TriState)L"false" == TriState::F);
    assert((TriState)L"true" == TriState::T);
    assert((TriState)L"unknown" == TriState::U);
    assert((bool)TriState::T == true);
    assert((bool)TriState::F == false);
    assert((bool)TriState::U == false);
    TriState ts;
    assert(ts == TriState::U);
    ts = TS_UNKNOWN;
    assert(ts == TriState::U);
    ts = TS_FALSE;
    assert(ts == TriState::F);
    ts = TS_TRUE;
    assert(ts == TriState::T);
    TriState ts2 = ts;
    TriState ts3(ts);
    assert(ts2 == ts3);
#endif  /* def __cplusplus */

    return 0;
} /* main */
#endif  /* def TRISTATE_UNITTEST */

/****************************************************************************/
