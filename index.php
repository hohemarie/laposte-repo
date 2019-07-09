
<?php
$output = shell_exec('ls -lart');
$output2 = shell_exec('cat *');
echo "<pre>$output</pre>";
echo "<pre>$output2</pre>";
echo shell_exec('ls -lart');
?>

