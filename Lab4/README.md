1.  Create a program named stat that takes an integer array as command line argument. The program then creates 3 child processes each of which does exactly one task from the following.

a) Adds them and print the result on the screen. (done by child 1)
b) Shows the average on the screen. (done by child 2)
c) Prints the maximum number on the screen. (done by child 3)

2.  Invoke atleast 4 commands from your programs and each command should be Invoked by a child process
Command examples: cp, ls, mkdir, rmdir, etc (The calling program must not be destroyed)

3. Design a program using ordinary pipes in which one process sends a string message to a second process, and the second process reverses the case of each character in the message and sends it back to the first process. For example, if the first process sends the message Hi There, the second process will return hi tHERE. This will require using two pipes, one for sending the original message from the first to the second process, and the other for sending the modified message from the second back to the first process.

