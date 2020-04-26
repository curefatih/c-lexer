#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // tolower()
#include <stdlib.h>

void toLowerString(char **str);

void traverseCode(char *str, FILE *fp);

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

  toLowerString(&str);

  for (int i = 0; i < 18; i++)
  {
    if (strcmp(str, keywords[i]) == 0)
    {
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
  strcpy(temp, *str);
  char *tptr = (char *)temp;
  while (*temp)
  {
    *temp = tolower(*temp);
    temp++;
  }
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
char *getBracketToken(char ch)
{
  char *str;
  switch (ch)
  {
  case '{':
    str = "LeftCurlyBracket";
    return str;
    break;

  case '(':
    str = "LeftPar";
    return str;
    break;

  case '[':
    str = "LeftSquareBracket";
    return str;
    break;

  case '}':
    str = "RightCurlyBracket";
    return str;
    break;

  case ']':
    str = "RightSquareBracket";
    return str;
    break;

  case ')':
    str = "RightPar";
    return str;
    break;

  default:
    printf("Error! Cannot get bracket type for '%c'\n", ch);
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
  for (int i = 0; i < strlen(str); i++)
  {
    if (!(str[i] <= 'z' && str[i] >= 'a') && !(str[i] <= 'Z' && str[i] >= 'A') && str[i] != '_' && !isInteger(&str[i]))
    {
      return false;
    }
  }

  if ((str[0] <= 'z' && str[0] >= 'a') && (str[0] <= 'Z' && str[0] >= 'A') || str[0] == '_' || isInteger(&str[0]))
  {
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
  // the beginning of the fp
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
  if (ch == ' ' || ch == '\n' || isBracket(ch) || isOperatorStart(ch) || isEOL(ch))
  {
    return true;
  }

  return false;
}

void test()
{
  printf("\n");
  printf("'Break' is a keyword : %s", isKeyword("Break") ? "true" : "false");
  printf("\n");

  printf("'++' is a operator : %s\n", isOperator("+") ? "true" : "false");
  printf("'+2' is a operator : %s", isOperator("+2") ? "true" : "false");
  printf("\n");

  printf("'123' is a integer : %s\n", isInteger("123") ? "true" : "false");
  printf("'1a2' is a integer : %s", isInteger("1a2") ? "true" : "false");
  printf("\n");

  char str = '}';
  bool is_bracket = isBracket(str);
  char *bracket = getBracketToken(str);
  printf("'%c' token : %s", str, is_bracket ? bracket : "false");
  printf("\n");

  printf("';' is EOL: = %s\n", isEOL(';') ? "true" : "false");
  printf("'-' is EOL: = %s", isEOL('-') ? "true" : "false");
  printf("\n");

  printf("'while12' valid identifier : = %s\n", isValidIdentifier("while12") ? "true" : "false");
  printf("'12asd' is a valid identifier : = %s", isValidIdentifier("while") ? "true" : "false");
  printf("\n");

  printf("'\" Hello this is a string' is a string : %s\n", isString("\" Hello this is a string but not ended") ? "true" : "false");
  printf("'\" Hello this is a string\"' is a string : %s", isString("\" Hello this is a string\"") ? "true" : "false");
  printf("\n");

  printf("'\"' is a string sign : %s \n", isStringSign('"') ? "true" : "false");
  printf("'-' is a string sign : %s ", isStringSign('-') ? "true" : "false");
  printf("\n");

  printf("'(*comment *)' is a comment : %s\n", isComment("(*comment *)") ? "true" : "false");
  printf("'(*not comment' is a comment : %s", isComment("(*not comment") ? "true" : "false");
  printf("\n");
}

int main()
{
  printf("\n\nFunction test start ______\n");
  test();
  printf("\nFunction test end ________\n\n");
  char *fp;
  char file_name[] = "code.psi";
  readFile(file_name, "r", &fp);

  printf("The contents of %s file are: \n%s \n", file_name, fp);

  char new_file_name[] = "code.lex";
  FILE *newFile = fopen(new_file_name, "w");
  traverseCode(fp, newFile);
  fclose(newFile);
  printf("Done!\n");
  return 0;
}

void traverseCode(char *str, FILE *fp)
{
  int strCounter = 0;
  bool isCommentEnded = true;
  bool isStringEnded = true;

  int right = 0;
  int left = 0;
  int codeLength = strlen(str);

  // printf("right intitial:%d\n", right);

  // printf("_________\nstr initial: %s", str);

  // printf("\nright:i %d, left: %d, codeLength: %d\n", right, left, codeLength);

  while (right <= codeLength)
  {

    char *subStr = subString(str, left, right);

    // printf("str[right] = %c \nright: %d \n", str[right], right);
    // printf("\nright: %d, left: %d \n", right, left);
    if (isStringSign(str[right]) || isStringEnded == false)
    {
      if (isStringEnded == true)
      {
        isStringEnded = false;
      }

      right++;
      if (isStringEnded == false && right == codeLength)
      {
        printf("!ERROR: String not ended.");
        exit(0);
        left = right;
      }

      if (isString(subStr))
      {
        isStringEnded = true;
        // printf("STRINGCONSTANT(%s)\n", subStr);
        fprintf(fp, "StringConstant(%s)\n", subStr);
      }

      continue;
    }

    if (isCommentEnded == false)
    {
      right++;
      // printf("comment: %s\n", subStr);
      if (isComment(subStr))
      {
        // printf("COMMENT(%s)\n", subStr);
        isCommentEnded = true;
        left = right;
      }
      else if (isComment(subStr) == false && right - 1 == codeLength)
      {
        printf("!ERROR: Comment not ended\n");
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
        // printf("\nEOL(%c)\n", str[right]);
        fprintf(fp, "EndOfLine\n");
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
              // printf("\nOPERATOR(%s)\n", subString(str, left, right + 1));
              fprintf(fp, "Operator(%s)\n", subString(str, left, right + 1));
              right++;
            }
            else if (str[right + 1] != '=')
            {
              printf("\n!Warning: Assignment may be used wrong.\n");
            }
          }
          else
          {
            printf("\n!Warning: Assignment may be used wrong.\n");
          }
        }
        else if (str[right] != ':' && right + 1 <= codeLength)
        {
          if (str[right] == '+' && str[right + 1] == '+')
          {
            right++;
            // printf("\nOPERATOR(%s)", subString(str, left, right));
            fprintf(fp, "Operator(%s)\n", subString(str, left, right));
          }
          else if (str[right] == '-' && str[right + 1] == '-')
          {
            right++;
            // printf("\nOPERATOR(%s)", subString(str, left, right));
            fprintf(fp, "Operator(%s)\n", subString(str, left, right));
          }
          else
          {
            // printf("\nOPERATOR(%c)", str[right]);
            fprintf(fp, "Operator(%c)\n", str[right]);
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
          char *bracket = getBracketToken(str[right]);
          // printf("--> %s", bracket);
          fprintf(fp, "%s\n", bracket);
        }
      }

      right++;
      left = right;
    }
    else if (isDelimiter(str[right]) && left != right || (right == codeLength && left != right))
    {
      // printf("\n3-sub:%s, iden: %s", subStr, isValidIdentifier(subStr) ? "true": "fasle");
      if (isKeyword(subStr))
      {
        fprintf(fp, "Keyword(%s)\n", subStr);
        // printf("\nKeyword(%s)", subStr);
      }
      else if (isInteger(subStr))
      {
        fprintf(fp, "IntConst(%s)\n", subStr);
        // printf("\nIntConst(%s)", subStr);
      }
      else if (isValidIdentifier(subStr) && isKeyword(subStr) == false)
      {
        // printf("\n4-sub: ", subStr);
        if (strlen(subStr) > 20)
        {
          printf("\n!ERROR: Identifier cannot be longer thna 20 char.\n");
          exit(0);
          left = right;
          continue;
        }
        // printf("\nIdentifier(%s)", subStr);
        fprintf(fp, "Identifier(%s)\n", subStr);
      }

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