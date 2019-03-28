

#include <stdio.h>

int main (int argc, char const *argv[])
{
    char name[20];
    scanf("%[^\n]s",name);
    printf("%s\n", name);
    return 0;
}
