### PACMAN GAME
This is a 2D arcade game developed using OpenGL 3.0.

## How to run the game:-

# Using QTCreator
- Open QTCreator
- Press "Open Project" and navigate to project directory
- Select CMakeLists.txt
- If you are asked to configure kits, make sure desktop is checked and press continue
- Build -> Run (Only this needed after editing)

# Using CLI
```
cd path/to/project
mkdir build
cd build
cmake ..
Run from here after editing
make
./tut


## Controls of the game:-

# Keyboard controls:-

- Player left => key 'A'
- Player right => key 'D'
- Player jump => Spacebar key
- Panning => Arrow keys(Up,Down,Right,Left)

# Mouse controls:-

- Player left => Drag left
- Player right => Drag right
- Zoom in => Scroll Up
- Zoom out => Scroll Down

## Playing the game:-

- The objective of the game is to score as much as possible.
- The player of the game is the red coloured ball and the enemies are the balls of various other colors.
- Score increases as the player hits/destroys the enemy balls.
- Score, Level and Lives are displayed on the top of the screen.
- Game level will increase after every increase of 1000 points in the score.
- On levelling up, speed of enemy balls increases.
- Basic physics has been strictly implemented in the game.
- On landing on the trampoline, the ball is reflected back into the air with high speed.
- When the player is inside the water body(pond), movement speed is slowed down.The player ball follows the curve until the lowermost point is reached(provided the player isn’t explicitly moving it sideways). If the player is moving left or right, he should follow the path along the semi-circle.
- After landing on the moving porcupines, the porcupine disappears and the Player's lives decreases by 1.
- Game will end when the player ball loses all its lives.
- Magnet appears many times for some period of time during the game play and affects the horizontal motion of player.
- Some enemy balls have inclined planes of different sizes attached to them. After hitting these inclined planes, player bounces following laws of reflection.
```

