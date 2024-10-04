# Airlines Management System

## Overview
The Airlines Management System is a console-based application developed in C that utilizes fundamental data structures to manage flight details, book tickets, and maintain passenger information. The system employs linked lists to handle flights and passengers, enabling efficient management of data.

## Features
- **Add Flights**: Users can add new flights with details such as flight number, departure and arrival times, locations, and capacity.
- **Book Flights**: Passengers can book available seats on flights by providing their name and contact details.
- **Display Flight Details**: Users can view flight details based on departure and destination locations.
- **View Passenger List**: Display a list of passengers booked on a specific flight.
- **Delete Flights**: Remove a flight from the system.
- **Memory Management**: The system ensures proper memory management, freeing up allocated resources to prevent memory leaks.

## Data Structures Used
- **Linked Lists**: 
  - `Passenger`: A linked list to store passenger details for each flight.
  - `flightDetails`: A linked list to store flight details, allowing for dynamic addition and removal of flights.

## Prerequisites
- C Compiler (e.g., GCC)
- Basic understanding of C programming and data structures

