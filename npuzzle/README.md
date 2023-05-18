### Compile
make

### Run
./npuzzle

#### If you want to modify the size of the puzzle, please modify the constant puzzle_size in npuzzle.cpp (e.g. puzzle_size=15)



Fig1.
Current state:		Goal State:
	[1 2 7]				[1 2 3]
	[6 5 4]				[4 5 6]
	[3 8 0]				[7 8 9]


Fig3.
Depth 0		Depth 2		Depth 4		Depth 8		Depth 12	Depth 16	Depth 20	Depth 24
[1 2 3]		[1 2 3]		[1 2 3]		[1 3 6]		[1 3 6]		[1 6 7]		[7 1 2]		[0 7 2]
[4 5 6]		[4 5 6]		[5 0 6]		[5 0 2]		[5 0 7]  	[5 0 3]		[4 8 5] 	[4 6 1]
[7 8 0] 	[0 7 8]		[4 7 8] 	[4 7 8] 	[4 8 2] 	[4 8 2] 	[6 3 0]	 	[3 5 8]