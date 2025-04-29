/*
Title: cryptoMagic Encryption/Decryption
Author: Cherith Boya and Hamza Khan
Summary: This program allows the user to encrypt or decrypt a file based on their choice. 
The user can specify whether they want to encrypt or decrypt a file by using the flags -E (for encryption) or -D (for decryption). 

The program reads the file and processes it line by line. For encryption, it shifts the characters in the file and writes the transformed content to a new file with a .crp extension. 
For decryption, it reverses the transformation and writes the original content back to a new file with a .txt extension.

ENCRYPTION USAGE: ./cryptoMagic.exe -E <filename>
DECRYPTION USAGE: ./cryptoMagic.exe -D <filename>

Note: If there already exists a file with the same name, the program will not overwrite it.


ANOTHER NOTE PLEASE ENTER FORMMATED LIKE THIS AS OR COMPUTERS WERE OBTAINING ISSUES WITH DIRECTORY LOCATION 
& "C:\Users\hamza\OneDrive\Documents\C Programming\If Statements\ENGG1410-Labs\MINIPROJECT_2\cryptoMagic.exe" -E 
"C:\Users\hamza\OneDrive\Documents\C Programming\If Statements\ENGG1410-Labs\MINIPROJECT_2\text.txt"

^ THIS IS IN THE README FILE TOO

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void encrypt(const char *input_filename);  // Function to encrypt a file
void decrypt(const char *input_filename);  // Function to decrypt a file
void process_line_for_encryption(const char *line, FILE *output_file);  // Encrypts each line
void process_line_for_decryption(const char *line, FILE *output_file);  // Decrypts each line
void write_output_file(const char *filename, const char *content);  // Writes the encrypted/decrypted content to a file
void generate_output_filename(const char *input_filename, const char *mode, char *output_filename);  // Generates output filename based on mode (encryption or decryption)

// Main function: Entry point of the program
// The program checks if the user has provided the correct number of arguments and whether the mode (-E or -D) is valid
int main(int argc, char *argv[]) {
  // Check if the number of arguments is less than 2 (the program requires at least 2 arguments: mode and filename)
  if (argc < 2) {
    printf("Usage: cryptoMagic [-E|-D] <filename>\n");  // Inform the user how to use the program
    return 1;  // Exit the program if the user did not provide enough arguments
  }

  // Default to encryption mode
  int encrypt_flag = 1;  
  char *input_filename = argv[argc - 1];  // Set the input file to the last argument (filename)

  // Check if the user has specified decryption mode (-D) or encryption mode (-E)
  if (argc == 3) {  // If there are exactly 3 arguments (mode and filename)
    if (strcmp(argv[1], "-D") == 0) {  // If the mode is decryption, set the flag to 0 (false)
      encrypt_flag = 0;
    } else if (strcmp(argv[1], "-E") != 0) {  // If the mode is not -E or -D, print an error message
      printf("Invalid option. Use -E for encryption or -D for decryption.\n");
      return 1;  // Exit the program with an error
    }
  }

  // Check if the input filename is valid (it should not be NULL or empty)
  if (input_filename == NULL || strlen(input_filename) == 0) {
    printf("Error: No input file provided.\n");  // Error message if no filename is provided
    return 1;  // Exit the program if the filename is invalid
  }

  // Based on the flag, either encrypt or decrypt the file
  if (encrypt_flag) {
    encrypt(input_filename);  // Call the encrypt function if the flag is set to 1 (encryption)
  } else {
    decrypt(input_filename);  // Call the decrypt function if the flag is set to 0 (decryption)
  }

  return 0;  // Exit the program successfully
}

// Function to encrypt a file
// This function reads the input file, encrypts its content, and writes the encrypted content to a new output file
void encrypt(const char *input_filename) {
  // Open the input file in read mode ("r")
  FILE *input_file = fopen(input_filename, "r");
  if (!input_file) {  // If the file could not be opened, display an error and exit
    printf("Error opening input file");
    exit(1);
  }

  // Generate the output filename with the .crp extension for encryption
  char output_filename[255];
  generate_output_filename(input_filename, "E", output_filename);

  // Open the output file in write mode ("w")
  FILE *output_file = fopen(output_filename, "w");
  if (!output_file) {  // If the output file could not be opened, display an error and exit
    perror("Error opening output file");
    exit(1);
  }

  char line[121];  // Buffer to hold each line of the input file (up to 120 characters)

  // Read the input file line by line and encrypt each line
  while (fgets(line, sizeof(line), input_file)) {
    process_line_for_encryption(line, output_file);  // Encrypt the line and write it to the output file
  }

  fclose(input_file);  // Close the input file
  fclose(output_file);  // Close the output file
}

// Function to decrypt a file
// This function reads the input file, decrypts its content, and writes the decrypted content to a new output file
void decrypt(const char *input_filename) {
  // Open the input file in read mode ("r")
  FILE *input_file = fopen(input_filename, "r");
  if (!input_file) {  // If the file could not be opened, display an error and exit
    printf("Error opening input file");
    exit(1);
  }

  // Generate the output filename with the .txt extension for decryption
  char output_filename[255];
  generate_output_filename(input_filename, "D", output_filename);

  // Open the output file in write mode ("w")
  FILE *output_file = fopen(output_filename, "w");
  if (!output_file) {  // If the output file could not be opened, display an error and exit
    printf("Error opening output file");
    exit(1);
  }

  char line[256];  // Buffer to hold each line of the input file (up to 255 characters)

  // Read the input file line by line and decrypt each line
  while (fgets(line, sizeof(line), input_file)) {
    process_line_for_decryption(line, output_file);  // Decrypt the line and write it to the output file
  }

  fclose(input_file);  // Close the input file
  fclose(output_file);  // Close the output file
}

// Function to process each line of the file during encryption
// This function shifts the characters in the line and writes the result to the output file
void process_line_for_encryption(const char *line, FILE *output_file) {
  // Loop through each character in the line
  while (*line) {
    if (*line == '\t') {  // If the character is a tab, write "TT" to the output file
      fputs("TT", output_file);
    } else if (*line == '\n') {  // If the character is a newline, write it as is
      fputc('\n', output_file);
    } else {  // For other characters, shift their ASCII value and write the encrypted result
      int outChar = *line - 16;  // Shift the ASCII value by -16
      if (outChar < 32) {  // If the result is below the printable ASCII range
        outChar = (outChar - 32) + 144;  // Wrap it into a higher printable range
      }
      // Write the encrypted character as a 2-digit hexadecimal value to the output file
      fprintf(output_file, "%02X", outChar);
    }
    line++;  // Move to the next character in the line
  }
}

// Function to process each line of the file during decryption
// This function converts the hexadecimal characters back to their original form
void process_line_for_decryption(const char *line, FILE *output_file) {
  char hex_pair[3] = {0};  // Temporary buffer to hold each pair of hexadecimal characters

  // Loop through the characters in the line
  while (*line) {
    if (*line == 'T' && *(line + 1) == 'T') {  // If the sequence "TT" is found, replace it with a tab
      fputc('\t', output_file);
      line += 2;  // Skip the next character since "TT" is two characters
    } else {  // Otherwise, convert the hexadecimal pair back to the original character
      hex_pair[0] = *line++;  // Get the first character of the hex pair
      hex_pair[1] = *line++;  // Get the second character of the hex pair
      int outChar = strtol(hex_pair, NULL, 16) + 16;  // Convert hex pair to decimal and reverse the shift

      if (outChar > 127) {  // If the result is outside the printable ASCII range
        outChar = (outChar - 144) + 32;  // Wrap it back into the printable range
      }

      fputc(outChar, output_file);  // Write the decrypted character to the output file
    }
  }
}

// Function to generate the output filename based on the input filename and operation mode (encryption or decryption)
// It adds .crp for encryption and .txt for decryption to the filename
void generate_output_filename(const char *input_filename, const char *mode, char *output_filename) {
  // Find the file extension (if any) in the input filename
  const char *ext = strrchr(input_filename, '.');
  if (ext) {
    // Copy the filename without the extension
    strncpy(output_filename, input_filename, ext - input_filename);
    output_filename[ext - input_filename] = '\0';  // Null-terminate the string
  } else {
    strcpy(output_filename, input_filename);  // If there is no extension, use the whole filename
  }

  // Append the appropriate extension based on the mode (encryption or decryption)
  if (strcmp(mode, "E") == 0) {
    strcat(output_filename, ".crp");  // Add .crp for encryption
  } else {
    strcat(output_filename, ".txt");  // Add .txt for decryption
  }
}
