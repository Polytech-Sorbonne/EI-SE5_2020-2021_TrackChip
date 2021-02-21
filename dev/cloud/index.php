<!DOCTYPE html>

<head>
  <title>TrackChip : Geolocation - LogIn</title>

  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <!--bootstrap styles -->
  <link href="//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">

  <!-- Custom styles for this template -->
  <link href="css/login.css" rel="stylesheet">

  <script src="//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
  <script src="//cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script src="//code.jquery.com/jquery-1.11.1.min.js"></script>

</head>

<body>

  <div class="wrapper fadeInDown">
    <div id="formContent">

      <!-- Login Form -->
      <form method=POST action="/php/login.php" class="needs-validation" novalidate>

        <h2>TrackChip : Authentification</h2>

        <input type="text" id="username" class="fadeIn second" name="username" placeholder="username" required>

        <input type="password" id="password" class="fadeIn third" name="password" placeholder="password" required>
        
        <input type="submit" class="fadeIn fourth" value="Log In">

        <?php
        $auth_failed = $_REQUEST['auth_failed'];
        if ($auth_failed == true) 
        {
          echo "<p>Error : Wrong username or password</p>";
        }
        ?>

      </form>

    </div>
  </div>
</body>