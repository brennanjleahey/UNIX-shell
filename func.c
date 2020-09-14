#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

//Function to get the size of the history buffer
int sizeOfBuffer()
{
	return sizeof(historyBuffer) / sizeof(char*);
}

//Function that adds a command to the history buffer if the size of the buffer is not exceeded.
//Otherwise, clear the first command in the buffer, and add the command there.
//Parameter - cmdToAdd is the command to be added.
void addCmdToHistory(char *cmdToAdd)
{
	if(historyCount < MAX_HISTORY_SIZE)
	{
		historyBuffer[historyCount] = strdup( cmdToAdd );
		historyCount++;
	}
	else
	{
		free( historyBuffer[0] );
		int i;
		for(i = 1; i < MAX_HISTORY_SIZE; i++)
		{
			historyBuffer[i - 1] = strdup( cmdToAdd );
		}
		historyCount++;
	}
	elemIndex = historyCount;
}

//Function to display the history buffer
void displayHistory()
{
	int elemIndex = historyCount-1;
	if(elemIndex == 0)
	{
		printf("No commands in history");
     }

	int count = 0;
	printf("\n");

	while(count < 10 && elemIndex >= 0)
	{
		printf("%i - ", elemIndex+1);
		printf("%s", historyBuffer[elemIndex]);
		printf("\n");
		elemIndex--;
		count++;
	}
}

//Function to set recent command
void setRecentCommand(int *recCom)
{
	*recCom = elemIndex;
}

//Function to get most recent command
int getRecentCommand()
{
	return elemIndex;
}

//Function to clear the history buffer
int clearHistory(char *historyBuffer[])
{
	int i;

	for(i = 0; i < sizeOfBuffer(); i++)
	{
		free(historyBuffer[i]);
		historyBuffer[i] = NULL;
	}
	return 0;
}
//Function to parse a string of 1 or more commands entered by the user
void parse(char *cmd, char **params)
{
    int i;
    for (i = 0; i < MAX_PARAM; i++)
    {
        params[i] = strsep(&cmd, " ");

        if (params[i] == NULL)
        {
            break;
        }
    }
}