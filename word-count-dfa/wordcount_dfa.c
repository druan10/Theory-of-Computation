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
int num_of_characters = 0;
int transition_table[100][128];
char *file_contents;
long input_file_size;
int num_states = 0;

/*
------ THE SUBROUTINES BELOW ARE RECOMMENDED ------

void print_trans_table()

*/

int get_word_length(char *word) {

  int i = 0;
  while (word[i] != '\0') {
    i++ ;
  }

  return (i);
}

/*Return the number of unique characters found in our alphabet*/
int get_num_characters(char *word) {

  int count = 0;

  for (int i = 0; i < 128; i++) {
    if ( alphabet[i] > 1 ) {
      count++;
    }
  }
  return count;

}

int construct_frequency_table(char* word) {

  int i;
  int count = 0;

  for (i = 0; i < 128; i++) {
    alphabet[i] = 0;
  }

  for (i = 0; i < word_length; i++) {
    if (word[i] < 97) {
      alphabet[word[i+32]]++;
    } else {
      alphabet[word[i]]++;
    }
  }

  for (i = 0; i < 128; i++) {
    if (alphabet[i] != 0) {
      count++;
    }
  }

  return count;
}




int main(int argc, char *argv[])
{

  /////////////////////////////////////////////////////////////////////////
  /* 
     Read in a file by it's name and put contents into an array called:
     "file_contents" that is null terminated and length: "input_file_size"
     I highly recommend you use the variable input_file_size
  */

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
  
  /*num_of_states = word_length + 4;
  num_of_characters = get_num_characters + 3;*/

  word_length = get_word_length(word);

  printf("Word Length: %i\n", word_length);
  num_of_characters = construct_frequency_table(word);
  printf("Number of Unique Characters in \'%s\': %i\n", word, num_of_characters);
  return 0;

}



