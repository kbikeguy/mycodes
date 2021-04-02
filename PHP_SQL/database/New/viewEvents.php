<!DOCTYPE html>
<HTML>

<HEAD>
    <TITLE>View Events</TITLE>
</HEAD>

<BODY bgcolor=wheat>

<?php
$startdate = $_POST['startdate'];
$enddate = $_POST['enddate'];
$start = $startdate;
$end = $enddate;

if($startdate > $enddate) 
{
    echo "Start date must be before end date.";
    header("Refresh: 2; manageEvent.php");
}

else{ 
    echo "<CENTER>";

    echo "<H2>Events from $startdate to $enddate</H2>";

$host="services1.mcs.sdsmt.edu"; //hostname URL
$port=3306;						 //default port 3306
$user="s7356506_s19";			 //DBMS login username
$password="Keebler1";			 //DBMS login password
$dbname="db_7356506_s19";		 //Select DB 


/* Connect to MySQL */
$mysqli = new mysqli($host, $user, $password, $dbname, $port);


/* Check connection error*/
if ($mysqli->connect_errno) {
    printf("Connect failed: %s\n", $mysqli->connect_error);
    exit();
}

/* Access the Events table */
$startdate .= " 00:00:00";
$enddate .= " 23:59:59";
$result = $mysqli->prepare("Select * from Events where DateTime >= ? AND DateTime <= ?");
$result->bind_param("ss", $startdate, $enddate);
$result->execute();
$result = $result->get_result();

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
$count = 0;
/* Fetch and displays each row of $result */ 
if($result)
   while($row=$result->fetch_row())
   {
      echo "<TR>";
      for ($i=0; $i < $result->field_count; $i++)
      {
         echo "<TD> $row[$i] </TD>";
         $count++;
      }
      echo "</TR>\n";
   }
echo "</TABLE>";
if (!$count)
   echo "There is currently no events scheduled from $start to $end";


$result->close();






$mysqli->close();
echo "<BR><BR><a href = manageEvent.php>Return to Events Page</a>";
echo "<BR><a href = ../index.html>Return to Main Web Page</a>";
echo "<CENTER>";
}

?>
</BODY>
</HTML>