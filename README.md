# Group 06 - MONKEyCAR <img width="186" alt="Screenshot_2022-04-01_at_11 53 16-removebg-preview" src="https://user-images.githubusercontent.com/78755376/170331539-acdcd870-eb76-4726-8fca-ca9629b43191.png" align="right">
<br />
<br />

## Project Desription
### What you are going to make?

Our goal was to create a web-based application similar to [Scratch](https://scratch.mit.edu) that teaches children how to code. However, unlike Scratch, MONKEyCAR (the name of our application) will work with the real smart-car, which will perform the actions that the child “programmed” in our app, such as "Move 10 steps forward".

<img width="515" alt="Screenshot 2022-05-25 at 19 36 09" src="https://user-images.githubusercontent.com/78755376/170335429-d73501ee-811c-49df-b4c6-d1490704640a.png" align="left">
<img width="415" alt="Screenshot 2022-05-25 at 19 39 39 copy" src="https://user-images.githubusercontent.com/78755376/170335858-2728d6b4-0395-4e51-bcf2-ef1171468f89.png">

<br />

### Why will you make it and what problem does it solve?

Ultimately, our hopes in making this program was to be able to **teach and inspire kids to code in a more fun and interactive way!** Technology is being integrated more and more into our day to day lives, with a larger number of people wanting to learn programming. However, for young children, programming might be a bit intimidating at first, and our goal is to create a user-friendly, supportive platform that will help guide them and realise that programming can be a lot of fun.

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


### What kind of technology will we use?
We will be primarily using **HTML, CSS and JavaScript** in order to develop our website, and then use **C++** for the translated car movements.

<br />

## Get started

### Setup the emulator

- Clone the repository on your device
- Download and open SMCE [here](https://github.com/ItJustWorksTM/smce-gd/releases/tag/v1.3.4)

| <img width="260" alt="Screenshot 2022-05-25 at 19 37 42" src="https://user-images.githubusercontent.com/78755376/170339214-770db480-9e86-4880-ad81-0cfa12e07118.png" align="left"> | <img width="495" alt="Screenshot 2022-05-25 at 19 37 51" src="https://user-images.githubusercontent.com/78755376/170339279-a64f3e8d-f6fb-466f-bd8c-95d429c9efc3.png">| <img width="230" alt="Screenshot 2022-05-25 at 19 38 41" src="https://user-images.githubusercontent.com/78755376/170339286-890b2202-1036-4c31-802f-4c4ad0a3fc91.png"> <img width="230" alt="Screenshot 2022-05-25 at 19 38 48" src="https://user-images.githubusercontent.com/78755376/170339289-ba46789e-d4e2-47a9-9aa4-7210d2a6b93d.png">|
|:--:| :--:| :--:| 
| *Press + to add a new arduino sketch* | *Add a new sketch* | *Select the file "smartcar.ino" from the folder "arduino"* |
| <img width="440" alt="Screenshot 2022-05-25 at 19 38 58" src="https://user-images.githubusercontent.com/78755376/170339292-300a690d-d225-4fc8-aad0-a44e2c92c4e3.png"> | <img width="440" alt="Screenshot 2022-05-25 at 19 39 06" src="https://user-images.githubusercontent.com/78755376/170339299-f9e22501-1abb-461d-8be4-b628d5ed9ba4.png">| <img width="440" alt="Screenshot 2022-05-25 at 19 39 32" src="https://user-images.githubusercontent.com/78755376/170339307-4410e53c-9e40-493f-9870-15ec00a193f5.png">|
| *Select the added sketch* | *Compile the sketch* | *Press start to run the sketch* |



<img width="578" alt="Screenshot 2022-05-25 at 19 39 39" src="https://user-images.githubusercontent.com/78755376/170339310-7d1dd91b-cd45-4f71-b531-424295432a2f.png">
This is how your screen look now.

### Using the app
<img width="550" alt="Screenshot 2022-05-27 at 10 03 00" src="https://user-images.githubusercontent.com/78755376/170657836-ae65c6f1-b22b-4a4f-bade-9a783847e593.png" align="right">

- Open the file "index.html" located in the folder "gui" in a browser of your choice
- The code blocks in the selection menu on the left all represent a different action that the car can perform
- They can be dragged into the canvas on the right, where they together form a code sequence that can be executed by the car
- When the play button on top of the page is pressed the code blocks within the canvas are translated into commands that are sent either to the physical car or the emulator
- The clear button clears out all the blocks in the canvas. Before that is done it asks the user for permission.

### The code blocks
<img width="370" alt="Screenshot 2022-05-25 at 14 53 14" src="https://user-images.githubusercontent.com/78755376/170266551-859a31fb-d5ba-4dd4-9d31-5580133be83e.png" align="left">

**Move x seconds forward** takes as input the number of seconds the car is supposed to drive forward.

**Move x seconds backwards** takes as input the number of seconds the car is supposed to drive backwards.

**Turn x degrees left** takes as input a degree and turns the car to the left by that number.

**Turn x degrees right** takes as input a degree and turns the car to the right by that number.

**Turn around** does not take any input but makes the car turn 180° so that it can go into the other direction.

**Spin around** does not take any input but makes the car drive spin by 360°. This does not refer to turning on the spot but rather to making a full circle

**Wait x seconds** takes as input the number of seconds the car is supposed to stand still before performing the next action

**Repeat x times** is a special block that is resembling the programming concept of for loops, instead of just executing everything sequencially. The code block has a field where all the other code blocks may be dragged into. Those code blocks are then executed x times. It is not possible to drag this code block into another "repeat x times" block.

<br />

## Demo video

Here is a link to our demo video:

<br />

## Structure

If you want to learn a little more about how the system works, how our code is structured and how the different components work and communicate with each other this is the section for you. :point_down:


### Components

The main components of our system are the GUI (and the logic for that), the MQTT broker and the arduino board running on the physical car or in the emulator. This diagram shows the basic components and how they interact with each other.

![Untitled Diagram-2](https://user-images.githubusercontent.com/78755376/170674607-39d607f2-020f-4fd4-9105-dd95bd39ab86.png)


if you want to go into a little more detail we recommend looking at the following diagram. It further describes how our compontents interact with each other. As you can see we also added sub-components, like the sensors for the car or the relevant GUI components. Don't get confused why we have two car components. This is just supposed to showcase, that we can either work with the physical car or with the car in the emulator.

![Untitled Diagram](https://user-images.githubusercontent.com/78755376/170675070-4954cdb9-7f5c-4001-a46f-bf7f591274ad.png)


### Folder structure

The components described above can also be recognized in our folder structure. The main two folders are "gui" and "arduino" which represent the components MONKEyCar Website and SmartCar. 



Please provide a link to your group's repository.
<https://github.com/DIT113-V22/group-06.git>
