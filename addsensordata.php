<?php
   	include("db_connection.php");
   	$link=Connection();
	$Sql="insert into tempmoi (temp1,moi1)  values ('".$_GET["temp1"]."', '".$_GET["moi1"]."')";     
   	mysql_query($Sql,$link);
   	header("Location: displaysensordata.php");
?>