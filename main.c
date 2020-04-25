#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // tolower()
#include <stdlib.h>

void toLowerString(char **str);

void traverseCode(char *str);

char *subString(char *str, int left, int right);

bool isKeyword(char *str)
{
  char keywords[18][8] = {
      "break",
      "case",
      "char",
      "const",
      "continue",
      "do",
      "else",
      "enum",
      "float",
      "for",
      "goto",
      "int",
      "if",
      "long",
      "record",
      "return",
      "static",
      "while"};

  // char *tolower_s = &str;
  toLowerString(&str);
  // printf("tolower: %s, address: %u \n", str, *tolower_s);
  // printf("org: %s, address: %u \n", str, *str);

  for (int i = 0; i < 18; i++)
  {
    if (strcmp(str, keywords[i]) == 0)
    {
      // printf("-> %s == %s\n", str, keywords[i]);
      return true;
    }
  }

  return false;
}

/**
 * makes string lowercase
*/
void toLowerString(char **str)
{
  char *temp = strdup(*str); // make a copy
  // printf("str: %s \n", *str);

  strcpy(temp, *str);
  // printf("temp: %s \n", temp);
  char *tptr = (char *)temp;

  while (*temp)
  {
    *temp = tolower(*temp);
    // printf("%s \n", tptr);
    temp++;
  }
  // printf("tp: %s \n", tptr);
  // printf("temp: %s \n", temp);

  *str = tptr;
}

bool isOperator(char *str)
{
  char *operators[7] = {
      '+',
      "++",
      '-',
      "--",
      '/',
      '*',
      ":="};

  for (int i = 0; i < 7; i++)
  {
    // printf("-> %s == %s\n", str, operators[i]);
    if (strcmp(str, operators[i]) == 0)
    {
      return true;
    }
  }

  return false;
}

bool isInteger(char *str)
{
  int i, len = strlen(str);

  if (len == 0)
    return (false);
  for (i = 0; i < len; i++)
  {
    if (
        str[i] != '0' &&
        str[i] != '1' &&
        str[i] != '2' &&
        str[i] != '3' &&
        str[i] != '4' &&
        str[i] != '5' &&
        str[i] != '6' &&
        str[i] != '7' &&
        str[i] != '8' &&
        str[i] != '9')
      return (false);
  }
  return (true);
}

bool isBracket(char str)
{
  char brackets[6] = {
      '{',
      '(',
      '[',
      '}',
      ')',
      ']'};
  for (int i = 0; i < 6; i++)
  {
    if (str == brackets[i])
    {
      return true;
    }
  }

  return false;
}

/**
 * gets token for given bracket
*/
void getBracketToken(char **str)
{
  switch (**str)
  {
  case '{':
    *str = "LeftCurlyBracket";
    break;

  case '(':
    *str = "LeftPar";
    break;

  case '[':
    *str = "LeftSquareBracket";
    break;

  case '}':
    *str = "RightCurlyBracket";
    break;

  case ']':
    *str = "RightSquareBracket";
    break;

  case ')':
    *str = "RightPar";
    break;

  default:
    printf("Error! Cannot get bracket type for '%s'\n", *str);
    exit(0);
  }
}

bool isEOL(char str)
{
  if (str == ';')
  {
    return true;
  }

  return false;
}

bool isComment(char *str)
{
}

bool isCommentAllowed(char *str)
{
  return true;
}

bool isValidIdentifier(char *str)
{
  // printf("%d", str[0]);
  for (int i = 0; i < strlen(str); i++)
  {
    // printf("\n%s", !(str[i] <= 'z' && str[i] >= 'a') ? "true" : "false");
    // printf("\n%s", !(str[i] <= 'Z' && str[i] >= 'A') ? "true" : "false");
    // printf("\n%s", str[i] != '_' ? "true" : "false");
    // printf("\n%s", !(str[i] <= 'z' && str[i] >= 'a') || !(str[i] <= 'Z' && str[i] >= 'A') || str[i] != '_' ? "true" : "false");
    if (!(str[i] <= 'z' && str[i] >= 'a') && !(str[i] <= 'Z' && str[i] >= 'A') && str[i] != '_')
    {
      return false;
    }
  }

  if ((str[0] <= 'z' && str[0] >= 'a') && (str[0] <= 'Z' && str[0] >= 'A') || str[0] == '_')
  {
    // printf("\n%s", !(str[0] <= 'z' && str[0] >= 'a') ? "true" : "false");
    // printf("\n%s", !(str[0] <= 'Z' && str[0] >= 'A') ? "true" : "false");
    return (false);
  }

  return (true);
}

