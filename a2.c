//-----------------------------------------------------------------------------
// a2.c
//
// Playfair Cipher
// A program which uses a simple playfair-like cipher alogirthm 
// to encrypt and decrpyt messages using a choosable key
//
// Group: 12
//
// Author: 12007661
//-----------------------------------------------------------------------------
//

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
void getInput(char* input, OperationType operation_type);
void cipher(char* playfair_square, char* input, OperationType operation_type);
int createBigrams(char* input, OperationType operation_type);
void printOutput(char* message, OperationType operation_type);
void printBigrams(char* bigrams);
void getIndices(char* playfair_square, char element, char* element_x, char* element_y);
char shiftRight(char index);
char shiftLeft(char index);

//-----------------------------------------------------------------------------
///
/// The main program
/// 
/// Generates a playfair square based on a key that the user must input
/// Then gives the user the choice to encrypt or decrypt a message
/// The program only ends if the user wishes so
///
/// @return always zero
//
int main()
{
  char playfair_square[SQUARE_SIDE][SQUARE_SIDE];
  generatePlayfairSquare(*playfair_square);

  char choice = 1;
  while(choice != CHOICE_STOP)
  {
    choice = getUserChoice();
    OperationType operation_type;

    if (choice == CHOICE_ENCRYPT)
    {
      operation_type = IS_ENCRYPTING;
    }
    else if (choice == CHOICE_DECRYPT)
    {
      operation_type = IS_DECRYPTING;
    }

    if (choice != CHOICE_INVALID && choice != CHOICE_STOP)
    {
    char input[MAX_INPUT_LENGTH] = "";

    getInput(input, operation_type);
    cipher(*playfair_square, input, operation_type);
    printOutput(input, operation_type);
    }
  }
  return 0;
}

//-----------------------------------------------------------------------------
/// Prompts the user to make a choice between 3 options
/// Reads the input and only accepts values '0', '1' and '2'
/// Everything else will automatically be set to the INVALID_CHOICE constant
///
/// @return a character between '0' and '2' or the INVALID_CHOICE constant
//
char getUserChoice() 
{
  printf(
    "\nWählen Sie bitte eine Option:\n"
    "1 - Verschlüsseln\n"
    "2 - Entschlüsseln\n"
    "0 - Programm beenden\n\n"
  );

  char choice;
  char tmp = CHOICE_INVALID;
  int i = 0;
  do  
  {
    choice = tmp;
    tmp = getchar();
    i++;
  } 
  while (tmp != '\n');

  if (i > 2)
  {
    choice = CHOICE_INVALID;
  }

  return choice;
}

