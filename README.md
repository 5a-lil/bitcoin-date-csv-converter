# Bitcoin_Date_CSV_Converter

A program that takes a file as input and outputs the value associated to a given date based on bitcoin value over the years.

To test, do this first to compile the program:

````
$ make
````

Then with this ```test-file``` as input file:

```
$ cat -e test-file
date | value$
2011-01-01 | 22$
2011-10-26 | 20.7$
2008-00-00 | 321$
2011-12-36 | 1$
2011-12-01 | ddd$
```

Do:

```
$ ./btc test-file | cat -e
2011-01-01 => 22 = 6.6$
2011-10-26 => 20.7 = 62.1$
Error: input a month between 1 and 12.$
Error: input a month between 1 and 31.$
Error: bad input => 2011-12-01 | ddd$
```

Note: the given ```data.csv``` is considered constant, i voluntary didn't parse it, so don't change it if you want things to work correctly.

Have fun ! 🔥
