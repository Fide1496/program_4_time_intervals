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
    
    // Input file
    const char *input_file = "angl.dat";

    // Nanosleep variables
    struct timespec ts;
    ts.tv_sec=1;
    ts.tv_nsec=0;

    // Open input file and 
    int fd = checkError(open(input_file,O_RDONLY),"Open angl.dat");

    double buffer[PACKET_SIZE*DOUBLE_SIZE];

    while (read(fd, buffer, DOUBLE_SIZE * PACKET_SIZE) == DOUBLE_SIZE * PACKET_SIZE)
    {
        // If range conditions are met for roll and pitch, print values   
        double roll = buffer[0];
        double pitch = buffer[1];
        double yaw = buffer[2];


        if(roll > -20 && roll < 20 && pitch > -20 && pitch < 20)
        {
            printf("Values for roll and pitch inside the range -20 to 20\n");
            printf("Roll: %.2lf, Pitch: %.2lf \n", roll, pitch);
            fflush(stdout);
        }

        // Delay each print out message by 1 second
        nanosleep(&ts,NULL);
    }

    // Close input file
    close(fd);

    exit(EXIT_SUCCESS);
}