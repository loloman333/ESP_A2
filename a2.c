//-----------------------------------------------------------------------------
// a2.c
//
// TODO
//
// Group: 12
//
// Author: 12007661
//-----------------------------------------------------------------------------
//

//TODO mehrere definitionen in einer zeile????

// Includes
#include  <stdio.h>
#include "framework.h"

// Defines
#define CHOICE_INVALID 0
#define CHOICE_STOP '0'
#define CHOICE_ENCRYPT '1'
#define CHOICE_DECRYPT '2'

#define MAX_INPUT_LENGTH 50

#define FILL_CHAR 'X'

#define SUCCESS 1

// Forward definitions
int stringLength(char *text);
void toUpper(char *text);
void replaceLetters(char *text, char original, char new_char);

char getUserChoice();
void cipher(char* playfairSquare, OperationType op);
void getInput(char* input, OperationType op);
int makeBigram(char* input, OperationType op);
void printBigram(char* bigram);
void getIndices(char* playfairSquare, char element, char* element_x, char* element_y);

char shiftRight(char index);
char shiftLeft(char index);

//-----------------------------------------------------------------------------
///
/// The main program
/// 
/// TODO
///
/// @return always zero
//
int main()
{
  char playfairSquare[5][5];
  generatePlayfairSquare(*playfairSquare);

  char choice = 1;
  while(choice != CHOICE_STOP)
  {
    choice = getUserChoice();

    if (choice == CHOICE_ENCRYPT)
    {
      cipher(*playfairSquare, IS_ENCRYPTING);
    }
    else if (choice == CHOICE_DECRYPT)
    {
      cipher(*playfairSquare, IS_DECRYPTING);
    }


  }
  return 0;
}


//-----------------------------------------------------------------------------
/// Reads a character from stdin and returns it
/// 
///
/// @return character from user input or INVALID_CHOICE if input has multiple characters
//
char getUserChoice() 
{
  printf(
    "\nWählen Sie bitte eine Option:\n"
    "1 - Verschlüsseln\n"
    "2 - Entschlüsseln\n"
    "0 - Programm beenden\n\n"
  );

  char choice, tmp = CHOICE_INVALID;
  int i = 0;
  do  
  {
    choice = tmp;
    tmp = getchar();
    i++;
  } while (tmp != '\n');

  if (i > 2)
  {
    choice = CHOICE_INVALID;
  }

  return choice;
}

//-----------------------------------------------------------------------------
/// TODO
/// 
///
/// @return pointer to the char array
//
void cipher(char* playfairSquare, OperationType op)
{
  char input[MAX_INPUT_LENGTH] = "";
  getInput(input, op);
  
  int string_len = stringLength(input);
  for (int i = 0 ; i < string_len; i++){

    if (i % 2 == 1){
      char first = input[i - 1];
      char second = input[i];
      char first_x, first_y, second_x, second_y;

      getIndices(playfairSquare, first, &first_x, &first_y);
      getIndices(playfairSquare, second, &second_x, &second_y);

      if (first_y == second_y)
      {
        if (op == IS_ENCRYPTING)
        {
          first_x = shiftRight(first_x);
          second_x = shiftRight(second_x);
        }
        else
        {
          first_x = shiftLeft(first_x);
          second_x = shiftLeft(second_x);
        }
      }
      else if (first_x == second_x)
      {
        if (op == IS_ENCRYPTING)
        {
          first_y = shiftRight(first_y);
          second_y = shiftRight(second_y);
        }
        else
        {
          first_y = shiftLeft(first_y);
          second_y = shiftLeft(second_y);
        }
      }
      else
      {
        char temp = first_x;
        first_x = second_x;
        second_x = temp;
      }

      //printf("%c wird zu %c! Oho!", input[i-1], playfairSquare[first_y * SQUARE_SIDE + first_x]);
      //printf("%c wird zu %c! Oho!", input[i], playfairSquare[second_y * SQUARE_SIDE + first_x]);
  
      input[i - 1] = playfairSquare[first_y * SQUARE_SIDE + first_x];
      input[i] = playfairSquare[second_y * SQUARE_SIDE + second_x];
    }
  }

  if (op == IS_ENCRYPTING) printf("Ciphertext: ");
  else printf("Klartext: ");
  printBigram(input);
}

