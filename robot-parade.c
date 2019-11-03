/***********************************************************************
 * Name:  Devansh Chandgothia                                          *
 * Project: Robot Parade                                               *
 ***********************************************************************/

/* *********************************************************************
 *   Written/online sources used:                                      *
 *     Robot Command Project by Devansh Chandgothia                    *
 *     quarts-comm-line by Henry Walker                                *
 *     comm-line-example.c by Henry Walker                             *
 *     http://www.cs.grinnell.edu/~walker/courses/161.sp18/            *
 *     show-resource.php?resourceID=1037                               *
 *     http://www.cs.grinnell.edu/~walker/courses/161.sp18/            *
 *     scribbler2-sensors.php                                          *
 ***********************************************************************/

#include <stdio.h>
#include <MyroC.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void forwardAction(FILE * input, FILE * output);
void backwardAction(FILE * input, FILE * output);
void turnLeftAction(FILE * input, FILE * output);
void turnRightAction(FILE * input, FILE * output);
void beepAction(FILE * input, FILE * output);
void songAction(FILE * input, FILE * output);
void song(int n);
void timeLog(FILE * output);
void brightnessLog(FILE * output);


/* Preconditions for main: Scribbler robot must be switched on
                           The Program ends only after the program reads "quit"
                           from either of the input souces
  Postconditions for main: The robot performs movements and beeps, depending
                           on the choices of user and inputs given by the user
                           to those choices.
*/
int main(int argc, char * argv[]) {
  rConnect("/dev/rfcomm0"); //Connecting with the scribbler robot
  printf("This program allows the user to control the actions and sounds");
  printf(" of the scribbler robot to perform in a robot parade\n\n");


  //Inital commands to move to starting line
  FILE * inputSource= stdin;
  FILE * outputFile= NULL;


  // processing command-line parameters
  for (int i = 1; i < argc; i++) {
    if (strcmp (argv[i], "-input") == 0) {
      inputSource = fopen(argv[i+1], "r");
      i++; //Incrementing i so that for loop does not compare the file name
    }
    else if (strcmp (argv[i], "-log") == 0) {
      outputFile = fopen(argv[i+1], "w");
      i++;
    }
    else
    printf ("unrecognized command-line argument\n");
  }

  char ch;
  printf("Enter a letter to start movement towards starting point: ");
  scanf(" %c", &ch);
  rMotors(0.25, 0.25);
  printf("Enter a letter to stop movement: ");
  scanf(" %c", &ch);
  rMotors(0.0,0.0);

  //Declaring variables
  char option[10]= "NULL";
  double speed, duration;
  int num, frequency;

  if(inputSource == stdin) {
    //Printing the menu options
    printf ("Menu Options\n");
    printf ("forward\n");
    printf ("backward\n");
    printf ("turnLeft\n");
    printf ("turnRight\n");
    printf ("beep\n");
    printf ("song\n");
    printf ("quit\n");
  }

  //While quit is not entered by the user
  while ((strcmp(option, "quit")) != 0) {
    //Accepting an option from the user
    if(inputSource == stdin) {
      printf ("Enter option:  ");
    }
    fscanf(inputSource, " %s", option);

    if(outputFile != NULL)
    fprintf(outputFile, "%s ", option);

    //Checking which option to perform
    if ((strcmp(option, "forward")) == 0) {
      forwardAction(inputSource, outputFile);
    }
    else if ((strcmp(option, "backward")) == 0) {
      backwardAction(inputSource, outputFile);
    }
    else if ((strcmp(option, "turnLeft")) == 0) {
      turnLeftAction(inputSource, outputFile);
    }
    else if ((strcmp(option, "turnRight")) == 0) {
      turnRightAction(inputSource, outputFile);
    }
    else if ((strcmp(option, "beep")) == 0) {
      beepAction(inputSource, outputFile);
    }
    else if ((strcmp(option, "song")) == 0) {
      songAction(inputSource, outputFile);
    }
    else if ((strcmp(option, "quit")) == 0) {
      break;//Exiting the while loop
    }
    else {
      //None of the menu options matched with what the user entered
      if(inputSource == stdin)
      printf("Wrong option. Please enter a correct option.\n");
      else
      while(fgetc(inputSource) != '\n');
    }
  }
  fclose (inputSource);
  fclose (outputFile);
  rDisconnect();//Disconnecting with the robot
  return 0; //No errors
}

