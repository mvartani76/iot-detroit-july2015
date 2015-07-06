<html>
   <head>
      <title>Data of Sensor</title>
   </head>
   <body>
      <h1>Data from the temperature and photo sensors</h1>
         <form action="addsensordata.php" method="get">
         <table>
            <tr>
               <td>Temperature 1</td>
               <td><input type="text" name="temp1" size="20" maxlength="30"></td>
            </tr>
            <tr>
               <td>Photo Sensor 1</td>
               <td><input type="text" name="photo1" size="20" maxlength="30"></td>
            </tr>
         </table>
         <input type="submit" name="record_button" value="Record">
         </FORM>
         <hr>
      <?php
         include("db_connection.php");
         $link=Connection();
         $result=mysqli_query($link,"select * from sensordata order by id desc");
      ?>
      <table border="1" cellspacing="1" cellpadding="1">
         <tr>
            <td>&nbsp;Temperature 1&nbsp;</td>
            <td>&nbsp;Photo Sensor 1&nbsp;</td>
          </tr>
         <?php     
            while($row = mysqli_fetch_array($result)) {
               printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td></tr>", $row["temp1"], $row["photo1"]);
            }
            mysqli_free_result($result);
         ?>
      </table>
   </body>
</html>