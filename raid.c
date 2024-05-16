/*
Felicia Drysdale: Operating Systems Project 3
Section: 001
This program maps the location of sectors in a RAID device into the sectors of the hard disks that compose it.
This code reads from standard input and prints the result to standard output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void raid0(int N, int C, int Q, int queries[]);
void raid1(int Q, int queries[]);
void raid01(int N, int Q, int queries[]);
void raid10(int N, int Q, int queries[]);
void raid4(int N, int Q, int queries[]);
void raid5(int N, int Q, int queries[]);

int main() {

    //Declare T to hold the string
    char T[4]; 

    int N, C, S, Q;
    scanf("%s %d %d %d %d", T, &N, &C, &S, &Q);

    //Allocate memory for queries
    int *queries = (int*)malloc(Q * sizeof(int));
    if (queries == NULL) {
        return 1;
    }
    //Read the queries and store
    for (int i = 0; i < Q; i++) {
        scanf("%d", &queries[i]);
    }
    //Check to see what RAID to run
    if (strcmp(T, "0") == 0) {
        //Raid-0
        raid0(N, C, Q, queries);

    } else if (strcmp(T, "1") == 0) {
        //Raid-1
        raid1(Q, queries);

    } else if (strcmp(T, "01") == 0) {
        //Raid-01
        raid01(N, Q, queries);

    } else if (strcmp(T, "10") == 0) {
        //Raid-10
        raid10(N, Q, queries);

    } else if (strcmp(T, "4") == 0) {
        //Raid-4
        raid4(N, Q, queries);

    } else if (strcmp(T, "5") == 0) {
        //Raid-5
        raid5(N, Q, queries);
    }

    free(queries);
    return 0;
}

//RAID-0
void raid0(int N, int C, int Q, int queries[]) {

    int disk, stripe, disk_tb, stripe_width;

    for (int i=0; i < Q; i++) {
        disk = (queries[i] / C) % N;

        //Disk calculation from the textbook
        disk_tb = queries[i] % C;

        //Stripe width, then final stripe calculation
        stripe_width = C * N;
        stripe = (queries[i] / stripe_width) * C + disk_tb;
        printf("%d %d\n", disk, stripe);
    }
}

//RAID-1
void raid1(int Q, int queries[]) {

    //Since RAID1 is always mirrored and N=2 always, it will always be on both disks 
    int disk1 = 0;
    int disk2 = 1;
    int stripe;

    for (int i=0; i < Q; i++) {
        stripe = queries[i];
        printf("%d %d %d\n", disk1, stripe, disk2);
    }
}

//RAID-01
void raid01(int N, int Q, int queries[]) {

    int disk1, disk2, stripe;
    int half_disks = N/2;

    for (int i=0; i < Q; i++) {
        stripe = queries[i] / half_disks;

        //Calculate disks
        disk1 = queries[i] % half_disks;
        disk2 = disk1 + half_disks;
        printf("%d %d %d\n", disk1, stripe, disk2);
    }

}

//RAID-10
void raid10(int N, int Q, int queries[]) {

    int disk1, disk2, stripe;
    int half_disks = N/2;

    for (int i=0; i < Q; i++) {
        stripe = queries[i] / half_disks;

        //Disk calculations
        disk1 = (queries[i] % half_disks) * 2; 
        disk2 = disk1 + 1;
        printf("%d %d %d\n", disk1, stripe, disk2);
    }
}

//RAID-4
void raid4(int N, int Q, int queries[]) {

    int disk1, disk2, stripe;
    int parity = N - 1;

    for (int i=0; i < Q; i++) {
        //Calculate disk1, disk2 is parity
        disk1 = queries[i] % parity;
        disk2 = parity;

        //Stripe calculation using parity
        stripe = queries[i] / parity;
        printf("%d %d %d\n", disk1, stripe, disk2);  
    }
}

//RAID-5
void raid5(int N, int Q, int queries[]) {

    int disk1, disk2, stripe;
    int parity = N - 1;

    for (int i=0; i < Q; i++) {
        //Stripe calculation using parity
        stripe = queries[i] / parity;

        //Calculate disk1, disk2 is parity
        if (((queries[i] - N) % N) < 0) {
            disk1 = queries[i];
        } else {
            disk1 = (queries[i] - N) % N;
        }
        disk2 = ((parity - stripe)) % N;

        //If not zero or result is negative, then adjust with N
        if ((disk2 != 0) && (disk2 < 0)) {
            disk2 = abs(disk2 + N);
        }
        printf("%d %d %d\n", disk1, stripe, disk2);
    }
}