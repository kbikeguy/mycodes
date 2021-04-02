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

/******Delete a person*****************/
function deletePerson($name, $table) {
    global $host, $user, $password, $dbName, $port;

    //Connect to MySQL
    $mysqli = new mysqli($host, $user, $password, $dbName, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    echo "Name: ",$name," Table: ", $table,"\n";

    //define the query
    switch ($table) {
        case "All":
            $query =
                "DELETE FROM ContactInfo
            WHERE Name = ?;";
            break;

        case "Participants":
            $query =
                "DELETE FROM Participants
            WHERE ContactInfo_Name = ?;";
            break;

        case "Staff":
            $query =
                "DELETE FROM Staff
            WHERE ContactInfo_Name = ?;";
            break;

        case "Managers":
            $query =
                "UPDATE vendor
            SET ManagerName = NULL
            WHERE ManagerName = ?;";
            break;
        default:
            exit();
    }

    echo $query;

    //create the statement
    $stmt = $mysqli->prepare($query);


    $stmt->bind_param("s", $name);
    $stmt->execute();
    $stmt->close();
    $mysqli->close();
}

/******Get a person*****************/
function getPerson($name) {
    global $host, $user, $password, $dbName, $port;

    //Connect to MySQL
    $mysqli = new mysqli($host, $user, $password, $dbName, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    //create the statement
    $stmt = $mysqli->prepare("SELECT * FROM ContactInfo WHERE Name = ?;");

    //execute and get the result
    $stmt->bind_param("s", $name);
    $stmt->execute();
    $queryResult = $stmt->get_result();

    //close
    $stmt->close();
    $mysqli->close();

    //put result into an arrray
    if ($queryResult->num_rows === 0) {
        echo "NULL";
    } else {
        $row = $queryResult->fetch_row();
        $data["Name"] = $row[0];
        $data["Email"] = $row[1];
        $data["Phone"] = $row[2];
        $data["BDate"] = $row[3];

        echo json_encode($data);
    }

}

/******Edit a person*****************/
function editPerson($name, $data) {
    global $host, $user, $password, $dbName, $port;

    //Connect to MySQL
    $mysqli = new mysqli($host, $user, $password, $dbName, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    //create the statement
    $stmt = $mysqli->prepare(
        "UPDATE ContactInfo
    SET EmailAddress = ?, PhoneNum = ?, BirthDate = ?
    WHERE Name = ?;");

    //execute
    $stmt->bind_param("ssss", $data["Email"], $data["Phone"], $data["BDate"], $name);
    $stmt->execute();

    //close
    $stmt->close();
    $mysqli->close();
}

/******Handle the REQUEST*****************/
//a - action (edit, delete, update, get)
//t - tab name
//p - person name

//query to get data
switch ($_REQUEST["a"]) {
    case "edit":
        //edit a person
        if (!is_null($_REQUEST["p"])
            and !is_null($_REQUEST["Email"])
            and !is_null($_REQUEST["Phone"])
            and !is_null($_REQUEST["BDate"])) {
            editPerson($_REQUEST["p"], $_REQUEST);
        }
        break;

    case "delete":
        //delete a person :(
        if (!is_null($_REQUEST["p"]) and !is_null($_REQUEST["t"])) {
            deletePerson($_REQUEST["p"], $_REQUEST["t"]);
        }
        break;

    case "update":
        //query and output staff table
        //outputStaffTable($_REQUEST["s"], $_REQUEST["d"], $filters);
        break;

    case "get":
        //get a single person's information
        if ( !is_null($_REQUEST["p"]) ) {
            getPerson($_REQUEST["p"]);
        }
}
?>
