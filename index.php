
<?php
$output = shell_exec('ls -lart');
$output2 = shell_exec('ls -l');
echo "<pre>$output</pre>";
echo "<pre>$output2</pre>";
?>

