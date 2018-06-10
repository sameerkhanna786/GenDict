# GenDict

Philphix is a replacement tool that accepts a single command line argument, the name of a replacement set to use. This replacement set consists of pairs of "words", each pair on its own line. The first word only consists of alphanumeric characters, but the second word can include any non-whitespace printable character.

For each word (sequence of letters and numbers unbroken by any other character) in the input it processes it to see if it should be replaced. It first checks if that word is in the replacement set, then checks that word with all but the first character converted to lower case, and finally checks if the word converted completely to lower case. If there is no match the word is printed to standard output unchanged; if there is a match, it prints the highest priority match.
