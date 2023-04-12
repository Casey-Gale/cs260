this program uses three integers to represent the number of marbles with that color-- 'r' for red marbles, 'g' with green marbles, 'b' for blue marbles.
at the beginning of the program, the user will be prompted to choose either hard-coded testing or manual testing. if the user chooses the hard-coded testing:
  the program will automatically run through several tests around important edge-cases and will print out the expected value and the value that the program 
  produces. as the final test showcases, the program does not handle marble counts higher than the 32-bit integer limit. a further test that is not implemented
  in this program might be to check whether or not marble counts summing to a number greater than the 32-bit integer limit break the program. however, it is 
  very likely that this does in fact produce unexpected results.
if the user chooses to do manual testing:
  the program will prompt the user to add a marble, draw a marble, or count all marbles and will loop this choice until the user wishes to end the program. 
  if the user chooses to add a marble:
    the program will ask for a color of marble to add. if the user does not type 'r', 'g', or 'b', the program will not add a marble at all. otherwise,
    it will add the respective color to the bag (increment the color integer).
  if the user chooses to draw a marble:
    the program will choose a random marble from the bag to remove and print out which one it draws. it does not operate on a 1/3 chance for each color,
    but on a weighted probability based on the number of each color (hopefully the chances are correct).
  if the user chooses to count marbles:
    the program will sum up all marbles and print out the total number.
  it should be difficult to break the program via unexpected user inputs, but who knows.

  line numbers:
  (field 3.1) implementation of adding marbles is in lines 40-62
  (field 3.2) implementation of drawing marbles is in lines 66-84
  (field 3.3) implementation of counting marbles is in lines 88-90
  (field 4) testing begins at line 135