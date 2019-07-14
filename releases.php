<?php
echo "<pre><a href='index.php'>back to home page</a></pre>";
echo "<pre>my 10 latest heroku releases</pre>";
$authtoken = shell_exec('export HEROKU_API_KEY=356352cc-06a0-46ca-83e1-3fc6914e4649 2>&1');
$releases = shell_exec('heroku releases --json -n 10 2>&1');
echo "<pre>$releases</pre>";
echo "<pre><a href='index.php'>back to home page</a></pre>";
?>
