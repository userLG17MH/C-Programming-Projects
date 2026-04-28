#include <stdio.h>
#include <stdlib.h>

// Function to encrypt the file
void encryptFile(const char *inputFileName, const char *outputFileName, int key) 
{
    FILE *inputFile, *outputFile;
    char ch;

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) 
    {
        perror("Error opening input file for encryption");
        exit(EXIT_FAILURE);
    }

    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) 
    {
        perror("Error opening output file for encryption");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(inputFile)) != EOF) 
    {
        fputc(ch + key, outputFile); // Encrypt by adding the key
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("File encrypted successfully to %s\n", outputFileName);
}

// Function to decrypt the file
void decryptFile(const char *inputFileName, const char *outputFileName, int key) 
{
    FILE *inputFile, *outputFile;
    char ch;

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) 
    {
        perror("Error opening input file for decryption");
        exit(EXIT_FAILURE);
    }

    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) 
    {
        perror("Error opening output file for decryption");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(inputFile)) != EOF) 
    {
        fputc(ch - key, outputFile); // Decrypt by subtracting the key
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("File decrypted successfully to %s\n", outputFileName);
}

int main() 
{
    const char *originalFile = "original.txt";
    const char *encryptedFile = "encrypted.txt";
    const char *decryptedFile = "decrypted.txt";
    int encryptionKey = 3; // Example key

    // Create a sample original file
    FILE *fp = fopen(originalFile, "w");
    if (fp == NULL) 
    {
        perror("Error creating original file");
        return EXIT_FAILURE;
    }
    fprintf(fp, "This is a secret message.");
    fclose(fp);

    encryptFile(originalFile, encryptedFile, encryptionKey);
    decryptFile(encryptedFile, decryptedFile, encryptionKey);

    return 0;
}