<?php

$servername = "localhost";
$dBUsername = "id21914709_david";
$dBPassword = "DaviK023.";
$dBName = "id21914709_led";

$conn = mysqli_connect($servername, $dBUsername, $dBPassword, $dBName);

if (!$conn) {
    die("Connection failed: ".mysqli_connect_error());
}


if (isset($_POST['toggle_LED'])) {
    $sql = "SELECT * FROM LED_STATUS;";
    $result   = mysqli_query($conn, $sql);
    $row  = mysqli_fetch_assoc($result);
    
    if($row['status'] == 0){
        $update = mysqli_query($conn, "UPDATE LED_STATUS SET status = 1 WHERE id = 1;");        
    }       
    else{
        $update = mysqli_query($conn, "UPDATE LED_STATUS SET status = 0 WHERE id = 1;");        
    }
}
?>

<style>
    #submit_button {
        background-color: #FF5733; /* Rojo */
        color: #FFF;
        font-weight: bold;
        font-size: 20px;
        border-radius: 15px;
        text-align: center;
        padding: 10px 20px;
        cursor: pointer;
        border: none;
        transition: background-color 0.1s; /* Hacemos la transición más rápida */
    }

    #submit_button:active {
        background-color: #ff9999; /* Cambiamos a un color claro cuando se presiona */
    }
</style>


<html>
<head>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.0/jquery.min.js" type="text/javascript"></script>
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
    <div style="text-align: center;">
        <form action="index.php" method="post" id="LED" enctype="multipart/form-data">           
            <input id="submit_button" type="submit" name="toggle_LED" value="Alimentar/Cerrar" />
        </form>
            
        <script type="text/javascript">
        $(document).ready (function () {
            var updater = setTimeout (function () {
                $('div#refresh').load ('index.php', 'update=true');
            }, 1000);
        });
        </script>    
    </div>
</body>
</html>

