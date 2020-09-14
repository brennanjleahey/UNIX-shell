

#define MAX_LINE 80
#define MAX_PARAM 8
#define MAX_HISTORY_SIZE 100


int elemIndex;
int historyCount;
char *historyBuffer[MAX_HISTORY_SIZE];


//Function to get the size of the history buffer
int sizeOfBuffer();

//Function that adds a command to the history buffer if the size of the buffer is not exceeded.
//Otherwise, clear the first command in the buffer, and add the command there.
//Parameter - cmdToAdd is the command to be added.
void addCmdToHistory(char *cmdToAdd);

//Function to display the history buffer
void displayHistory();

//Function to set recent command
void setRecentCommand(int *recCom);

//Function to get most recent command
int getRecentCommand();

//Function to clear the history buffer
int clearHistory(char *historyBuffer[]);

//Function to parse a string of 1 or more commands entered by the user
void parse(char *cmd, char **params);
