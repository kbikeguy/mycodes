<!DOCTYPE html>
<HTML>

<HEAD>
    <TITLE>Edit Events</TITLE>
</HEAD>

<BODY bgcolor=wheat>
    <CENTER>

    <?php
    $task = $_POST['choice'];
    $host = "services1.mcs.sdsmt.edu"; //hostname URL
    $port = 3306;                        //default port 3306
    $user = "s7356506_s19";                    //DBMS login username
    $password = "Keebler1";                //DBMS login password
    $dbname = "db_7356506_s19";        //Select DB

    /* Connect to MySQL */
    $mysqli = new mysqli($host, $user, $password, $dbname, $port);
    
    //ADD
    if ($task == "add")
    {
        echo "<H2>Add a new Event</H2>";
       //SET VALUES
        echo "<form method = 'post' action = manageEvent.php>";
        echo "Enter event title<br>";
        echo "<input name='title' type='text' required>";
        echo "<br><br>Enter available seating<br>";
        echo "<input name='seats' type='number' required min = '0' max = '5000'>";
        echo "<br><br>Enter the ticket price<br>";
        echo "<input name='price' type='number' step='0.01' required min = '0'>";
        echo "<br><br>Enter the date and time (yyyy-mm-dd hh:mm)<br>";
        echo "<input name='date' type='datetime-local' required>";
        echo "<br><br>";     
        echo "<input type='submit' value = 'Add' name='addButton'>";
        echo " <INPUT TYPE='RESET' VALUE='Reset'>";
        echo "</form>";  
    } 
    //DELETE
    else if ($task == "delete")
    {
        echo "<a name='top'></a>";
        $found = false;
        $resultEvent = $mysqli->query("Select EventID, Title, DateTime from Events");
        echo "<H2>Delete an Event</H2>";
        echo"<TABLE Border='1'>";
        echo"<TR>";

        
        /* Fetch and display the Staff attribute names */
        while ($field=$resultEvent->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultEvent)
            while($row=$resultEvent->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $resultEvent->field_count; $i++)
                {
                    echo "<TD> $row[$i] </TD>";
                    $found = true;
                }
                echo "</TR>\n";
            }
        if(!$found)
        {    
            echo "</TABLE>";            
            echo "<TR>There is no information at this time</TR>";            
        }
            
        echo "</TABLE>";
        echo "<form method = 'post' action = manageEvent.php>";
        echo "<br>Enter event ID<br>";
        echo "<input name='ID' type='number' value = 1 required min=1>";
        echo "<br><br>";     
        echo "<input type='submit' value = 'Delete' name='delButton'>";
        echo " <INPUT TYPE='RESET' VALUE='Reset'>";
        echo "</form>";
        echo "<br><a href='#top'>Back to Top</a>";       
    } 

    //EDIT
    else if ($task == "edit")
    {
        header("Refresh: 0; updateButton.php");
    }






    echo nl2br("\n\n<a href = manageEvent.php>Return to Event page</a>");

    echo nl2br("\n<a href = ../index.html>Return to Main Web Page</a>");

    //close connections
    $mysqli->close();
    ?>


    </CENTER>
</BODY>

</HTML>