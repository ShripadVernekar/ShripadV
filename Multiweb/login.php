<?php
  include('log.php');
//   include('sess.php');
  if (isset($_SESSION['login_user'])){
    echo "<script>window.location.href=index.html</script>";
  }
?>

<!DOCTYPE html>
<html>
<head>
  <link rel="stylesheet" type="text/css" href="CSS/lin2.css">
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js" charset="utf-8"></script>
</head>
<body>

<form action="" method="POST" style="border:1px solid #ccc">
  <div class="container">
    <h1>Sign in </h1>

    <hr>

    <label for="email"><b>Email</b></label>
    <input type="text" placeholder="Enter Email" class="txtb" name="user_email" required>

    <label for="psw"><b>Password</b></label>
    <input type="password" placeholder="Enter Password" class="txtb" name="password" required>

    <div class="clearfix">
        <button type="button" name="cancel" class="cancelbtn">Cancel</button>
        <button type="submit" name="submit" class="signinbtn">Sign in</button>
      </div>
    <p style="color:yellow">Forgot your password?<a href="#" style="color:aqua">get help</a></p>
    <hr>
    <p style="color:yellow" >Dont have an account?<a href="register.php" style="color:aqua">register here</a></p>

    
    
  </div>
</form>

<!-- window.location.href='.php'; -->

      <script type="text/javascript">
      $(".txtb input").on("focus",function(){
        $(this).addClass("focus");
      });

      $(".txtb input").on("blur",function(){
        if($(this).val() == "")
        $(this).removeClass("focus");
      });

      </script>
    

  </body>
</html>
