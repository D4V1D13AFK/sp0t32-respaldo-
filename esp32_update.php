<?php
$servername = "localhost";
$dBUsername = "id21914709_david";
$dBPassword = "DaviK023.";
$dBName = "id21914709_led";
$conn = mysqli_connect($servername, $dBUsername, $dBPassword, $dBName);
if (!$conn) {
	die("Connection failed: ".mysqli_connect_error());
}

//Read the database
if (isset($_POST['check_LED_STATUS'])) {
	$led_id = $_POST['check_LED_STATUS'];	
	$sql = "SELECT * FROM LED_STATUS WHERE id = '$led_id';";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	if($row['status'] == 0){
		echo "LED_is_off";
	}
	else{
		echo "LED_is_on";
	}	
}	

//Update the database
if (isset($_POST['toggle_LED'])) {
	$led_id = $_POST['toggle_LED'];	
	$sql = "SELECT * FROM LED_STATUS WHERE id = '$led_id';";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	if($row['status'] == 0){
		$update = mysqli_query($conn, "UPDATE LED_STATUS SET status = 1 WHERE id = 1;");
		echo "LED_is_on";
	}
	else{
		$update = mysqli_query($conn, "UPDATE LED_STATUS SET status = 0 WHERE id = 1;");
		echo "LED_is_off";
	}	
}	
?>