#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/* This comment must not be removed
This  File was written by PetrifiedLasagna and is from the following Github repository
https://github.com/PetrifiedLasagna/random-number-generator-and-visualizer

these files should come with a file explaining their usage/license.
*/

///data is aligned to match 18 bytes. Notice all char variables are created first
typedef struct TGAH {

    char offset;

    char colort;
    char imgt;

    char bpp;
    char orien;

    char palb;
    short palstr;
    short pallen;

    short orx;
    short ory;
    short width;
    short height;
};

///24 bit pixels(no alpha)
typedef struct pixel24 {
    char red;
    char green;
    char blue;
};

///Write the header info
void writehead(FILE *f, TGAH *inf){
    fwrite(&inf->offset, 1, 1, f);

    fwrite(&inf->colort, 1, 1, f);
    fwrite(&inf->imgt, 1, 1, f);

    fwrite(&inf->palstr, 2, 1, f);
    fwrite(&inf->pallen, 2, 1, f);
    fwrite(&inf->palb, 1, 1, f);

    fwrite(&inf->orx, 2, 1, f);
    fwrite(&inf->ory, 2, 1, f);
    fwrite(&inf->width, 2, 1, f);
    fwrite(&inf->height, 2, 1, f);

    fwrite(&inf->bpp, 1, 1, f);
    fwrite(&inf->orien, 1, 1, f);
}

///Write pixels
void writepixels(FILE *f, pixel24 *pixs, int num){
    fwrite(pixs, num * sizeof(pixel24), 1, f);
}

int main(int argc, char *argv[]){

    genrseed();
    FILE *f;

    if(argc>1 && strcmp(argv[1], "ascii")==0){
        int fillen = 0;

        if(argc > 2)
            strtol(argv[2], NULL, 0);

        if(fillen == 0)
            fillen = 1000;

        f = fopen("rnd.txt", "w");
        if(f == NULL)
            return 3;

        for(int i = 0; i < fillen; i++)
            fprintf(f, "%u\n", (unsigned)rnd()%256);

    }else {

        short imgs = 0;

        if(argc == 2)
            imgs = strtol(argv[1], NULL, 0);

        if(imgs == 0)
            imgs = 250;

        ///Setup TGA header information
        TGAH head = {0,
                    0, 2,
                    sizeof(pixel24) * 8,0,
                    0, 0, 0,
                    0, 0, imgs, imgs};

        ///allocate pixel data
        pixel24 *dta = (pixel24*) malloc(imgs*imgs*sizeof(pixel24));
        if(dta == NULL)
            return 1;

        for(int i = 0; i < imgs*imgs; i++){
            int res = rnd()%256;
            res = res < 256/2 ? 0 : 255;
            dta[i].red = dta[i].green = dta[i].blue = res;
        }

        f = fopen("rnd.tga", "wb");
        if(f == NULL)
            return 2;

        writehead(f, &head);
        writepixels(f, dta, imgs*imgs);
    }

    fclose(f);

    return 0;
}
