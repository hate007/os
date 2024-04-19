#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main() {

  int head, num_disk_blocks, queue[MAX], i, total_head_movement = 0; 
  
  printf("\nEnter initial head position: ");
  scanf("%d", &head);
   
  printf("\nEnter number of disk blocks: ");
  scanf("%d", &num_disk_blocks);
   
  printf("\nEnter requests sequence: ");
  for(i = 0; i < num_disk_blocks; i++) 
    scanf("%d", &queue[i]);

  printf("\nOrder of requests served:\n");
  
  for(i = 0; i < num_disk_blocks; i++) {
    printf("%d ", queue[i]);
    total_head_movement += abs(queue[i] - head);
    head = queue[i];
  }
   
  printf("\nTotal head movement = %d \n", total_head_movement);
  
  return 0;  
}
