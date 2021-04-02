<!DOCTYPE html>
<HTML>

<HEAD>
    <TITLE>Events</TITLE>
</HEAD>

<BODY bgcolor=wheat>
    <H2>
        <CENTER>Display events in the selected range
        </CENTER>
    </H2>
    <FORM METHOD="post" action="viewEvents.php">
        <P>
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
                if(isset($_POST['addButton']))
                {        
                    $title = $_POST['title'];        
                    $seats = $_POST['seats'];        
                    $price = $_POST['price'];        
                    $date = $_POST['date'];

                    //prepare statements
                    $result = $mysqli->prepare("INSERT INTO Events (Title, SeatsAvailable, SeatPrice, DateTime) VALUES (?, ?, ?, ?)");
                    $result->bind_param("sids", $title, $seats, $price, $date);
                    $result->execute();
                    /*
                    $query = "insert into Events (Title, SeatsAvailable, SeatPrice, DateTime) values ('$title','$seats','$price','$date')";        
                    $result = $mysqli->query($query);
                    */
                    if ($result)
                        $message = "*****Record added*****";
                    else
                        $message = "*****Error adding record*****";                        
                }
                if(isset($_POST['delButton']))
                {           
                    $ID = $_POST['ID'];
                    $result = $mysqli->prepare("DELETE FROM Events WHERE EventID=?");
                    $result->bind_param("i", $ID);
                    $result->execute();

                    if ($result)
                        $message = "*****Record deleted*****";
                    else
                        $message = "*****Error deleting record*****";                    
                } 

                ?>
                <!SETUP BEFORE AND AFTER DROP DOWN>
           
                <!SELECT DATE>
                Enter start date:
                <input name="startdate" type="date" required>
                Enter end date:
                <input name="enddate" type="date" required>
                <br><br>
            
                <input type="submit">
                <INPUT TYPE="RESET"
                VALUE="Reset fields">
                <P>
        </form>   
<BR>
        <H2>
        <CENTER>Add, delete, or edit an event
        </CENTER>
    </H2>
    <FORM METHOD="post" action="updateEvents.php">
        <P>
            <CENTER>
                
                <!SETUP EDIT DROP DOWN>
           
                <!SELECT DATE>
                <select name="choice">
                <option value="add">Add</option>
                <option value="delete">Delete</option>
                <option value="edit">Edit</option>
                </select>
            
                <input type="submit" value="Submit">
                <?php
                echo "<br>".$message;
                ?>
               
        <P>
    </form>
    <H2>
        <BR>View revenue for a specific event
    </H2>
    <FORM ACTION="eventRevenue.php">
        <input type="submit" value="View revenues">
    </FORM>

    <H2>
    <BR>View merchandise for a specific event
    </H2>
     <FORM ACTION="eventMerch.php">
         <input type="submit" value="View merchandise">
     </FORM>

    <BR>
<BR>   
    <a href=../index.html>Return to Main Web Page</a>
    </CENTER>
</BODY>
<HTML>