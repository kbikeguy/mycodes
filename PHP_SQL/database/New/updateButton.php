<HTML>
<HEAD>
    <TITLE>Update Event</TITLE>
</HEAD>

<BODY bgcolor = wheat>
<H2><CENTER>Update Event
    </CENTER></H2>
<FORM METHOD="post" action="updateButton.php">
    <P>
    <HR>
    <CENTER>

        <?php

        $host="services1.mcs.sdsmt.edu"; //hostname URL
        $port=3306;						//default port 3306
        $user="s7356506_s19";					//DBMS login username
        $password="Keebler1";				//DBMS login password
        $dbname="db_7356506_s19";		//Select DB
        $message = "<BR><BR>";

        /* Connect to MySQL */
        $mysqli = new mysqli($host, $user, $password, $dbname, $port);

        /* Check connection error*/
        if ($mysqli->connect_errno) {
            printf("Connect failed: %s\n", $mysqli->connect_error);
            exit();
        }

        if (!isset($_POST['id']))
            $id=1;
        else
            $id = $_POST['id'];

        if (isset($_POST['left']))
        {
            // prepare and bind
            $prep = $mysqli->prepare("SELECT * FROM Events WHERE  EventID < ? ORDER BY EventID DESC");
            $prep->bind_param("i",$id);
            $prep->execute();
            $result = $prep->get_result();
            $row=$result->fetch_row();
            if ($row[0] > 0)
            {
                $id       = $row[0];
                $Title    = $row[1];
                $Seats    = $row[2];
                $Price    = $row[3];
                $DateTime = $row[4];
            }
        }

        elseif (isset($_POST['right']))
        {

            // prepare and bind
            $prep = $mysqli->prepare("SELECT * FROM Events WHERE  EventID > ? ORDER BY EventID ASC");
            $prep->bind_param("i",$id);
            $prep->execute();
            $result = $prep->get_result();
            $row=$result->fetch_row();
            if ($row[0] > 0)
            {
                $id       = $row[0];
                $Title    = $row[1];
                $Seats    = $row[2];
                $Price    = $row[3];
                $DateTime = $row[4];
            }
        }

        elseif (isset($_POST['search']))
        {
            $id = 0;
            $Title = "%{$_POST['Title']}%";

            // prepare and bind
            $prep = $mysqli->prepare("SELECT * FROM Events WHERE Title LIKE ? AND EventID > ?");
            $prep->bind_param("si", $Title,$id);
            $prep->execute();
            $result = $prep->get_result();
            $row=$result->fetch_row();
            if ($row[0] > 0)
            {
                $id       = $row[0];
                $Title    = $row[1];
                $Seats    = $row[2];
                $Price    = $row[3];
                $DateTime = $row[4];                
                $message .= "*****Record found*****";
            }
            else {
                $Title= trim($Title, "%");
                $message .= "*****Record not found*****";
            }
        }

        elseif (isset($_POST['update']))
        {
            $id = $_POST['id'];
            $Title = $_POST['Title'];
            $Seats = $_POST['Seats'];
            $Price = $_POST['Price'];
            $DateTime = $_POST['DateTime'];

            // prepare and bind
            $prep = $mysqli->prepare("UPDATE Events SET Title=?, SeatsAvailable=?, SeatPrice=?, DateTime=? WHERE EventID = ?");
            $prep->bind_param("sidsi", $Title, $Seats, $Price, $DateTime, $id);
            $prep->execute();

            if ($prep)
                $message .= "*****Record updated*****";
            else
                $message .= "*****Error updating record*****";
        }

        $id = trim($id);
        $Title = trim($Title);
        $Seats = trim($Seats);
        $Price = trim($Price);
        $DateTime = trim($DateTime);

        //close connections
        $mysqli->close();
        

        ?>

        <BR> Event ID:
        <BR><INPUT TYPE="TEXT" NAME="id"
            <?php echo "VALUE=\"$id\"" ?>>
        <BR>
        <BR> Title:
        <BR><INPUT TYPE="TEXT"  NAME="Title"
            <?php echo "VALUE=\"$Title\"" ?>>
        <BR>
        <BR> Seats Available:
        <BR><INPUT TYPE="number"  min = "1" max = "5000" NAME="Seats"
            <?php echo "VALUE=\"$Seats\"" ?>>
        <BR>
        <BR> Seat Price:
        <BR><INPUT TYPE="number"  min = "0" step="0.01" NAME="Price"
            <?php echo "VALUE=\"$Price\"" ?>>
        <BR>
        <BR> Event Date (yyyy-mm-dd hh:mm):
        <BR><INPUT TYPE="TEXT"  NAME="DateTime"
            <?php echo "VALUE=\"$DateTime\"" ?>>
        <BR>
        <BR>

        <INPUT TYPE="SUBMIT" NAME="left"   VALUE="<">
        <INPUT TYPE="SUBMIT" NAME="right"  VALUE=">">
        <INPUT TYPE="SUBMIT" NAME="search" VALUE="Search Title">

        <BR>
        <BR>
        <INPUT TYPE="SUBMIT" NAME="update" VALUE="Update">

        <?php        
            echo "$message";
        ?>
</FORM>
        <BR>
        <BR>
        <a href = manageEvent.php>Return to Events Page</a>
        <BR>
        <a href = ../index.html>Return to Main Web Page</a>
    </CENTER>

</BODY>
</HTML>
