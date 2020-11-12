// Assignment 2 Playfair Cypher 
// Autor: Tutors
//

// Constants
#define SIZE_BUFFER 300
#define MAX_KEY_LENGTH 25
#define SQUARE_SIDE 5
#define ERROR 0

// Strings
#define KEY_PROMPT "Bitte Schlüssel eingeben:"
#define SQUARE_STRING "\nPlayfair Quadrat:\n"
#define CHOSEN_KEY "Ausgewählter Schlüssel:"
#define LETTER_TO_SUBSTITUTE 'W'
#define SUBSTITUTE_LETTER 'V'
#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVXYZ"

//Enums
typedef enum 
{
  IS_ENCRYPTING = 1, 
  IS_DECRYPTING = 2,
  IS_KEY
} OperationType;

enum SearchResult 
{
  FOUND = 1,
  NOT_FOUND = -1
};

//-----------------------------------------------------------------------------
// Reads the key, checks and prepares it, then generates and outputs the 
// square
//
// @param square array where playfair square is written 
//
void generatePlayfairSquare(char *square);

//-----------------------------------------------------------------------------
// Checks if a string (key, plain/encrypted text) is valid
//
// @param text 
// @param max_length
// @param op
//
// @return 0 if invalid, 1 if valid 
//
int checkStringValidity(char *text, int max_length, OperationType op);

//-----------------------------------------------------------------------------
// Computes and returns the length of a string 
//
// @param text string to check 
//
// @return length of the string
//
extern int stringLength(char *text);

//-----------------------------------------------------------------------------
// Check if text contains only letters and spaces and returns the total number of letters
//
// @param text string to check
//
// @return 0 if the string contains non-alpha characters, otherwise the number of letters
//
int containsOnlyAlpha(char *text);

//-----------------------------------------------------------------------------
// Cleans string (remove spaces, change text to upper case, replaces W with V),
// removes any duplicate letter, appends the remaining alphabet to the key. Also
// prints the modified key.
//
// @param key original key 
//
void prepareKey(char *key);

//-----------------------------------------------------------------------------
// Removes spaces in the string and changes it to upper case and in case of decryption
// replaces W with V
//
// @param text string to clean
// @param op type of operation performed
//
void cleanString(char *text, OperationType op);

//-----------------------------------------------------------------------------
// Removes all spaces in place
//
// @param text string to modify
//
void removeSpaces(char *text);

//-----------------------------------------------------------------------------
// Changes a string to upper case 
//
// @param text string to modify
//
extern void toUpper(char *text);

//-----------------------------------------------------------------------------
// Replace all the occurences of a letter in a string with another letter 
//
// @param text string to modify
// @param original letter to replace
// @param new_char letter used for the substitution
//
extern void replaceLetters(char *text, char original, char new_char);

//-----------------------------------------------------------------------------
// Removes any duplicate letters in place
//
// @param text string to modify
//
void removeDuplicateLetters(char *text);

//-----------------------------------------------------------------------------
// Appends the remaining letters of the alphabet to the key 
//
// @param key current key 
//
void appendAlphaToKey(char *key);

//-----------------------------------------------------------------------------
// Checks if the string contains a certain character 
//
// @param text string to check
// @param to_find character to find
//
// @return FOUND(1) or NOT_FOUND(-1)
//
int stringContainsChar(char *text, char to_find);
