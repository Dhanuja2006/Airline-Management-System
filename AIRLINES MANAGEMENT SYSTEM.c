#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Passenger {
    char name[50];
    char contact[50];
    struct Passenger *next;
};

struct flightDetails {
    char flno[20];
    char ar_time[30];
    char des_time[30];
    char dep[50];
    char des[50];
    int capacity;
    int av_seats;
    struct Passenger *pas_list;
    struct flightDetails *next;
};

struct flightDetails* addFlight(struct flightDetails *head, char n[], char at[], char dt[], char departure[], char destination[], int cap) {
    struct flightDetails *newnode = (struct flightDetails*)malloc(sizeof(struct flightDetails));
    strcpy(newnode->flno, n);
    strcpy(newnode->ar_time, at);
    strcpy(newnode->des_time, dt);
    strcpy(newnode->dep, departure);
    strcpy(newnode->des, destination);
    newnode->capacity = cap;
    newnode->av_seats = cap;
    newnode->pas_list = NULL; // Initialize the passenger list to NULL
    newnode->next = head; // Insert at the beginning
    printf("Added Flight %s\n", n);
    return newnode; // Return the new head
}

struct Passenger* addPassenger(char n[], char c[]) {
    struct Passenger *passenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    strcpy(passenger->name, n);
    strcpy(passenger->contact, c);
    passenger->next = NULL;
    return passenger;
}

void book_flight(struct flightDetails *flight, struct Passenger *passenger) {
    if (flight->av_seats > 0) {
        flight->av_seats--;
        if (flight->pas_list == NULL) {
            flight->pas_list = passenger;
        } else {
            passenger->next = flight->pas_list;
            flight->pas_list = passenger;
        }
        int seatNo = flight->capacity - flight->av_seats; // Calculate seat number
        printf("FLIGHT BOOKED! YOUR SEAT NO IS %d\n", seatNo);
    } else {
        printf("Seats Not Available! Cannot book.\n");
        free(passenger); // Free memory if booking fails
    }
}

void displayPassengers(struct flightDetails *flight) {
    struct Passenger *ptr = flight->pas_list;
    if (ptr == NULL) {
        printf("No passengers booked for this flight.\n");
        return; // Return if the passenger list is empty
    }

    int i = 1;
    while (ptr != NULL) {
        printf("Passenger %d\n", i);
        printf("Name: %s\n", ptr->name);
        printf("Contact Details: %s\n", ptr->contact);
        ptr = ptr->next;
        i++;
    }
}

void findFlight(struct flightDetails *flight, char departure[], char destination[]) {
    struct flightDetails *ptr = flight;
    int found = 0; // Flag to check if any flight is found
    while (ptr != NULL) {
        if (strcmp(ptr->dep, departure) == 0 && strcmp(ptr->des, destination) == 0) {
            printf("Flight details:\n");
            printf("Flight number: %s\n", ptr->flno);
            printf("Flight departure time: %s\n", ptr->ar_time);
            printf("Flight arrival time: %s\n", ptr->des_time);
            printf("Capacity: %d\n", ptr->capacity);
            printf("Available seats: %d\n", ptr->av_seats);
            found = 1; // Set found flag
        }
        ptr = ptr->next;
    }
    if (!found) {
        printf("No flights available from %s to %s.\n", departure, destination);
    }
}

struct flightDetails *isFlight(struct flightDetails *l, char n[]) {
    struct flightDetails *ptr = l;
    while (ptr != NULL) {
        if (strcmp(ptr->flno, n) == 0) {
            return ptr; // Return found flight
        }
        ptr = ptr->next;
    }
    return NULL; // Return NULL if not found
}

struct flightDetails* deleteFlight(struct flightDetails *head, char flightNumber[]) {
    struct flightDetails *temp = head, *prev = NULL;

    // Check if the flight to be deleted is the head node
    if (temp != NULL && strcmp(temp->flno, flightNumber) == 0) {
        head = temp->next; // Change head
        free(temp);        // Free old head
        printf("Flight %s deleted successfully.\n", flightNumber);
        return head;
    }

    // Search for the flight to be deleted
    while (temp != NULL && strcmp(temp->flno, flightNumber) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If flight not found
    if (temp == NULL) {
        printf("Flight not found!\n");
        return head;
    }

    // Unlink the node from the list
    prev->next = temp->next;
    free(temp); // Free memory
    printf("Flight %s deleted successfully.\n", flightNumber);

    return head;
}

int main() {
    printf("AIRLINES MANAGEMENT SYSTEM\n");
    struct flightDetails *list = NULL; // Initialize to NULL
    char c = 'Y';
    printf("1) Add Flight\n2) Book Flight Ticket\n3) Display Flight Details\n4) Display Passenger List\n5) Delete Flight\n6) Exit\n");
    while (c == 'Y') {
        printf("\nEnter your choice:\n");
        int n;
        scanf(" %d", &n);
        switch (n) {
            case 1: {
                char flno[30], dt[50], at[50], dl[50], al[50];
                int cap;
                printf("Enter Flight number: ");
                scanf("%29s", flno); // Limiting input size to prevent overflow
                printf("Enter Flight departure time: ");
                scanf("%49s", dt);
                printf("Enter Flight arrival time: ");
                scanf("%49s", at);
                printf("Enter Flight departure location: ");
                scanf("%49s", dl);
                printf("Enter Flight arrival location: ");
                scanf("%49s", al);
                printf("Enter Flight capacity: ");
                scanf("%d", &cap);
                list = addFlight(list, flno, dt, at, dl, al, cap);
                break;
            }
            case 2: {
                char no[30];
                printf("Enter Flight Number: ");
                scanf("%29s", no);

                struct flightDetails *fd = isFlight(list, no);
                if (fd != NULL) {
                    struct Passenger *pas;
                    char name[50], con[50];

                    printf("Enter name: ");
                    scanf("%49s", name);
                    printf("Enter contact details: ");
                    scanf("%49s", con);
                    pas = addPassenger(name, con);

                    book_flight(fd, pas);
                } else {
                    printf("Flight Not Available\n");
                }
                break;
            }
            case 3: {
                char dep[50];
                char des[50];
                printf("Enter departure location: ");
                scanf("%49s", dep);
                printf("Enter destination location: ");
                scanf("%49s", des);
                findFlight(list, dep, des);
                break;
            }
            case 4: {
                char no[30];
                printf("Enter Flight Number: ");
                scanf("%29s", no);

                struct flightDetails *fd = isFlight(list, no);
                if (fd != NULL) {
                    displayPassengers(fd);
                } else {
                    printf("Flight Not Found\n");
                }
                break;
            }
            case 5: // Deletion of flight
            {
                char flno[30];
                printf("Enter Flight Number to delete: ");
                scanf("%29s", flno);
                list = deleteFlight(list, flno);
                break;
            }
            case 6: {
                printf("\nTHANK YOU\n");
                c = 'N';
                break;
            }
            default: {
                printf("Invalid choice\n");
                break;
            }
        }
    }

    // Free the allocated memory for flights and passengers at the end
    struct flightDetails *current = list;
    while (current != NULL) {
        struct flightDetails *temp = current;
        current = current->next;

        struct Passenger *passenger = temp->pas_list;
        while (passenger != NULL) {
            struct Passenger *passengerTemp = passenger;
            passenger = passenger->next;
            free(passengerTemp); // Free each passenger
        }
        free(temp); // Free flight details
    }

    return 0;
}
