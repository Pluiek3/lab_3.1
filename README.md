# Lab_3

Subject: Developing a simple UI web application in C using the Mongoose library.

Objective of the work: Learn the principles of creating simple web interfaces using the C programming language and the Mongoose library; master the processing of HTTP requests, data transfer via HTML forms and the implementation of basic user interaction logic; gain basic HTML/CSS skills as part of a UI application, and ensure the launch and maintenance of a web application in the Linux OS environment.

The purpose of the work determines the formulation and solution of the following tasks:

1. Introduction to the basics of developing UI applications in C using the Mongoose library.
2. Studying the principles of processing HTTP requests (GET and POST) and organizing routing within an application.
3. Implementing a user authorization form with receiving and analyzing data transmitted from an HTML form.
4. Connecting and using static resources (HTML, CSS) as part of a C program.
5. Setting up automated project build using Makefile.
6. Working with environment variables for storing confidential data (username and password).
7. Analyzing application behavior with different types of user input and processing conditions (successful authorization, incorrect input, missing environment variables).
8. Implementation of the basic logic of the web application with the return of the corresponding pages and HTTP response codes.
9. Testing the functionality of the application in the Linux OS environment using a browser and command line utilities (for example, curl or wget).
10. Completing an individual assignment. The assignment number is determined by the student's number in the journal. If the number exceeds the maximum number of assignments, the variant is calculated using the formula: journal number % maximum assignment number (where % is the remainder of the division). 
11. Prepare documentation for the project and upload the project to a remote git repository.

## Compiling

Command to compile and run:

```
make

```
Go to the bin directory and start the server with the command:

```
./sleep_server

```

## Documentation 

Command to generate Doxygen documentation:

```
doxygen Doxyfile
```
The project used a custom style developed by jothepro. The style is in the directory (./Docs/doxygen-awasome-cdd-main).

The documentation itself is located in (./Docs/doxygen), this documentation contains a description of all the main elements of the project.

## Additional modules

| Command | Description |
| --- | --- |
| `Just do it` |To begin the Lab_3 work|
| `sudo apt install doxygen` | Generate Doxygen documentation |
| `sudo apt install libcunit1 libcunit1-dev` | CUnit tests |
|`sudo apt-get install clang-format`| Code format |


