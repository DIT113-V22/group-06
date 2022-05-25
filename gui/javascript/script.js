let message = ''
const client = new Paho.MQTT.Client('broker.emqx.io', 8083, 'group-06-monkeycar')

// set callback handlers
client.onConnectionLost = onConnectionLost
client.onMessageArrived = onMessageArrived

// connect the client
client.connect({ onSuccess: onConnect })

// called when the client connects
function onConnect () {
  // Once a connection has been made, make a subscription and send a message.
  console.log('Connected successfully')
  client.subscribe('smartcar/control/#')
}

// This method is to help us send the right message to the emulator based on the code blocks
function publishForMovement (direction, steps) {
  if (direction === 'forward') {
    message = new Paho.MQTT.Message(steps)
    message.destinationName = 'smartcar/control/throttle'
    client.send(message)
  }

  if (direction === 'backwards') {
    message = new Paho.MQTT.Message(steps)
    message.destinationName = 'smartcar/control/reverse'
    client.send(message)
  }
  if (direction === 'left') {
    message = new Paho.MQTT.Message(steps)
    message.destinationName = 'smartcar/control/steer-left'
    client.send(message)
  }
  if (direction === 'right') {
    message = new Paho.MQTT.Message(steps)
    message.destinationName = 'smartcar/control/steer-right'
    client.send(message)
  }
}

// called when the client loses its connection
function onConnectionLost (responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log('onConnectionLost:' + responseObject.errorMessage)
  }
}

// called when a message arrives
function onMessageArrived (message) {
  console.log('Sent messages: ' + message.payloadString)
}

class BlockEntity {
  constructor (direction, steps) {
    this.direction = direction
    this.steps = steps
  }

  toJson () {
    return JSON.stringify({
      direction: this.direction,
      steps: this.steps
    })
  }
}

// with this function we allow elements to be dropped in a certain place.
window.allowDrop = function allowDrop (ev) {
  ev.preventDefault()
}

// this function allows us to drag elements from one place to another
window.drag = function drag (ev) {
  ev.dataTransfer.setData('text', ev.target.id)
  ev.target.classList.add('dragging')
}

// with this method we remove a node (one block)
function removeNode (node) {
  node.parentNode.removeChild(node)
}

// This function is to drop an element in the canvas
window.drop = function drop (ev) {
  if (ev.target.id !== 'repeat-canvas') {
    ev.preventDefault()
    const canvas = document.getElementById('canvas')
    // we get the data we set in the drag() method
    const data = ev.dataTransfer.getData('text')
    // we check whether the selected block is inside the selection menu or in the canvas and make a copy of it
    const isLeft = (data === 'move-forward' || data === 'move-backwards' || data === 'move-left' || data === 'move-right' || data === 'turn-around' || data === 'spin' || data === 'wait' || data === 'repeat')
    const nodeCopy = document.getElementsByClassName('dragging').item(0).cloneNode(true)
    // we set the class to dragging so that we can distinguish it from the others
    // we check whether we try to drop it on the canvas (otherwise we can also drop inside the other blocks)
    const elementAfter = getElementAfter(ev.clientY, true, null)

    if (data === 'repeat') {
      nodeCopy.children[3].setAttribute('ondrop', 'dropInRepeat(event)')
      nodeCopy.children[3].setAttribute('ondragover', 'allowDrop(event)')
    }

    if (isLeft && ev.target.id !== 'trash-icon') {
      // we need different id´s for the elements in the menu and the ones in the canvas
      nodeCopy.id = data + '-copy'
      checkAndInsertElement(elementAfter, nodeCopy, canvas)
    } else if (ev.target.id === 'trash-icon') {
      removeNode(canvas.getElementsByClassName('dragging').item(0))
    } else {
      // We check which element would come after the position we are dropping the element, remove the element and append it on the right position
      removeNode(canvas.getElementsByClassName('dragging').item(0))
      checkAndInsertElement(elementAfter, nodeCopy, canvas)
    }
    removeDragging(ev, data, nodeCopy)
    ev.stopPropagation()
    return false
  }
}

