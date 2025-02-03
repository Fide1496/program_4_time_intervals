#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

#define PACKET_SIZE 3
#define DOUBLE_SIZE sizeof(double)

// Function to check errors when opening files
int checkError(int val, const char *msg) {
    if (val == -1) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return val;
}

int main(){
    
    const char *input_file = "angl.dat";

    int fd = checkError(open(input_file,O_RDONLY),"Open angl.dat");

    double buffer[PACKET_SIZE];
    struct timespec req = {1, 0};
    
    while (read(fd, buffer, DOUBLE_SIZE * PACKET_SIZE) == DOUBLE_SIZE * PACKET_SIZE)
    {
        printf("roll: %lf pitch: %lf yaw: %lf\n", buffer[0], buffer[1], buffer[2]);
        
        // Delay each print out message by 1 second
        if (nanosleep(&req, NULL) < 0) {
            perror("nanosleep failed");
            break;
        }
    }

    // Close input file
    close(fd);

    return EXIT_SUCCESS;
}