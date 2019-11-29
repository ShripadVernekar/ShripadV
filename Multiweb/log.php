<?php

// session_start();
$error = ''; 
if (isset($_POST['submit'])) {
	if (empty($_POST['user_email']) || empty($_POST['password'])) {
		$error = "Email or Password is invalid";
	    echo ("<SCRIPT LANGUAGE='JavaScript'>
        alert('$error') 
        </SCRIPT>");
	}
else{
    // session_start(); // Starting Session
	$email = $_POST['user_email'];
	$password = sha1($_POST['password']);
	// mysqli_connection
	$conn = mysqli_connect("localhost", "id11674721_root", "register", "id11674721_register");
	// verification
	$query = "SELECT email, password from useraccounts where email=? AND password=? LIMIT 1";
	$stmt = $conn->prepare($query);
	$stmt->bind_param("ss", $email, $password);
	$stmt->execute();
	$stmt->bind_result($email, $password);
	$stmt->store_result();
	if($stmt->fetch()){ 
		$_SESSION['login_user'] = $email; 
		echo "<script>window.location.href='categories.html'</script>"; 
	}
	else{
		echo ("<SCRIPT LANGUAGE='JavaScript'>
        alert('Invalid!!') 
        </SCRIPT>");
	}
	mysqli_close($conn); 
	}
}
?>