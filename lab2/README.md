# lab 2

Launch is pretty straight forward.
Launch the program specified in the command line via forking and exec and report some stuff, so I made a method that handles the forking, and another that handles preparing argv for the program that will be launched in the child. This will hopefully give me some leverage that'll help make tube.c easier to make.

For tube.c I copy and pasted the code from launch and modified it. I added a start param to the method that prepares the argv for that dictates what section of argv to copy to the new argv var. In addition, forking is now handled by a for loop that terminates if the returned pid_t is less than or equal to zero, avoiding unecessary forking in children while ensuring two total children are created in the parent.

Piping was confusing but it appears to be doing what was on the rubric so I assume I did it right?
What I attempted was, as stated, closed both ends of the pipe in the parent, then proceeded to: In the first child; close the read end of the pipe, dup stdout and the write end of the pipe, and finally close the write end of the pipe and in the second child; close the write end of the pipe, dup stdin and the read end of the pipe, and finally close the read end of the pipe.
