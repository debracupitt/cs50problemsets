#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  string s = get_string("input: ");
  printf("output: \n");

  for (int i = 0; i < strlen(s); i++)
  {
    printf("%c %i \n", s[i], (int) s[i]);
  }

  int n = 0;
  while (s[n] != '\0')
  {
    n++;
  }
  printf("The length of s is: %i \n", n);
}