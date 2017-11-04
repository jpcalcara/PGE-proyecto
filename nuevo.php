<?php
$servername = "localhost";
$username = "id2893737_megabeat7";
$password = "qwerty777";
$dbname = "DBusuarios"
//$dbname = "id2893737_usuarios"; por si quiero usar la DB de hosting

// Creo la conexion
$conn = new mysqli($servername, $username, $password, $dbname);

//verifico la conexion
if ($conn->connect_error) {
    die("Conexion Fallida: " . $conn->connect_error);
} 
echo "Conexion Exitosa";


// Creamos la DB

$sql = "CREATE TABLE usuarios (
id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY, 
name VARCHAR(30) NOT NULL,
surname VARCHAR(30) NOT NULL,
telephone VARCHAR(30),
email VARCHAR(50),
user VARCHAR(15),
password VARCHAR(15),
)";

if ($conn->query($sql) === TRUE) {
    echo "Se creo la Tabla ok";
} else {
    echo "Error al crear la Tabla: " . $conn->error;
}

// Insertamos datos en la DB
$sql = "INSERT INTO usuarios (name, surname, telephone, email, user, password)
VALUES ('', '', '', '', '', '')";

//si quiero cargar multiples consultas utilizo  $conn->multi_query($sql)
if ($conn->query($sql) === TRUE) {
    //$last_id = $conn->insert_id;
    //echo "ID del ultimo registro ingresado: " . $last_id;
	
    echo "Registro exitoso";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}


$sql = "SELECT * FROM usuarios";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
   
    while($row = $result->fetch_assoc()) {
        echo "<br> id: ". $row["id"]. " - Name: ". $row["firstname"]. " " . $row["lastname"] . "<br>";
    }
} else {
    echo "0 results";
}

$conn->close();//cerramos la conexion de la DB
?>
