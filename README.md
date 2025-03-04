# magicSquareOfSquares
N threads search for a magic square of perfect squares. 

N threads search for a magic square of perfect squares.

TODO: The magic sum must always be equal to 3E where E is the number in the center of the square. The code needs to incorporate this logic.

TODO: Need to integrate with API to delgate targets (magic sums).

OPTIMIZE: -> Remove pause check in for loops (use OS level pausing instead). -> Use binary search for determining values.

PAUSED: -> I'm abandoning this effort for now because after further mathematically research it was determined that this is a non-starter. The numbers are too large even for a 64 bit integer. If a solution exists, they're probably few and far between.

xyz*(y+z)*(y-z) must be divisible by 2^4 * 3^2 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41 * 43 * 47 * 53 * 61 * 67 = 3196605376710617107476240

xyz*(y+z)*(y-z) must be divisible by 2^13 * 3^5 * 5^2 * 7^2 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41 * 43 * 47 * 53 * 61 * 67 = 1546645545467664981281303961600.