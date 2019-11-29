<!DOCTYPE html>
<html>
<head>
   <link rel="stylesheet"  href="CSS/reg.css">

    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js" charset="utf-8"></script>
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

</head>
<body>

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post" name="reg" onsubmit="return validateform()" style="border:1px solid #ccc">
  <div class="container">
    <h1>Sign Up</h1>
    <p>Please fill in this form to create an account.</p>
    <hr>
    <label for="name"><b>Name</b></label>
    <input type="text" class="txtb" placeholder="Enter Name" id="fullname" name="fullname" autofocus required>

    <label for="email"><b>Email</b></label>
    <input type="email" class="txtb" placeholder="Enter Email" id="email" name="email" required><br><br>

    <label for="dob"><b>DOB</b></label><br>
    <input type="date" class="txtb" placeholder="Enter dob" min="1950-01-01" max="2009-01-01" id="dob" value="2002-01-01" name="dob" required><br><br>

    <label for="phone"><b>Phone no</b></label><br>
    <input type="tel" class="txtb" pattern="[0-9]{3}[0-9]{3}[0-9]{4}" placeholder="Enter phone no" id="phone" name="phone" required><br><br>

    <label style="color:white;">Gender</label> <br>
        <select class="custom-select" name="gender" id="gender" style=" margin: 2rempx 0px;">
          <option value="1">Male</option>
          <option value="2">Female</option>
          <option value="3">Others</option>
        </select> <br><br>

    <label for="psw"><b>Password</b></label>
    <input type="password" placeholder="Enter Password" id="password" name="password" required>

    <label for="psw-repeat"><b>Confirm Password</b></label>
    <input type="password" placeholder="Confirm Password" id="cpassword" name="cpassword" required>
    <span><small>password should be between 8 to 15 characters which contain at least one lowercase letter, one uppercase letter, one numeric digit, and one special character</small></span>
    <p>By creating an account you agree to our <a href="#" style="color:aqua;text-decoration: none;">Terms & Privacy</a>.</p>


    <div class="clearfix">
      <button type="button" class="cancelbtn">Cancel</button>
      <button type="submit" id="registe" name="submit" class="signupbtn" >Sign Up</button>  
    </div>
</form>

    <script type="text/javascript">
      $(".txtb input").on("focus",function(){
        $(".txtb input").addClass("focus").val();
      });

      $(".txtb input").on("blur",function(){
        if($(".txtb input").val() == "")
        $(".txtb input").removeClass("focus").val();
      });

      </script>

      <script type="text/javascript">
                
        function validateform(){
          // For name
          var fname =document.forms["reg"]["fullname"].value;
          var x     =document.forms["reg"]["password"].value;
          var y     =document.forms["reg"]["cpassword"].value;
          var pass  =document.forms["reg"]["password"].value;

          var decimal=  /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9])(?!.*\s).{8,15}$/;
          var letters = /^[A-Za-z]+$/;

          if(!(fname.match(letters)))
          {
          
              alert('Please input alphabet characters only');
              return false;
          }
          // for password
          
          if(!(pass.match(decimal)))
          {
              alert('Enter correct format of password');
              return false;
          }

         
          if (x!=y){
              alert("please check the password");
              return false;
          }
        }
      </script>
<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);
if (isset($_POST['submit'])){
    $fullname = $_POST['fullname'];
    $dob = $_POST['dob'];
    $gender = $_POST['gender'];
    $email = $_POST['email'];
    $phone = $_POST['phone'];
    $password =sha1 ($_POST['password']);
    if (!empty($fullname) && !empty($password) && !empty($gender) && !empty($email) && !empty($dob) && !empty($phone)) {
    $host = "localhost";
    $dbUsername = "id11674721_root";
    $dbPassword = "register";
    $dbname = "id11674721_register";
      //create connection
      $conn = new mysqli($host, $dbUsername, $dbPassword, $dbname);
      if (mysqli_connect_error()) {
      die('Connect Error('. mysqli_connect_errno().')'. mysqli_connect_error());
      } else {
      $SELECT = "SELECT email From useraccounts Where email = ? Limit 1";
      $INSERT = "INSERT Into useraccounts (fullname, dob, gender, email, phone, password) values(?, ?, ?, ?, ?, ?)";
      //Prepare statement
      $stmt = $conn->prepare($SELECT);
      $stmt->bind_param("s", $email);
      $stmt->execute();
      $stmt->bind_result($email);
      $stmt->store_result();
      $rnum = $stmt->num_rows;
      if ($rnum==0) {
      $stmt->close();
      $stmt = $conn->prepare($INSERT);
      $stmt->bind_param("ssssss", $fullname, $dob, $gender, $email, $phone, $password);
      $result=$stmt->execute();
      // echo "Successfully registered";
      if ($result)
      {
      // echo "Successfully registered";
        echo ("<SCRIPT LANGUAGE='JavaScript'>
        window.alert('Succesfully Registered')
        window.location.href='index.html';
        </SCRIPT>"); 
      }
      } 
      else {
            echo ("<SCRIPT LANGUAGE='JavaScript'>
            window.alert('Not Registered!!Someone already register using this email ')
            window.location.href='register.php';
            </SCRIPT>");
        
           //echo "Someone already register using this email";
        }
        $stmt->close();
        $conn->close();
        }
    } else {
    echo "All field are required";
    die();
    }
}
?>
  
  

</body>
</html>
