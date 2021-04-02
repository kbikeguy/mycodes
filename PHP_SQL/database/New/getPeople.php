<?php


/******Parse a ';' delimited array*****************/
function parseParam($param)
{
    $arr = explode( ';', $param );

    if (count($arr) === 0 or $arr[0] === "")
        return null;
    else
        return $arr;
}


/******Output table for "All"*****************/
function outputAllTable($sortCol, $sortDir, $filters)
{
    //-----build the main query-----------------------------
    $query =
        "SELECT Name,
            EmailAddress as Email, 
            PhoneNum as 'Phone #', 
            BirthDate as 'Birth Date'
    FROM ContactInfo";

    //Add the filters
    $filterString = "";
    //name
    if (!is_null($filters["Name"]))
    {
        $filterString .= "LEFT(SUBSTRING_INDEX(Name, ' ', -1), 1) >= \"".$filters["Name"][0]."\" AND LEFT(SUBSTRING_INDEX(Name, ' ', -1), 1) <= \"".$filters["Name"][1]."\"";
    }
    //birthdate
    if (!is_null($filters["BirthDate"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "BirthDate >= \"".$filters["BirthDate"][0]."\" AND BirthDate <= \"".$filters["BirthDate"][1]."\"";
    }

    //append to the query
    if ($filterString != "")
    {
        $query .= "\nWHERE ".$filterString;
    }

    //Figure out the sorting
    if (is_null($sortCol))
    {
        //no sorting specified
        $query .= ";";
    }
    else
    {
        //add the sorting column
        $query .= "\nORDER BY ".$sortCol;

        //Ascending or Descending
        if (!is_null($sortDir) and $sortDir == 'd') {
            $query .= " DESC;";
        }
        else
        {
            $query .= " ASC;";
        }
    }

    //-----connection info-----------------------------
    $host="services1.mcs.sdsmt.edu"; //hostname URL
    $port=3306;						//default port 3306
    $user="s7354704_s19";					//DBMS login username
    $password="97John97";				//DBMS login password
    $dbname="db_7354704_s19";		//Select DB
    /*
    $host = "services1.mcs.sdsmt.edu"; //hostname URL
    $port = 3306;                        //default port 3306
    $user = "s7356506_s19";                    //DBMS login username
    $password = "Keebler1";                //DBMS login password
    $dbname = "db_7356506_s19";        //Select DB
*/

    //-----Connect to MySQL-----------------------------
    $mysqli = new mysqli($host, $user, $password, $dbname, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    //query to get All
    $stmt = $mysqli->prepare($query);
    $stmt->bind_param('ss', $code, $language, $official, $percent);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();

    //-----Build the table-----------------------------
    echo '<TABLE Border="1">';

    //Output row headers
    echo "<TR>";
    $c = 1;
    while ($field=$queryResult->fetch_field())
    {
        echo '<TH ';
        if (!is_null($sortCol) and $sortCol === strval($c))
            echo 'class="sortCol" ';
        echo 'onclick="sortBy(this,\'',$c++,'\')">';
        echo "$field->name";
        echo "</TH>";
    }
    echo "<TH></TH>";  //empty column for edit buttons
    echo "</TR>";

    //Output rows if there are any
    if($queryResult->num_rows == 0)
    {
        echo "<TR><TD colspan=\"42\"><center>No Entries found.</center></TD></TR>";
    }
    else
    {
        //Fetch and display each row of table
        if($queryResult)
        {
            while($row=$queryResult->fetch_row())
            {
                echo "<TR>";

                for ($i=0; $i < $queryResult->field_count; $i++)
                {
                    echo "<TD>";
                    echo $row[$i];
                    echo "</TD>";
                }

                //X and edit buttons
                echo "<TD><div class=\"editButton\" onclick=\"editPerson('$row[0]')\">&nbsp;</div>
                      <div class=\"deleteButton\" onclick=\"deletePerson('$row[0]')\">X</div></TD>";

                echo "</TR>\n";
            }
        }
    }
    echo "</TABLE>";
}


/******Output table for participants*****************/
function outputParticipantsTable($sortCol, $sortDir, $filters)
{
    $eventsCol = -1; //Events column #
    $participantName = "";

    //-----build the main query-----------------------------
    $query =
        "Select p.ContactInfo_Name as Name, 
            JobTitle as 'Job Title',\n";

    //get max or min event depending on sort
    if (!is_null($sortCol) and $sortCol == 3 and !is_null($sortDir) and $sortDir == 'd')
    {
        $query .= "MAX(e.Title)";
    }
    else
    {
        $query .= "MIN(e.Title)";
    }

    //rest of the query
    $query .= " as 'Events',
            CONCAT('$', Payment) as Payment,
            EmailAddress as Email, 
            PhoneNum as 'Phone #', 
            BirthDate as 'Birth Date'
    from Participants p
         LEFT JOIN ContactInfo c
         ON p.ContactInfo_Name = c.Name
         LEFT JOIN Junc_Event_Partic ep
         ON p.ContactInfo_Name = ep.ContactInfo_Name
         LEFT JOIN Events e
         ON ep.EventID = e.EventID";

    //Add the filters
    $filterString = "";
    //name
    if (!is_null($filters["Name"]))
    {
        $filterString .= "LEFT(SUBSTRING_INDEX(Name, ' ', -1), 1) >= \"".$filters["Name"][0]."\" AND LEFT(SUBSTRING_INDEX(Name, ' ', -1), 1) <= \"".$filters["Name"][1]."\"";
    }
    //job title
    if (!is_null($filters["JobTitle"]))
    {
        if ($filterString != "") $filterString .= " AND";

        $filterString .= " (";
        for ($i = 0; $i < count($filters["JobTitle"]); $i++) {
            if ($i != 0) $filterString .= " OR ";
            $filterString .= "JobTitle = \"".$filters["JobTitle"][$i]."\"";
        }
        $filterString .= ")";
    }
    //Events
    if (!is_null($filters["Event"]))
    {
        if ($filterString != "") $filterString .= " AND";

        $filterString .= " (";
        for ($i = 0; $i < count($filters["Event"]); $i++) {
            if ($i != 0) $filterString .= " OR ";
            $filterString .= "ep.EventID = ".$filters["Event"][$i];
        }
        $filterString .= ")";
    }
    //Payment
    if (!is_null($filters["Payment"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "Payment >= \"".$filters["Payment"][0]."\" AND Payment <= \"".$filters["Payment"][1]."\"";
    }
    //birthdate
    if (!is_null($filters["BirthDate"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "BirthDate >= \"".$filters["BirthDate"][0]."\" AND BirthDate <= \"".$filters["BirthDate"][1]."\"";
    }

    //append to the query
    if ($filterString != "")
    {
        $query .= "\nWHERE ".$filterString;
    }

    //Add the ordering
    $query .= "\nGROUP BY p.ContactInfo_Name";

    //Figure out the sorting
    if (is_null($sortCol))
    {
        //no sorting specified
        $query .= ";";
    }
    else
    {
        //add the sorting column
        $query .= "\nORDER BY ".$sortCol;

        //Ascending or Descending
        if (!is_null($sortDir) and $sortDir == 'd') {
            $query .= " DESC;";
        }
        else
        {
            $query .= " ASC;";
        }
    }

    //-----build the events query-----------------------------
    //query to get a list of events given a participant's name
    $eventsQuery =
        "SELECT e.Title as Event 
        FROM Junc_Event_Partic ep
             JOIN Events e
             ON ep.EventID = e.EventID
        WHERE ep.ContactInfo_Name = ?";
    //Filter events
    if (!is_null($filters["Event"]))
    {
        $eventsQuery .= " AND (";
        for ($i = 0; $i < count($filters["Event"]); $i++) {
            if ($i != 0) $eventsQuery .= " OR ";
            $eventsQuery .= "ep.EventID = ".$filters["Event"][$i];
        }
        $eventsQuery .= ")";
    }
    $eventsQuery .= "\nORDER BY e.Title ";

    //choose sorting direction
    if (!is_null($sortCol) and $sortCol == 3 and !is_null($sortDir) and $sortDir == 'd')
    {
        $eventsQuery .= "DESC;";
    }
    else
    {
        $eventsQuery .= "ASC;";
    }


    //-----connection info-----------------------------
    $host="services1.mcs.sdsmt.edu"; //hostname URL
    $port=3306;						//default port 3306
    $user="s7354704_s19";					//DBMS login username
    $password="97John97";				//DBMS login password
    $dbname="db_7354704_s19";		//Select DB
    /*
    $host = "services1.mcs.sdsmt.edu"; //hostname URL
    $port = 3306;                        //default port 3306
    $user = "s7356506_s19";                    //DBMS login username
    $password = "Keebler1";                //DBMS login password
    $dbname = "db_7356506_s19";        //Select DB
*/

    //-----Connect to MySQL-----------------------------
    $mysqli = new mysqli($host, $user, $password, $dbname, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    //query to get All
    $stmt = $mysqli->prepare($query);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();

    //-----Build the table-----------------------------
    echo '<TABLE Border="1">';

    //Output row headers
    echo "<TR>";
    $c = 1;
    while ($field=$queryResult->fetch_field())
    {
        //get column # for "Events"
        if ($field->name == "Events")
        {
            $eventsCol = $c;
        }

        echo '<TH ';
        if (!is_null($sortCol) and $sortCol === strval($c))
            echo 'class="sortCol" ';
        echo 'onclick="sortBy(this,\'',$c++,'\')">';
        echo "$field->name";
        echo "</TH>";
    }
    echo "<TH></TH>";  //empty column for edit buttons
    echo "</TR>";

    //Output rows if there are any
    if($queryResult->num_rows == 0)
    {
        echo "<TR><TD colspan=\"42\"><center>No Entries found.</center></TD></TR>";
    }
    else
    {
        //Fetch and displays each row of $resultParticipants
        if($queryResult)
        {
            //Connect to MySQL to get event list
            $mysqli = new mysqli($host, $user, $password, $dbname, $port);

            //Check connection error
            if ($mysqli->connect_errno) {
                printf("Connect failed: %s\n", $mysqli->connect_error);
                exit();
            }

            //set up the prepared statement
            $stmt = $mysqli->prepare($eventsQuery);
            $stmt->bind_param("s", $participantName);

            while($row=$queryResult->fetch_row())
            {
                echo "<TR>";
                $participantName = $row[0];
                for ($i=0; $i < $queryResult->field_count; $i++)
                {
                    echo "<TD>";

                    //if events column, load events list
                    if ($i == $eventsCol - 1)
                    {
                        $stmt->execute();

                        //get and use the result
                        $result = $stmt->get_result();
                        if($result->num_rows === 0) echo "<i>None</i>";
                        else
                        {
                            //first event
                            $eventRow = $result->fetch_row();
                            echo '• ',$eventRow[0];

                            //additional events
                            while($eventRow = $result->fetch_row()) {
                                echo "<br>",'• ',$eventRow[0];
                            }
                        }
                    }
                    else
                    {
                        echo $row[$i];
                    }

                    echo "</TD>";
                }

                //X and edit buttons
                echo "<TD><div class=\"editButton\" onclick=\"editPerson('$row[0]')\">&nbsp;</div>
                      <div class=\"deleteButton\" onclick=\"deletePerson('$row[0]')\">X</div></TD>";

                echo "</TR>\n";
            }

            $stmt->close();
            $mysqli->close();
        }
    }
    echo "</TABLE>";
}


/******Output table for staff*****************/
function outputStaffTable($sortCol, $sortDir, $filters)
{
    $eventsCol = -1; //Events column #
    $staffName = "";

    //-----build the main query-----------------------------
    $query ="Select s.ContactInfo_Name as Name, 
                JobTitle as 'Job Title',\n";

    //get max or min event depending on sort
    if (!is_null($sortCol) and $sortCol == 3 and !is_null($sortDir) and $sortDir == 'd')
    {
        $query .= "MAX(e.Title)";
    }
    else
    {
        $query .= "MIN(e.Title)";
    }

    //rest of the query
    $query .=
        " as 'Events',
                ShiftStartTime as 'Shift Start', 
                ShiftEndTime as 'Shift End', 
                CONCAT('$', Salary) as Salary,
                c.EmailAddress as Email, 
                c.PhoneNum as 'Phone #', 
                c.BirthDate as 'Birth Date'
        from Staff s
             LEFT JOIN ContactInfo c
             ON s.ContactInfo_Name = c.Name
             LEFT JOIN Junc_Event_Staff es
             ON s.ContactInfo_Name = es.ContactInfo_Name
             LEFT JOIN Events e
             ON es.EventID = e.EventID";

    //Add the filters
    $filterString = "";
    //name
    if (!is_null($filters["Name"]))
    {
        $filterString .= "LEFT(SUBSTRING_INDEX(Name, ' ', -1), 1) >= \"".$filters["Name"][0]."\" AND LEFT(SUBSTRING_INDEX(Name, ' ', -1), 1) <= \"".$filters["Name"][1]."\"";
    }
    //job title
    if (!is_null($filters["JobTitle"]))
    {
        if ($filterString != "") $filterString .= " AND";

        $filterString .= " (";
        for ($i = 0; $i < count($filters["JobTitle"]); $i++) {
            if ($i != 0) $filterString .= " OR ";
            $filterString .= "JobTitle = \"".$filters["JobTitle"][$i]."\"";
        }
        $filterString .= ")";
    }
    //Events
    if (!is_null($filters["Event"]))
    {
        if ($filterString != "") $filterString .= " AND";

        $filterString .= " (";
        for ($i = 0; $i < count($filters["Event"]); $i++) {
            if ($i != 0) $filterString .= " OR ";
            $filterString .= "es.EventID = ".$filters["Event"][$i];
        }
        $filterString .= ")";
    }
    //ShiftStart
    if (!is_null($filters["ShiftStart"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "ShiftStartTime >= \"".$filters["ShiftStart"][0]."\" AND ShiftStartTime <= \"".$filters["ShiftStart"][1]."\"";
    }
    //ShiftEnd
    if (!is_null($filters["ShiftEnd"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "ShiftEndTime >= \"".$filters["ShiftEnd"][0]."\" AND ShiftEndTime <= \"".$filters["ShiftEnd"][1]."\"";
    }
    //Salary
    if (!is_null($filters["Salary"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "Salary >= \"".$filters["Salary"][0]."\" AND Salary <= \"".$filters["Salary"][1]."\"";
    }
    //birthdate
    if (!is_null($filters["BirthDate"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "BirthDate >= \"".$filters["BirthDate"][0]."\" AND BirthDate <= \"".$filters["BirthDate"][1]."\"";
    }

    //append to the query
    if ($filterString != "")
    {
        $query .= "\nWHERE ".$filterString;
    }

    //Add the ordering
    $query .= "\nGROUP BY s.ContactInfo_Name";

    //Figure out the sorting
    if (is_null($sortCol))
    {
        //no sorting specified
        $query .= ";";
    }
    else
    {
        //add the sorting column
        $query .= "\nORDER BY ".$sortCol;

        //Ascending or Descending
        if (!is_null($sortDir) and $sortDir == 'd') {
            $query .= " DESC;";
        }
        else
        {
            $query .= " ASC;";
        }
    }

    //-----build the events query-----------------------------
    //query to get a list of events given a staff's name
    $eventsQuery =
        "SELECT e.Title as Event 
        FROM Junc_Event_Staff es
             JOIN Events e
             ON es.EventID = e.EventID
        WHERE es.ContactInfo_Name = ?";

    //Filter events
    if (!is_null($filters["Event"]))
    {
        $eventsQuery .= " AND (";
        for ($i = 0; $i < count($filters["Event"]); $i++) {
            if ($i != 0) $eventsQuery .= " OR ";
            $eventsQuery .= "es.EventID = ".$filters["Event"][$i];
        }
        $eventsQuery .= ")";
    }
    $eventsQuery .= "\nORDER BY e.Title ";

    //choose sorting direction
    if (!is_null($sortCol) and $sortCol == 3 and !is_null($sortDir) and $sortDir == 'd')
    {
        $eventsQuery .= "DESC;";
    }
    else
    {
        $eventsQuery .= "ASC;";
    }


    //-----connection info-----------------------------
    $host="services1.mcs.sdsmt.edu"; //hostname URL
    $port=3306;						//default port 3306
    $user="s7354704_s19";					//DBMS login username
    $password="97John97";				//DBMS login password
    $dbname="db_7354704_s19";		//Select DB
    /*
    $host = "services1.mcs.sdsmt.edu"; //hostname URL
    $port = 3306;                        //default port 3306
    $user = "s7356506_s19";                    //DBMS login username
    $password = "Keebler1";                //DBMS login password
    $dbname = "db_7356506_s19";        //Select DB
*/

    //-----Connect to MySQL-----------------------------
    $mysqli = new mysqli($host, $user, $password, $dbname, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    //query to get All
    $stmt = $mysqli->prepare($query);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();

    //-----Build the table-----------------------------
    echo '<TABLE Border="1">';

    //Output row headers
    echo "<TR>";
    $c = 1;
    while ($field=$queryResult->fetch_field())
    {
        //get column # for "Events"
        if ($field->name == "Events")
        {
            $eventsCol = $c;
        }

        echo '<TH ';
        if (!is_null($sortCol) and $sortCol === strval($c))
            echo 'class="sortCol" ';
        echo 'onclick="sortBy(this,\'',$c++,'\')">';
        echo "$field->name";
        echo "</TH>";
    }
    echo "<TH></TH>";  //empty column for edit buttons
    echo "</TR>";

    //Output rows if there are any
    if($queryResult->num_rows == 0)
    {
        echo "<TR><TD colspan=\"42\"><center>No Entries found.</center></TD></TR>";
    }
    else
    {
        //Fetch and displays each row of $resultParticipants
        if($queryResult)
        {
            //Connect to MySQL to get event list
            $mysqli = new mysqli($host, $user, $password, $dbname, $port);

            //Check connection error
            if ($mysqli->connect_errno) {
                printf("Connect failed: %s\n", $mysqli->connect_error);
                exit();
            }

            //set up the prepared statement
            $stmt = $mysqli->prepare($eventsQuery);
            $stmt->bind_param("s", $staffName);

            while($row=$queryResult->fetch_row())
            {
                echo "<TR>";
                $staffName = $row[0];
                for ($i=0; $i < $queryResult->field_count; $i++)
                {
                    echo "<TD>";

                    //if events column, load events list
                    if ($i == $eventsCol - 1)
                    {
                        $stmt->execute();

                        //get and use the result
                        $result = $stmt->get_result();
                        if($result->num_rows === 0) echo "<i>None</i>";
                        else
                        {
                            //first event
                            $eventRow = $result->fetch_row();
                            echo '• ',$eventRow[0];

                            //additional events
                            while($eventRow = $result->fetch_row()) {
                                echo "<br>",'• ',$eventRow[0];
                            }
                        }
                    }
                    else
                    {
                        echo $row[$i];
                    }

                    echo "</TD>";
                }

                //X and edit buttons
                echo "<TD><div class=\"editButton\" onclick=\"editPerson('$row[0]')\">&nbsp;</div>
                      <div class=\"deleteButton\" onclick=\"deletePerson('$row[0]')\">X</div></TD>";

                echo "</TR>\n";
            }

            $stmt->close();
            $mysqli->close();
        }
    }
    echo "</TABLE>";
}

/******Output table for Managers*****************/
function outputManagersTable($sortCol, $sortDir, $filters)
{
    //-----build the main query-----------------------------
    $query =
        "SELECT ManagerName as Name, 
                VendorName as Vendor,
                EmailAddress as Email, 
                PhoneNum as 'Phone #', 
                BirthDate as 'Birth Date'
    FROM vendor 
         JOIN ContactInfo 
         ON ManagerName = Name";

    //Add the filters
    $filterString = "";
    //name
    if (!is_null($filters["Name"]))
    {
        $filterString .= "LEFT(SUBSTRING_INDEX(ManagerName, ' ', -1), 1) >= \"".$filters["Name"][0]."\" AND LEFT(SUBSTRING_INDEX(ManagerName, ' ', -1), 1) <= \"".$filters["Name"][1]."\"";
    }
    //Vendor
    if (!is_null($filters["Vendor"]))
    {
        if ($filterString != "") $filterString .= " AND";

        $filterString .= " (";
        for ($i = 0; $i < count($filters["Vendor"]); $i++) {
            if ($i != 0) $filterString .= " OR ";
            $filterString .= "VendorName = \"".$filters["Vendor"][$i]."\"";
        }
        $filterString .= ")";
    }
    //birthdate
    if (!is_null($filters["BirthDate"]))
    {
        if ($filterString != "") $filterString .= " AND ";

        $filterString .= "BirthDate >= \"".$filters["BirthDate"][0]."\" AND BirthDate <= \"".$filters["BirthDate"][1]."\"";
    }

    //append to the query
    if ($filterString != "")
    {
        $query .= "\nWHERE ".$filterString;
    }

    //Figure out the sorting
    if (is_null($sortCol))
    {
        //no sorting specified
        $query .= ";";
    }
    else
    {
        //add the sorting column
        $query .= "\nORDER BY ".$sortCol;

        //Ascending or Descending
        if (!is_null($sortDir) and $sortDir == 'd') {
            $query .= " DESC;";
        }
        else
        {
            $query .= " ASC;";
        }
    }

    //-----connection info-----------------------------
    $host="services1.mcs.sdsmt.edu"; //hostname URL
    $port=3306;						//default port 3306
    $user="s7354704_s19";					//DBMS login username
    $password="97John97";				//DBMS login password
    $dbname="db_7354704_s19";		//Select DB
    /*
    $host = "services1.mcs.sdsmt.edu"; //hostname URL
    $port = 3306;                        //default port 3306
    $user = "s7356506_s19";                    //DBMS login username
    $password = "Keebler1";                //DBMS login password
    $dbname = "db_7356506_s19";        //Select DB
*/

    //-----Connect to MySQL-----------------------------
    $mysqli = new mysqli($host, $user, $password, $dbname, $port);

    //Check connection error
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }

    //query to get All
    $stmt = $mysqli->prepare($query);
    $stmt->bind_param('ss', $code, $language, $official, $percent);
    $stmt->execute();
    $queryResult = $stmt->get_result();
    $stmt->close();
    $mysqli->close();

    //-----Build the table-----------------------------
    echo '<TABLE Border="1">';

    //Output row headers
    echo "<TR>";
    $c = 1;
    while ($field=$queryResult->fetch_field())
    {
        echo '<TH ';
        if (!is_null($sortCol) and $sortCol === strval($c))
            echo 'class="sortCol" ';
        echo 'onclick="sortBy(this,\'',$c++,'\')">';
        echo "$field->name";
        echo "</TH>";
    }
    echo "<TH></TH>";  //empty column for edit buttons
    echo "</TR>";

    //Output rows if there are any
    if($queryResult->num_rows == 0)
    {
        echo "<TR><TD colspan=\"42\"><center>No Entries found.</center></TD></TR>";
    }
    else
    {
        //Fetch and display each row of table
        if($queryResult)
        {
            while($row=$queryResult->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $queryResult->field_count; $i++)
                {
                    echo "<TD>";
                    echo $row[$i];
                    echo "</TD>";
                }

                //X and edit buttons
                echo "<TD><div class=\"editButton\" onclick=\"editPerson('$row[0]')\">&nbsp;</div>
                      <div class=\"deleteButton\" onclick=\"deletePerson('$row[0]')\">X</div></TD>";

                echo "</TR>\n";
            }
        }
    }
    echo "</TABLE>";
}


/******Handle the REQUEST*****************/
//q - tab name
//s - sort col
//d - direction
//f_name
//f_jobTitle
//f_Event
//f_payment
//f_shiftStart
//f_shiftEnd
//f_salary
//f_vendor
//f_birthDate

//get filters
$filters["Name"] = parseParam($_REQUEST["f_name"]);
$filters["JobTitle"] = parseParam($_REQUEST["f_jobTitle"]);
$filters["Event"] = parseParam($_REQUEST["f_Event"]);
$filters["Payment"] = parseParam($_REQUEST["f_payment"]);
$filters["ShiftStart"] = parseParam($_REQUEST["f_shiftStart"]);
$filters["ShiftEnd"] = parseParam($_REQUEST["f_shiftEnd"]);
$filters["Salary"] = parseParam($_REQUEST["f_salary"]);
$filters["Vendor"] = parseParam($_REQUEST["f_vendor"]);
$filters["BirthDate"] = parseParam($_REQUEST["f_birthDate"]);

//query to get data
switch ($_REQUEST["q"]) {
    case "All":
        //query and output table with all people
        outputAllTable($_REQUEST["s"], $_REQUEST["d"], $filters);
        break;

    case "Participants":
        //query and output participants table
        outputParticipantsTable($_REQUEST["s"], $_REQUEST["d"], $filters);
        break;

    case "Staff":
        //query and output staff table
        outputStaffTable($_REQUEST["s"], $_REQUEST["d"], $filters);
        break;

    case "Managers":
        //query and output managers table
        outputManagersTable($_REQUEST["s"], $_REQUEST["d"], $filters);
        break;

    default:
        echo "Invalid query. Something has gone terribly wrong...";
}
?>
