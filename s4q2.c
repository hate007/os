#include <stdio.h>
#include <stdlib.h>

int main() {
    int requests[100], num_req, total_head = 0, initial, disk_size, move;

    printf("Enter the number of requests: ");
    scanf("%d", &num_req);
    
    printf("Enter the request sequence: ");
    for (int i = 0; i < num_req; i++)
        scanf("%d", &requests[i]);
        
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    
    printf("Enter total disk size: ");
    scanf("%d", &disk_size);
    
    printf("Enter the head movement direction (1 for Right, 0 for Left): ");
    scanf("%d", &move);

    for (int i = 0; i < num_req - 1; i++) {
        for (int j = 0; j < num_req - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index = 0;
    while (index < num_req && initial > requests[index])
        index++;

    printf("Order of requests served: ");

    if (move == 1) { //Right
        for (int i = index; i < num_req; i++){
            total_head += abs(requests[i] - initial);
            initial = requests[i];
            printf("%d ", requests[i]);
            }
        total_head += abs(disk_size - requests[num_req - 1]);
        initial = disk_size;
        for (int i = index-1; i >=0 ; i--){
            total_head += abs(requests[i] - initial);
            printf("%d ", requests[i]);
            initial = requests[i];
            }
    } else { // Left
        for (int i = index - 1; i >= 0; i--){
            total_head += abs(requests[i] - initial);
            initial = requests[i];
            printf("%d ", requests[i]);
            }
        total_head += abs(requests[0] - 0);
        initial = 0;
        for (int i = index; i <= num_req - 1 ; i++){
            total_head += abs(requests[i] - initial);
            initial = requests[i];
            printf("%d ", requests[i]);
        }
    }
    
    printf("\n");
    printf("Total head movement: %d\n", total_head);

    return 0;
}
