<HTML>
<a name='top'></a>
<HEAD>
    <TITLE>View Merchandise</TITLE>
</HEAD>

<BODY bgcolor = wheat>
<H2><CENTER>Merchandise of an event
    </CENTER></H2>
    <CENTER>
        <?php
        error_reporting(E_ALL);
        $host = "services1.mcs.sdsmt.edu"; //hostname URL
        $port = 3306;                        //default port 3306
        $user = "s7356506_s19";                    //DBMS login username
        $password = "Keebler1";                //DBMS login password
        $dbname = "db_7356506_s19";        //Select DB

        /* Connect to MySQL */
        $mysqli = new mysqli($host, $user, $password, $dbname, $port);

        /* Check connection error*/
        if ($mysqli->connect_errno) {
            printf("Connect failed: %s\n", $mysqli->connect_error);
            exit();
        }

        $found = false;
        $resultEvent = $mysqli->query("Select EventID, Title, DateTime from Events");        
       
        echo "<TABLE Border='1'>";
        echo "<TR>";
        
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
                if($resultEvent->field_count)
                {
                    echo "<TD align=\"center\"> $row[0] </TD><TD> $row[1] </TD><TD> $row[2]</TD>";
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
        ?>
<!START OF QUERY AND RESULTS TABLE>
<FORM METHOD="post" action="eventMerch.php">
    <?php
    $found = false;
    echo "<br>Enter event ID<br>";
    echo "<input name='id' type='number'  required min=1>";
    echo "<br><br>";     
    echo "<input type='submit' value = 'Select' name='selection'>";
    echo " <INPUT TYPE='RESET' VALUE='Reset'>";

    if (isset($_POST['selection']))
    {         
        $id = $_POST['id'];

        $resultMerch = $mysqli->prepare("SELECT ProductName, Price FROM Merchandise m JOIN Junc_Event_Merch j 
                                                ON m.ProductID = j.ProductID WHERE j.EventID = ?");
        $resultMerch->bind_param("i", $id);
        $resultMerch->execute();
        $resultMerch = $resultMerch->get_result();

        echo "<BR><BR>";
        echo "<TABLE Border='1'>";
        echo "<H2> Available Merchandise <H2>";
        echo "<TR>";
        echo "<TH> Product name </TH><TH> Price </TH>";
        echo "</TR>";

        
        //Fetch and displays rows of selected merchandise
        if($resultMerch)
            while($row=$resultMerch->fetch_row())
            {
                $merchsub += $row[1] * $row[2];
                echo "<TR>";
                if($resultMerch->field_count)
                {
                    echo "<TD> $row[0] </TD><TD align=\"right\">\$$row[1]</TD>";
                    $found = true;
                }
                echo "</TR>\n";
            }
        if(!$found)
        {    
            echo "</TABLE>";            
            echo "<TR>There is no information at this time</TR>";            
        }
        $found = false;        
        echo "</TABLE>";        
    }
?>

</FORM>

<BR>
<BR>
<a href="#top">Back to Top</a>
<BR>
<BR>
<a href = manageEvent.php>Return to Events Page</a>
<BR>
<a href ='../index.html'>Return to Main Web Page</a>
</CENTER>

<?php
//CLOSE CONNECTIONS
$resultEvent->close();
$resultMerch->close();
$mysqli->close();
?>


    </BODY>
</HTML>