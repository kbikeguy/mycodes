<!DOCTYPE html>
<html lang="en">
<head>

    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <script src="fileJS.js" type="text/javascript"></script>
    <title>
        File Manager
    </title>

</head>
<body>

<!--basic structure for a file upload-->
<?php
//determine what to do based on GET variables
if (isset($_GET['up'])) {
    upload();
}
?>


<div class="grid-container">
    <div class="Links">
        <h1>
            <a href=index.php><h2>Main</h2></a>
            <a href=fileManager.php><h2>Files</h2></a>
            <a href=help.html><h2>Help</h2></a>
        </h1>
    </div>
</div>
<br>
<br>


<form action="fileManager.php?up=1" method="post" enctype="multipart/form-data">
    <h2>Select file to upload:
        <input type="file" name="fileToUpload" id="fileToUpload">
        <input type="submit" value="Upload" name="submit">
    </h2>
</form>


<?php
echo "<p><br><h1>Availible files:<br><br></p>";

$myFiles = scandir("./uploads/");
echo "<ul>";
foreach ($myFiles as $f) {
    if (!is_dir($f)) {
        echo "<li>" . $f . "<button onclick=\"loadSavedGame('$f')\"> load</button>";
        echo "<button onclick=\"downloadFile('$f')\"> download</button></li>";
        echo "<br>";
    }
}
echo "</ul></h1>";


?>


</body>
</html>

<?php

/*
 * this method uploads a file to the server. this is mostly copied from the upload function example that
 * was posted on d2l with build in error checking
 */
function upload()
{
    //keep uploads separate for security. uploads MUST allow public write, which is VERY unsafe if allowed in general
    $target_dir = "./uploads/";
    $message = '';

    /////////////////////////////
    $upload_dir = $_SERVER['DOCUMENT_ROOT'] . "/images/";


    //only one file will be permitted to be saved. If you want to permit multiple saves (e.g. one for each user). This:
    $target_file = $target_dir . $_FILES["fileToUpload"]["name"];
    //would be better as it names it the same as what the user uploaded.
    //or best yet, use a unique id (uniqid())
    $file = $_FILES["fileToUpload"];
    //$target_file = $target_dir . "test.txt";
    //how to check for file type
    $imageFileType =
        strtolower(pathinfo($file["name"], PATHINFO_EXTENSION));


    if ($imageFileType != "txt") {
        echo "Only txt file types are supported. Please, try a different file.<br>";
        return;
    }

    // Check file size which should be MUCH smaller than the server limit
    if ($file["size"] > 5000) {
        echo "Ack, the file is too large for me!";
        return;
    }

    // Check if file already exists, and delete it if it does so we can overwrite it
    if (file_exists($target_file)) {
        unlink($target_file);
    }


    //check other errors
    $message .= 'Error uploading file';
    switch ($_FILES['fileToUpload']['error']) {
        case UPLOAD_ERR_OK:
            $message = false;
            break;
        case UPLOAD_ERR_INI_SIZE:
        case UPLOAD_ERR_FORM_SIZE:
            $message .= ' - file too large.';
            break;
        case UPLOAD_ERR_PARTIAL:
            $message .= ' - file upload was not completed.';
            break;
        case UPLOAD_ERR_NO_FILE:
            $message .= ' - zero-length file uploaded.';
            break;
        default:
            $message .= ' - internal error #' . $_FILES['fileToUpload']['error'];
            break;
    }


    //if OK thus far, try to save
    if (!$message) {
        if (!is_uploaded_file($file['tmp_name'])) {
            $message = 'Error uploading file - unknown error.';
        } else {
            // Let's see if we can move the file.
            if (!move_uploaded_file($file["tmp_name"], $target_file)) { // No error suppression so we can see the underlying error.
                $message = 'Error uploading file - could not save upload 
                (this will probably be a permissions problem in ' . $target_dir . ')';
            }
        }
    }

    //final check, and copy and force download for confirmation
    if ($message != '') {
        echo $message;
    }
}

?>


