<?php

  // Recupere les donnees postee par Sigfox et les insere dans la base de donnee

  echo "On rentre dans sigfox.php\n";

  // Receive Data from SigFox
  if (isset($_POST['data0'], $_POST['data1'], $_POST['data2'], $_POST['data3'], $_POST['data4'], 
            $_POST['data5'], $_POST['data6'], $_POST['data7'], $_POST['data8'], $_POST['data9']))
  {

    for ($i=0; $i < 10; $i++) { 
      
      $data_str = "data" . $i;
      echo "data_str : " . $data_str . "\n";

      $data = (int)$_POST[$data_str];

      $data_hex = dechex($data);

      if ($data < 15) {
        $data_hex = "0" . $data_hex; 
      }

      echo "data_hex : " . $data_hex . "\n";
      $hex_str = $hex_str . $data_hex;
    }

    // $hex_str    = bin2hex($raw_data);
    echo "hex_str : " . $hex_str . "\n";

    if (strlen($hex_str) != 20) 
    {
      echo "ERREUR EUGENE\n";
      return;
    }

    $auth_str   = substr($hex_str, 2, 2);
    echo "auth_str : " . $auth_str . "\n";

    $auth_hex   = hexdec($auth_str);
    echo "auth_hex : " . $auth_hex . "\n";

    // message 1 : WiFi info 1
    if ((int)$auth_hex == 1) 
    {
      echo "AUTH 1\n";

      $puissance1_str = substr($hex_str, 4, 2);
      echo "puissance1_str : " . $puissance1_str . "\n";

      $puissance1     = (int)(hexdec($puissance1_str));
      echo "puissance1 : " . $puissance1 . "\n";

      $mac1_raw       = substr($hex_str, 6, 12);
      echo "mac1_raw : " . $mac1_raw . "\n";

      $altitude_str   = substr($hex_str, 18, 2);
      echo "altitude_str : " . $altitude_str . "\n";

      $altitude       = (int)(hexdec($altitude_str));
      echo "altitude : " . $altitude . "\n";
    }

    // message 2 : WiFi info 2
    elseif ((int)$auth_hex == 2) 
    {
      echo "AUTH 2\n";

      $puissance2_str = substr($hex_str, 4, 2);
      $puissance2     = (int)(hexdec($puissance2_str));

      $mac2_raw       = substr($hex_str, 6, 12);
      echo "mac2_raw : " . $mac2_raw . "\n";

      $altitude_str   = substr($hex_str, 18, 2);
      echo "altitude_str : " . $altitude_str . "\n";

      $altitude       = (int)(hexdec($altitude_str));
      echo "altitude : " . $altitude . "\n";
    }

      // message 3 : GPS Location
    elseif ((int)$auth_hex == 3) 
    {
      echo "AUTH 3\n";

      $altitude_str   = substr($hex_str, 2, 2);
      $altitude       = (int)(hexdec($altitude_str));

      $latitude_str   = substr($hex_str, 4, 8);
      $latitude       = (double)(hexdec($latitude_str));

      $longitude_str  = substr($hex_str, 12, 8);
      $longitude      = (double)(hexdec($longitude_str));
    }
    else
    {
      echo "Error AUTH";
    }
  }
  else
  {
    echo "Error POST";
  }

  // Connection to database
  try
  {
    // system('bash ../database/database.sh');
    $db = new SQLite3('../database/track_chip.db');
  }
  catch(Exception $e)
  { 
    die('Erreur : '.$e->getMessage());
  }

  // message 1 : WiFi info 1
  if ($auth_hex == 1)
  {
    $puissance1 = $puissance1 * (-1);

    for ($i = 0 ; $i < strlen($mac1_raw) ; $i++) 
    {
      $mac1 .= $mac1_raw[$i];

      if (($i % 2) == 1) 
      {
        $mac1 .= '-';
      }
    }

    $mac1 = substr($mac1, 0, -1);

    echo 'puissance1 : ' . $puissance1 . "\n";
    echo 'mac1 : ' . $mac1 . "\n";

    $res = $db->query('INSERT INTO WifiEndpoint (mac, puissance, device_id) VALUES ("' . $mac1 . '", ' . $puissance1 . ', 1);');
  }

  // message 2 : WiFi info 2
  elseif ($auth_hex == 2)
  {
    $puissance2 = $puissance2 * (-1);

    for ($i = 0 ; $i < strlen($mac2_raw) ; $i++) 
    {
      $mac2 .= $mac2_raw[$i];

      if (($i % 2) == 1) 
      {
        $mac2 .= '-';
      }
    }

    // delete last elem of string
    $mac2 = substr($mac2, 0, -1);

    echo 'puissance2 : ' . $puissance2 . "\n";
    echo 'mac2 : ' . $mac2 . "\n";

    $res = $db->query('INSERT INTO WifiEndpoint (mac, puissance, device_id) VALUES ("' . $mac2 . '", ' . $puissance2 . ', 1);');
  }

  // message 3 : GPS Location
  elseif ($auth_hex == 3) 
  {
    // scalling SigFox data
    $latitude   = ($latitude / 100000) - 180;
    $longitude  = ($longitude / 100000) - 90;

    echo "altitude : "  . $altitude . "\n";
    echo "latitude : "  . $latitude . "\n";
    echo "longitude : " . $longitude . "\n";
    
    // Insert in to database
    $res = $db->query('INSERT INTO Location(altitude, latitude, longitude, device_id) VALUES ('.$altitude.', '.$latitude.', ' .$longitude.', 1);');

    return;
  }

  else {
    echo "Error AUTH";
  }


  $response = $db->query('SELECT * FROM WifiEndpoint WHERE id=2;');
  $res = $response->fetchArray(1);

  echo "res (check if 2 WiFis Endpoints in database) :\n";
  print_r($res);

  // request to API Google
  if (empty($res) == false) 
  {  

    echo "There's at least 2 lines in WiFI Endpoints\n";

    $response       = $db->query('SELECT * FROM WifiEndpoint WHERE (id >= (SELECT MAX(id) FROM WifiEndpoint) - 1);');
    $wifi_endpoints = array();

    while ($res = $response->fetchArray(1))
    {
      array_push($wifi_endpoints, $res);
    }

    echo "WiFi Messages Treatments\n";

    // Request to WiFi Location API (Google)
    $url = "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyDMnY8W47H_ztdC4sJjo2Z9_bu2y9-zEPM";

    // Data: Json file
    $data = array (
            'wifiAccessPoints' => 
            array (
              0 => 
              array (
                'macAddress'      => ($wifi_endpoints[0])['mac'],
                'signalStrength'  => ($wifi_endpoints[0])['puissance']
              ),
              1 => 
              array (
                'macAddress'      => ($wifi_endpoints[1])['mac'],
                'signalStrength'  => ($wifi_endpoints[1])['puissance']
              ),
            ),
          );
    $postdata = json_encode($data);

    echo "postdata : " . $postdata . "\n";

    $curl = curl_init();
    
    curl_setopt($curl, CURLOPT_POST, 1);
    curl_setopt($curl, CURLOPT_POSTFIELDS, $postdata);
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));

    $result = curl_exec($curl);

    curl_close($curl); 

    // Retrieve lat and lng from API response
    $result = json_decode($result);

    echo "result : \n";
    print_r($result);

    $array = json_decode(json_encode($result), true);

    echo "test lat : \n";
    print_r($array['location']['lat']);
    echo "\n";
    $latitude = $array['location']['lat'];

    echo "test lng : \n";
    print_r($array['location']['lng']);
    echo "\n";
    $longitude = $array['location']['lng'];

    // Insert them in database
    $res = $db->query('INSERT INTO Location(altitude, latitude, longitude, device_id) VALUES ('.$altitude.', '.$latitude.', ' .$longitude.', 1);');
  }

?>