function init() {
    var canvas = document.getElementById("myCanvas");
    var context = canvas.getContext("2d");
    
    context.lineWidth = 2;
}
var pos;
function allowDrop(ev) {
    ev.preventDefault();
}

function get_pos(ev){
    pos = [ev.pageX, ev.pageY];
}

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