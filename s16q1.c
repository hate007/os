#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_BLOCKS 100

int disk[MAX_BLOCKS] = {0};
char directory_name[MAX_BLOCKS][20];
int start_blocks[MAX_BLOCKS] = {0};
int file_counts[MAX_BLOCKS] = {0};

void showBitVector(int n);
void createNewFile(int n);
void showDirectory(int n);

int main() {
    int n, choice;
    
    printf("Enter the total number of disk blocks: ");
    scanf("%d", &n);
    
    srand(time(NULL));
    
    for (int i = 0; i < n/2; i++) {
        int block = rand() % n;
        disk[block] = 1;
    }
    
    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                showBitVector(n);
                break;
            case 2:
                createNewFile(n);
                break;
            case 3:
                showDirectory(n);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        } 
    } while(choice != 4);

    return 0;
}

void showBitVector(int n) {
    printf("\nBit Vector (Disk Blocks):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

void createNewFile(int n) {
    char filename[20];
    int length;
    
    printf("\nEnter filename: ");
    scanf("%s", filename);
    
    printf("Enter length of the file '%s': ", filename);
    scanf("%d", &length);
    
    int start_block = -1;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (disk[i] == 0) {
            if (count == 0) {
                start_block = i;
            }
            count++;
            if (count == length) {
                break;
            }
        } else {
            count = 0;
            start_block = -1;
        }
    }
    
    if (start_block == -1 || count < length) {
        printf("Error: No contiguous space available for file '%s'.\n", filename);
        return;
    }
    
    for (int i = start_block; i < start_block + length; i++) {
        disk[i] = 1;
        strcpy(directory_name[i], filename); 
        start_blocks[i] = start_block;
        file_counts[i] = length;
    }
    
    printf("File '%s' created successfully.\n", filename);
}

void showDirectory(int n) {
    printf("\nDirectory:\n");
    printf("--------------------------\n");
    printf("Filename     Start  Count\n");
    printf("--------------------------\n");
    
    for (int i = 0; i < n; i++) {
        if (disk[i] == 1 && i == start_blocks[i]) {
            printf("%-12s %-5d %-5d\n", directory_name[i], start_blocks[i], file_counts[i]);
        }
    }
    
    printf("----------------------------\n");
}
