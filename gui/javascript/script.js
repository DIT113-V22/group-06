let CANVAS=null;
let CONTEXT=null;
let BLOCKS=[];

function main() {
    CANVAS = document.getElementById("myCanvas")
    CONTEXT = CANVAS.getContext("2d")
}

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