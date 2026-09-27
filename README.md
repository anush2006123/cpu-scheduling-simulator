# CPU Scheduling Simulator

This project is a C++ based CPU Scheduling Simulator developed to demonstrate the working of different CPU scheduling algorithms.

## Algorithms Implemented

1. First Come First Serve (FCFS)
2. Shortest Job First (SJF) - Non-Preemptive
3. Priority Scheduling - Non-Preemptive
4. Round Robin

## Features

- Takes process Arrival Time, Burst Time and Priority as input.
- Allows the user to select a scheduling algorithm.
- Supports user-defined Time Quantum for Round Robin.
- Calculates Completion Time (CT).
- Calculates Turnaround Time (TAT).
- Calculates Waiting Time (WT).
- Displays Average Turnaround Time and Average Waiting Time.

## Technologies Used

- C++
- C++17
- Standard Template Library (STL)
- g++

## How to Run

Compile the program:

g++ cpu_scheduler_anush.cpp -o cpu_scheduler

Run the program:

./cpu_scheduler

For Windows:

cpu_scheduler.exe

## Project Structure

cpu-scheduling-simulator/
|
|-- cpu_scheduler_anush.cpp
|-- README.md

## Project Objective

The main objective of this project is to understand and implement CPU scheduling algorithms using C++. The project also demonstrates the use of vectors, queues, sorting and basic algorithmic concepts.

## Author

Anush Choudhary
B.Tech CSE
Lovely Professional University
