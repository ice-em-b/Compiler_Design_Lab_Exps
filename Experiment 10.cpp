#include<stdio.h>
#include<string.h>
#include<conio.h>
int tempVarCount = 1;
void genTemp(char newTemp[])
{
FILE *looker = fopen("temp.txt", "w+");
fprintf(looker, "t%d", tempVarCount);
fseek(looker, 0, 0);
fscanf(looker, "%s", newTemp);
remove("temp.txt");
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
int isOperator(char input)
{
if((input == '+')||(input == '-')||(input == '*')||(input == '/')||(input == '(')||(input == ')')||(input
== '$'))
return(1);
else
return(0);
}
int getHandle(char stack[], char handle[])
{
int i, opCount = 0, stackLen = strlen(stack);
for(i=stackLen-1; i>=0; i--)
{
if(isOperator(stack[i]) == 1)

opCount++;
if(opCount == 2)
{
strcpy(handle, &stack[i+1]);
break;
}
}
if(((opCount == 2)&&(handle[0] != '(')))
return(1);
else
return(0);
}
void getSubHandle(char stack[], char handle[])
{
int i, stackLen = strlen(stack);
for(i=stackLen-1; i>=0; i--)
{
if(isOperator(stack[i]) == 1)
{
strcpy(handle, &stack[i+1]);
break;
}
}
}
void genExpression(char stack[], char handle[])
{
char newTemp[5];
genTemp(newTemp);
printf("%s = %s\n", newTemp, handle);
pop(stack, handle);
strcat(stack, newTemp);
tempVarCount++;
}
void interMedCodeGen(char inputString[])
{
char stack[100], handle[20];
strcpy(stack, "$");
strcat(inputString, "$");
while((stack[strlen(stack)-1] != '$')||(inputString[0] != '$'))
{

if((inputString[0] == '+')||(inputString[0] == '-'))
{
if(getHandle(stack, handle) == 1)
genExpression(stack, handle);
else
{
push(stack, inputString[0]);
strcpy(inputString, &inputString[1]);
}
}
else if((inputString[0] == ')')||(inputString[0] == '$'))
{
if(getHandle(stack, handle) == 1)
genExpression(stack, handle);
else
{
getSubHandle(stack, handle);
if(inputString[0] == '$')
pop(stack, handle);
else if(inputString[0] == ')')
{
pop(stack, handle);
pop(stack, "(");
strcat(stack, handle);
strcpy(inputString, &inputString[1]);
}
}
}
else
{
push(stack, inputString[0]);
strcpy(inputString, &inputString[1]);
}
}
}
int main()
{
char inputString[100];
printf("Enter the expression for intermediate-code generation...\n");
scanf("%s", inputString);
interMedCodeGen(inputString);
getch();
return 0;
}
