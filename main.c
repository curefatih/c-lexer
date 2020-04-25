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

bool isOperatorStart(char ch)
{
  if (ch == '+' || ch == '-' || ch == ':')
  {
    return true;
  }

  return false;
}

bool isOperator(char *str)
{
  char *operators[7] = {
      "++",
      "+",
      "-",
      "--",
      "/",
      "*",
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
  if (strlen(str) >= 4 && str[0] == '(' && str[1] == '*' && str[(strlen(str) - 2)] == '*' && str[(strlen(str) - 1)] == ')')
  {
    return true;
  }
  return false;
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
    if (!(str[i] <= 'z' && str[i] >= 'a') && !(str[i] <= 'Z' && str[i] >= 'A') && str[i] != '_' && !isInteger(&str[i]))
    {
      return false;
    }
  }

  if ((str[0] <= 'z' && str[0] >= 'a') && (str[0] <= 'Z' && str[0] >= 'A') || str[0] == '_' || isInteger(&str[0]))
  {
    // printf("\n%s", !(str[0] <= 'z' && str[0] >= 'a') ? "true" : "false");
    // printf("\n%s", !(str[0] <= 'Z' && str[0] >= 'A') ? "true" : "false");
    return (false);
  }

  return (true);
}

bool isString(char *str)
{
  if (str[0] == '"' && str[(strlen(str) - 1)] == '"' && strlen(str) >= 2)
  {
    return true;
  }
  return false;
}

bool isStringSign(char ch)
{
  if (ch == '"')
  {
    return true;
  }
  return false;
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
  if (ch == ' ' || isBracket(ch) || isOperatorStart(ch) || isEOL(ch))
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
  // char x = "+";
  printf("++ is a operator? : %s", isOperator("+") ? "true" : "false");
  printf("\n");

  printf("isinteger %s", isInteger("123") ? "true" : "false");
  printf("\n");

  // char str = '}';
  // char *gb = &str;
  // bool is_bracket = isBracket(str);
  // getBracketToken(&gb);
  // printf("%s\n", is_bracket ? gb : "false");
  // printf("\n");

  // printf("isEOL: = %s", isEOL(";") ? "true" : "false");
  // printf("\n");

  printf("validIdentifier: = %s", isValidIdentifier("_while") ? "true" : "false");
  printf("\n");

  // printf("isString: %s", isString("\" Hello this is a string") ? "true" : "false");
  // printf("\n");
  // printf("isStringStart:%s ", isStringStart('"') ? "true" : "false");
  // printf("\n");

  // printf("isComment: %s", isComment("(*addition *)") ? "true": "false");
  // printf("\n");

  char *fp;
  char file_name[] = "app.psi";
  readFile(file_name, "r", &fp);

  printf("The contents of %s file are: \n%s \n", file_name, fp);

  traverseCode(fp);

  return 0;
}

void traverseCode(char *str)
{
  int strCounter = 0;
  bool isCommentEnded = true;
  bool isStringEnded = true;

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
  while (right <= codeLength)
  {

    char *subStr = subString(str, left, right);
    // printf("0\n");

    // printf("str[right] = %c \nright: %d \n", str[right], right);
    // printf("\nright: %d, left: %d \n", right, left);

    // if(isStringEnded == false || isCommentEnded == false){
    //   right++;
    // }
    // printf("1\n");
    if (isStringSign(str[right]) || isStringEnded == false)
    {
      // printf("looking for string: %s, i: %d\n", subStr, i);
      if (isStringEnded == true)
      {
        isStringEnded = false;
      }

      right++;
      if (isStringEnded == false && right == codeLength)
      {
        printf("!STRING NOT ENDED");
        left = right;
      }

      if (isString(subStr))
      {
        // printf("looking for string: %s, i: %d\n", subStr, i);
        isStringEnded = true;
        printf("STRINGCONSTANT(%s)\n", subStr);
      }

      continue;
    }

    if (isCommentEnded == false)
    {
      right++;
      // printf("comment: %s\n", subStr);
      if (isComment(subStr))
      {
        printf("COMMENT(%s)\n", subStr);
        isCommentEnded = true;
        left = right;
      }
      else if (isComment(subStr) == false && right - 1 == codeLength)
      {
        printf("!COMMENT NOT ENDED, str: %s \n", subStr);
      }

      continue;
    }

    if (isDelimiter(str[right]) == false)
    {
      right++;
    }

    if (isDelimiter(str[right]) && left == right)
    {
      if (isEOL(str[right]))
      {
        printf("\nEOL(%c)\n", str[right]);
      }

      if (isOperatorStart(str[right]))
      {
        // printf("\noperator starts i : %d\n ", i);
        if (str[right] == ':')
        {

          if (right + 1 <= codeLength)
          {
            if (str[right + 1] == '=')
            {
              printf("\nOPERATOR(%s)\n", subString(str, left, right + 1));
              right++;
            }
            else if (str[right + 1] != '=')
            {
              printf("\n!ASSIGNMENT ERROR");
            }
          }
          else
          {
            printf("\n!ASSIGNMENT ERROR");
          }
        }
        else if (str[right] != ':' && right + 1 <= codeLength)
        {
          if (str[right] == '+' && str[right + 1] == '+')
          {
            right++;
            printf("\nOPERATOR(%s)", subString(str, left, right + 1));
          }
          else if (str[right] == '-' && str[right + 1] == '-')
          {
            right++;
            printf("\nOPERATOR(%s)", subString(str, left, right + 1));
          }
          else
          {
            printf("\nOPERATOR(%c)", str[right]);
          }
        }
      }

      if (isBracket(str[right]))
      {
        if (right + 1 <= codeLength && str[right + 1] == '*')
        {
          isCommentEnded = false;
          continue;
        }
        else
        {
          printf("BRACKET\n");
        }
      }

      right++;
      left = right;
    }
    else if (isDelimiter(str[right]) && left != right || (right == codeLength && left != right))
    {
      // printf("\n3 -sub: %s\n", subStr);

      if (isKeyword(subStr))
        printf("\nKeyword(%s)", subStr);

      else if (isInteger(subStr))
        printf("\nIntConst(%s)", subStr);

      else if (isValidIdentifier(subStr) && isKeyword(subStr) == false)
        printf("\nIdentifier(%s)", subStr);
      

      left = right;
    }
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