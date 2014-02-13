#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main (int argc, char** argv)
{
	int i = 1;
	int toreturn = 0;
	int invertflag = 0;
	int linenumflag = 0;
	int quietflag = 0;
	FILE * fp = stdin;
	char input[2000];
	int linenum = 1;
    
	while(argv[i]!=NULL) //scan commands, set flags
	{
		if (strcmp(argv[i], "--help") == 0)
		{
			printf("Usage: grep-lite [OPTION]... PATTERN\n");
            printf("Search for PATTERN in standard input. PATTERN is a\n");
            printf("string. grep-lite will search standard input line by\n");
            printf("line, and (by default) print out those lines which\n");
            printf("contain pattern as a substring.\n\n");
			printf("  -v, --invert-match     select non-matching lines\n");
			printf("  -n, --line-number      print line numbers with output\n");
			printf("  -q, --quiet            suppress all output\n\n");
			printf("Exit status is 0 if any line is selected, 1 otherwise;\n");
			printf("if any error occurs, then the exit status is 2.\n\n");
            return EXIT_SUCCESS;
        }
		if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--invert-match") == 0)
		{
			invertflag = 1;
		}
		if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--line-number") == 0)
		{
			linenumflag = 1;
		}
		if(strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0)
		{
			quietflag = 1;
			toreturn = 0;
			return toreturn;
		}
        i++;
    }
	//if -v is found
	//set invert flag
	//print strstr!=null lines instead
	//******************
	//if -n is found
	//set linenum flag
	//print line numbers
	//*******************
	//if -q is found
	//set quiet flag
	//no output
	int len = i - 1;
	if(argv[len][0] == '-')
	{
		fprintf(stderr, "ERROR: PATTERN cannot start with '-'\n");
		toreturn = 2;
		return toreturn;
	}
	while(fgets(input, sizeof(input), fp))
	{
		if(input == NULL)
		{
			break;
		}
		if(linenumflag == 0)
		{
			if(invertflag == 0)
			{
				if(strstr(input, argv[len])!=NULL)
				{
					printf("%s",input);
				}
			}
			else
			{
				if(strstr(input, argv[len])==NULL)
				{
					printf("%s",input);
				}
			}
		}
		else
		{
		if(invertflag == 0)
			{
				if(strstr(input, argv[len])!=NULL)
				{
					printf("%d:%s",linenum,input);
				}
			}
			else
			{
				if(strstr(input, argv[len])==NULL)
				{
					printf("%d:%s",linenum,input);
				}
			}
		}
		linenum++;
	}
	//REGULAR FUNCTIONALITY WORKS
	//-v works
	//-q works...?
	//Working on -n
	
	return toreturn;
}