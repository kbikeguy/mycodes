<!DOCTYPE html>
<HTML>
<HEAD>
    <TITLE>
        All Data
    </TITLE>
</HEAD>
<a name="top"></a>
<BODY bgcolor = wheat >
<center>
        <P><STRONG><U><FONT size=7>**** All Data ****</FONT></U
        ></STRONG></P>
<center>
<HR height=8>
<br><br>
<H2>Display Staff</H2>
<P>

    <?php

    $host="services1.mcs.sdsmt.edu"; //hostname URL
    $port=3306;						//default port 3306
    $user="s7356506_s19";					//DBMS login username
    $password="Keebler1";				//DBMS login password
    $dbname="db_7356506_s19";		//Select DB


    /* Connect to MySQL */
    $mysqli = new mysqli($host, $user, $password, $dbname, $port);


    /* Check connection error*/
    if ($mysqli->connect_errno) {
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
    }




    // Access the Staff table
    $resultStaff = $mysqli->prepare("Select * from Staff");
    $resultStaff->execute();
    $resultStaff = $resultStaff->get_result();

    //Access the Events table
    $resultEvent = $mysqli->prepare("Select * from Events");
    $resultEvent->execute();
    $resultEvent = $resultEvent->get_result();

    //Access the vendor table
    $resultVendor = $mysqli->prepare("Select * from vendor");
    $resultVendor->execute();
    $resultVendor = $resultVendor->get_result();

    //Access the ContactInfo table
    $resultContactInfo = $mysqli->prepare("Select * from ContactInfo");
    $resultContactInfo->execute();
    $resultContactInfo = $resultContactInfo->get_result();

    //Access the Participants table
    $resultParticipants = $mysqli->prepare("Select * from Participants");
    $resultParticipants->execute();
    $resultParticipants = $resultParticipants->get_result();

    //Access the Merchandise table
    $resultMerchandise = $mysqli->prepare("Select * from Merchandise");
    $resultMerchandise->execute();
    $resultMerchandise = $resultMerchandise->get_result();

    //Access the Junc_Event_Staff table
    $resultJunc_Event_Staff = $mysqli->prepare("Select * from Junc_Event_Staff");
    $resultJunc_Event_Staff->execute();
    $resultJunc_Event_Staff = $resultJunc_Event_Staff->get_result();

    //Access the Junc_Event_Merch table
    $resultJunc_Event_Merch = $mysqli->prepare("Select * from Junc_Event_Merch");
    $resultJunc_Event_Merch->execute();
    $resultJunc_Event_Merch = $resultJunc_Event_Merch->get_result();

    //Access the table
    $resultJunc_Event_Partic = $mysqli->prepare("Select * from Junc_Event_Partic");
    $resultJunc_Event_Partic->execute();
    $resultJunc_Event_Partic = $resultJunc_Event_Partic->get_result();

    $found = false;
    
    ?>
<!PRINT THE STAFF TABLE>
<TABLE Border="1">
    <TR>

        <?php
        /* Fetch and display the Staff attribute names */
        while ($field=$resultStaff->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultStaff)
            while($row=$resultStaff->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $resultStaff->field_count; $i++)
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
        $found = false;
        ?>    
</TABLE>

<!PRINT THE EVENTS TABLE>
<br><br>
<H2>Display Events</H2>
<TABLE Border="1">
    <TR>

        <?php
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
        $found = false;
        ?>    
</TABLE>

<!PRINT THE VENDER TABLE>
<br><br>
<H2>Display Venders</H2>
<TABLE Border="1">
    <TR>

        <?php
        /* Fetch and display the Staff attribute names */
        while ($field=$resultVendor->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultVendor)
            while($row=$resultVendor->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $resultVendor->field_count; $i++)
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
        $found = false;
        ?>    
</TABLE>

