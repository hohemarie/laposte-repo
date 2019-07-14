<?php
$cattext = shell_exec('cat test.txt');
$cattext2 = utf8_encode($cattext);
echo "<pre>$cattext</pre>";
?>
