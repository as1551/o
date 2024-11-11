#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_REQUESTS 100
// Function prototypes
void sstf(int requests[], int n, int head);
void scan(int requests[], int n, int head, int disk_size);
void c_look(int requests[], int n, int head);
int main() {
int n, head, choice, disk_size;
int requests[MAX_REQUESTS];
printf("Enter the number of requests: ");
scanf("%d", &n);
printf("Enter the request queue: ");
for (int i = 0; i < n; i++) {
scanf("%d", &requests[i]);
}
printf("Enter the initial head position: ");
scanf("%d", &head);
printf("Enter the total number of cylinders in the disk: ");
scanf("%d", &disk_size);
do {
printf("\nDisk Scheduling Algorithms\n");
printf("1. SSTF\n2. SCAN\n3. C-LOOK\n4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
sstf(requests, n, head);
break;
case 2:
scan(requests, n, head, disk_size);
break;
case 3:
c_look(requests, n, head);
break;
case 4:
printf("Exiting...\n");
break;
default:
printf("Invalid choice!\n");
}
} while (choice != 4);
return 0;
}
// Helper function to sort the array
void sort(int arr[], int n) {
int temp;
for (int i = 0; i < n-1; i++) {
for (int j = i+1; j < n; j++) {
if (arr[i] > arr[j]) {
temp = arr[i];
arr[i] = arr[j];
arr[j] = temp;
}
}
}
}
// SSTF Algorithm
void sstf(int requests[], int n, int head) {
int total_seek_time = 0, completed = 0, min_index, min_seek;
int completed_requests[MAX_REQUESTS] = {0}; // Keep track of completed requests
int current_head = head;
printf("\nSSTF Disk Scheduling\n");
printf("Order of service: ");
while (completed < n) {
min_seek = 9999; // Large value for comparison
for (int i = 0; i < n; i++) {
if (!completed_requests[i]) {
int seek_time = abs(requests[i] - current_head);
if (seek_time < min_seek) {
min_seek = seek_time;
min_index = i;
}
}
}
total_seek_time += min_seek;
current_head = requests[min_index];
completed_requests[min_index] = 1;
completed++;
printf("%d ", current_head);
}
printf("\nTotal Seek Time: %d\n", total_seek_time);
printf("Average Seek Time: %.2f\n", (float)total_seek_time /
n);
}
// SCAN Algorithm
void scan(int requests[], int n, int head, int disk_size) {
int total_seek_time = 0, current_head = head;
int requests_with_limits[MAX_REQUESTS + 2]; // Including 0and disk_size
int i, j;
printf("\nSCAN Disk Scheduling\n");
printf("Order of service: ");
// Include 0 and disk_size as limits
requests_with_limits[0] = 0;
for (i = 0; i < n; i++) {
requests_with_limits[i + 1] = requests[i];
}
requests_with_limits[n + 1] = disk_size - 1;
// Sort the requests along with 0 and disk_size
sort(requests_with_limits, n + 2);
// Move towards the right from head
for (i = 0; i < n + 2; i++) {
if (requests_with_limits[i] >= head) {
break;
}
}
// Serve the right side
for (j = i; j < n + 2; j++) {
printf("%d ", requests_with_limits[j]);
total_seek_time += abs(current_head -
requests_with_limits[j]);
current_head = requests_with_limits[j];
}
// Serve the left side after reaching the end
for (j = i - 1; j >= 0; j--) {
printf("%d ", requests_with_limits[j]);
total_seek_time += abs(current_head -
requests_with_limits[j]);
current_head = requests_with_limits[j];
}
printf("\nTotal Seek Time: %d\n", total_seek_time);
printf("Average Seek Time: %.2f\n", (float)total_seek_time /
n);
}
// C-LOOK Algorithm
void c_look(int requests[], int n, int head) {
int total_seek_time = 0, current_head = head;
int i, j;
printf("\nC-LOOK Disk Scheduling\n");
printf("Order of service: ");
// Sort the requests
sort(requests, n);
// Move towards the right from head
for (i = 0; i < n; i++) {
if (requests[i] >= head) {
break;
}
}
// Serve the right side
for (j = i; j < n; j++) {
printf("%d ", requests[j]);
total_seek_time += abs(current_head - requests[j]);
current_head = requests[j];
}
// Jump to the beginning (lowest request) and serve the left side
for (j = 0; j < i; j++) {
printf("%d ", requests[j]);
total_seek_time += abs(current_head - requests[j]);
current_head = requests[j];
}
printf("\nTotal Seek Time: %d\n", total_seek_time);
printf("Average Seek Time: %.2f\n", (float)total_seek_time /
n);
}
