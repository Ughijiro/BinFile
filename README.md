This program reads a binary file containing a sequence of signed integers, each encoded in a custom format:

Each integer is preceded by a 1-byte size tag indicating its length:

0x01 → 1-byte integer

0x02 → 2-byte integer

0x04 → 4-byte integer

The integer data follows the tag and is stored in little-endian format.

The program processes all integers in the file and writes the following statistics to an output text file:

Maximum integer value

Minimum integer value

Average of all integers (to two decimal places)

Count of 1-byte, 2-byte, and 4-byte integers

Usage:
./program input_file.bin output_file.txt
