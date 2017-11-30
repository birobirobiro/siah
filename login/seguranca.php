<?php
ob_start();
if(($_SESSION['usuarioId'] == "") || ($_SESSION['usuarioNome'] == "") || ($_SESSION['usuarioNivelAcesso'] == "") || ($_SESSION['usuarioLogin'] == "") || ($_SESSION['usuarioSenha'] == "")){
	unset($_SESSION['usuarioId'],			
		  $_SESSION['usuarioNome'], 		
		  $_SESSION['usuarioNivelAcesso'], 
		  $_SESSION['usuarioLogin'], 		
		  $_SESSION['usuarioSenha']);
	//Mensagem de Erro
	$_SESSION['loginErro'] = "Área restrita para usuários cadastrados";
	
	//Manda o usuário para a tela de login
	header("Location: login.php");
}