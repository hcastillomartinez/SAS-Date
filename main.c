#include "hashtable.h"
#include "date_parser.h"
#include <errno.h>

int main(int argc, char *argv[]) {

    HashTable *t = NULL;
    FILE *fp = NULL;
    FILE *out_fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int ret = 0;
    char *rest = NULL;
    long count = 0;
    const char *date_file = "./valid_dates.txt"; // default name


    if (argc < 2) {
        printf("need a count\n");
        return 1;
    }

    errno = 0;
    count = strtol(argv[1], &rest, 10);
    if (errno != 0 || *rest != '\0') {
        printf("Invalid value for count\n");
        return 1;
    }

    if (argc < 3) {
        printf("using default data file %s\n", date_file);
    } else {
        date_file = argv[2];
    }

    printf("Table size: %ld\nData file: %s\n", count, date_file);

    fp = fopen(date_file, "r");
    if (fp == NULL) {
        ret = 1;
        printf("Bad date file\n");
        goto cleanup;
    }

    out_fp = fopen("./out_file.txt", "w");
    if (out_fp == NULL) {
        ret = 1;
        goto cleanup;
    }

    t = create_table(count);
    if (t == NULL) {
        ret = 1;
        goto cleanup;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        line[read - 1] = '\0'; // drop the \n
        ret = validate_date(line);
        if (ret) {
            ret = add_item(t, line);
            if (ret)
                fprintf(out_fp, "%s\n", line);
        }
    }

    ret = 0;
    cleanup:
    if (fp != NULL) {
        fclose(fp);
    }
    if (out_fp != NULL) {
        fclose(out_fp);
    }
    if (t != NULL) {
        destroy_table(&t);
    }
    return ret;
}