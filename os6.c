#include <stdio.h>
#include <stdbool.h>
#define FRAME_SIZE 3 // Define the frame size for the algorithms
// Function to print the current page frame
void printFrame(int frame[], int size) {
for (int i = 0; i < size; i++) {
printf("%d ", frame[i]);
}
printf("\n");
}
// FCFS Page Replacement Algorithm
void FCFS(int pages[], int page_count) {
int frame[FRAME_SIZE];
for (int i = 0; i < FRAME_SIZE; i++) {
frame[i] = -1; // Initialize frame with -1 (indicating empty)
}
int page_faults = 0;
int index = 0;
for (int i = 0; i < page_count; i++) {
bool page_found = false;
for (int j = 0; j < FRAME_SIZE; j++) {
if (frame[j] == pages[i]) {
page_found = true;
break;
}
}
if (!page_found) {
frame[index] = pages[i];
index = (index + 1) % FRAME_SIZE; // Move to next index cyclically
page_faults++;
}
printFrame(frame, FRAME_SIZE);
}
printf("Total Page Faults (FCFS): %d\n", page_faults);
}
// LRU Page Replacement Algorithm
void LRU(int pages[], int page_count) {
int frame[FRAME_SIZE];
int last_used[FRAME_SIZE];
for (int i = 0; i < FRAME_SIZE; i++) {
frame[i] = -1; // Initialize frame with -1 (indicating empty)
last_used[i] = -1; // Initialize last used time
}
int page_faults = 0;
int time = 0;
for (int i = 0; i < page_count; i++) {
bool page_found = false;
for (int j = 0; j < FRAME_SIZE; j++) {
if (frame[j] == pages[i]) {
page_found = true;
last_used[j] = time++;
break;
}
}
if (!page_found) {
int lru_index = 0;
for (int j = 1; j < FRAME_SIZE; j++) {
if (last_used[j] < last_used[lru_index]) {
lru_index = j;
}
}
frame[lru_index] = pages[i];
last_used[lru_index] = time++;
page_faults++;
}
printFrame(frame, FRAME_SIZE);
}
printf("Total Page Faults (LRU): %d\n", page_faults);
}
// Optimal Page Replacement Algorithm
void Optimal(int pages[], int page_count) {
int frame[FRAME_SIZE];
for (int i = 0; i < FRAME_SIZE; i++) {
frame[i] = -1; // Initialize frame with -1 (indicating empty)
}
int page_faults = 0;
for (int i = 0; i < page_count; i++) {
bool page_found = false;
for (int j = 0; j < FRAME_SIZE; j++) {
if (frame[j] == pages[i]) {
page_found = true;
break;
}
}
if (!page_found) {
int farthest_index = 0;
int farthest_dist = -1;
for (int j = 0; j < FRAME_SIZE; j++) {
int k;
for (k = i + 1; k < page_count; k++) {
if (frame[j] == pages[k]) {
if (k > farthest_dist) {
farthest_dist = k;
farthest_index = j;
}
break;
}
}
if (k == page_count) {
farthest_index = j;
break;
}
}
frame[farthest_index] = pages[i];
page_faults++;
}
printFrame(frame, FRAME_SIZE);
}
printf("Total Page Faults (Optimal): %d\n", page_faults);
}
int main() {
int n =0;
printf("enter the totatl length of process :");
scanf("%d",&n);
int pages [n];
printf("enter the page reference string :\n");
for(int i =0;i<n;i++){

scanf("%d",&pages[i]);

}
int page_count = sizeof(pages) / sizeof(pages[0]);
printf("Page Replacement using FCFS:\n");
FCFS(pages, page_count);
printf("\nPage Replacement using LRU:\n");
LRU(pages, page_count);
printf("\nPage Replacement using Optimal:\n");
Optimal(pages, page_count);
return 0;
}



//7 0 1 2 0 3 0 4 2 3 0 3 7 0 1  
