#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM    "randstr"
#define AUTHOR     "V. Silvansky"
#define MAIL       "<v.silvansky@gmail.com>"
#define YEARS      "2012"
#define VERSION    "0.1"

#define KEY_HELP           "--help"
#define KEY_HELP_SHORT     "-h"
#define KEY_VERSION        "--version"
#define KEY_VERSION_SHORT  "-v"

#define L(X) strlen(X)

#define GLOBAL_BUFFER_INITIAL_SIZE   1024
#define GLOBAL_BUFFER_GROW           2.0

// global string buffer
static char * globalBuffer = NULL;
static size_t globalBufferLength = 0;
static size_t globalBufferSize = 0;

void printUsage()
{
	// TODO
}

void printVersion()
{
	// TODO
}

size_t initBuffer()
{
	if (!globalBuffer)
	{
		globalBufferSize = GLOBAL_BUFFER_INITIAL_SIZE;
		globalBuffer = malloc(globalBufferSize);
		globalBufferLength = 0;
	}
	return globalBufferSize;
}

size_t growBuffer()
{
	char * tmp = globalBuffer;
	globalBufferSize = (size_t)(globalBufferSize * GLOBAL_BUFFER_GROW);
	globalBuffer = malloc(globalBufferSize);
	memcpy(globalBuffer, tmp, globalBufferLength);
	free(tmp);
	return globalBufferSize;
}

void releaseBuffer()
{
	if (globalBuffer)
	{
		free(globalBuffer);
		globalBufferLength = globalBufferSize = 0;
	}
}

size_t addToBuffer(const char * str, size_t size)
{
	initBuffer();
	if (size > globalBufferSize - globalBufferLength)
	{
		growBuffer();
	}
	strncpy(globalBuffer + globalBufferLength, str, size);
	globalBufferLength += size;
	return globalBufferLength;
}

int countInBuffer(char c)
{
	int count = 0;
	char * found = globalBuffer;
	while (found)
		if ((found = strchr(found, c)))
		{
			count++;
			found++;
		}
	return count;
}

char * getLineFromBuffer(int line, size_t *size)
{
	int pos = 0;
	char *found = globalBuffer;
	char *prevFound = NULL;
	while (pos != line + 1)
	{
		prevFound = found;
		found = strchr(found, '\n');
		found++;
		pos++;
	}
	*size = found - prevFound;
	char *tmpLine = malloc((*size) + 1);
	strncpy(tmpLine, prevFound, *size);
	if (tmpLine[(*size) - 1] == '\n')
		tmpLine[(*size) - 1] = '\0';
	else
		tmpLine[*size] = '\0';
	return tmpLine;
}

int main(int argc, char *argv[])
{
	// TODO: add possibility to read from custom file (first argument is file name)
	// FILE *file;
	// if (no args) file = stdin;
	if (argc > 1)
	{
		if ((!strncmp(argv[1], KEY_HELP, L(KEY_HELP)) || !strncmp(argv[1], KEY_HELP_SHORT, L(KEY_HELP_SHORT))) || argc > 2)
		{
			printUsage();
		}
		if (!strncmp(argv[1], KEY_VERSION, L(KEY_VERSION)) || !strncmp(argv[1], KEY_VERSION_SHORT, L(KEY_VERSION_SHORT)))
		{
			printVersion();
		}
	}
	else
	{
		while (!feof(stdin))
		{
			size_t sz = 0;
			char * tmp = fgetln(stdin, &sz);
			char * tmpBuff = malloc(sz);
			strncpy(tmpBuff, tmp, sz);
			addToBuffer(tmpBuff, sz);
			free(tmpBuff);
		}
		size_t sz = 0;
		srandomdev();
		long rndLine = random() % countInBuffer('\n');
		char *result = getLineFromBuffer(rndLine, &sz);
		printf("%s\n", result);
		free(result);
	}
	releaseBuffer();
	return 0;
}
