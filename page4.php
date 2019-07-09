<?php
$i1 = shell_exec('cd pkg*/');
$i2 = shell_exec('pwd');
echo "<pre>directory$i2</pre>";
echo "<pre>sh scripts",shell_exec('ls *.sh'),"</pre>";
?>
