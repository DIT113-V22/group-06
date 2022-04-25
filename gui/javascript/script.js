const canvas = document.getElementById("canvas-container")


//with this function we allow elements to be dropped in a certain place.
function allowDrop(ev) {
    ev.preventDefault();
}

//this function allows us to drag elements from one place to another
function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

//with this method we remove a node (one block)
function removeNode(node) {
    node.parentNode.removeChild(node);
}
  
//This function is to drop an element in the canvas
function drop(ev) {
    ev.preventDefault();
    //we get the data we set in the drag() method
    var data = ev.dataTransfer.getData("text");
    //we check whether the selected block is inside the selection menu or in the canvas and make a copy of it
    var isLeft = 'move-forward' == data || "move-backwards" == data || "move-left" == data || "move-right" == data;
    var nodeCopy = document.getElementById(data).cloneNode(true);

    //we check whether we try to drop it on the canvas (otherwise we can also drop inside the other blocks)
    if(ev.target.id == "canvas"){
        if (isLeft) {
            //we need different id´s for the elements in the menu and the ones in the canvas
            nodeCopy.id = data + "-copy";
            ev.target.appendChild(nodeCopy);

        }
        else {
            //right now we can only add to the end of the document. We remove the element and add it again at the end
            removeNode(document.getElementById(data));
            ev.target.appendChild(nodeCopy);
            
        }
    }
    ev.stopPropagation();
    return false;

    
 }