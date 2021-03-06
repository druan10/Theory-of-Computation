#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int alphabet[128]; //Character frequency table
int unique_characters[128]; // Unique characters in word + comma period and space, in order
int word_length = 0, num_of_unique_characters = 0, num_of_symbols = 0, num_of_states = 0;
int transition_table[100][128]; //[state][column]
char *file_contents;
long input_file_size;

int get_word_length(char* word) {
  int i = 0;
  while (word[i] != '\0') {i++;}
  return (i);
}

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
    //set up only lowercase symbols
    if (ascii_value < 97){
      alphabet[ascii_value+32]++;
    } else {
      alphabet[ascii_value]++;
    }
  }
}


void print_transition_table(char *word) {
  printf("  * |  _  ,  .");
  for (int i = 0; i < word_length; i++) {printf(" %2c", (char) unique_characters[i]);}
  printf("\n");
  for (int i = 0; i < num_of_states; i++) {
    printf(" %2i |",i);
    for (int j = 0; j < num_of_symbols; j++) {printf(" %2i", transition_table[i][j]);}
    printf("\n");
  }
  printf("\n");
}

void construct_transition_table(char *word) {
  construct_frequency_table(word);
  num_of_states = word_length + 4; //Rows in table
  num_of_symbols = get_num_of_unique_characters() + 3; //Columns in Table


  int count, i, j, found_flag = 0, current_char = 0, row = 0;
  int word_in_ascii[word_length]; //Int array where each index represents letter in the word in ascii

  //Sets up word_in_ascii_array
  for (i = 0; i < word_length; i++){
    if (word[i] < 97){
      word_in_ascii[i] = (int) word[i] + 32;
    } else {
      word_in_ascii[i] = (int) word[i];
    }
  }

  //Initialize Transition Table (most states redirect to state 1)
  for (i = 0; i < num_of_states; i++){
    for (j = 0; j < num_of_symbols; j++){
      transition_table[i][j] = 1;
    }
  }

  //Known states
  transition_table[0][0] = 2;
  transition_table[1][0] = 2;
  transition_table[1][1] = 2;
  transition_table[1][2] = 2;
  
  count=0;
  for (i = 0; i < 128; i++){
    if ( alphabet[i] != 0 ) {
      unique_characters[count] = i; 
      count++;
    }
  }
  
  //Second to Last Row
  for (i = 0; i < 3; i++){
    transition_table[num_of_states-2][i] = num_of_states-1;
  }

  //First and third row, in case first letter is the first letter of the word
  for (i = 0; i < word_length; i++){
    if (word_in_ascii[0] == unique_characters[i]){
      transition_table[0][i+3]=3;
      transition_table[2][i+3]=3;
    }
  }

  //Sets the values of the fourth to second to last rows linking letters
  int character_to_find=0;
  for (row = 3; row < num_of_symbols; row++){
    character_to_find = word_in_ascii[row-2];
    for (i = 0; i < num_of_symbols; i++){
      if (unique_characters[i]==character_to_find){
        transition_table[row][i+3] = row+1;
        break;
      }
    }
    
  }

  print_transition_table(word);
}

int grep_string(char *word, char *string){ 
  int k, i;  
  int current_state = 0, appearances = 0, count = 0, index = 3; 
  int accepting_state = num_of_states - 1;
  int symbols_in_ascii[num_of_symbols];

  symbols_in_ascii[0] = 32;
  symbols_in_ascii[1] = 44;
  symbols_in_ascii[2] = 46;

  count = 3;
  //set up symbols array
  for (i = 3; i < num_of_symbols; i++){
    //copies unique characters to an array of symbols including the space period and comma
    symbols_in_ascii[i]=unique_characters[i-3];
  }

  word_length = get_word_length(word); 

  for (k = 0;k < input_file_size; k++) { //parse input string

    int change_state_flag = 0; //If we haven't changed state, we didn't identify the character as a possible symbol
    int current_char = (int) file_contents[k]; 

    for (i = 0; i < num_of_symbols; i++) { 

      if (current_char == symbols_in_ascii[i] || current_char + 32 == symbols_in_ascii[i]) {
        //printf("%i\n", i);
        current_state = transition_table[current_state][i]; 
        change_state_flag = 1; 
        // printf("New state is %s\n", current_state);
      } 

    } 

    if (change_state_flag == 0){
      current_state = 1; 
    } 

    if(current_state == accepting_state) { 
      appearances++; current_state = 1; 
    } 

  } 

  printf("\n"); 
  printf("There word appeared %i times.\n", appearances); 
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
  construct_transition_table(word);
  printf("Number of States: %i\n", num_of_states);
  printf("Number of Symbols %i\n", num_of_symbols);
  printf("Word Length: %i\n", word_length);
  grep_string(word, file_contents);
  return 0;

}



