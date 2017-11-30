<?php
error_reporting (E_ALL & ~ E_NOTICE & ~ E_DEPRECATED);
$conectar = mysql_connect("localhost","root","") or die ("Erro na conexão");
mysql_select_db("tcc")or die ("Base não encontrada");
?>