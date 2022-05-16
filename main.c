#include "hashtable.h"
#include "date_parser.h"


int main(void) {

  HashTable *t = NULL;
  t = create_table(10000);
  if (t != NULL)
  {
    printf("Have a table!\n");
  }

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("./dates.txt", "r");
  int ret = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
      // printf("Retrieved line of length %zu:\n", read);
      line[read-1] = '\0';
      printf("%s\n", line);
      ret = validate_date(line);
      if (ret)
      {
        ret = add_item(t, line);
        if (ret)
          printf("Added date = %d\n", ret);
        else
          printf("Collision\n");
      }
  }

  fclose(fp);

  destroy_table(&t);

  if (t == NULL)
  {
    printf("Table is destroyed!\n");
  }
  return 0;
}