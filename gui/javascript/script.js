function allowDrop(ev) {
    ev.preventDefault();
}

function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

function removeNode(node) {
    node.parentNode.removeChild(node);
}
      
function drop(ev) {
    
    
    
    ev.preventDefault();
    var data = ev.dataTransfer.getData("text");
    var isLeft = 'move-forward' == data || "move-backwards" == data || "move-left" == data || "move-right" == data;
    var nodeCopy = document.getElementById(data).cloneNode(true);
    //nodeCopy.id = data + ev.target.id;
    nodeCopy.style.cssText += 'width: 100%'


    // clean target space if needed
    if (isLeft) {
        
        if (ev.target.nodeName == 'FORM') {
        ev.target.parentNode.appendChild(nodeCopy);
        removeNode(ev.target);
        }
        else 
        ev.target.appendChild(nodeCopy);
    }
    else {
        if (ev.target.nodeName != 'FORM') {
        removeNode(document.getElementById(data));
        ev.target.appendChild(nodeCopy);
        }
    }
    ev.stopPropagation();
    return false;

    
 }