void readFile(char *filename, char *mode, char **buf)
{
  FILE *fp;
  fp = fopen(filename, mode);
  if (fp == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  long numbytes;
  char *buffer;

  /* Get the number of bytes */
  fseek(fp, 0L, SEEK_END);
  numbytes = ftell(fp);

  // reset the fp position indicator to
  //the beginning of the fp
  fseek(fp, 0L, SEEK_SET);

  // grab sufficient memory for the
  // buffer to hold the text */
  buffer = (char *)calloc(numbytes, sizeof(char));

  /* memory error */
  if (buffer == NULL)
    exit(EXIT_FAILURE);

  /* copy all the text into the buffer */
  fread(buffer, sizeof(char), numbytes, fp);

  *buf = buffer;
  fclose(fp);
  return;
}

bool isDelimiter(char ch)
{
  if (ch == ' ' || isBracket(ch))
  {
    return true;
  }

  return false;
}

int main()
{
  // printf("\n");
  // printf(isKeyword("Break") ? "true" : "false");
  // printf("\n");
  char x = "+";
  printf("++ is a operator? : %s", isOperator(&x) ? "true" : "false");
  printf("\n");

  // printf(isInteger("-9") ? "true" : "false");
  // printf("\n");

  // char str = '}';
  // char *gb = &str;
  // bool is_bracket = isBracket(str);
  // getBracketToken(&gb);
  // printf("%s\n", is_bracket ? gb : "false");
  // printf("\n");

  // printf("isEOL: = %s", isEOL(";") ? "true" : "false");
  // printf("\n");

  // printf("validIdentifier: = %s", isValidIdentifier("a_") ? "true" : "false");
  // printf("\n");

  char *fp;
  char file_name[] = "app.psi";
  readFile(file_name, "r", &fp);

  // fscanf(fp, "%s", buff);
  // fgets(buff, 255, (FILE *)fp);
  // printf("2: %s\n", buff);
  // printf("1 : %s\n", buff);

  // printf("", *fp);

  // char ch;

  // char *line = NULL;

  // int i = 1;
  // while ((ch = fgetc(fp)) != EOF)
  // {
  //   printf("\n%d -  %c", i, ch);
  //   i++;
  // }

  // printf("\n");

  printf("The contents of %s file are: \n%s \n", file_name, fp);

  traverseCode(fp);

  return 0;
}

void traverseCode(char *str)
{
  int strCounter = 0;
  bool isCommentEnded,
      isStringEnded = true;

  int right = 0;
  int left = 0;
  int codeLength = strlen(str);

  printf("right intitial:%d\n", right);

  /**
   * lastType for knowing posible type for next token.
   * To find next token we store last type before current.
   * _____________________________________________________
   * 
   * Unknown: 0
   * Identifier: 1
   * Integer: 2
   * Operator: 3
   * Brackets: 4
   * StringContant: 5
   * Keyword: 6
   * EndOfLine: 7
   * Comment: 8
  */
  int lastType = 0;
  int currentType = 0;

  printf("_________\nstr initial: %s", str);

  printf("\nright: %d, left: %d, codeLength: %d\n", right, left, codeLength);

  int i = 0;
  // while (right <= codeLength && left <= right)
  while (i <= 10)
  {
    //   char *subStr = subString(str, left, right - 1);
    //   printf("right: %d, left: %d ", right, left);
    //   printf("\nsubStr: %s\n__________\n", subStr);

    //   if (isValidIdentifier(subStr))
    //   {
    //     currentType = 1;
    //   }
    //   else if (isInteger(subStr))
    //   {
    //     currentType = 2;
    //   }
    //   else if (isOperator(subStr))
    //   {
    //     currentType = 3;
    //   }
    //   else if (isBracket(subStr))
    //   {
    //     currentType = 4;
    //     // if its comment
    //   }
    //   else if (isEOL(subStr))
    //   {
    //     currentType = 7;
    //   }
    //   else
    //   {
    //     currentType = 0;
    //   }

    //   // change if its unknown
    //   if (lastType == 0)
    //     lastType = currentType;

    //   printf("currentType: %d, lastType: %d ", currentType, lastType);

    //   // check if changes type
    //   if (lastType != currentType)
    //   {
    //     if (lastType == 1 && (currentType != 2))
    //     {
    //       printf("\n%s is a identifier or keyword \n", subStr);
    //       left = right - 1;
    //     }
    //   }

    //   right++;
    //   i++;
    // }

    // if (lastType == 0)
    // {
    //   right++;
    //   continue;
    // }

    /**
     * types:
     * identifier | keyword : 1
     * operator: 2
     * bracket | comment : 3
     * integer: 4
     * endofline: 5
    */
    // right++;

    // char *subStr = subString(str, left, right - 1);

    // // if (str[right] == ' ' || str[right] == ':')
    // // {
    // //   left = right;
    // //   right++;
    // //   continue;
    // // }

    // if (isValidIdentifier(subStr) || isKeyword(subStr))
    // {
    //   printf("\nvalid identifier | keyword: %s", subStr);
    //   currentType = 1;
    // }
    // else if (isOperator(subStr))
    // {
    //   printf("\nvalid operator: %s", subStr);
    //   currentType = 2;
    // }
    // else if (isBracket(str[right])) //comment not implemented yet
    // {
    //   printf("\nvalid bracket | comment: %s", subStr);
    //   currentType = 3;
    // }
    // else if (isInteger(subStr))
    // {
    //   currentType = 4;
    // }
    // else if (isEOL(str[right]))
    // {
    //   currentType = 5;
    // }
    // else
    // {
    //   currentType = 0;
    // }
    // printf("\nsubStr: %s", subStr);
    // printf("\n1-loop: %d, right: %d, left: %d, lastType: %d, currentType: %d", i, right, left, lastType, currentType);

    // if (currentType != lastType)
    // {
    //   lastType = currentType;
    //   // left = right;

    //   if (currentType == 5 || currentType == 3)
    //   {
    //     left = right;
    //   }

    //   continue;
    // }

    // printf("\nsubStr: %s", subStr);
    // printf("\n2-loop: %d, right: %d, left: %d, lastType: %d, currentType: %d", i, right, left, lastType, currentType);
    // i++;
    // printf("\n");

    char *subStr = subString(str, left, right - 1);
    // printf("0\n");

    // printf("str[right] = %d \nright: %d \n", str[right], right);

    if (str[right] != ' ' || !isOperator(subStr) || !isBracket(str[right]) || isEOL(str[right]))
    {
      right++;
      printf("1\n");
    }

    if (str[right] == ' ' || isOperator(subStr) || isBracket(str[right]) || isEOL(str[right]))
    {
      printf("2\n");

      if (isBracket(str[right]))
      {
        printf("\nbracket: %s", &str[right]);
      }

      if (isOperator(subStr))
      {
        if (str[right] == '+' || str[right] == ':')
        {
          right++;
          continue;
        }
        else
        {
          printf("\noperator: %s\n", subStr);
        }
      }

      if (isEOL(str[right]))
      {
        printf("\nEOL: %s \n", subStr);
      }

      right++;
      left = right;
    }
    else if ((str[right] == ' ' || isOperator(subStr) || isBracket(str[right])) && left != right)
    {
      printf("3");

      if (isValidIdentifier(subStr))
      {
        printf("\nidentifier | keyword: %s", subStr);
      }
      else if (isInteger(subStr))
      {
        printf("\ninteger: %s", subStr);
      }
      left = right;
    }

    i++;
  }
  return;
}

char *subString(char *str, int left, int right)
{
  int i;
  char *subStr = (char *)malloc(
      sizeof(char) * (right - left + 2));

  for (i = left; i <= right; i++)
    subStr[i - left] = str[i];
  subStr[right - left + 1] = '\0';
  return (subStr);
}