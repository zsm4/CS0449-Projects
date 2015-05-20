/*
  txt2bin.c

  MY NAME: Zachary Martin
  MY PITT EMAIL: zsm4@pitt.edu

  use this command to compile: (you can name the executable whatever you like)
		gcc -W -Wall -Wextra -O2  txt2bin.c  -o txt2bin.exe

  use this command to execute:  (you can of course test on both input files)
		txt2bin.exe sine-1.bin
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	FILE* txtFile, *binFile;	//declare variables
	short int shortVal;

	if (argc<3)	//check for correct # of args
	{
		printf("usage: %s  <infilename> <outfilename> (i.e. ./txt2bin.exe sine-1.txt sine-1.bin)\n", argv[0] );
		return EXIT_FAILURE;
	}

	txtFile = fopen( argv[1], "rt" );	//try to open input file 
	if (txtFile == NULL )	//error if can't open input file
	{
		printf("Can't open %s for input. Program halting\n",argv[1] );
		return EXIT_FAILURE;
	}

	binFile = fopen( argv[2], "wb" );	//try to open output file
	if (binFile == NULL )	//error if can't open output file	
	{
		printf("Can't open %s for output. Program halting\n",argv[2] );
		return EXIT_FAILURE;
	}

	/*
		read each value from the text file using fscanf as a short int and write it out to the binary file using fwrite
	*/

        fscanf(txtFile,"%hi",&shortVal);
	while(feof(txtFile)==0)
	{
            	printf("%d\n",shortVal);	//print number being printed to console for error checking
	    	fwrite(&shortVal,sizeof(shortVal),1,binFile);	//write shortval as binary to binFile
            	fscanf(txtFile,"%hi",&shortVal);	//read in next number to shortval
	}

	fclose( txtFile );	//close files 
	fclose( binFile );

	return EXIT_SUCCESS;  // 0 value return means no errors
}
