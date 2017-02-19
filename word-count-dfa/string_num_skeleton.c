#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
     This global variable is recommended to contain the NUMBER of times each 
     ascii symbol appears in the text file (i.e. I suggest using it as a
     frequency table).
  
     Note that you only need to pay attention to the symbols 'A-Z' and  'a-z' 
     and ' ' and ',' and '.' as the program only parses out words made up of 
     english letters and the only allowable punctuation is space, comma, 
     and period. 
 */
int alphabet[128];
int word_length = 0;


/*
------ THE SUBROUTINES BELOW ARE RECOMMENDED ------

void print_trans_table()

void construct_trans_table()


*/

int get_word_length(char *word) {

  int i = 0;
  while (word[i] != '\0') {
    i++ ;
  }

  return (i);
}

/*number of unique characters in a word*/
int get_num_characters(char *word) {

  /*Characters are identified by ascii value*/
  int current_letter = 0;
  int characters_found[word_length];
  int num_unique_characters = 0;

  //Initialize array of found characters
  for (int i = 0; i < word_length; i++) {
    characters_found[i] = 0;
  }

  /*Get unique characters in the word*/
  for (int i = 0; i < word_length; i++) {

    current_letter = (int) word[i];
    
    for (int j = 0; j < word_length; j++) {
      
      if ( current_letter == characters_found[j] ) {
        break;
      }

      if ( characters_found[j] == 0 ) {
        characters_found[j] =  current_letter;
        printf("%c\n", (char) current_letter);
        num_unique_characters++;
        break;
      }
    }
  }

  return num_unique_characters;
  
}

int main(int argc, char *argv[])
{

  /////////////////////////////////////////////////////////////////////////
  /* 
     Read in a file by it's name and put contents into an array called:
     "file_contents" that is null terminated and length: "input_file_size"
     I highly recommend you use the variable input_file_size
  */

  char *file_contents;
  long input_file_size;
  FILE *input_file = fopen(argv[1], "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  file_contents[input_file_size] = '\0';

  /////////////////////////////////////////////////////////////////////////
  
  char *word = argv[2] ;
  char trans_table[100][128] ;
  int flag = 0 ;
  int k ;

  printf("\"") ;
  for(k=0;k<input_file_size;k++) {
    if(file_contents[k] == '\n') { printf("\"") ; flag = 1 ; }
    printf("%c",file_contents[k]) ;
  }
  if(flag == 0) { printf("\"") ; } 
  printf("\n") ;

  /////////////////////////////////////////////////////////////////////////

  int l;
  int num_characters;

  for (int l = 0; l < 128; l++) {
    alphabet[l] = 0;
  }

  word_length = get_word_length(word);
  printf("Word Length: %i\n", word_length);
  num_characters = get_num_characters(word);
  printf("Num of Unique Characters in \'%s\': %i\n", word, num_characters);

  return 0;

}



