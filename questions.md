# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word in the English dictionary, refers to a lung disease caused by inhaling ash and dust. This is significant because it gives us an upper bound on our word array.

## What does `getrusage` do?

getrusage (a.k.a. get resource usage) returns resource usage measurments. It is called in the format

    int getrusage(int who, struct rusage *usage);

which returns usage measures for 'int who'. In speller.c, the value of who is RUSAGE_SELF, which returns resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

## How many members are in a variable of type `struct rusage`?

There are 16 members/fields:
struct rusage
{
               struct timeval ru_utime; /* user CPU time used */
               struct timeval ru_stime; /* system CPU time used */
               long   ru_maxrss;        /* maximum resident set size */
               long   ru_ixrss;         /* integral shared memory size */
               long   ru_idrss;         /* integral unshared data size */
               long   ru_isrss;         /* integral unshared stack size */
               long   ru_minflt;        /* page reclaims (soft page faults) */
               long   ru_majflt;        /* page faults (hard page faults) */
               long   ru_nswap;         /* swaps */
               long   ru_inblock;       /* block input operations */
               long   ru_oublock;       /* block output operations */
               long   ru_msgsnd;        /* IPC messages sent */
               long   ru_msgrcv;        /* IPC messages received */
               long   ru_nsignals;      /* signals received */
               long   ru_nvcsw;         /* voluntary context switches */
               long   ru_nivcsw;        /* involuntary context switches */
};

## Why do we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

We do this because passing large structs is inefficient and takes up a lot of memory, and therefore we pass their pointers as parameters instead.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

1) If the character is an alphabetical character or an apostrophe that is not at index 0 of the word, the character is appended to the word array.
2) Else if the character is numerical, the word is ignored and we skip ahead to the next word (which is found after a space).
3) Else if we hit a space or punctuation, we must have found a whole word so we terminate the word by adding \0 to the word array.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

If we use fscanf(), it will only read characters until a space is found. Since sentences in .txt files can sometimes end in punctuation marks, fscanf() will treat the punctiation as part of the word.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

We use the 'const' keyword because it prevents changes to the words in the dictionary and the words being read.
