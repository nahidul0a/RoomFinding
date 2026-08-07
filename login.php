<?php
session_start();
include "config/database.php";

$message = "";

if (isset($_SESSION['success_msg'])) {
    $message = $_SESSION['success_msg'];
    unset($_SESSION['success_msg']);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email    = trim($_POST['email']);
    $password = $_POST['password'];

    // Retrieve user details using prepared statement
    $stmt = $conn->prepare("SELECT student_id, name, password FROM students WHERE email = ?");
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($row = $result->fetch_assoc()) {
        // Verify hashed password
        if (password_verify($password, $row['password'])) {
            $_SESSION['student_id']   = $row['student_id'];
            $_SESSION['student_name'] = $row['name'];
            header("Location: dashboard.php");
            exit();
        } else {
            $message = "Invalid password!";
        }
    } else {
        $message = "No account found with that email!";
    }
    $stmt->close();
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login - SkillSwap</title>
    <style>
        body { font-family: Arial, sans-serif; background: #f4f6f9; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }
        .card { background: white; padding: 30px; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); width: 320px; }
        h2 { text-align: center; margin-bottom: 20px; color: #333; }
        .input-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input { width: 100%; padding: 8px; box-sizing: border-box; border: 1px solid #ccc; border-radius: 4px; }
        button { width: 100%; padding: 10px; background: #28a745; color: white; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; }
        button:hover { background: #218838; }
        .msg { color: red; margin-bottom: 15px; text-align: center; }
        .link { text-align: center; margin-top: 15px; font-size: 14px; }
    </style>
</head>
<body>
    <div class="card">
        <h2>Student Login</h2>
        <?php if ($message): ?>
            <div class="msg"><?php echo $message; ?></div>
        <?php endif; ?>
        <form action="login.php" method="POST">
            <div class="input-group">
                <label>Email</label>
                <input type="email" name="email" required placeholder="Enter your email">
            </div>
            <div class="input-group">
                <label>Password</label>
                <input type="password" name="password" required placeholder="Enter password">
            </div>
            <button type="submit">Login</button>
        </form>
        <div class="link">
            Don't have an account? <a href="register.php">Register here</a>
        </div>
    </div>
</body>
</html>