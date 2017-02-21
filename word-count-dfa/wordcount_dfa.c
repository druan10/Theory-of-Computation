#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int alphabet[128]; //Characters in the language
int ascii_values[128]; //Used to hold ascii values of characters in order
int word_length = 0, num_of_unique_characters = 0, num_of_symbols = 0, num_of_states = 0;
int transition_table[100][128]; //[state][column]
char *file_contents;
long input_file_size;

int get_word_length(char* word){
  int i = 0;
  while (word[i] != '\0') {i++;}
  return (i);
}

/*Return the number of unique characters found in our alphabet*/
int get_num_of_unique_characters() {
  int i, count = 0;
  for (i = 0; i < 128; i++) {
    if ( alphabet[i] != 0 ) {count++;}
  }
  return count;
}

/*Construct character frequency table for the given word*/
void construct_frequency_table(char *word) {
  int i, count = 0, ascii_value = 0;
  
  for (i = 0; i < 128; i++) {alphabet[i] = 0;}

  for (i = 0; i < word_length; i++){ 
    ascii_value = (int) word[i];
    if (ascii_value < 97){
      alphabet[ascii_value+32]++;
    } else {
      alphabet[ascii_value]++;
    }
  }

  // i = 0;
  // printf("Unique Characters Found: ");

  // for (i = 0; i < 128; i++){
  //   if ( alphabet[i] != 0){
  //     printf(" %c", (char) i);
  //   }
  // }
  // printf("\n");
}


void print_trans_table(char *word){
  //Print Heading
  printf(" * | _ , .");
  for (int i = 0; i < word_length; i++) {
    printf(" %c", (char) ascii_values[i]);
  }
  printf("\n");
  //Print Table
  for (int i = 0; i < num_of_states; i++) {
    printf(" %i |",i); //Print State
    for (int j = 0; j < num_of_symbols; j++) {
      printf(" %i", transition_table[i][j]); //Print value @ index [i][j], the position to move to
    }
  printf("\n");
  }
}

void construct_transition_table(char *word) {
  //Calculate the properties for the transition table
  construct_frequency_table(word);
  num_of_symbols = get_num_of_unique_characters() + 3; 
  num_of_states = word_length + 4; 

  int count = 0;

  for (int i = 0; i < 128; i++){
    if ( alphabet[i] != 0 ) {
      ascii_values[count] = i;
      count++;
    }
  }

  printf("Number of Symbols in transition table: %i\n", num_of_symbols);
  printf("Number of States: %i\n", num_of_states);
  print_trans_table(word);
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
  
  word_length = get_word_length(word);
  printf("Word Length: %i\n", word_length);
  construct_transition_table(word);
  num_of_unique_characters=get_num_of_unique_characters();
  printf("Number of Unique Characters in \'%s\': %i\n", word, num_of_unique_characters);
  return 0;

}



