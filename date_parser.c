#include "date_parser.h"


static int sub_validate(char *str, int sz, char separator, int min, int max) {
    char *tmp = calloc(1, sz + 1);
    char *pEnd;
    memcpy(tmp, str, sz);
    long int num = strtol(tmp, &pEnd, 10);
    int res = 0;

    if (tmp[sz - 1] != separator) {
        // separator not valid
        goto cleanup;
    }

    // check that end is only the separator and is of expected size (1 or 0 if the end)
    if ((*pEnd == separator && strlen(pEnd) == 1)
        || (*pEnd == separator && separator == '\0' && strlen(pEnd) == 0)) {
        if (num < min || num > max) {
            // number of out range
            goto cleanup;
        }
    } else {
        // pEnd is larger than expected or not the correct separator
        goto cleanup;
    }
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

    // if not valid size just toss
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
    }
    cleanup:
    return res;
}