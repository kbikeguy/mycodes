var row = 5;
var col = 5;
var currColor = "rgb(0, 0, 0)";
var mybutton;
//our undo/redo helper class
var hist = new History();

/*
this method increments the value of the column slider by 1 and calls showVal to update the display
 */
function addCol()
{
    document.getElementById("sldCol").value = parseInt(document.getElementById("sldCol").value) + 1;
    showVal("sliderCol", document.getElementById("sldCol").value);
}

/*
this method increments the value of the row slider by 1 and calls showVal to update the display
 */
function addRow()
{
    document.getElementById("sldRow").value = parseInt(document.getElementById("sldRow").value) + 1;
    showVal("sliderRow", document.getElementById("sldRow").value);
}

/*
this method builds a new gameboard based off the current size of row and col and sets an ID to each cell
of 0 through row * col - 1. the color of these cells are set to white. the size of the cells are set to
40px by 40px inside of the mystyle.css file. the onclick is set to setCellColor
 */
function buildBoard() {
    var board = document.getElementById("game");
    var size = row * col;

    //clear the board
    while (board.firstChild)
        board.removeChild(board.firstChild);

    for (var i = 0; i < size; i++)
    {
        var button = document.createElement("button");
        button.id = i.toString();
        button.onclick = setCellColor;
        button.style.backgroundColor = "rgb(255, 255, 255)";
        board.append(button);
    }

    board.style.gridTemplateColumns = "repeat(" + col + ", auto)";
    board.style.gridTemplateRows = "repeat(" + row + ", auto)";
    document.body.appendChild(board);
}

/*
this method is a helper for the UndoRedoColor function. the element ID and color to change to are passed in
and the element is changed to the color
 */
function colorHelper(id, color) {
    if(id === "textColor") {
        document.getElementById("textColor").style.color = color;
        document.getElementById("newColor").value = color;
    }
    else
        document.getElementById(id.toString()).style.backgroundColor = color;
}

/*
this is the history class for implementing the management of the stack of
undoRedo classes. this is mostly copied from the example file on d2l
 */
function History() {
    //GRADING: MANAGE
    var UndoRedos =[];
    var index = 0;

    //new UndoRedo, remove everything after the current UndoRedo index
    //and append the new function
    this.executeAction = function(cmd){
        UndoRedos.length = index; //trims length from 0 to index
        UndoRedos.push(cmd);
        index = UndoRedos.length;

        //run the UndoRedo and update
        cmd.exec();
        updateUI();
    };

    //undo called. Call the undo functin on the current UndoRedo and move back one
    this.undoCmd = function(){
        if(index > 0)
        {
            var cmd = UndoRedos[index-1];
            cmd.undo();
            index= index - 1;
            updateUI();
        }
    };

    //redo called. Call the execution function on the current UndoRedo and move forward one
    this.redoCmd = function(){
        if(index < UndoRedos.length)
        {
            var cmd = UndoRedos[index];
            cmd.exec();
            index = index + 1;
            updateUI();
        }
    };


    //is undo available
    this.canUndo = function(){
        return index !== 0;
    };

    //is redo available
    this.canRedo = function(){
        return index < UndoRedos.length;
    };
}

/*
this method takes in a string and returns true if it is a legal CSS color
 */
function isColor(strColor){
    const str = new Option().style;
    str.color = strColor;
    return str.color === strColor;
}

/*
this method takes in a string of the file to rebuild a saved game board.
there is error checking for invalid extracted dimensions. at each cell color,
more error checking is done for invalid colors. if at any time an invalid item
is found, an alert if displayed with the error and the default 5x5 white board
will be built instead.
 */
function loadGame(oldGame) {
    var newGame = oldGame.split('?');
    row = parseInt(newGame.shift());
    col = parseInt(newGame.shift());
    newGame.pop(); //removing a trailiing ?

    //error checking dimensions
    if(isNaN(row) || isNaN(col) || row > 14 || col > 14){
        row = col = 5;
        buildBoard();
        alert("An invalid file was loaded. the default board will be built");
        return;
    }

    buildBoard();

    //recolor the board
    for(var i = 0; i < newGame.length; i++) {

        //error checking colors
        if (!isColor(newGame[i])) {
            row = col = 5;
            buildBoard();
            alert("An invalid file was loaded. the default board will be built");
            return;
        }
        //so far so good
        document.getElementById((i).toString()).style.backgroundColor = newGame[i];
    }
}

