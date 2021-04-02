<?php

session_start();

/*
 * this is how a game gets saved into a server file by using the cookie that was created in the saveIt()
 * method inside of undopattern.js
 */
if(isset($_GET["save"]))
{
    $target_dir = "./uploads/";
    $target_file = $target_dir . "savedGame.txt";

    $file = fopen($target_file, 'w') or die("Unable to open " . $target_file);

    $saved = $_COOKIE["savedGame"];

    echo"<script> console.log('the saved file is ' + '$saved') </script>";

    fwrite($file, $saved );
    fclose($file);

    echo "<p>File saved as: savedGame.txt</p>";
    return;
}
?>


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">

    <title>
        Home
    </title>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
     <script src="undopattern.js" type="text/javascript"></script>
 </head>

 <body>
 <div class="grid-container">
     <div class="header">
         <h1>Nonogram</h1>
     </div>

     <div class="Links">
         <a href = index.php><h2>Main</h2></a>  <a href = fileManager.php><h2>Files</h2></a> <a href = help.html><h2>Help</h2></a>
     </div>

     <p>
     <div class="selectColor">
             <h3 id="textColor">The selected color</h3>
             <h3 id="color">
                 <label
                     for="newColor">
                 </label>
                 <input  type="color" id="newColor" onchange="setColor()" />
             </h3>

     </div>
 </p>
     <div class="size">
         <h5>
             Rows: <span id="sliderRow"></span>
             <input type="button" id="row-" value=" - " onClick="subRow()">
             1 <input type="range" min="1" max="14" step="1" id="sldRow" value="1" oninput="showVal('sliderRow', this.value)"> 14
             <input type="button" id="row+" value=" + " onClick="addRow()">

             Cols: <span id="sliderCol"></span>
             <input type="button" id="col-" value=" - " onClick="subCol()">
             1 <input type="range" min="1" max="setMax()" step="1" id="sldCol" value="1" oninput="showVal('sliderCol', this.value)">
             <input type="button" id="col+" value=" + " onClick="addCol()">
             <span id="colMax"></span>
         </h5>
         <br>
         <button class="myButtns" onclick="setCustomSize()"> Custom Size </button>
         <button class="myButtns" onclick="setSize(5, 5)"> 5 x 5 </button>
         <button class="myButtns" onclick="setSize(10,10)"> 10 x 10 </button>
     </div>

     <div class="saveUndoRedo">
         <button class="myButtns" id="save" name="saveBtn" onclick="saveIt()"> Save</button>
         <button class="myButtns" id="undo">Undo</button>
         <button class="myButtns" id="redo">Redo</button>
        <h6> <p id="ajax"></p></h6>
     </div>

 </div>
 <button onclick="topFunction()" id="myBtn" title="Go to top">Top</button>

 <!-- Nonogram Part****************-->
 <p>
    <div class="gameWrapper">
        <div class="gameContainer" id="game"></div>
    </div>
 </p>


 </body>

<?php

/*
 * this is how the loaded file gets open, read into a string, and then that string is passed into
 * my JS funtion inside of undopattern.js for building the saved game
 */
if(isset($_GET["load"]))
{
    $fileName = $_GET["load"];
    $file = fopen('./uploads/'. $fileName, 'r');
    while (!feof($file))  //feof equivalent to C++ fin.eof()
        $fileContents = fgets($file);

    fclose($file);
    echo"<script> console.log('the loaded file is ' + '$fileContents') </script>";
    echo "<script> loadGame('$fileContents'); </script>";
}

?>