<!PRINT THE CONTACTINFO TABLE>
<br><br>
<H2>Display ContactInfo</H2>
<TABLE Border="1">
    <TR>

        <?php
        /* Fetch and display the Staff attribute names */
        while ($field=$resultContactInfo->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultContactInfo)
            while($row=$resultContactInfo->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $resultContactInfo->field_count; $i++)
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
        $found = false;
        ?>    
</TABLE>

<!PRINT THE PARTICIPANTS TABLE>
<br><br>
<H2>Display Participants</H2>
<TABLE Border="1">
    <TR>

        <?php
        /* Fetch and display the Staff attribute names */
        while ($field=$resultParticipants->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultParticipants)
            while($row=$resultParticipants->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $resultParticipants->field_count; $i++)
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
        $found = false;
        ?>    
</TABLE>

<!PRINT THE MERCHANDISE TABLE>
<br><br>
<H2>Display Merchandise</H2>
<TABLE Border="1">
    <TR>

        <?php
        /* Fetch and display the Staff attribute names */
        while ($field=$resultMerchandise->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $resultStaff */
        if($resultMerchandise)
            while($row=$resultMerchandise->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $resultMerchandise->field_count; $i++)
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
        $found = false;
        ?>    
</TABLE>

    <!PRINT THE Junc_Event_Staff TABLE>
    <br><br>
    <H2>Display Junc_Event_Staff</H2>
    <TABLE Border="1">
        <TR>

            <?php
            /* Fetch and display the Staff attribute names */
            while ($field=$resultJunc_Event_Staff->fetch_field())
            {
                echo "<TH>";
                echo "$field->name";
                echo "</TH>";
            }
            echo "</TR>";

            /* Fetch and displays each row of $resultStaff */
            if($resultJunc_Event_Staff)
                while($row=$resultJunc_Event_Staff->fetch_row())
                {
                    echo "<TR>";
                    for ($i=0; $i < $resultJunc_Event_Staff->field_count; $i++)
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
            $found = false;
            ?>
    </TABLE>

    <!PRINT THE Junc_Event_Merch TABLE>
    <br><br>
    <H2>Display Junc_Event_Merch</H2>
    <TABLE Border="1">
        <TR>

            <?php
            /* Fetch and display the Staff attribute names */
            while ($field=$resultJunc_Event_Merch->fetch_field())
            {
                echo "<TH>";
                echo "$field->name";
                echo "</TH>";
            }
            echo "</TR>";

            /* Fetch and displays each row of $resultStaff */
            if($resultJunc_Event_Merch)
                while($row=$resultJunc_Event_Merch->fetch_row())
                {
                    echo "<TR>";
                    for ($i=0; $i < $resultJunc_Event_Merch->field_count; $i++)
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
            $found = false;
            ?>
    </TABLE>

    <!PRINT THE Junc_Event_Partic TABLE>
    <br><br>
    <H2>Display Junc_Event_Partic</H2>
    <TABLE Border="1">
        <TR>

            <?php
            /* Fetch and display the Staff attribute names */
            while ($field=$resultJunc_Event_Partic->fetch_field())
            {
                echo "<TH>";
                echo "$field->name";
                echo "</TH>";
            }
            echo "</TR>";

            /* Fetch and displays each row of $resultStaff */
            if($resultJunc_Event_Partic)
                while($row=$resultJunc_Event_Partic->fetch_row())
                {
                    echo "<TR>";
                    for ($i=0; $i < $resultJunc_Event_Partic->field_count; $i++)
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
            $found = false;
            ?>
    </TABLE>


<a href="#top">Back to Top</a>
<BR>
<a href ='../index.html'>Return to Main Web Page</a>


<BR>
<BR>
<?php
//close connections    
    $resultStaff->close();
    $resultEvent->close();
    $resultVendor->close();
    $resultContactInfo->close();
    $resultParticipants->close();
    $resultMerchandise->close();
    $resultJunc_Event_Partic->close();
    $resultJunc_Event_Merch->close();
    $resultJunc_Event_Staff->close();
    $mysqli->close();
?>
<BR>
<BR>

</BODY>
</HTML>
