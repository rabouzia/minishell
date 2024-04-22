# minishell

### Our goal 🎯 
---
The final challenge in the C language  
The students learned the importance of team projects and increased their understanding of shell programming and how the operating system works
### Commit Rules
---
- Force push and push to main branch are prohibited
- Create a sub-branch instead of the main branch
- Each commit have to be pushed with a brief comment of what you've written code
- Use labeling and questions for peer review

### Process
---
1. Input Handling
- Use the readline or read system call to accept user input.
- Analyze the input string to separate commands from arguments.

2. Command Parsing
- Tokenizes the input string and breaks it into individual commands and arguments.
- Handles pipes (|), redirects (<, >, >>), and other special characters.
- Handles quoting (", ') to preserve whitespace and special characters.

3. Environment Variable Handling
- Implement the env command to print the current environment variables.
- Implement the export command to set a new environment variable or modify an existing one.
- Implement the unset command to remove an environment variable.
- Handle the $ character to expand the value of an environment variable.

4. Implement Built-in Commands
- Implement the cd command to change the current working directory.
- Implement the echo command to print the arguments.
- Implements the pwd command to print the path to the current working directory.
- Implements the exit command to exit the shell.

5. External Command Execution
- Use the fork system call to create a newkprocess.
- In the child process, use the execve system call to execute an external command.
- The parent process waits for the child process and handles its exit status.

6. Signal Handling
- Handles the SIGINT signal (Ctrl+C) to interrupt the current instruction.
- Handles the SIGQUIT signal (Ctrl+) to generate a core dump.

7. Pipeline Handling
- Organize instruction sequences into pipelines for processing.
- Creates multiple processes and connects them with a pipe to pass the output to the input of the next process.

8. Redirection Handling
- Use the < operator to read input from a file.
- Write output to a file using the > operator (overwrite mode).
- Append output to the file using the >> operator (append mode).

9. Path Search
- Use the PATH environment variable to search for the path to an external command.
- The current directory is included in the search path.

10. Implement Additional Features
- Add extended features (e.g., history, autocomplete, aliases, etc.).
- Implement error handling and debugging features.


### Flow Diagram
![minishell_diagram](https://github.com/Action2theFuture/minishell/assets/74296888/63bc7daf-be36-4275-94a1-4ab6040f1c1f)