/*
this method builds a CVS string using a ? of the current state of the board.
that string is saved as a cookie to be saved as a .txt file to the server on
the PHP side inside of index.php. the first 2 value are the row and column size
respectively, all remaining values are the cell colors organized by cell ID
 */
function saveIt() {
    const xhttp = new XMLHttpRequest(); //say we want a new http connection
    var size = row * col;
    var csv = row.toString() + "?" + col.toString() + "?";

    //build the CSV string
    for(var i = 0; i < size; i++)
            csv += document.getElementById(i.toString()).style.backgroundColor + "?";

    document.cookie = "savedGame=; expires= Fri, 08 Apr 1983 00:00:00 GMT"; //delete cookie if it exists
    document.cookie = "savedGame=" + csv; //add the cookie

    //wait for a good connection
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4 && this.status === 200) {
            //ready now, get response text
            document.getElementById("ajax").innerHTML = this.responseText;
        }
    };

    //open connection with GET protocal 
    xhttp.open( "GET","index.php?save"  , true);


    //commit request
    xhttp.send();
}

/*
this method takes in a color change event, collects the needed values, and passes
everything into the undoRedo pattern as the action
 */
function setCellColor(event) {
    var num = event.target.id;
    var prevColor = document.getElementById(num.toString()).style.backgroundColor;

    // GRADING: ACTION
    hist.executeAction(new UndoRedoColor(num, prevColor, currColor));
}

/*
this method handles a new color selection from the color selector and passes the needed
information into the undoRedo pattern as the action
 */
function setColor() {
    var prevColor = currColor;
    currColor = document.getElementById("newColor").value;

    // GRADING: ACTION
    hist.executeAction(new UndoRedoColor("textColor", prevColor, currColor));
    updateUI();
}

/*
this method takes in the values set in the row and column range elements and
passes that information to setSize() to start the undoRedo pattern action
 */
function setCustomSize() {
    const newRows = parseInt(document.getElementById("sldRow").value);
    const newCols = parseInt(document.getElementById("sldCol").value);
    setSize(newRows, newCols);
}

/*
this method check for the current width of the browser and determines how
many 40px grid cells could be displayed on it. then this number is checked against
14, the max width the game allows, and returns the smaller of these two values.
this method is used for setting the dynamic sizing of the max column range
 */
function setMax() {
    return Math.min(Math.floor(((document.documentElement.clientWidth - 20) / 44) - 1), 14).toString();
}

/*
this method resets/updates the row and column ranges and their displayed values
whenever the browser window size is changed for dynamic scaling
 */
function setRange() {
    document.getElementById("sldCol").max = document.getElementById("colMax").innerHTML = setMax();
    document.getElementById("sldRow").value = document.getElementById("sldCol").value = 1;
    document.getElementById("sliderCol").innerHTML = document.getElementById("sliderRow").innerHTML = "1";
}

/*
this method takes in new rows and columns to build a new game board to and passes
that information into the undoRedo pattern as the action
 */
function setSize(newRows, newCols) {

    // GRADING: ACTION
    hist.executeAction(new UndoRedoSize(currColor, row, newRows, col, newCols));
}

/*
this method updates the display values of the current row or col range slider then
calls updateUI()
 */
function showVal(id, val)
{
    document.getElementById(id.toString()).innerHTML = val.toString();
    updateUI();
}

/*
this method is a helper function for the changing board size action in the undo redo pattern.
this method takes in a color, row size, column size, row range value, and column range value
then sets the appropriate elements to these new values and builds a new board
 */
function sizehelper(color, r, c, rSlide, cSlide ) {
    currColor = color;
    row = r;
    col = c;
    document.getElementById("textColor").style.color = currColor;
    document.getElementById("newColor").value = currColor;
    document.getElementById("sldRow").value = rSlide;
    document.getElementById("sldCol").value = cSlide;
    document.getElementById("sliderCol").innerHTML = cSlide.toString();
    document.getElementById("sliderRow").innerHTML = rSlide.toString();
    buildBoard();
}

