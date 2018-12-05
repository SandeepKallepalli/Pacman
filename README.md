# Game Controls:

    Up Arrow - jump
    Left Arrow - Move Left
    Right Arrow - Move Right

    W - Pan up
    A - Pan left
    S - Pan down
    D - Pan Right

    Mouse Scroll - Zoom In/Out

## Game World
* There are Balls which are enemies moving from left to right at different speeds and sizes.
* Some enemies have an inclined plane attached to it . If the player fall on it then the sloped enemy is destroyed and player is projected along the normal of the plane.

## Pond
* There will be pond filled with water so that when the ball falls on the pond it goes inside
and can't jump unless it gets ground support.

* The Ball eventually drifts to the lowest point of the pond following circlular path .

## Levels
* The first level is basic player and enemies moving from left to right.
* After 1st level i.e in the 2nd level porcupine and the trampoline appears.
* If u step on the porcupine then the player dies i.e no.of lives decreases.There are 3 lives in total given in a game.
* In 3rd level the magnet appears for small amount of time and again appears for every level further.
Since the player is metal it will experience a accerlation towards magnet.

## Bonus-
* I have printed the Score, Level and Lives of the player on the screen using 7 segment Lines.
* I also implemented the zoom in/out using mouse scroll.
* I also implemented Panning the screen using 'wasd' keys.
* If the player goes to right of the screen then it comes from the left extreme of the screen and vice-versa.
* I move the porcupine towards player as if it senses where the player is.
i.e it always moves towards player to kill it.

# How to run the code :

## In Terminal:
    cd build
    cmake ..
    make
    ./pacman


## In QT Creator:
    Open the Project in QT Creator and then run Ctrl-r to run
