<?php
   	include("db_connection.php");
   	$link=Connection();
	$Sql="INSERT INTO sensordata (temp1,photo1) VALUES ('".$_GET["temp1"]."', '".$_GET["photo1"]."')";     

	if (!mysqli_query($link, $Sql)) {
    	echo "Error: " . $Sql . "<br>" . mysqli_error($link);
	}

   	header("Location: displaysensordata.php");
?>