<?php

/*
 * this is the file for downloading the server saved file. this is mostly copied
 * from the demo files on d2l
 */
$file = $_GET["file"];

$target_file = "./uploads/" . $file;

if (file_exists($target_file)) {
    header('Content-disposition: attachment; filename=' . $file );
    readfile($target_file);
}

