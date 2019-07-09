<?php
$i1 = shell_exec('cd pkg-oss-db9aa7353d86');
$i2 = shell_exec('pwd');
echo "<pre>$i2</pre>";
echo "<pre>",shell_exec('ls *.sh'),"</pre>";
?>
