# CheckersAI
Our checkers program was broken up into two separate programs. The first is the client version and the second is the training version. The purpose of this was to make training the neural network easier and not waste resources including the networking stuff. However both versions did share some similarities, including the board representation, move generation and neural network layout. The big differences is that the client version does not have any of the tournament code, while the training version does not have any of the networking code. Each section, client, neural network/alphabeta search, board representation, move generation, training and validation and verification will be discussed in detail separately.

### Client
The client code was written in python to simplify the networking. However in order for the client to use the neural network, and move generation which was written in C++, the C++ code will have to be modified to make a python library. This was done using the Boost Standard Libraries for both Python and C++ to generate a dynamic library to be called from the python client code. The client code does some additional checking to make sure the checkers game board is correct before it is passed to the server and before it is sent to the checkers library. In addition the client program will create a GUI that will display the moves made by each of the players.

### Neural Network/AlphaBeta Search
For the neural network, we choose to use Blondie’s neural net structure of 32-40-10-1. We choose this structure because it seemed arbitrary, and the evidence seemed to point to this being a good structure. If we had more time, we would have tried other set ups. Personally we would have liked to do this, but time constraints kept this from happening. As for the alphabeta search, we implemented the basic algorithm.

### Board Representation
The board representation standard was created in class. This standard will be used to pass the board to the server. The standard is as follows:
- Message Format
  - The first byte will be a status byte (described in that section)
  - The remaining 64 bytes will stand for each square on the board. The first byte will correspond to 0x0 on the board. The second byte will correspond to 0x1 on the board etc.
- Each space on the board will be represented with the following format.
  - The least significant bit determines if a piece is present. 0 represents no and 1 represents yes.
  - The next least significant bit determines the color of the piece. 0 is red and 1 is black
  - The next least significant bit determines the kingness of the piece. 0 for non king and 1 for king
  - The next least significant bit determines the color of the square. 0 for black and 1 for red.
- The status byte will be in the following format.
  - The least significant bit will determine whether or not there is a status change. 0 is fine and 1 is an error
  - The remaining 7 bits determine the status by value.
  - The value 1 means game is over.
  - The value 2 means illegal move
  - The value 3 means corrupted board.

For our board representation we defined a board as a 10x10 2D character array. Where the 2D array looks like this:
```
[x] [x] [x] [x] [x] [x] [x] [x] [x] [x]
[x] [ ] [b] [ ] [b] [ ] [b] [ ] [b] [x]
[x] [b] [ ] [b] [ ] [b] [ ] [b] [ ] [x]
[x] [ ] [b] [ ] [b] [ ] [b] [ ] [b] [x]
[x] [_] [ ] [_] [ ] [_] [ ] [_] [ ] [x]
[x] [ ] [_] [ ] [_] [ ] [_] [ ] [_] [x]
[x] [r] [ ] [r] [ ] [r] [ ] [r] [ ] [x]
[x] [ ] [r] [ ] [r] [ ] [r] [ ] [r] [x]
[x] [r] [ ] [r] [ ] [r] [ ] [r] [ ] [x]
[x] [x] [x] [x] [x] [x] [x] [x] [x] [x]
```
- `[x]` = boarder to simplify edged of the game board
- `[ ]` = invalid piece placements, no piece should ever be in these spots
- `[_]` = valid piece placements, pieces could be moved to these spots
- `[r]` = normal red piece
- `[R]` = king red piece
- `[b]` = normal black piece
- `[B]` = king black piece

### Move Generation
Move generation is done by generating moves depending on which player the computer is, meaning the black player move generation is different and separated from the red player move generation. The start of the move generation begins by creating a vector to store new boards. Where once a possible move has been found a new board with the move applied is created and placed into the vector.

The move is generated by walking through the 2D board, and finding the corresponding piece, black or red. It determines whether or not if the piece is a king or a normal piece and judges based on the piece where it can move. Once all of the possible moves have been found it determines if a piece can jump. When looking for jumps, if a piece can jump it must, therefor the program short circuits in a manner of speaking, where if a jump is found delete the other moves from the list. For determining multijumps, it recursively calls the jump function, and if multijumps are found the same short circuit idea comes into play where the biggest multijump is always taken.

After all of the jumps have been found, piece promotion starts, where it looks at the piece’s opposite end and promotes any piece to king that is in the end zone. In addition the piece count is updated to make judging who one simpler where if the piece count is equal to zero that player loses, which also sets the corresponding status bit. From here the vector of boards is passed to the alphabeta
search function to determine the best available move.

### Training
For training we used a round robin tournament structure. We choose the round robin structure since it provides the, in our opinion, best assessment of a neural nets skill. We also tried several different generation sizes, from 16 to 128, and found that, due to the quadratic nature of round robin, that 32 was optimal. At this size, we found that the generations happened fast enough, but kept the diversity high enough to prevent too much inbreeding.

For mutations, we choose to diverge from blondie. Specifically, the we only kept the top quarter of the nets, and mutated those twice. The final quarter were reseeded randomly, to keep diversity high. Using this method we manage to produce generations at the rate of about 1 every 5 minutes.

### Validation and Verification
This involved two functions, the first is cycle detection and the second is board validation. In cycle detection, a character array was made where each element would hold a game board with a move. A cycle is defined as a piece that moves from one spot to another and back again, where no forward progress is made. By comparing past moves with each other a cycle can be found if the game boards are the same. Once a cycle has been detected the corresponding status bit is set and sent to the server.

The board validation will check for two things, the opponents move was valid and that the board was not corrupted. This is done by passing the current players board and the opponent's board to the check board function. The current players board is used to generate all of the possible moves the opponent can make using the same move generation functions, and checking to see if the opponent's board is equal to any of the boards that was generated. If a board was found then everything is fine and execution can continue, if a board was not found then the correct status bit is set and sent to the server.
