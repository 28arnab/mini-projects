#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// We are going to work with chunks of 512 bytes
#define BLOCK_SIZE 512
// JPEG files have a special start signature that is 4 bytes long
#define JPEG_HEADER_SIZE 4

// We use BYTE to mean a single byte (like a small piece of data)
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if the user gave us exactly one file name
    if (argc != 2)
    {
        // If not, show them how to use the program
        printf("Usage: %s image\n", argv[0]);
        return 1; // Tell the computer something went wrong
    }

    // Open the file the user gave us
    FILE *infile = fopen(argv[1], "r");
    // If we can't open the file, show an error message
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 1; // Tell the computer something went wrong
    }

    // A place to store our data chunks
    BYTE buffer[BLOCK_SIZE];
    // We need to keep track of how many pictures we've found
    int file_count = 0;
    // A place to keep track of our current picture file
    FILE *outfile = NULL;
    // The name we will give to each picture file
    char filename[8];

    // Read the file in chunks of 512 bytes
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        // Look through each chunk to find the start of a JPEG picture
        for (int i = 0; i < BLOCK_SIZE - JPEG_HEADER_SIZE + 1; i++)
        {
            // Check if we found the start of a JPEG picture
            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff &&
                (buffer[i + 3] >= 0xe0 && buffer[i + 3] <= 0xef))
            {

                // If we already had a picture open, close it
                if (outfile != NULL)
                {
                    fclose(outfile);
                }

                // Give the new picture file a name like "000.jpg", "001.jpg", etc.
                sprintf(filename, "%03d.jpg", file_count++);
                // Open the new picture file
                outfile = fopen(filename, "w");
                // If we can't open the new file, show an error message
                if (outfile == NULL)
                {
                    printf("Could not create file %s.\n", filename);
                    fclose(infile);
                    return 1; // Tell the computer something went wrong
                }
            }

            // If we have a picture file open, write the data to it
            if (outfile != NULL)
            {
                fwrite(&buffer[i], sizeof(BYTE), BLOCK_SIZE - i, outfile);
                // Stop looking in this chunk because we've already written what we need
                break;
            }
        }
    }

    // If we had an open picture file, close it
    if (outfile != NULL)
    {
        fclose(outfile);
    }

    // Close the original file
    fclose(infile);

    // Tell the computer everything went fine
    return 0;
}