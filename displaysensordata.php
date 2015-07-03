<html>
<head>
   <title>Data of Sensor</title>
</head>
<body>
<h1>Data from the temperature and moisture sensors</h1>
<form action="addsensordata.php" method="get">
<TABLE>
<tr>
   <td>Temperature 1</td>
   <td><input type="text" name="temp1" size="20" maxlength="30"></td>
</tr>
<tr>
   <td>Moisture 1</td>
   <td><input type="text" name="moi1" size="20" maxlength="30"></td>
</tr>
</TABLE>
<input type="submit" name="accion" value="Grabar">
</FORM>
<hr>
<?php
   include("db_connection.php");
   $link=Connection();
   $result=mysql_query("select * from tempmoi order by id desc",$link);
?>
<table border="1" cellspacing="1" cellpadding="1">
      <tr>
         <td>&nbsp;Temperature 1&nbsp;</td>
         <td>&nbsp;Moisture 1&nbsp;</td>
       </tr>
<?php     
   while($row = mysql_fetch_array($result)) {
printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td></tr>", $row["temp1"], $row["moi1"]);
   }
   mysql_free_result($result);
?>
</table>
</body>
</html>