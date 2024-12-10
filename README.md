# TPsynthese

ENSEA Tiny Shell (enseash)
Project Overview
ENSEA Tiny Shell (enseash) is a simple shell application developed as part of the Synthesis Practical Work for 2nd-year Computer Science students. The goal is to create a lightweight shell that executes commands, displays return codes, measures execution times, and manages more advanced features like I/O redirection, piping, and background processes.

Features
- Welcome Message and Basic Prompt
  - Displays a welcome message at startup.
  - A basic prompt (enseash %) waits for user input.

- Command Execution
  - Executes simple user-entered commands.
  - Returns to the prompt after command execution.
  
- Exit Management
  - Handles the exit command or <Ctrl>+D to terminate the shell gracefully.

- Return Code Display
  - Displays the return code (exit:0) or signal (sign:9) of the previously executed command in the prompt.

- Execution Time Measurement
  - Measures and displays the time taken to execute a command in milliseconds using clock_gettime.

HOW TO USE THE CODE

- download code or clone th repo
- in a terminal go where the code folder is and :
- make 
- ./enseash 


