#include<stdio.h>
#include<stdlib.h>
int main()
{
    int requests[100],i,j,num_req,total_head = 0,initial,disk_size,move;
    printf("Enter the number of Requests: ");
    scanf("%d",&num_req);
    printf("Enter the Requests sequence: ");
    for(i = 0;i < num_req; i++)
     scanf("%d",&requests[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter total disk size: ");
    scanf("%d",&disk_size);
    printf("Enter the head movement direction for Right 1 and for Left 0: ");
    scanf("%d",&move);
    
    for(i = 0;i < num_req; i++) {
        for(j = 0;j < num_req - i - 1; j++) {
            if(requests[j] > requests[j + 1]) {
                int temp;
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests [j + 1] = temp;
            }
        }
    }

    int index = 0;
    while (index < num_req && initial > requests[index])
        index++;

    printf("Order of requests served: ");
    if(move == 1) {
        for(i = index; i < num_req; i++) {
            total_head = total_head + abs(requests[i] - initial);
            initial = requests[i];
            printf("%d ", requests[i]);
        }
        for(i = index - 1; i >= 0;i--) {
             total_head = total_head + abs(requests[i] - initial);
             initial= requests[i];
             printf("%d ", requests[i]);
        }
    } else {
        for(i = index - 1; i >= 0;i--) {
            total_head = total_head + abs(requests[i] - initial);
            initial = requests[i];
            printf("%d ", requests[i]);
        }
        for(i = index; i < num_req; i++) {
             total_head = total_head + abs(requests[i] - initial);
             initial = requests[i];
             printf("%d ", requests[i]);
            
        }
    }
    printf("\nTotal head movement is %d",total_head);
    return 0;
}
