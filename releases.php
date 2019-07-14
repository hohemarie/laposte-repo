<?php
echo "<pre><a href='index.php'>back to home page</a></pre>";
echo "<pre>my 10 latest heroku releases</pre>";
$releases = shell_exec('heroku releases --json -n 10');
echo "<pre>$releases</pre>";
echo "<pre><a href='index.php'>back to home page</a></pre>";
?>
