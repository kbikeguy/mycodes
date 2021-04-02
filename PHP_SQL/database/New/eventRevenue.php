<HTML>
<a name='top'></a>
<HEAD>
    <TITLE>View Revenue</TITLE>
</HEAD>

<BODY bgcolor = wheat>
<H2><CENTER>Revenue Generated
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
        $resultEvent1 = $mysqli->query("Select EventID, Title, DateTime from Events");        
       
        echo "<TABLE Border='1'>";
        echo "<TR>";
        
        /* Fetch and display the Staff attribute names */
        while ($field=$resultEvent1->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultEvent1)
            while($row=$resultEvent1->fetch_row())
            {
                echo "<TR>";
                if($resultEvent1->field_count)
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
<FORM METHOD="post" action="eventRevenue.php">
    <?php
    $found = false;
    echo "<br>Enter event ID<br>";
    echo "<input name='id' type='number'  required min=1>";
    echo "<br><br>";     
    echo "<input type='submit' value = 'Select' name='selection'>";
    echo " <INPUT TYPE='RESET' VALUE='Reset'>";

    if (isset($_POST['selection']))
    { 
        $merchsub = 0;
        $id = $_POST['id'];

        /*
        $resultMerch = $mysqli->prepare("SELECT ProductName, Price FROM Merchandise m JOIN Junc_Event_Merch j
                                                ON m.ProductID = j.ProductID WHERE j.EventID = ?");
        $resultMerch->bind_param("i", $id);
        $resultMerch->execute();
        $resultMerch = $resultMerch->get_result();
        */
        //query Events
        $resultEvent = $mysqli->prepare("SELECT SeatsAvailable, SeatPrice FROM Events WHERE EventID = ?");
        $resultEvent->bind_param("i", $id);
        $resultEvent->execute();
        $resultEvent = $resultEvent->get_result();

        //query Merchandise
        $resultMerch = $mysqli->prepare("SELECT ProductName, QuantitySold, Price FROM Merchandise m JOIN 
                                                Junc_Event_Merch j ON m.ProductID = j.ProductID WHERE j.EventID = ?");
        $resultMerch->bind_param("i", $id);
        $resultMerch->execute();
        $resultMerch = $resultMerch->get_result();

        echo "<BR><BR>";
        echo "<TABLE Border='1'>";
        echo "<TR>";
        echo "<TH> Tickets Sold </TH><TH> Price</TH><TH> Event Subtotal </TH>";
        echo "</TR>";

        //Fetch and displays rows of selected event
        if($resultEvent)
            while($row=$resultEvent->fetch_row())
            {
                $eventsub = (5000 - $row[0]) * $row[1];
                echo "<TR align=\"right\">";
                if($resultEvent->field_count)
                {
                    echo "<TD> ",5000 - $row[0]," </TD><TD> \$$row[1]</TD><TD> \$$eventsub</TD>";
                    $found = true;
                }                
                echo "</TR>\n";
            }
        if(!$found)
        {    
            echo "</TABLE>";            
            echo "<TR>There is no information at this time<BR></TR>";            
        }
        $found = false;        
        echo "</TABLE>";

        echo "<BR>";
        echo "<TABLE Border='1'>";
        echo "<TR>";
        echo "<TH> Product Name </TH><TH> Amount Sold </TH><TH> Price </TH><TH> Product Subtotals </TH>";
        echo "</TR>";

        //Fetch and displays rows of selected merchandise
        if($resultMerch)
            while($row=$resultMerch->fetch_row())
            {
                $merchsub += $row[1] * $row[2];
                echo "<TR>";
                if($resultMerch->field_count)
                {
                    echo "<TD> $row[0] </TD><TD align=\"right\"> $row[1] </TD><TD align=\"right\"> \$$row[2] </TD><TD align=\"right\"> \$", $row[1] * $row[2],"";
                    $found = true;
                }
                echo "</TR>\n";
            }
            if($found)
            echo "<TD><TD><TD> <strong>Merchandise Subtotal</strong> </TD><TD align=\"right\">\$", $merchsub, "</TD>";
        if(!$found)
        {    
            echo "</TABLE>";            
            echo "<TR>There is no information at this time</TR>";            
        }
        $found = false;        
        echo "</TABLE>";

        //DISPLAY TOTAL
        echo "<TABLE>";
        echo "<BR><BR>";
        echo "<TABLE Border='1'>";
        echo "<TR>";
        echo "<TH> Total Revenue </TH>";
        if($resultEvent->field_count && $resultMerch->field_count)
            echo "<TD>\$", $eventsub + $merchsub;
        echo "</TR>";
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
$resultEvent1->close();
$resultEvent->close();
$resultMerch->close();
$mysqli->close();
?>



    </BODY>
</HTML>