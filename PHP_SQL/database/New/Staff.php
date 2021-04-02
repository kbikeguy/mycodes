<!DOCTYPE html>
<HTML>
<HEAD>
    <TITLE>
        Video Status
    </TITLE>
</HEAD>
<BODY bgcolor = wheat >
<H2>Display Staff</H2>
<HR height=8>
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


    /* Access the Staff table */
    $result = $mysqli->query("Select * from Staff");

    ?>

<TABLE Border="1">
    <TR>

        <?php
        /* Fetch and display the attribute names */
        while ($field=$result->fetch_field())
        {
            echo "<TH>";
            echo "$field->name";
            echo "</TH>";
        }
        echo "</TR>";

        /* Fetch and displays each row of $result */
        if($result)
            while($row=$result->fetch_row())
            {
                echo "<TR>";
                for ($i=0; $i < $result->field_count; $i++)
                {
                    echo "<TD> $row[$i] </TD>";
                }
                echo "</TR>\n";
            }

        $result->close();
        $mysqli->close();
        ?>

</TABLE>

<BR>
<BR>
<a href = ../index.html>Return to Main Web Page</a>

</BODY>
</HTML>
