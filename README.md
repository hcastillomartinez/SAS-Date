# SAS-Date
Program that reads a large list of date-time values from a file and writes to a separate file the list of unique, valid date-time values (no duplicates). A valid date-time value follows the format ISO 8601.

## Assumptions
Data files follow the structure of each date being on a single line.

Output file follows the same structure and will be named out_file.txt

## Building
Makefile at root will build the program with the following command `make build`. This will build the program and also generate
test data. The files generated are valid_dates.txt and invalid_dates.txt and each contain 1000 records. Python script that generates test data
is also standalone and amount of records desired is the only argument eg `./generator.py 10000`

Additionaly, `make clean` is provided to clear out generated files and cmake cache files.

## Running
The program takes 2 arguments. First is **count** (required) which determines the size of the number of buckets in the hashtable that is used to verify uniqueness.
 Second (optional) is **path** which is the fully qualified or relative path to file.


Makefile also provides a quick way to run the program via `make test`.