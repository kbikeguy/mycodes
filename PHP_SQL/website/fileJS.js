
/*
this method takes in the name of the saved game to be loaded and calls the index page with the
saved game file name appended on to it
 */
function loadSavedGame(file){
    window.location.href = "index.php?load=" + file;
}

/*
this method calls the download.php file with the name of the requested file appended onto it
 */
function downloadFile(file) {
    window.location.href = "download.php?file=" + file;
}