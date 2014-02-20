#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "answer05.h"


// -------------------------------------------------------------- BMP_checkValid

/**
 * We are only interested in a subset of 264 functionality.
 */
static int checkValid_264(ImageHeader * header)
{
    // Make sure this is a 264 file
    if (header->magic_number != ECE264_IMAGE_MAGIC_NUMBER) return 0;

    if (header->width == 0 || header->width) return 0;
    
    if (header->height == 0) return 0;
	
	unsigned long long overflowCheck;
    overflowCheck = header->width*header->height;
    if(overflowCheck >= 0x100000000L){
        return 0;
    }
    
    if (header->comment_len == 0) return 0;
    
    // We're winners!!!
    return 1;   
}

Image * Image_load(const char * filename)
{
    FILE * fp = NULL;
    char * comment;
    uint8_t * pixels;
    int pixelcount;
    //int c;
    Image * returnImage;
    size_t read;
    ImageHeader header;
    //Image * tmp_im = NULL, * im = NULL;
    fp = fopen(filename, "rb");
    if(!fp) {
        fprintf(stderr, "Failed to open file '%s'\n", filename);
        return NULL;
    }
    
    read = fread(&header, sizeof(ImageHeader), 1, fp);
    if(read != 1) {
        fprintf(stderr, "Failed to read header from '%s'\n", filename);
        return NULL;
    }
    
    
    /*if(!err) { // Print the header
    BMP_printHeader(&header);
    }*/
    if(!checkValid_264(&header)) {
        fprintf(stderr, "Invalid header in '%s'\n", filename);
        return NULL;
    }
    
    comment = malloc(header.comment_len);
    if (comment == NULL)
    {
        fprintf(stderr, "Failed to malloc comment \n");
        return NULL;
    }
    if (fread(comment, header.comment_len, 1, fp) != 1)
    {
        fprintf(stderr, "Comment didn't read the correct num of bytes \n");
        free(comment);
        return NULL;
    }
    if (comment[header.comment_len-1]!='\0')
    {
        fprintf(stderr, "The last byte of comment != null \n");
        free(comment);
        return NULL;
    }
    
    
    
    pixelcount = header.width*header.height;
    pixels = malloc(pixelcount);
    if (fread(pixels, pixelcount, 1, fp) != 1)
    {
        fprintf(stderr, "Failed to malloc pixelcount \n");
        free(comment);
        free(pixels);
        return NULL;
    }
    if (fgetc(fp) != EOF)
    {
        fprintf(stderr, "Did not get to EOF \n");
        free(comment);
        free(pixels);
        return NULL;
    }
    returnImage = malloc(sizeof(Image));
    returnImage->width = header.width;
    returnImage->height = header.height;
    returnImage->comment = comment;
    returnImage->data = pixels;
    return returnImage;
}

int Image_save(const char * filename, Image * image)
{
	FILE * fp = NULL;
	fp = fopen(filename, "wb");
	fwrite(&header, sizeof(ImageHeader), 1, fp);
	fwrite(comment, header->comment_len, 1, fp);
	fwrite(pixels, header->width*header->height, 1, fp);
	fclose();

	return 1;
}
void print_usage(char * argv0)
{
    printf("\n"
       "   Usage: %s <in-filename> <out-filename>\n"
       "\n"
       "      Reads ECE264 image file <in-filename> and then:\n"
       "      (1) Converts it to grayscale\n"
       "      (2) Inverts pixel intensity\n"
       "      (3) Writes inverted image to ECE264 file <out-filename>\n"
       "\n",
       basename(argv0));
}

/**
 * Welcome to PA05.
 *
 * This file is an example to help you get started.
 * It works on BMP files and inverts the pixel intensity (whiteness)
 * You will need to write routines to read and write the simpler
 * ece264 format, and perform linear normalization.
 */
int main(int argc, char * * argv)
{
    int ret = EXIT_SUCCESS; // unless otherwise noted

    // Parse input arguments
    if(argc != 3) {
    print_usage(argv[0]);
    if(argc == 2 && strcmp(argv[1], "--help") == 0)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
    }

    const char * in_filename = argv[1];
    const char * out_filename = argv[2];

    // Read the file
    Image * im = Image_load(in_filename);
    if(im == NULL) {
    fprintf(stderr, "Error: failed to read '%s'\n", in_filename);
    return EXIT_FAILURE;
    }

    // Linear Normalization
    int n_pixels = im->width * im->height;
    int ind;
	int min = 255;
	int max = 0;
    for(ind = 0; ind < n_pixels; ind++)
	{
		if (im->data[ind] < min)
		{
			min = im->data[ind];
		}
		if (im->data[ind] > max)
		{
			max = im->data[ind];
		}
	}
	
	for(ind = 0; ind < n_pixels; ind++)
	{
		im->data[ind] = (im->data[ind] - min) * 255.0 / (max - min);
	}

    // Write out a new file
    if(!Image_save(out_filename, im)) {
    fprintf(stderr, "Error attempting to write '%s'\n", out_filename);
    ret = EXIT_FAILURE;
    }

   // Image_free(im); // a memory leak until you write this function
    
 /**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */

    return ret;
}