//-----------------------------------------------------------------------------
/// Encrypts or Decrypts a message based on a playfair square
/// 
/// @param playfair_square two dimensional array for ciphering
/// @param input the message to en- or decrypt, already in bigram-form
/// @param operation_type either IS_ENCTYPTING or IS_DECRYPTING
//
void cipher(char* playfair_square, char* input, OperationType operation_type)
{  
  int string_len = stringLength(input);
  for (int i = 0 ; i < string_len; i++){

    if (i % 2 == 1){
      char first = input[i - 1];
      char second = input[i];
      char first_x; 
      char first_y; 
      char second_x; 
      char second_y;

      getIndices(playfair_square, first, &first_x, &first_y);
      getIndices(playfair_square, second, &second_x, &second_y);

      if (first_y == second_y)
      {
        if (operation_type == IS_ENCRYPTING)
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
        if (operation_type == IS_ENCRYPTING)
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
  
      input[i - 1] = playfair_square[first_y * SQUARE_SIDE + first_x];
      input[i] = playfair_square[second_y * SQUARE_SIDE + second_x];
    }
  }
}

//-----------------------------------------------------------------------------
/// Prompts the user for an input for en- or decrypting, 
/// checks if it is valid and processes it into bigrams
/// If the input is invalid it prompts the user again
/// 
/// @param input the array to save the input in
/// @param operation_type either IS_ENCTYPTING or IS_DECRYPTING 
//
void getInput(char* input, OperationType operation_type)
{
  // Copied code from: Framework
  // START
  while(1) 
  {
    if (operation_type == IS_ENCRYPTING) printf("Klartext: ");
    else printf("Ciphertext: ");

    fgets(input, MAX_INPUT_LENGTH, stdin);

    if(checkStringValidity(input, MAX_INPUT_LENGTH, operation_type)) break;
  }
  // END

  cleanString(input, operation_type);
  if (createBigrams(input, operation_type) == ERROR)
  {
    getInput(input, operation_type);
    return;
  }

  if (operation_type == IS_ENCRYPTING)
  {
    printf("Vorbereiteter Klartext: ");
  }
  else
  {
    printf("Vorbereiteter Ciphertext: ");
  } 

  printBigrams(input);
}

//-----------------------------------------------------------------------------
/// Takes a message for en- or decrypting and processes it into bigrams
/// If the message is for decrypting, also checks if the message is valid
///
/// @param input the message to process into bigrams
/// @param operation_type either IS_ENCTYPTING or IS_DECRYPTING
///
/// @return SUCCESS if the message was valid ERROR otherwise
//
int createBigrams(char* input, OperationType operation_type)
{
  int string_len = stringLength(input);
  char last_char = 0;
  char bigram[MAX_INPUT_LENGTH] = "";
  int j = 0;

  for (int i = 0; i < string_len; i++)
  {
    char current_char = input[i];

    if (current_char == 'W' && operation_type == IS_DECRYPTING)
    {
      return ERROR;
    }

    if (i % 2 == 1 && last_char == current_char)
    {
      if (operation_type == IS_DECRYPTING) {
        return ERROR;
      }
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
    if (operation_type == IS_ENCRYPTING) 
    {
      bigram[string_len] = FILL_CHAR;
      string_len++;
    }
    else
    {
      return ERROR;
    }
  }

  for (int i = 0; i < string_len; i++) input[i] = bigram[i];

  return SUCCESS;
}

//-----------------------------------------------------------------------------
/// Prints a variable amount if bigrams to stdout
///
/// @param bigrams the bigrams to print
//
void printBigrams(char* bigrams)
{
  int string_len = stringLength(bigrams);

  for (int i = 0; i < string_len; i++)
  {
    printf("%c", bigrams[i]);
    if ((i % 2) == 1 && i != string_len - 1)
    {
      printf(" ");
    }
  }
  printf("\n");
}

//-----------------------------------------------------------------------------
/// Prints the output after en- or decrypting to stdout
///
/// @param message the proccessed message to output
//
void printOutput(char* message, OperationType operation_type)
{
  if (operation_type == IS_ENCRYPTING)
  {
    printf("Ciphertext: ");
  }
  else
  {
    printf("Klartext: ");
  } 
  printBigrams(message);
}

//-----------------------------------------------------------------------------
/// Shifts an index one to the right/down and returns it
/// If the index is already in the right most/lowest positon of the playfair square
/// it gets set to the left most/highest positon instead
///
/// @param index the index to shift
///
/// @return the new index
//
char shiftRight(char index)
{
  char new_index = index + 1;
  if (new_index == SQUARE_SIDE)
  {
    new_index = 0;
  } 
  return new_index;
}

//-----------------------------------------------------------------------------
/// Shifts an index one to the left/up and returns it
/// If the index is already in the left most/highest positon of the playfair square
/// it gets set to the right most/lowest positon instead
///
/// @param index the index to shift
///
/// @return the new index
//
char shiftLeft(char index)
{
  char new_index = index - 1;
  if (new_index == -1)
  {
    new_index = SQUARE_SIDE - 1;
  } 
  return new_index;
}

//-----------------------------------------------------------------------------
/// Looks for the indices of a character in a 2D-array of characters
///
/// @param playfair_square the 2D-array to search in
/// @param element the char to search for
/// @param element_x gets set to the x index of the character
/// @param element_y gets set to the y index of the character
//
void getIndices(char* playfair_square, char element, char* element_x, char* element_y){

  for (int y_index = 0; y_index < SQUARE_SIDE; y_index++)
  {
    for (int x_index = 0; x_index < SQUARE_SIDE; x_index++)
    {
      if (playfair_square[y_index * SQUARE_SIDE + x_index] == element)
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
