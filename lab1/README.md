ONce upon a time, Ilia Benson gave his students a requirement to write readme files with his labs. 

So there old Allan was, thinking, how or what does one write a readme file. Nonetheless, there was no time to contemplate, old Allan set out to write his readmefile

I made 3 methods for lab1.c

The main, reportProcess, and printTime

the main handles the calls of the other two methods and forking

The printTime gets the current time and prints it. Depending on i, the function will initially print START or STOP.

The reportProcess method accepts the pid value that fork returned, and proceeds to do one of 3 things.
If pid is 0, it reports the necessary attributes of the child
If pid is -1, then that means things have gone haywire and the fork was unsuccessful, and prints such.
Otherwise it's the parent, so print out the requirements for the parent along with the use of function times() and print out the user, system, child user and child system times.
