CSCI 103 Zombies Programming Assignment 

Name: Joses Galdamez

Email Address: jgaldame@usc.edu

NOTE: You can delete the questions, we only need your responses.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

:

================================ Questions ==================================

1. Which kind of a loop did you use to iterate through the nights of a
   single simulation?  Why?
   
:while loop, since a for loop must have a constant increment for k, or the 
 number of zombies. However, due to the randomness of choosing victims, k 
 value will always increase by a different amount, which will make a while 
 loop easier to use, since you can have k change to anything and it will stop
 when it hits a certain limit. 

2. Which kind of a loop did you use to perform the M simulations? Why?

   
:for loop, since I knew that M increments will always be constant at 1, no 
 while loop was really necessary, even if both will be fine.


3. How did you ensure that if a human was turned into a zombie on a
   particular night that he/she didn't bite anyone until the following
   night?

:Instead of focusing on individual zombies and their place in the pop array
 in order to determine if they have been bit that night, it was easier to 
 simply run a for loop that turned any individual into a zombie from 
 0-number of zombies on that CERTAIN NIGHT. This ensured that only k amount 
 were biting that night, since it didnt matter if a zombie would 
 randomly bite itself. 


4. Experiment briefly running your program with fewer simulations 
   (smaller M value). One thing computer scientists do often is evaluate 
   trade-offs. Running with a smaller M results in some interesting 
   trade-offs: your program output three values, Average Nights, Max Nights 
   and Min Nights. How will these values be impacted by running fewer 
   simulations? On the other hand, what other property of your program is 
   affected by using a smaller M?

:fewer simulations will simulate less possible values for the program to 
 possibly receive, so it may cause a much more skewed values for all three 
 data points we focused on. running less simulations will also save your 
 program memory and time, since it will take much less time and energy to 
 run every simulation with a smaller M

5. (Optional Challenge -- Ungraded)
    You do not need to submit an answer if you prefer not to.) 
   Given a population of N and k initial zombies, can you find an expression
   for the theoretical minimum number of nights it would take for everyone
   to become a zombie?

: minnights = (N-k)/avgnights
not really sure how youd find one for MIN nights



================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:7 days

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:resetting variables continuosly is why it took me a good week to finish


Do you have any other remarks?

:Office hours did help me alot, but of course many who had trouble with this 
 project didnt' understand the concepts that were taught in class, not simply 
 because it's too "difficult to understand". 
