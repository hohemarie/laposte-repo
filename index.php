
<?php
$output = shell_exec('ls -lart');
$output2 = shell_exec('cat Procfile; cat .profile.d; cat .composer; cat .heroku');
echo "<pre>$output</pre>";
echo "<pre>$output2</pre>";
?>

