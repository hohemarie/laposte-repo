
<?php
$output = shell_exec('ls -lart');
$output2 = shell_exec('cat Procfile && sudo cat .profile.d && sudo cat .composer && sudo cat .heroku');
echo "<pre>$output</pre>";
echo "<pre>$output2</pre>";
?>

