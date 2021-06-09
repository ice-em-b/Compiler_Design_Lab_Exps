#include<stdio.h>
#include<string.h>
#include<conio.h>
void readLine(FILE *looker, char nonTerminal[], char production[])
{
fscanf(looker, "%[^->]", nonTerminal);
fseek(looker, 2, 1);
fscanf(looker, "%[^\n]", production);
fgetc(looker);
}
int isHandle(char fileName[], char handle[], char nonTerminal[])
{
FILE *looker = fopen(fileName, "r");
char production[10];
while(feof(looker) == 0)
{
readLine(looker, nonTerminal, production);
if(strcmp(handle, production) == 0)
{
fclose(looker);
return(1);
}
}
fclose(looker);
return(0);
}
int isShiftingPossible(char fileName[], char stack[], char inputString[])
{
FILE *looker = fopen(fileName, "r");
char nonTerminal[5], production[10], handle[10];
int stackLen = strlen(stack);
handle[0] = (stack[stackLen - 1] != '$') ? stack[stackLen - 1] : '\0';
handle[1] = inputString[0];
handle[2] = '\0';
while(feof(looker) == 0)
{
readLine(looker, nonTerminal, production);
if((handle[0] == production[0])&&(handle[1] == production[1]))
{
fclose(looker);

return(1);
}
}
fclose(looker);
return(0);
}
void push(char stack[], char element)
{
int len = strlen(stack);
stack[len] = element;
stack[len + 1] = '\0';
}
void pop(char stack[], char handle[])
{
int stackLen, handleLen, i;
stackLen = strlen(stack);
handleLen = strlen(handle);
for(i=stackLen-1; i>=stackLen-handleLen; i--)
stack[i] = '\0';
}
void parser(char fileName[], char inputString[])
{
FILE *looker = fopen(fileName, "r");
char stack[50], handle[10], nonTerminal[5], startState = fgetc(looker);
int i, action = 0;
strcat(inputString, "$");
strcpy(stack, "$");
printf("%-15s %25s", stack, inputString);
while(1)
{
action = 0;
if(isShiftingPossible(fileName, stack, inputString) != 1)
{
for(i=1; i<strlen(stack); i++)
{
strcpy(handle, &stack[i]);
if(isHandle(fileName, handle, nonTerminal) == 1)
{
pop(stack, handle);
push(stack, nonTerminal[0]);

printf("\treduce [%s->%s]\n%-15s %25s",nonTerminal, handle,
stack, inputString );

action = 1;
break;
}
}
}
if((action == 0)&&(inputString[0] != '$'))
{
push(stack, inputString[0]);
strcpy(inputString, &inputString[1]);
printf("\tshift\n%-15s %25s", stack, inputString);
action = 1;
}
if(action == 0)
break;

}
if((strlen(stack) == 2)&&(stack[1] == startState))
printf("\taccept\n");
else
printf("\treject\n");
fclose(looker);
}
int main()
{
FILE *looker;
char fileName[20], inputString[50];
printf("Enter the name of file containing grammar :: ");
scanf("%s", fileName);
printf("Enter the string to be parsed :: ");
scanf("%s", inputString);
printf("%-15s %25s\t%s\n", "STACK", "INPUT", "ACTION");
parser(fileName, inputString);
getch();
return 0;
}