//-----------------------------------------------------------------------------
/// TODO
/// 
///
/// @return pointer to the char array
//
void getInput(char* input, OperationType op)
{
  // Copied code from: Framework
  // START
  while(1) 
  {

    if (op == IS_ENCRYPTING) printf("Klartext: ");
    else printf("Ciphertext: ");

    fgets(input, MAX_INPUT_LENGTH, stdin);

    if(checkStringValidity(input, MAX_INPUT_LENGTH, op)) break;
  }
  // END
  cleanString(input, op);
  if (makeBigram(input, op) == ERROR) getInput(input, op);

  if (op == IS_ENCRYPTING) printf("Vorbereiteter Klartext: ");
  else printf("Vorbereiteter Ciphertext: ");

  printBigram(input);
}

//-----------------------------------------------------------------------------
/// TODO
///
/// @param text string to check 
///
/// @return length of the string
//
int makeBigram(char* input, OperationType op)
{

  int string_len = stringLength(input);
  char last_char = 0;
  char bigram[MAX_INPUT_LENGTH] = "";
  int j = 0;

  //printf("Stringlen of input: %d\n", string_len);

  for (int i = 0; i < string_len; i++)
  {
    char current_char = input[i];

    if (last_char != 0 && last_char == current_char)
    {
      if (op == IS_DECRYPTING) return ERROR;

      bigram[j++] = FILL_CHAR;
      bigram[j++] = current_char;
    }
    else 
    {
      bigram[j++] = current_char;
    }
    
    last_char = current_char;
  }

  string_len = stringLength(bigram);

  if (string_len % 2 != 0)
  {
    if (op == IS_ENCRYPTING) 
    {
      bigram[string_len] = FILL_CHAR;
      string_len++;
    }
    else return ERROR;
  }

  for (int i = 0; i < string_len; i++) input[i] = bigram[i];

  return SUCCESS;
}

//-----------------------------------------------------------------------------
/// TODO
///
/// @param text string to check 
///
/// @return length of the string
//
void printBigram(char* bigram)
{
  int string_len = stringLength(bigram);

  for (int i = 0; i < string_len; i++)
  {
    if ((i % 2) == 1) printf("%c ", bigram[i]);
    else printf("%c", bigram[i]);
  }

  printf("\n");
}


//-----------------------------------------------------------------------------
/// TODO
///
/// @param text string to check 
///
/// @return length of the string
//
char shiftRight(char index)
{
  char new_index = index + 1;
  if (new_index == SQUARE_SIDE) new_index = 0;

  return new_index;
}

//-----------------------------------------------------------------------------
/// TODO
///
/// @param text string to check 
///
/// @return length of the string
//
char shiftLeft(char index)
{
  char new_index = index - 1;
  if (new_index == -1) new_index = SQUARE_SIDE - 1;

  return new_index;
}

//-----------------------------------------------------------------------------
/// TODO
///
/// @param text string to check 
///
/// @return length of the string
//
void getIndices(char* playfairSquare, char element, char* element_x, char* element_y){

  for (int y_index = 0; y_index < SQUARE_SIDE; y_index++)
  {
    for (int x_index = 0; x_index < SQUARE_SIDE; x_index++)
    {
      if (playfairSquare[y_index * SQUARE_SIDE + x_index] == element)
      {
        *element_x = x_index;
        *element_y = y_index;
        return;
      }
    }
  }
}

//-----------------------------------------------------------------------------
/// Computes and returns the length of a string 
///
/// @param text string to check 
///
/// @return length of the string
//
int stringLength(char *text) 
{
  int i;
  for (i = 0; text[i]; i++);

  return i;
}

//-----------------------------------------------------------------------------
/// Changes a string to upper case 
///
/// @param text string to modify
//
void toUpper(char *text) 
{
  for (int i = 0; i < stringLength(text); i++)
  {
    if (text[i] >= 97 && text[i] <= 122)
    {
      text[i] -= 32;
    }
  }
}

//-----------------------------------------------------------------------------
/// Replace all the occurences of a letter in a string with another letter 
///
/// @param text string to modify
/// @param original letter to replace
/// @param new_char letter used for the substitution
//
void replaceLetters(char *text, char original, char new_char) 
{
  for (int i = 0; i < stringLength(text); i++)
  {
    if (text[i] == original)
    {
      text[i] = new_char;
    }
  }
}
