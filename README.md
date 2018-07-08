# Speller
Speller is a real-time spell checker that inspects .txt for errors. This was inspired by Harvard CS50's spell checker project. To run this program, go into the directory on a UNIX command line and execute 

>$ make 

and then execute 

>$ ./speller <.txt file to check>

I optimized the program's run-time by using an efficient hash function and storing the dictionary in a hash table.