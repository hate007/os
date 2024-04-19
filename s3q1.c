#include <stdio.h>
#include <stdbool.h>

int available[10];
int max[10][10];
int allocation[10][10];
int need[10][10];
int safeSequence[10];
int work[10];
bool finish[10];
int num_processes;
int num_resources;

void accept();
void displayAllocationMax();
void displayNeed();
void displayAvailable();
bool isSafeState();

int main() {
    int choice;

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    while (choice != 6) {
        printf("\nBanker's Safety Algorithm\n");
        printf("1. Accept Available, Allocation & Max\n");
        printf("2. Display Allocation and Max\n");
        printf("3. Display Need Matrix\n");
        printf("4. Display Available\n");
        printf("5. Check Safety and Display Safe Sequence\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                accept();
                break;
            case 2:
                displayAllocationMax();
                break;
            case 3:
                displayNeed();
                break;
            case 4:
                displayAvailable();
                break;
            case 5: {
                if (isSafeState()) {
                    printf("\nSystem is in a safe state.\n");
                    printf("Safe sequence: ");
                    for (int i = 0; i < num_processes; ++i)
                        printf("%d ", safeSequence[i]);
                    printf("\n");
                } else {
                    printf("\nSystem is in an unsafe state.\n");
                }
            } break;
            case 6:
                printf("\nExiting!!");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    return 0;
}

void accept() {
    printf("\nAccepting Available!!\n");
    printf("Enter available resources : ");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);
    printf("\nAccepting Allocation!!\n");
    printf("Enter all allocation : \n");
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &allocation[i][j]);
    printf("\nAccepting Max!!\n");
    printf("Enter all max : \n");
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &max[i][j]);
    // calculating need
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
            if (need[i][j] < 0)
                need[i][j] = 0;
        }

}

void displayAllocationMax() {
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < num_resources; ++j)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < num_resources; ++j)
            printf("%d ", max[i][j]);
        printf("\n");
    }
}

void displayNeed() {
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < num_resources; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void displayAvailable() {
    printf("\nAvailable Resources:\n");
    for (int i = 0; i < num_resources; ++i)
        printf("%d ", available[i]);
    printf("\n");
}

bool isSafeState() {
    for (int i = 0; i < num_resources; i++)
        work[i] = available[i];
    for (int i = 0; i < num_processes; i++)
        finish[i] = false;
    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                //checking need < work
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources) {
                    for (int k = 0; k < num_resources; ++k)
                        work[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}