CSCI 103 Twenty One Programming Assignment 

Name: Joses Galdamez

Email Address: jgaldame@usc.edu

NOTE: You can delete the questions, we only need your responses.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

:piazza was very helpful with many issues i had with shuffling, 
and test cases. 

================================ Questions ==================================

1. Did you use the 'suit', 'type' and 'value' arrays? What functions are easier
to implement when using these arrays? How do you use them?

:I used them to make it easier to determine what a certain Id meant in terms
of value, suit, etc. Utilizing the "/" and modules with 13 helped me easily
find exactly what type of card something the player/dealer had, and made it
much easier to display it in as few functions as possible.

2. Did you add any additional functions to your implementation? If so briefly
describe how the functions improved your solution.

:I simply made functions that showed the beginning screen with the dealer 
and the player's original cards, to make it easier to display what was 
needed in scenarios that dealt with the player having 21 on the first try.
The code wouldve been just as effecient without them, but it made it 
easier for me to see how to implement the issue of "21" 

3. There are many ways to shuffle the deck of cards. The method used in our
implementation generates a permutaion of the cards to shuffle. For an array of
size N, how many swap (exchange) operations does this algorithm do? Does the
algorithm require any extra memory to generate a permutation?

:N/2, since by swapping N/2 variables, every single object (should) be in 
a different position by then. I believe no extra memory is necessary. 


================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:At least 4 days, not in a  row

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:many that dealt with the various tests and how i had to take into account
issues of ties, aces, etc.

Do you have any other remarks?

:it was alot more exciting than the first time i even looked at the project.
