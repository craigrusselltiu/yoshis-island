# Documentation

A basic recreation of the side-scrolling system in Yoshi's Island written in C++ with Qt Creator.

## Game Extension (v1.0)
- I have extended the game to be a fully-playable game instead of being just a framework.
- It is now a non-stop side scroller where enemis must be avoided through a simple jump key.
- Added score to keep track of how many enemies have been avoided.
- Added jump functionality to the character.
- Added enemies that will result in a game over when touched.
- Added numerous extra animations to the character and enemies.

## Controls
- **Enter** - Start game
- **Spacebar** - Jump
- **P** - Pause

# Config Instructions

- The whole config file is read into a map, which can be read from easily if more config options need to be added.
- Adding a new config is formatted as, "key=value".
- For custom walking animations, insert paths in config file as, "sprite1", "sprite2", etc.
- Custom animations for custom actions can also be created.
	- Use format, "key1", "key2", etc. in config file, then use the "createAnimation" method in the image factory.

# Style Guide

My specified style is the Google C++ style with the following variations:

- Indentation is 4 spaces.
- Local header includes come before system header includes.
- Camel case is used for function and variable naming.
	- If two consecutive single letters are in the variable, then an underscore is used. (e.g. m_xCoordinate)
- Curly brackets start on the same line, not the one after.
- Comments are only done in double slash.
- There must be an empty line before a comment.
- Code is partitioned into sensible and related chunks.
- Wherever possible, same-type variables are initialised in one line.

# Components

## Image Class (Abstract)
- This class is created to better handle and use the "drawPixmap" function.
- Holds path for the image, coordinates for the lower-left corner of the image, and its size.
- These can all be set to simulate movement.
- Has a pure virtual function "animate".
	
## Character Class
Parameters: image path, coordinate, width, height, list of sprites

- Is an Image.
- Holds a string list of sprite paths, in addition to what is inherited.
- "animate" here is used to loop through the list of images to animate the character.

## Background Class
Parameters: image path, coordinate, width, height, background speed

- Is an Image.
- "animate" in this class is used to move the entire image to the left, looping back if required to simulate movement.

## ImageFactory Class
Parameters: config file

- Factory that handles selection and creation of Image types.
- It uses the config file to decide what input to use in creating objects.
- Function "newImage" takes an argument QString "type" and int "select".
- "type" is used to determine what kind of Image to return.
- "select" is used to pick a premade Image depending on the int.
- Passing select as 0 will return a generic Image of that "type".
- Easily extendable.

## Coordinate Class
Parameters: x coordinate, y coordinate, frame height

- Coordinate class used in a previous tutorial.
- Simply used to make the x and y values more intuitive.

## Config Class
Parameters: file path

- This class handles all of the reading from the config file.
- Creates a map of the config file when constructed.
- Reads the values of the config file into variables to be easily readable.
- "getSize" functions returns an int from the config file for character size.
- Easily extendable.

# Design Patterns

Factory Method
- The program will mostly be image based.
- Since a lot of different types of Image objects will be created:
	- It makes sense to have a factory that handles the different types of images.
	- Implementing the factory method greatly reduces code repetition.
	- Allows for easily extendable code.

# Stretch Goals Reached

Animated Character
- The character is animated by looping back and forth between a list of images.

Start And Pause Menu
- Start menu waits until game is started by pressing Enter.
- Pressing P will pause the game any time after starting.

Background Music And Sound Effects
- Background music when playing the game.
- Sound effects for pressing buttons, i.e. Enter and P.


Parallax Effect
- Foreground and background create an illusion of depth.
- Background moves slower than the foreground, which moves normally.

Extra Config Text File Options
- Custom resolution
- Custom background speed
- Custom character
- Custom background
- Custom foreground
- Custom sprite animations
- Toggleable parallax effect
- Toggleable animated character