window.dropInRepeat = function dropInRepeat (ev) {
  ev.preventDefault()
  // const selectedBlock =  getRepeatBlock(ev.clientY)
  const repeatBlock = getRepeatBlock(ev.clientY).children[3]

  console.log(repeatBlock)
  // we get the data we set in the drag() method
  const data = ev.dataTransfer.getData('text')
  // we check whether the selected block is inside the selection menu or in the canvas and make a copy of it
  const isLeft = (data === 'move-forward' || data === 'move-backwards' || data === 'move-left' || data === 'move-right' || data === 'turn-around' || data === 'spin' || data === 'wait' || data === 'repeat')
  const nodeCopy = document.getElementsByClassName('dragging').item(0).cloneNode(true)
  // we set the class to dragging so that we can distinguish it from the others
  // we check whether we try to drop it on the canvas (otherwise we can also drop inside the other blocks)
  const elementAfter = getElementAfter(ev.clientY, false, repeatBlock)

  if (isLeft && data !== 'repeat' && data !== 'repeat-copy') {
    // we need different id´s for the elements in the menu and the ones in the canvas
    nodeCopy.id = data + '-copy'
    checkAndInsertElement(elementAfter, nodeCopy, repeatBlock)
  } else if (data !== 'repeat' && data !== 'repeat-copy') {
    // We check which element would come after the position we are dropping the element, remove the element and append it on the right position
    removeNode(document.getElementsByClassName('dragging').item(0))
    checkAndInsertElement(elementAfter, nodeCopy, repeatBlock)
  }

  removeDragging(ev, data, nodeCopy)
  ev.stopPropagation()
  return false
}

function removeDragging (ev, data, nodeCopy) {
  // we remove the class dragging from the element because we dropped it (once for the selction menu and once for the canvas).
  if (ev.target.id !== 'trash-icon') {
    document.getElementById(data).classList.remove('dragging')
  }
  nodeCopy.classList.remove('dragging')
}

function checkAndInsertElement (elementAfter, nodeCopy, insertIn) {
  if (elementAfter === null) {
    insertIn.appendChild(nodeCopy)
  } else {
    insertIn.insertBefore(nodeCopy, elementAfter)
  }
}

// get the element before which the dragged element is supposed to be inserted.
function getElementAfter (y, canvas, repeatBlock) {
  // get all blocks in the canvas that are not being dragged.
  let remainingBlocks = []
  if (canvas === true) {
    remainingBlocks = [...document.getElementById('canvas').querySelectorAll('.block:not(.dragging)')]
  } else {
    remainingBlocks = [...repeatBlock.querySelectorAll('.block:not(.dragging)')]
  }
  console.log(remainingBlocks)
  // check which element is closest after(-> offset below 0) the current position and return it
  return remainingBlocks.reduce((closest, child) => {
    const box = child.getBoundingClientRect()
    const offset = y - box.top - box.height / 2
    if (offset < 0 && offset > closest.offset) {
      return { offset: offset, element: child }
    } else {
      return closest
    }
  }, { offset: Number.NEGATIVE_INFINITY }).element
}

function getRepeatBlock (y) {
  const canvas = document.getElementById('canvas')
  const blocks = canvas.querySelectorAll('.block')
  let offset = 1000000
  let blockToReturn = null
  let newOffset = 1000000
  let box = null
  for (let i = 0; i < blocks.length; i++) {
    if (blocks.item(i).id === 'repeat-copy') {
      box = blocks.item(i).getBoundingClientRect()
      newOffset = y - box.top - box.height / 2
      if (newOffset < 0) {
        newOffset = newOffset * -1
      }
      if (offset > newOffset) {
        offset = newOffset
        blockToReturn = blocks.item(i)
      }
    }
  }
  return blockToReturn
}

/// Function to get the text of all code blocks in the canvas
function retrieveContents () {
  const jsObjects = []
  const remainingBlocks = document.getElementById('canvas').querySelectorAll('.block')
  for (let i = 0; i < remainingBlocks.length; i++) {
    let subString2 = ''
    console.log(remainingBlocks[i].id)
    if (remainingBlocks[i].id === 'move-forward-copy') {
      subString2 = 'forward'
    } else if (remainingBlocks[i].id === 'move-backwards-copy') {
      subString2 = 'backwards'
    } else if (remainingBlocks[i].id === 'move-left-copy') {
      subString2 = 'left'
    } else if (remainingBlocks[i].id === 'move-right-copy') {
      subString2 = 'right'
    } else {
      subString2 = 'no-direction-specified'
    }

    const codeBlock = new BlockEntity(
      subString2,
      remainingBlocks[i].children[1].value
    )

    jsObjects[i] = codeBlock
  }
  return jsObjects
}

// For testing purposes when Play button is clicked
window.start = function start () {
  const contents = retrieveContents()
  for (let i = 0; i < contents.length; i++) {
    console.log(contents[i])
  }
}
// This will be tested later for the MQTT
window.start1 = function start1 () {
  if (!client.isConnected) {
    // Try to connect
    console.log('Not connected....')
  }
  console.log('Connected....')
  const contents = retrieveContents()
  console.log(contents)
  for (let i = 0; i < contents.length; i++) {
    publishForMovement(contents[i].direction, contents[i].steps)
  }
}
