#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int alphabet[128];
int word_length = 0;
int num_of_unique_characters = 0;
int num_of_symbols = 0;
int num_of_states = 0;
int transition_table[100][128];
char *file_contents;
long input_file_size;
/*void print_trans_table()*/

/*Return the length of the inputted word*/
int get_word_length(char* word) {
  int i = 0;
  while (word[i] != '\0') {i++ ;}
  return (i);
}

/*Return the number of unique characters found in our alphabet*/
int get_num_characters() {
  int count = 0;
  for (int i = 0; i < 128; i++) {
    if ( alphabet[i] != 0 ) {count++;}
  }
  return count;

}

/*Build a frequency table for the given word*/
void construct_frequency_table(char *word) {
  int i;
  int count = 0;
  for (i = 0; i < 128; i++) {alphabet[i] = 0;} //initialize alphabet
  for (i = 0; i < word_length; i++) { //increment appropriate arrays 
    if (word[i] < 97) {
      alphabet[word[i+32]]++;
    } else {
      alphabet[word[i]]++;
    }
  }
}

void construct_transition_table(char *word) {
  word_length = get_word_length(word);
  //Calculate the properties for the transition table
  construct_frequency_table(word);
  num_of_symbols = get_num_characters() + 3; //include space, comma, period
  num_of_states = word_length + 3; //1 step for every letter, 1 for accept, 1 for fail, and 1 for init

  printf("Number of Symbols: %i\n", num_of_symbols);
  printf("Number of States: %i\n", num_of_states);

}

void print_trans_table(){
  for (int i = 0; i < num_of_symbols; i++) {
    for (int j = 0; i < num_of_states; j++) {
      printf("%i ", transition_table[i][j]);
    }
  printf("\n");
  }
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
  /*print the input string*/
  
  char *word = argv[2] ;
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
  /*Creates a transition table and parses the string
  word_length = get_word_length(word);
  printf("Word Length: %i\n", word_length);
  construct_frequency_table(word);
  int symbols[num_of_unique_characters+3]; //Unique characters + space, comma, and Period
  printf("Number of Unique Characters in \'%s\': %i\n", word, num_of_unique_characters);
  */
  construct_transition_table(word);

  return 0;

}



