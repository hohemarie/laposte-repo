<?php
echo "<pre>",shell_exec('ls -lart'),"</pre>";
echo "<pre>",shell_exec('sudo ls pkg-oss-db9aa7353d86.tar.gz'),"</pre>";
echo "<pre>",shell_exec('sudo ls pkg-oss-db9aa7353d86.tar'),"</pre>";
echo "<pre>",shell_exec('sudo gunzip pkg-oss-db9aa7353d86.tar.gz'),"</pre>";
echo "<pre>",shell_exec('sudo ls pkg-oss-db9aa7353d86.tar'),"</pre>";
echo "<pre>",shell_exec('sudo ls pkg-oss-db9aa7353d86.tar.gz'),"</pre>";
echo "<pre>",shell_exec('tar -xvf pkg-oss-db9aa7353d86.tar'),"</pre>";
echo "<pre>",shell_exec('sudo ls pkg-oss-db9aa7353d86.tar'),"</pre>";
echo "<pre>",shell_exec('ls -lart'),"</pre>";

$install1 = shell_exec("sudo ls pkg-oss-db9aa7353d86.tar.gz");
echo "<pre>1$install1</pre>";

?>
