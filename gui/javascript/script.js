function init() {
    //var canvas = document.getElementById("myCanvas");
    //var context = canvas.getContext("2d");
    
    //context.lineWidth = 2;
}

var pos;
function allowDrop(ev) {
    ev.preventDefault();
}

function get_pos(ev){
    pos = [ev.pageX, ev.pageY];
}
/*
function drag(ev) {
    ev.dataTransfer.setData("Text",ev.target.id);
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


function allowDrop(ev) {
    ev.preventDefault();
}
*/
function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

function removeNode(node) {
        node.parentNode.removeChild(node);
      }
      
function drop(ev) {
    ev.preventDefault();
    var data = ev.dataTransfer.getData("text");
    var isLeft = 'move-backwards' == data || "move-forward" == data;
    var nodeCopy = document.getElementById(data).cloneNode(true);
    nodeCopy.id = "form" + ev.target.id;
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