# Group 06 - MONKEyCAR
## Project Desription
### What you are going to make?

Our goal is to make a web-based application similar to Scratch that teaches children how to code. However, unlike Scratch, MONKEyCAR (the name of our application) will work with the real smart-car, which will perform the actions that the child “programmed” in our app, such as "Move 10 steps forward".  

### Why will you make it?

Ultimately, our hopes in making this program was to be able to teach, and inspire kids to code in a more fun and interactive way!

### What problem does it solve?

Technology is being integrated more and more into our day to day lives, with a larger number of people wanting to learn programming. However, for young children, programming might be a bit intimidating at first, and our goal is to create a user-friendly, supportive platform that will help guide them.

### How you are going to make it?

We had a lot of different options on how to implement this idea, such as:
- Code blocks that you can put together and can be executed at the same time
- Different game modes depending on difficulty
- Buttons that are written like code that you can just press
- Storing different profiles (maybe with completion points, command history, favourite programmes, ..)
- Providing some challenges (like specific actions to do with code, code with blank spaces, change code to do something different, etc)
- Leaderboards for the challenges to encourage more coding
- Using the emulator within the web page to test the code or to use the app even if the car is not available
- Adding some sounds so that the car could make cars depending on certain conditions
- Using the sensors by making sure no obstacles are hit
\
\
However, this is what we _finally_ envisioned MONKEyCAR to look like:  
\
![MonkeyCar Protototype](/gui/assets/MonkeyCar-prototype.png "MonkeyCar Protototype")



### What kind of technology are we going to use?
We will be primarily using **HTML, CSS and JavaScript** in order to develop our website, and then use **C++** for the translated car movements.


## Get started

### Setup
- Clone the repository on your device
- Download and open SMCE
- Compile the sketch smartcar.ino in the emulator and press start
- Open the file index.html in a browser

### Using the app
- The code blocks in the selection menu on the left all represent a different action that the car can perform
- They can be dragged into the canvas on the right, where they together form a code sequence that can be executed by the car
- When the play button on top of the page is pressed the code blocks within the canvas are translated into commands that are sent either to the physical car or the emulator
- The stop button 

### The code blocks
<img width="400" alt="Screenshot 2022-05-25 at 14 53 14" src="https://user-images.githubusercontent.com/78755376/170266551-859a31fb-d5ba-4dd4-9d31-5580133be83e.png" align="left">

**Move x seconds forward** takes as input the number of seconds the car is supposed to drive forward.

**Move x seconds backwards** takes as input the number of seconds the car is supposed to drive backwards.

**Turn x degrees left** takes as input a degree and turns the car to the left by that number.

**Turn x degrees right** takes as input a degree and turns the car to the right by that number.

**Turn around** does not take any input but makes the car turn 180° so that it can go into the other direction.

**Spin around** does not take any input but makes the car drive spin by 360°. This does not refer to turning on the spot but rather to making a full circle

**Wait x seconds** takes as input the number of seconds the car is supposed to stand still before performing the next action

**Repeat x times** is a special block that is resembling the programming concept of for loops, instead of just executing everything sequencially. The code block has a field where all the other code blocks may be dragged into. Those code blocks are then executed x times. It is not possible to drag this code block into another "repeat x times" block.



## Demo video


Please provide a link to your group's repository.
<https://github.com/DIT113-V22/group-06.git>
