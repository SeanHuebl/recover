#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Number of bytes per block
const int BLOCK_SIZE = 512;

// Define a new byte type for 8 bit unsigned integer
typedef uint8_t BYTE;

// Define file number for writing image
BYTE digit_one = 0;
BYTE digit_two = 0;
BYTE digit_three = 0;
FILE *output;

void image_blocks(FILE *image);
bool first_three_bytes(BYTE bytes[]);
bool fourth_byte(BYTE fourth);
bool is_jpeg(BYTE b[]);
void count_up(void);

int main(int argc, char *argv[])
{

    // Only one command line argument
    if (argc != 2)
    {
        printf("Use format: ./format .jpg\n");
        return 1;
    }

    // Read input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    image_blocks(input);

    return 0;
}
// Helper Functions

// Return amount of 512byte blocks are in an image
void image_blocks(FILE *image)
{
    // Allocating 8 slots of memory, since ###.jpg is 7 and we need the \0
    char *image_number = malloc(8);

    // In case bytes dont start on a jpeg
    bool start_writing = false;

    // Iterate over data in 512 byte block chunks until finds new image bytes
    BYTE buffer[BLOCK_SIZE];

    // Will return false at end of data
    while (fread(buffer, 1, BLOCK_SIZE, image) == BLOCK_SIZE)
    {
        // Check first 4 bytes a jpeg == true signifies the start of a new image or first image
        if (is_jpeg(buffer))
        {
            // Now that we have found our first jpeg we set start writing to true
            start_writing = true;

            // Checking if we are on the first image aka 000.jpg, we omit fclose() on this one
            if (digit_one == 0 && digit_two == 0 && digit_three == 0)
            {
                // Sets image_number to a string based on the digits
                sprintf(image_number, "%i%i%i.jpg", digit_three, digit_two, digit_one);

                // Open new file to write based on image_number string
                output = fopen(image_number, "w");

                // Increments the digits
                count_up();
            }

            // If not the first jpeg found we must call fclose() to close currunt file as we are starting new blocks of data
            else
            {
                fclose(output);

                // Create new string at image_number since the digits change after every count up
                sprintf(image_number, "%i%i%i.jpg", digit_three, digit_two, digit_one);

                // Open a new file to output with name based on new image_number
                output = fopen(image_number, "w");

                // Increments the digits
                count_up();
            }
        }

        // Checking if start_writing is true, to block against first bytes of data not being jpeg
        if (start_writing)
        {
            // If true, take the buffer block of data and write it to output
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }

        // Loop again for new block
    }

    // Free up the memory
    free(image_number);
}

// Checks values of first three bytes of data to determine if jpeg is possible
bool first_three_bytes(BYTE bytes[])
{
    // Is first value a jpg value? if not we return early returning false
    if (bytes[0] != 0xff)
    {
        return false;
    }

    // If first value is true, we now check if second value is a jpg value. If not we return early returning false
    if (bytes[1] != 0xd8)
    {
        return false;
    }

    // First two bytes are jpg bites, but is the third?
    if (bytes[2] != 0xff)
    {
        return false;
    }

    // First three bytes are jpg bites, now we can return true since it is possible jpg, fourth byte a little more complicated
    return true;
}

// Checks fourth byte of data to determine if jpeg
bool fourth_byte(BYTE fourth)
{
    // Loops through all possible values of the fourth bite that still mean jpg
    for (BYTE i = 0xe0; i < 0xef; i++)
    {
        if (fourth == i)
        {
            return true;
        }
    }
    // If fourth bite isnt jpg we return false
    return false;
}

// This function combines first three bytes and fourth bytes check into one
bool is_jpeg(BYTE b[])
{
    // If first three bytes is false we don't bother checking fourth
    if (first_three_bytes(b))
    {
        // Checking fourth byte values to block against cases where 3 bites of data are jpg just by chance
        if (fourth_byte(b[3]))
        {
            // If all 4 bytes of data match up to jpg bytes, then we can return true, this IS a jpg
            return true;
        }
    }

    return false;
}

// Counting up from 000 by 1
void count_up(void)
{
    // Are we at i.e 009?
    if (digit_one == 9)
    {
        // Are we at i.e 099?
        if (digit_two == 9)
        {
            // Reset digits one and two to 0 and increment third digit i.e 100
            digit_three++;
            digit_two = 0;
            digit_one = 0;
        }

        else
        {
            // If not at i.e 099 increment digit two and reset digit one
            digit_two++;
            digit_one = 0;
        }
    }

    // Not at i.e 009?
    else
    {
        // Increment digit one
        digit_one++;
    }
}