/*
this method decrements the value of the column slider by 1 and calls showVal to update the display
 */
function subCol()
{
    document.getElementById("sldCol").value = parseInt(document.getElementById("sldCol").value) - 1;
    showVal("sliderCol", document.getElementById("sldCol").value);
}

/*
this method decrements the value of the row slider by 1 and calls showVal to update the display
 */
function subRow()
{
    document.getElementById("sldRow").value = parseInt(document.getElementById("sldRow").value) - 1;
    showVal("sliderRow", document.getElementById("sldRow").value);
}

/*
this method moves the view of the page back to the top. this is called when the
TOP button is clicked
 */
function topFunction() {
    document.body.scrollTop = 0;
    document.documentElement.scrollTop = 0;
}

/*
this method is the command function for the undoRedo pattern for a color change
 */
function UndoRedoColor(val, prevColor, currColor){
    //GRADING: COMMAND

    //need to store enough information to undo/redo
    this.id = val;
    this.newColor = currColor;
    this.oldColor = prevColor;

    //color an object
    this.exec = function(){
       colorHelper(this.id, this.newColor);
    };

    //uncolor an object
    this.undo = function(){
        colorHelper(this.id, this.oldColor);
    }
}

/*
this method is the command function for the undoRedo pattern for a grid size change
 */
function UndoRedoSize(color, prevRow, newRow, prevCol, newCol){
    //GRADING: COMMAND

    //need to store enough information to undo/redo
    this.oldColor = color;
    this.newColor = "rgb(0, 0, 0)";
    this.oldRow = prevRow;
    this.newRow = newRow;
    this.oldCol = prevCol;
    this.newCol = newCol;
    this.oldSize = this.oldRow * this.oldCol;
    this.cellColors = [];
    this.rowSlider = document.getElementById("sldRow").value;
    this.colSlider = document.getElementById("sldCol").value;

    //save all colors
    for(var i = 0; i < this.oldSize; i++)
        this.cellColors[i] = document.getElementById(i.toString()).style.backgroundColor;

    //resize the grid
    this.exec = function(){
        sizehelper(this.newColor, this.newRow, this.newCol, "1", "1");
    };

    //restore the grid
    this.undo = function(){
        sizehelper(this.oldColor, this.oldRow, this.oldCol, this.rowSlider, this.colSlider);

        //recolor the board with the old saved colors
        for(var i = 0; i < this.oldSize; i++)
            document.getElementById(i.toString()).style.backgroundColor = this.cellColors[i];
    };
}

/*
this method updates the buttons on the main page to be disabled or not depending of it they can be used
 */
function updateUI()
{
    document.getElementById("undo").disabled = !hist.canUndo();
    document.getElementById("redo").disabled = !hist.canRedo();

    document.getElementById("row-").disabled = (document.getElementById("sliderRow").innerText === "1");
    document.getElementById("row+").disabled = (document.getElementById("sliderRow").innerText === "14");


    var maxCol = document.getElementById("colMax").innerText;
    document.getElementById("col+").disabled = (document.getElementById("sliderCol").innerText === maxCol.toString());
    document.getElementById("col-").disabled = (document.getElementById("sliderCol").innerText === "1");
}

/*
this method sets up the initial state of the main page when it is loaded
 */
window.onload = function() {
    //set up a fresh board if needed
    if(document.getElementById("game").firstChild === null)
        buildBoard();

    //set button clicks
    document.getElementById("undo").onclick = hist.undoCmd;
    document.getElementById("redo").onclick = hist.redoCmd;
    mybutton = document.getElementById("myBtn");

    //set the max value of the column range slider
    setRange();

    //update the buttons to enabled or disabled
    updateUI();
};

/*
this method calls serRange() when the browser window changes size
 */
window.onresize = function(){
    setRange();
};

/*
this method makes the return to top button appear or disappear depending on if the view
is more or less than 20px from the top of the page
 */
window.onscroll = function() {
    if (document.body.scrollTop > 20 || document.documentElement.scrollTop > 20)
        mybutton.style.display = "block";
    else
        mybutton.style.display = "none";
};
