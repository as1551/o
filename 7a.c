#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX 1024
// Function to count characters, words, and lines in a string
void count(char *str, int *charCount, int *wordCount, int
*lineCount) {
int i = 0;
*charCount = 0;
*wordCount = 0;
*lineCount = 0;
int inWord = 0;
while (str[i] != '\0') {
// Ignore spaces and newlines for character count
if (str[i] != ' ' && str[i] != '\n') {
(*charCount)++;
}
// Count words: a word starts when we see a non-spaceafter a space/newline
if (str[i] != ' ' && str[i] != '\n' && !inWord) {
(*wordCount)++;
inWord = 1;
}
// Word ends when we encounter a space or newline
if (str[i] == ' ' || str[i] == '\n') {
inWord = 0;
}
// Count lines: increment when we see a newline
if (str[i] == '\n') {
(*lineCount)++;
}
i++;
}
// If the last character isn't a newline, we still count one line
if (i > 0 && str[i-1] != '\n') {
(*lineCount)++;
}
}
int main() {
char input[MAX];
char full_input[MAX] = ""; // Buffer to store all input lines
int fd1, fd2;
int charCount, wordCount, lineCount;
FILE *fp;
// Create two FIFOs
mkfifo("pipe1", 0666);
mkfifo("pipe2", 0666);
pid_t pid = fork();
if (pid > 0) { // Parent Process (Process 1)
// Continuously accept input from the user
printf("Enter sentences (end input with CTRL+D):\n");
while (fgets(input, MAX, stdin) != NULL) {
strcat(full_input, input); // Append each line of input to ull_input buffer
}
// Write the combined input to pipe1
fd1 = open("pipe1", O_WRONLY);
write(fd1, full_input, strlen(full_input) + 1);
close(fd1);
// Read processed data from pipe2
fd2 = open("pipe2", O_RDONLY);
char result[MAX];
read(fd2, result, sizeof(result));
close(fd2);
// Display the result
printf("Processed result from Process 2:\n%s\n", result);
// Remove the FIFOs
unlink("pipe1");
unlink("pipe2");
} else if (pid == 0) { // Child Process (Process 2)
// Read data from pipe1
fd1 = open("pipe1", O_RDONLY);
read(fd1, full_input, sizeof(full_input));
close(fd1);
// Count characters, words, and lines
count(full_input, &charCount, &wordCount, &lineCount);
// Write the counts to a file
fp = fopen("output.txt", "w");
fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n",
charCount, wordCount, lineCount);
fclose(fp);
// Write the contents of the file to pipe2
fd2 = open("pipe2", O_WRONLY);
fp = fopen("output.txt", "r");
char fileContents[MAX];
fread(fileContents, sizeof(char), MAX, fp);
write(fd2, fileContents, strlen(fileContents) + 1);
close(fd2);
fclose(fp);
} else {
perror("Fork failed");
exit(1);
}
return 0;
}
