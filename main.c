#include "hashtable.h"
#include "date_parser.h"


int main(void) {

  HashTable *t = NULL;
  FILE * fp;
  FILE *out_fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int ret = 0;


  t = create_table(1000000);
  if (t == NULL)
    goto cleanup;
  
  fp = fopen("./valid_dates.txt", "r");
  out_fp = fopen("./out_file.txt", "w");

  while ((read = getline(&line, &len, fp)) != -1) {
      // printf("Retrieved line of length %zu:\n", read);
      line[read-1] = '\0';
      // printf("%s\n", line);
      ret = validate_date(line);
      if (ret)
      {
        ret = add_item(t, line);
        if (ret)
          fprintf(out_fp, "%s\n", line);
      }
  }


cleanup:
  if (fp != NULL)
    fclose(fp);
  if (out_fp != NULL)
    fclose(out_fp);
  if (t!= NULL)
    destroy_table(&t);
  return 0;
}