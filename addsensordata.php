<?php
   	include("db_connection.php");
   	$link=Connection();
	$Sql="insert into sensordata (temp1,photo1)  values ('".$_GET["temp1"]."', '".$_GET["photo1"]."')";     
   	mysql_query($Sql,$link);
   	header("Location: displaysensordata.php");
?>