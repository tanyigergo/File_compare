
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./compare file1 file2\n");
        return 1;
    }

    // remember filenames
    char *file1 = argv[1];
    char *file2 = argv[2];
    unsigned char byteFirst = 0;
    unsigned char byteSecond= 0;
    int cnt = 0;



    /************************************************ open first file *******************************/
    FILE *inptr = fopen(file1, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file1);
        return 2;
    }

    /************************************************ open second file *******************************/
    FILE *outptr = fopen(file2, "r");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", file2);
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

    // close file1
    fclose(inptr);

    // close file2
    fclose(outptr);

    printf("There are %d differences!\n", cnt);

    // success
    return 0;
}
