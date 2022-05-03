# Recover
## This Project Is Homework From Harvard's CS50 Class. Per Their Academic Honesty Policy You Are NOT Allowed To Use This code As A Submission For Your Homework!

Recovers JPEGS from a deleted memory card

Project: Recover | Language: C‍

For this homework assignment, we had to create a program that would iterate over a broken / deleted hard drive and find and recover all the pictures that were on it.The pictures were JPEG. This was my first time working with files inside of C by loading and unloading them. I learned how to iterate over them in 512 byte chunks and I wrote a program that initially look for the first 4 bytes of a JPEG, and once it found a JPEG it would open a new file, name it by JPEG 000 and start writing the data to the file. Once it found a new JPEG 4 byte header, it would close the file it was writing, open a new file incrementing the '000' value by 1 and start writing the data to a new file.My program was successful and was able to recover all the lost images!

Assignment given:

Implement a program called recover that recovers JPEGs from a forensic image.

Implement your program in a file called recover.c in a directory called recover.

Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.

If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.

If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.

The files you generate should each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.

Your program, if it uses malloc, must not leak any memory.