void forwardAction(FILE * input, FILE * output) {
  if(input == stdin) {
    printf("Enter speed and duration:  ");
  }
  fscanf(input, "%lf", &speed);
  fscanf(input, "%lf", &duration);
  if(output != NULL) {
    fprintf(output, "%lf ", speed);
    fprintf(output, "%lf ", duration);
    timeLog(output);
    brightnessLog(output);
    fprintf (output, "\n");
  }
  rForward(speed,duration);
  if(input != stdin)
  while(fgetc(input) != '\n');
}

void backwardAction(FILE * input, FILE * output) {
  if(input == stdin)
  printf("Enter speed and duration:  ");
  fscanf(input, "%lf", &speed);
  fscanf(input, "%lf", &duration);
  if(output != NULL) {
    fprintf(output, "%lf ", speed);
    fprintf(output, "%lf ", duration);
    timeLog(output);
    brightnessLog(output);
    fprintf (output, "\n");
  }
  rBackward(speed,duration);
  if(input != stdin)
  while(fgetc(input) != '\n');
}

void turnRightAction(FILE * input, FILE * output) {
  if(input == stdin)
  printf("Enter speed and duration:  ");
  fscanf(input, "%lf", &speed);
  fscanf(input, "%lf", &duration);
  if(output != NULL) {
    fprintf(output, "%lf ", speed);
    fprintf(output, "%lf ", duration);
    timeLog(output);
    brightnessLog(output);
    fprintf (output, "\n");
  }
  rTurnRight(speed,duration);
  if(input != stdin)
  while(fgetc(input) != '\n');
}

void turnLeftAction(FILE * input, FILE * output) {
  if(input == stdin)
  printf("Enter speed and duration:  ");
  fscanf(input, "%lf", &speed);
  fscanf(input, "%lf", &duration);
  if(output != NULL) {
    fprintf(output, "%lf ", speed);
    fprintf(output, "%lf ", duration);
    timeLog(output);
    brightnessLog(output);
    fprintf (output, "\n");
  }
  rTurnLeft(speed,duration);
  if(input != stdin)
  while(fgetc(input) != '\n');
}

void beepAction(FILE * input, FILE * output) {
  if(input == stdin)
  printf("Enter duration and frequency:  ");
  fscanf(input, "%lf", &duration);
  fscanf(input, "%d", &frequency);
  if(output != NULL) {
    fprintf(output, "%lf ", duration);
    fprintf(output, "%d ", frequency);
    timeLog(output);
    brightnessLog(output);
    fprintf (output, "\n");
  }
  rBeep(duration,frequency);
  if(input != stdin)
  while(fgetc(input) != '\n');
}

void songAction(FILE * input, FILE * output) {
  if(input == stdin)
  printf("Enter the number of repitions:  ");
  fscanf(input, "%d", &num);
  if(output != NULL) {
    fprintf(output, "%d ", num);
    timeLog(output);
    brightnessLog(output);
    fprintf (output, "\n");
  }
  song(num);
  if(input != stdin)
  while(fgetc(input) != '\n');
}

void song(int n) {
  while(n>0) {
    rBeep(0.3, 740);
    rBeep(0.3, 740);
    rBeep(0.6, 795);
    rBeep(0.2, 740);
    rBeep(0.2, 890);
    rBeep(0.4, 850);
    n--;
  }
}

void timeLog(FILE * output) {
  /* determine time and print it */
  time_t mytime = time (NULL);
  char * timeStr = ctime (&mytime);

  /*remove '\n' at end of time string, if present */
  if (timeStr[strlen(timeStr)-1] == '\n') {
    timeStr[strlen(timeStr)-1] = 0;
  }
  fprintf (output, "   %s", timeStr);
}

void brightnessLog(FILE * output) {
  fprintf (output, " (");
  fprintf (output,"%d,", rGetLightTxt("left", 3));
  fprintf (output," %d,", rGetLightTxt("middle", 3));
  fprintf (output," %d", rGetLightTxt("right", 3));
  fprintf (output, ")");
}
