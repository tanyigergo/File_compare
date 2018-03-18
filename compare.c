/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./copy file1 file2\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];
    unsigned char byteFirst = 0;
    unsigned char byteSecond= 0;
    int cnt = 0;



    /************************************************ open first file *******************************/
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    /************************************************ open second file *******************************/
    FILE *outptr = fopen(outfile, "r");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    fseek( inptr, 0, SEEK_SET );
    fseek( outptr, 0, SEEK_SET );


/********************************Read both files byte by byte till EOF of either file***********/

    while( !( feof(inptr) ) || ( feof(outptr) ))
    {
        //Read  bytes from both files
        fread(&byteFirst, sizeof(char), 1, inptr);
        fread(&byteSecond, sizeof(char), 1, outptr);

        //If they differ, prints it out
        if (byteFirst != byteSecond)
        {
            cnt++;
            printf("Difference in %ld. byte (%02x : %02x)\n", ftell(inptr), byteFirst, byteSecond);
        }


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    printf("There are %d differences!\n", cnt);

    // success
    return 0;
}
