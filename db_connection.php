<?php
function Connection(){
   if (!($link=mysqli_connect("37.60.225.35","iotdetro_dbusr","password")))  {
      exit();
   }
   if (!mysql_select_db("iotdetro_arduino-iot-test-july2015",$link)){
      exit();
   }
   return $link;
}
?>