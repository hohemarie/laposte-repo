
<?php
$output = shell_exec('ls -lart');
$output2 = shell_exec('cat *');
echo "<pre>$output</pre>";
echo "<pre>$output2</pre>";
$output3 = shell_exec('ls -lart');
echo "<pre>$output3</pre>";
echo "<pre>",shell_exec('ls -lart'),"</pre>";
echo "<a href="page2.php">part 2</a>";
?>

