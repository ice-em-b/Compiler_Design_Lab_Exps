#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
void readLine(FILE *looker, char nonTerminal[], char production[])
{
fscanf(looker, "%[^->]", nonTerminal);
fseek(looker, 2, 1);
fscanf(looker, "%[^\n]", production);
fgetc(looker);
}
void computeFirst(char fileName[])
{
FILE *looker = fopen(fileName, "r");
char nonTerminal[5], production[10], crntState, prevState, buff = fgetc(looker);
crntState = buff;
while(buff != EOF)
{
fseek(looker, -1, 1);
readLine(looker, nonTerminal, production);
if(crntState != prevState)
printf("FIRST(%c) = { ", crntState);
if((isupper(production[0]) != 0) && (nonTerminal[0] != production[0]))
printf("FIRST(%c), ", production[0]);
else if(nonTerminal[0] != production[0])
printf("%c, ", production[0]);
prevState = crntState;
crntState = buff = fgetc(looker);
if(prevState != crntState)
printf("\b\b }\n");
}
fclose(looker);
}
void computeFollow(char fileName[])
{
FILE *looker = fopen(fileName, "r");
FILE *explorer = fopen(fileName, "r");
char crntNT[5], nonTerminal[5], production[10], crntState, prevState, startState, buff, *index,
follower;
crntState = startState = buff = fgetc(looker);
while(buff != EOF)

{
fseek(looker, -1, 1);
readLine(looker, crntNT, production);
if(crntState != prevState)
{
printf("FOLLOW(%s) = { ", crntNT);
if(crntState == startState)
printf("$, ");
fseek(explorer, 0, 0);
while((buff = fgetc(explorer)) != EOF)
{
fseek(explorer, -1, 1);
readLine(explorer, nonTerminal, production);
if((index = strstr(production, crntNT)) == NULL )
continue;
follower = *(index+1);
if((follower == '\0')&&(strcmp(crntNT, nonTerminal) != 0))
printf("FOLLOW(%s), ", nonTerminal);
else if(isupper(follower) != 0)
printf("FIRST(%c), ", follower);
else
printf("%c, ", follower);
}
printf("\b\b }\n");
}
prevState = crntState;
crntState = buff = fgetc(looker);
}
fcloseall();
}
int main()
{
char fileName[20];
printf("Enter the name of file containing grammar :: ");
scanf("%s", fileName);
computeFirst(fileName);
putchar('\n');
computeFollow(fileName);
getch();
}
