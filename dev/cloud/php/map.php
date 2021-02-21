<!DOCTYPE html>
<html>
  <head>
    
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>TrackChip - Geolocation</title>

    <link rel="icon" href="favicone.ico" type="image/x-icon">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="../css/style.css">

    <!-- Google API JS -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>   
    
    <script src="../js/map.js" type="text/javascript" charset="utf-8" async defer></script>
    <script src="../js/datas.js" type="text/javascript" charset="utf-8" async defer></script>

  </head>

  <body>

    <div class="jumbotron text-center">
      <h1>Bienvenue sur votre Application de Tracking !</h1>
      <p>Ici, vous pourrez suivre votre position par rapport à celle de votre tracker !</p>
    </div>

    <div class="container">
      
      <h2>Informations iténaire :</h2>

      <p>Temps    : <span id ="time"></span> </p>
      <p>Distance : <span id ="dist"></span> </p>
      <p>Altitude :  <span id ="arrow"></span> <span id="abs_diff_alt"></span> m</p>

    </div>

    <div class="container" id="map"></div>

    <!-- Async script executes immediately and must be after any DOM elements used in callback. -->
    <script
      src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDMnY8W47H_ztdC4sJjo2Z9_bu2y9-zEPM&callback=initMap&libraries=&v=weekly"
      async
    ></script>

  </body>

</html>