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
  ev.preventDefault()
  const canvas = document.getElementById('canvas')
  // we get the data we set in the drag() method
  const data = ev.dataTransfer.getData('text')
  // we check whether the selected block is inside the selection menu or in the canvas and make a copy of it
  const isLeft = (data === 'move-forward' || data === 'move-backwards' || data === 'move-left' || data === 'move-right')
  const nodeCopy = document.getElementsByClassName('dragging').item(0).cloneNode(true)
  // we set the class to dragging so that we can distinguish it from the others
  // we check whether we try to drop it on the canvas (otherwise we can also drop inside the other blocks)
  const elementAfter = getElementAfter(ev.clientY)
  if (isLeft && ev.target.id !== 'trash-icon') {
    // we need different id´s for the elements in the menu and the ones in the canvas
    nodeCopy.id = data + '-copy'
    if (elementAfter === null) {
      canvas.appendChild(nodeCopy)
    } else {
      canvas.insertBefore(nodeCopy, elementAfter)
    }
  } else if (ev.target.id === 'trash-icon') {
    removeNode(canvas.getElementsByClassName('dragging').item(0))
  } else {
    // We check which element would come after the position we are dropping the element, remove the element and append it on the right position
    removeNode(canvas.getElementsByClassName('dragging').item(0))
    if (elementAfter === null) {
      canvas.appendChild(nodeCopy)
    } else {
      canvas.insertBefore(nodeCopy, elementAfter)
    }
  }

  // we remove the class dragging from the element because we dropped it.
  if (ev.target.id !== 'trash-icon') {
    document.getElementById(data).classList.remove('dragging')
  }
  nodeCopy.classList.remove('dragging')
  ev.stopPropagation()
  return false
}

// get the element before which the dragged element is supposed to be inserted.
function getElementAfter (y) {
  // get all blocks in the canvas that are not being dragged.
  const remainingBlocks = [...document.getElementById('canvas').querySelectorAll('.block:not(.dragging)')]
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

/// Function to get the text of all code blocks in the canvas
function retrieveContents () {
  const jsObjects = []
  const remainingBlocks = document.getElementById('canvas').querySelectorAll('.block')
  for (let i = 0; i < remainingBlocks.length; i++) {
    const subString1 = remainingBlocks[i].lastElementChild.innerHTML.slice(0, 5)
    let subString2 = remainingBlocks[i].lastElementChild.innerHTML
    if (subString1 === 'steps') {
      subString2 = remainingBlocks[i].lastElementChild.innerHTML.slice(6)
    } else {
      subString2 = remainingBlocks[i].lastElementChild.innerHTML.slice(1)
    }

    const codeBlock = new BlockEntity(
      subString2,
      remainingBlocks[i].children[1].value
    )

    console.log(codeBlock.toJson())

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
