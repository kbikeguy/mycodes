<?php
//connection info
$host="services1.mcs.sdsmt.edu"; //hostname URL
$port=3306;						//default port 3306
$user="s7354704_s19";					//DBMS login username
$password="97John97";				//DBMS login password
$dbName="db_7354704_s19";		//Select DB
/*
$host = "services1.mcs.sdsmt.edu"; //hostname URL
$port = 3306;                        //default port 3306
$user = "s7356506_s19";                    //DBMS login username
$password = "Keebler1";                //DBMS login password
$dbname = "db_7356506_s19";        //Select DB
*/

/******Get event filter options*****************/
//each returned as <option value=ID>Event</option>
function getEvents()
{
    global $host, $user, $password, $dbName, $port;
    //Connect to MySQL
    $mysqli = new mysqli($host, $user, $password, $dbName, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }
    
    //define the query
    $query = "SELECT EventID, Title FROM Events ORDER BY Title;";
    
    //execute the statement
    $stmt = $mysqli->prepare($query);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();
    
    //retreive the values and turn them into HTML
    if($queryResult and $queryResult->num_rows != 0)
    {
        //Fetch and display each row of $queryResult
        while($row=$queryResult->fetch_row())
        {
            echo "<option value=\"$row[0]\">$row[1]</option>";
        }
    }
}

/******Get Job Title filter options*****************/
//each returned as <option value="Job Title">Job Title</option>
function getJobTitles($type)
{
    global $host, $user, $password, $dbName, $port;
    //Connect to MySQL
    $mysqli = new mysqli($host, $user, $password, $dbName, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }
    
    //define the query
    $query = "SELECT JobTitle FROM ";
    $query .= ($type === "Participants" ? "Participants" : "Staff");
    $query .= " GROUP BY JobTitle ORDER BY JobTitle;";
    
    //execute the statement
    $stmt = $mysqli->prepare($query);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();
    
    //retreive the values and turn them into HTML
    if($queryResult and $queryResult->num_rows != 0)
    {
        //Fetch and display each row of $queryResult
        while($row=$queryResult->fetch_row())
        {
            echo "<option value=\"$row[0]\">$row[0]</option>";
        }
    }
}

/******Get Vendor options*****************/
//each returned as <option value=Vendor>Vendor</option>
function getVendors()
{
    global $host, $user, $password, $dbName, $port;
    //Connect to MySQL
    $mysqli = new mysqli($host, $user, $password, $dbName, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }
    
    //define the query
    $query = "SELECT VendorName FROM vendor ORDER BY VendorName;";
    
    //execute the statement
    $stmt = $mysqli->prepare($query);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();
    
    //retreive the values and turn them into HTML
    if($queryResult and $queryResult->num_rows != 0)
    {
        //Fetch and display each row of $queryResult
        while($row=$queryResult->fetch_row())
        {
            echo "<option value=\"$row[0]\">$row[0]</option>";
        }
    }
}


/******Handle the REQUEST*****************/
//f - filter name
//t - tab (all, participants, staff, managers)
 
//Return the items for the filter
switch ($_REQUEST["f"]) {
    case "jobTitle":
        //query and output job title options
        getJobTitles($_REQUEST["t"]);
        break;
        
    case "events":
        //query and output events options
        getEvents();
        break;
        
    case "vendor":
        //query and output events options
        getVendors();
        break;
        
    default:
        echo "Invalid query. Something has gone terribly wrong...";
}
?>