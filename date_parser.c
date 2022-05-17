#include "date_parser.h"


static int sub_validate(char *str, int sz, char seperator, int min, int max) {
    char *tmp = calloc(1, sz + 1);
    char *pEnd;
    memcpy(tmp, str, sz);
    long int num = strtol(tmp, &pEnd, 10);
    int res = 0;
    if (*pEnd == seperator) {
        if (num < min || num > max) {
            // printf("out of range\n");
            goto cleanup;
        }
        // printf("num = %ld\n", num);
    } else {
        // printf("Not expected size for string %s\n", pEnd);
        goto cleanup;
    }
    if (tmp[sz - 1] != seperator) {
        // printf("Not valid seperator\n");
        goto cleanup;
    }
    // printf("valid sub date!\n");
    res = 1;
    cleanup:
    free(tmp);
    return res;
}

/**
* Validates date string is in format of ISO 8601
*/
int validate_date(char *str) {
    int res = 0;
    char *date = str;

    size_t sz = strlen(str);

    if (sz == 25 || sz == 20) {
        // year
        res = sub_validate(date, 5, '-', 0, MAX_YEAR);
        date += 5;
        if (!res)
            goto cleanup;

        // month
        res = sub_validate(date, 3, '-', 1, MAX_MONTH);
        date += 3;
        if (!res)
            goto cleanup;
        // day
        res = sub_validate(date, 3, 'T', 1, MAX_DAY);
        date += 3;
        if (!res)
            goto cleanup;

        // hour
        res = sub_validate(date, 3, ':', 0, MAX_HOUR);
        date += 3;
        if (!res)
            goto cleanup;

        // minutes
        res = sub_validate(date, 3, ':', 0, MAX_MINUTE);
        date += 3;
        if (!res)
            goto cleanup;

        // validate tzd, 3 alternatives. (Seconds)
        res = sub_validate(date, 3, 'Z', 0, MAX_SECONDS);
        if (res)
            goto cleanup;

        res = sub_validate(date, 3, '+', 0, MAX_SECONDS);
        if (!res)
            res = sub_validate(date, 3, '-', 0, MAX_SECONDS);
        if (!res)
            goto cleanup;

        date += 3;

        // hour
        res = sub_validate(date, 3, ':', 0, MAX_HOUR);
        date += 3;
        if (!res)
            goto cleanup;

        // minutes
        res = sub_validate(date, 3, '\0', 0, MAX_MINUTE);
        if (!res)
            goto cleanup;
    } else {
        // printf("Wrong size\n");
    }
    cleanup:
    return res;
}