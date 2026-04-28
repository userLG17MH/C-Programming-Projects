#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text_content[10000]; // Buffer for loaded or created text content

// Function declarations
void save_to_file();
void load_from_file();
void display_text_file();
void encryptFile(const char *inputFileName, const char *outputFileName, int key);
void decryptFile(const char *inputFileName, const char *outputFileName, int key);

// Function to count words in a string
int count_words(const char *text) 
{
    int count = 0;
    int inWord = 0;

    for (int i = 0; text[i] != '\0'; i++) 
	{
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') 
		{
            inWord = 0;
        } else if (inWord == 0) 
		{
            inWord = 1;
            count++;
        }
    }
    return count;
}

// Save new content to a file
void save_to_file()
{
    char filename[50];
    FILE *file;

    printf("\nEnter filename to save: ");
    scanf("%s", filename);

    printf("Enter data to save (max 9999 characters):\n");
    getchar(); // consume leftover newline
    fgets(text_content, sizeof(text_content), stdin);

    file = fopen(filename, "w");
    if (!file)
    {
        printf("Error saving data!\n");
        return;
    }

    fputs(text_content, file);
    fclose(file);
    printf("Data saved successfully to '%s'!\n", filename);
}

// Load content from a file to text_content buffer
void load_from_file()
{
    char filename[50];
    FILE *file;

    printf("\nEnter filename to open: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (!file)
    {
        printf("No previous data found with name '%s'.\n", filename);
        return;
    }

    // Read file content into buffer
    size_t len = fread(text_content, 1, sizeof(text_content) - 1, file);
    text_content[len] = '\0'; // Null terminate

    fclose(file);
    printf("Data loaded successfully from '%s'!\n", filename);
}

// Display content and word count
void display_text_file() 
{
    if (strlen(text_content) == 0) 
	{
        printf("\nNo text content available. Please create or open a file first.\n");
        return;
    }
    printf("\n--- Current Text Content ---\n%s\n", text_content);
    printf("--- End of Content ---\n");
    printf("Word count: %d\n", count_words(text_content));
}

// Encrypt file content using a key and write to output file
void encryptFile(const char *inputFileName, const char *outputFileName, int key) 
{
	FILE *inputFile = fopen(inputFileName, "r");
	if (!inputFile) 
	{
		perror("Error opening input file for encryption");
		return;
	}
	
	FILE *outputFile = fopen(outputFileName, "w");
	if (!outputFile) 
	{
		perror("Error opening output file for encryption");
		fclose(inputFile);
		return;
	}
	
	int ch;
	while ((ch = fgetc(inputFile)) != EOF) 
	{
		fputc(ch + key, outputFile); // encrypt
	}
	
	fclose(inputFile);
	fclose(outputFile);
	printf("File encrypted successfully to '%s'\n", outputFileName);
}

// Decrypt file content using a key and write to output file
void decryptFile(const char *inputFileName, const char *outputFileName, int key) 
{
	FILE *inputFile = fopen(inputFileName, "r");
	if (!inputFile) 
	{
		perror("Error opening input file for decryption");
		return;
	}
	
	FILE *outputFile = fopen(outputFileName, "w");
	if (!outputFile) 
	{
		perror("Error opening output file for decryption");
		fclose(inputFile);
		return;
	}
	
	int ch;
	while ((ch = fgetc(inputFile)) != EOF) 
	{
		fputc(ch - key, outputFile); // decrypt
	}
	
	fclose(inputFile);
	fclose(outputFile);
	printf("File decrypted successfully to '%s'\n", outputFileName);
}

int main() 
{
    int choice;
    char input = 'Y';

    while(input == 'Y' || input == 'y') 
	{
        printf("\nWelcome To Text-File Management System with Encryption\n");
        printf("==========================================\n");
        printf(" **MENU** \n");
        printf(" 1. Make A New Text-File (Max 9999 characters)\n");
        printf(" 2. Load A Text File\n");
        printf(" 3. Display The Text File\n");
        printf(" 4. Encrypt A Text File\n");
        printf(" 5. Decrypt A Text File\n");
        printf(" 6. Exit\n");

        printf("Choose Any Option: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                save_to_file();
                break;
            case 2:
                load_from_file();
                break;
            case 3:
                display_text_file();
                break;
            case 4:
            {
                char inputFile[50], outputFile[50];
                int key;
                
                printf("Enter input filename to encrypt: ");
                scanf("%s", inputFile);
                printf("Enter output filename for encrypted result: ");
                scanf("%s", outputFile);
                printf("Enter encryption key (integer): ");
                scanf("%d", &key);
                encryptFile(inputFile, outputFile, key);
                break;
            }
            case 5:
            {
                char inputFile[50], outputFile[50];
                int key;
                printf("Enter input filename to decrypt: ");
                scanf("%s", inputFile);
                printf("Enter output filename for decrypted result: ");
                scanf("%s", outputFile);
                printf("Enter decryption key (integer): ");
                scanf("%d", &key);
                decryptFile(inputFile, outputFile, key);
                break;
            }
            case 6:
                printf("Thank You! Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }

        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &input);

        while (input != 'Y' && input != 'y' && input != 'N' && input != 'n') 
		{
            printf("Invalid input. Please enter Y/y for Yes or N/n for No: ");
            scanf(" %c", &input);
        }
    }
    printf("Program Exiting. Thank-You!\n");
    return 0;
}
