this program uses three integers to represent the number of marbles with that color- 'r' for red marbles, 'g' with green marbles, 'b' for blue marbles.
the program will prompt the user to add a marble, draw a marble, or count all marbles and will loop this choice until the user wishes to end the program. 
if the user chooses to add a marble:
  the program will ask for a color of marble to add. if the user does not type 'r', 'g', or 'b', the program will not add a marble at all. otherwise,
  it will add the respective color to the bag (increment the color integer).
if the user chooses to draw a marble:
  the program will choose a random marble from the bag to remove and print out which one it draws. it does not operate on a 1/3 chance for each color,
  but on a weighted probability based on the number of each color.
  (hopefully the chances are correct)
if the user chooses to count marbles:
  the program will sum up all marbles and print out the total number.
it should be difficult to break the program via unexpected user inputs, but who knows.
