let CANVAS=null;
let CONTEXT=null;
let BLOCKS=[];

function main() {
    CANVAS = document.getElementById("myCanvas")
    CONTEXT = CANVAS.getContext("2d")
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
}

//The blocks are the ones which are created when a mouse click is detected on the example blocks and
//which can be dragged into the canvas.
class BLOCK{
    constructor(typeOfMovement, angle, xPosition, yPosition, width, height){
        this.xPosition=xPosition;
        this.yPosition=yPosition;
        this.typeOfMovement=typeOfMovement;
        this.angle=angle;
        this.width=width;
        this.height=height
    }
}