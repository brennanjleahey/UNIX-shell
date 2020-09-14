#include "func.h"
#include "func.c"


//This is a simple shell program that includes the UNIX std library.
//its primary purpose is to take in commands from a user and execute them.
//it will read in processes, fork them, and execute them.
//the parent process will wait for the child process to execute unless
//an ampersand is entered after a command in which case the parent and child
//processes wil run concurrently
int main(void)
{
    printf("--------------------------------------------------------\n");
	printf("Welcome to my shell program. Try entering a command!\n");
    printf("'exit' to quit. /n");
	printf("--------------------------------------------------------\n");

     char *args[MAX_LINE / 2 + 1];
     int should_run = 1;
     printf("\n");
     clearHistory(historyBuffer);


     while (should_run != 0)
     {
          printf("\nosh> ");
          fflush(stdout);

          // c-str declarations
          char command[20]; // cmd entered by user
          // special command chars
          char exitCmd[5] = "exit";
          char amp[2] = "&";

          int statusChild;

          scanf("%s", command);

          parse(command, args);


          addCmdToHistory(*args);

          // check if user wants to exit
          if (strcmp(command, exitCmd) == 0)
          {
               printf("Program Terminated\n");
               should_run = 0;
               exit(0);
          }


          char hist[8] = "history";
          if ( strcmp(command, hist) == 0)
          {
               displayHistory();
               continue;
          }

          // fork a child process to handle command execution
          pid_t pid;
          pid = fork();

            // if fork failed, return
        if(pid < 0)
        {
            fprintf(stderr, "Fork Failed.");
            return 1;
        }

    		//Child process will execute user command
        else if(pid == 0)
          {
               //Check if command is !!
            char execRecent[3] = "!!";
            if(strcmp(command, execRecent) == 0)
                {
                //get the most recent command in the history buffer
                int rec = getRecentCommand();

                if(rec < 0)
				{
                    printf("No commands in history.\n");
					continue;
				}

				//Execute command
				rec = rec - 1;
				printf("Recent command is: %s", historyBuffer[rec - 1]);
				printf("\n");
				execvp(historyBuffer[rec - 1], args);
				continue;
                }
                //Check to see if command is !N
                if(command[0] == '!')
                {
                    int commandNum;
                    int one = 1;

                    if(isdigit(command[1]))
                    {
                        //Get the command number to execute and convert to int
                        commandNum = atoi(&command[one]);

                        //User command exceeds historyBuffer size
                        if(commandNum > historyCount)
                        {
                            printf("No such command in history.\n");
                        }
                        else
                        {
                            //Execute Nth command
                            printf("Command %i is: %s", commandNum, historyBuffer[commandNum-1]);
                            printf("\n");
                            execvp(historyBuffer[commandNum - 1], args);
                        }
                    }
                    continue;
                }
                //Execute regular command
                else
                {
                    //Execute command
                    execvp(args[0], args);

                    //Incorrect command was entered
                    int executeReturn = execvp(args[0], args);

                    if(executeReturn == -1)
                    {
                        exit(0);
                    }
               }
        }
        //Parent process
        else
        {
            if (!(command == amp))
            {
                wait(&statusChild);
            }
        else
		   {
                exit(0);
		   }
        }
    }

    return 0;
} //end main


