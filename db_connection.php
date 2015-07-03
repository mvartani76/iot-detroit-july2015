<?php
function Connection(){
   if (!($link=mysql_connect("your_ipserver","your_user","your_pass")))  {
      exit();
   }
   if (!mysql_select_db("your_database",$link)){
      exit();
   }
   return $link;
}
?>