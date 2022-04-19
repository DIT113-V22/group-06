<<<<<<< Updated upstream
let CANVAS=null;
let CONTEXT=null;
let SELECTION_MENU=null;
let CONTAINER=null;
let BLOCKS=[];
let EXAMPLE_BLOCKS=[];
let SELECTED_BLOCK = null;

function main() {
    CANVAS = document.getElementById("myCanvas");
    SELECTION_MENU = document.getElementsByClassName("selection-menu height100");
    CONTEXT = CANVAS.getContext("2d");
    CONTAINER = document.getElementsByClassName("container");
}

//This function adds the event listeners of clicking, moving and releasing the mouse
function addEventListeners(){
    //I am not sure whether it works to only add it to the canvas
    CONTAINER.addEventListener("mousedown", onMouseDown);
    CONTAINER.addEventListener("mousemove", onMouseMove);
    CONTAINER.addEventListener("mouseup", onMouseUp);
}

//function that describes what should happem if the mouse is clicked
function onMouseDown(evt){
    //The example blocks are the ones in the selection menu and the existing blocks are the ones in the canvas.
    PRESSED_EXAMPLE_BLOCK = exampleBlockPressed(evt);
    PRESSED_EXISTING_BLOCK = blockPressed(evt);
    //We do a check whether we click on an already existing block or an example block.
    if(PRESSED_EXAMPLE_BLOCK){
        NEW_BLOCK = new BLOCK(PRESSED_EXAMPLE_BLOCK.typeOfMovement, PRESSED_EXAMPLE_BLOCK.angle, PRESSED_EXAMPLE_BLOCK.xPosition, 
        PRESSED_EXAMPLE_BLOCK.yPosition, PRESSED_EXAMPLE_BLOCK.width, PRESSED_EXAMPLE_BLOCK.height);
        SELECTED_BLOCK = NEW_BLOCK;
    } else if (PRESSED_EXISTING_BLOCK){
        SELECTED_BLOCK = PRESSED_EXISTING_BLOCK;
    }
}

//function that describes what should happem if the mouse is moved
function onMouseMove(evt){
    //To-Do update position of the block

}

//function that describes what should happem if the mouse is released
function onMouseUp(evt){
    //To-Do we need to release, and also snap the element to the right position. 
    //If it is connected to a start block it needs to be added to the array list
    //Make sure to check whether it is inside the canvas.

=======
function init() {
    var canvas = document.getElementById("myCanvas");
    var context = canvas.getContext("2d");
    
    context.lineWidth = 2;
>>>>>>> Stashed changes
}
var pos;
function allowDrop(ev) {
    ev.preventDefault();
}

<<<<<<< Updated upstream
function initiateExampleBlocks(){
    //TODO add the values for all blocks, initialise them and update the example block array
}

//The example blocks are the blocks in the menu that we cannot move
class EXAMPLE_BLOCK{
    constructor(typeOfMovement, angle, xPosition, yPosition, width, height){
        this.xPosition=xPosition;
        this.yPosition=yPosition;
        this.typeOfMovement=typeOfMovement;
        this.angle=angle;
        this.width=width;
        this.height=height
    }
    //here we need a draw function to draw the box
=======
function get_pos(ev){
    pos = [ev.pageX, ev.pageY];
}

function drag(ev) {
    ev.dataTransfer.setData("Text",ev.target.id);
>>>>>>> Stashed changes
}

function drop(ev) {
    ev.preventDefault();
    var offset = ev.dataTransfer.getData("text/plain").split(',');
    var data=ev.dataTransfer.getData("Text");
    
    var img = canvas = document.getElementById("move-forward");
    var dx = pos[0] - img.offsetLeft;
    var dy = pos[1] - img.offsetTop;
    document.getElementById("myCanvas").getContext("2d").drawImage(document.getElementById(data), ev.pageX - dx, ev.pageY - dy);
}