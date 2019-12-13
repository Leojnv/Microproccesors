<?php

require 'vendor/autoload.php';

$email = new \SendGrid\Mail\Mail();
$email->setFrom("from@example.com", "sender");
$email->setSubject("[NUEVO] Data desde ESP");
$email->addTo("example@example.com", "destiny1");
$apiKey = 'API_KEY_PROVIDED_BY_SENDGRID';

// Keep this API Key value to be compatible with the ESP code provided in the project page. If you change this value, the ESP sketch needs to match
$api_key_value = "KCN17TZrrs";
$api_key = $value1 = $value2 = $value3 = $value4 = $value5 = $value5_msg = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $value1 = test_input($_POST["value1"]);
        $value2 = test_input($_POST["value2"]);
        $value3 = test_input($_POST["value3"]);
        $value4 = test_input($_POST["value4"]);
        $value5 = test_input($_POST["value5"]);
        
        // Email message         
        switch($value5){
            case 0:
                $value5_msg = " directa";
            break;
            case 1:
                $value5_msg = " abundante";
            break;
            case 2:
                $value5_msg = " presente";
            break;
            case 3:
                $value5_msg = " tenue";
            break;
            case 4:
                $value5_msg = " ausente";
            break;
            default:
                $value5_msg = " ERROR DE LECTURA";
            break;
        }
        
        $email->addContent(
            "text/html","<strong>Lectura de los sensores:</strong><br /><br /> ".
                        " Temperatura del aire: ". $value1 . "ºC <br /> " .
                        " Humedad del aire: ". $value2 . "% <br /> " .
                        " Temperatura del suelo: ". $value3 . "ºC <br /> " .
                        " Humedad del suelo: ". $value4 . "% <br /> " .
                        " Luz solar ". $value5_msg . " <br /> "                    
        );
        // send email with SendGrid
        $sendgrid = new \SendGrid($apiKey);
        try {
            $response = $sendgrid->send($email);
            print $response->statusCode() . "\n";
            print_r($response->headers());
            print $response->body() . "\n";
        } catch (Exception $e) {
            echo 'Caught exception: ',  $e->getMessage(), "\n";
        }
        
        
        echo "Email sent";
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
