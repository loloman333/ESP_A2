// Assignment 2 Playfair Cypher 
// Autor: Tutors
//

#include <stdio.h>
#include <ctype.h>

#include "framework.h"

//-----------------------------------------------------------------------------
void generatePlayfairSquare(char *square) 
{
  char key[SIZE_BUFFER] = "";
  while(1) 
  {
    printf("%s ", KEY_PROMPT);
    fgets(key, SIZE_BUFFER, stdin);
    if(checkStringValidity(key, MAX_KEY_LENGTH, IS_KEY)) break;
  }
  prepareKey(key);

  int limit = (SQUARE_SIDE * SQUARE_SIDE + 1) / 2;
  for(int counter = 0; counter < limit; counter++) 
  {
    *(square + counter * 2) = key[counter];
    if(counter != limit - 1) 
      *(square + counter * 2 + 1) = key[counter + limit];
  }
  printf("%s", SQUARE_STRING);
  for(int counter = 0; counter < SQUARE_SIDE * SQUARE_SIDE; counter++) 
  {
    printf("%c%c", square[counter], (counter + 1) % SQUARE_SIDE ? ' ' : '\n');
  }
}

//-----------------------------------------------------------------------------
int checkStringValidity(char *text, int max_length, OperationType op) 
{
  if(!*text || max_length < 0)
    return ERROR;

  int string_length = stringLength(text);
  if(text[string_length - 1] == '\n')
    text[string_length-- - 1] = '\0';
  else
  {
    int character;
    while((character = getchar()) != '\n' && character != EOF);
    return 0;
  }

  int number_of_letters = containsOnlyAlpha(text);

  if(op != IS_DECRYPTING)
    return string_length <= max_length && number_of_letters >= 1;

  return string_length <= max_length && number_of_letters >= 2 && !(number_of_letters % 2);
}

//-----------------------------------------------------------------------------
int containsOnlyAlpha(char *text) 
{
  int number_of_letters = 0;
  do 
  {
    if(isalpha(*text))
      number_of_letters++;
    else if(*text != ' ')
      return ERROR;
  } while(*++text);

  return number_of_letters;
}

//-----------------------------------------------------------------------------
void prepareKey(char *key) 
{ 
  cleanString(key, IS_KEY);
  removeDuplicateLetters(key);
  printf("%s %s\n", CHOSEN_KEY, key);
  appendAlphaToKey(key);
}

//-----------------------------------------------------------------------------
void cleanString(char *text, OperationType op) 
{
  removeSpaces(text);
  toUpper(text);
  if(op != IS_DECRYPTING)
    replaceLetters(text, LETTER_TO_SUBSTITUTE, SUBSTITUTE_LETTER);
}

//-----------------------------------------------------------------------------
void removeSpaces(char *text) 
{
  char *last_position = text;
  do 
  {
    if(*text != ' ')
      *last_position++ = *text;
  } while(*text++);
}

//-----------------------------------------------------------------------------
void removeDuplicateLetters(char *text) 
{
  do 
  {
    char *current_pos = text + 1;
    char *last_inserted = text + 1;
    do 
    {
      if(*current_pos != *text)
        *last_inserted++ = *current_pos;
    } while(*current_pos++);
  } while(*text++);
}

//-----------------------------------------------------------------------------
void appendAlphaToKey(char *key) 
{
  char alpha[SQUARE_SIDE * SQUARE_SIDE + 1] = ALPHA;
  int length = stringLength(key);
  for(int counter = 0; counter < SQUARE_SIDE * SQUARE_SIDE + 1; counter++) {
    if(stringContainsChar(key, alpha[counter]) == NOT_FOUND)
      *(key + length++) = alpha[counter];
  }
  *(key + length) = '\0';
}

//-----------------------------------------------------------------------------
int stringContainsChar(char *text, char to_find) {
  do {
    if(*text == to_find) return FOUND;
  } while(*text++);
  return NOT_FOUND;
}
