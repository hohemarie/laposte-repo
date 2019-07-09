<?php
// set the default timezone to use. Available since PHP 5.1
date_default_timezone_set('UTC');
ob_start();
echo "<pre>",shell_exec('ls -lart'),"</pre>";

$install1 = shell_exec("rm -rf *.tar.gz");
echo "<pre>1$install1</pre>";
$install2 = shell_exec("unzip pkg-oss-db9aa7353d86.zip");
echo "<pre>1$install2</pre>";
echo "<pre>",shell_exec('ls -lart'),"</pre>";
$install3 = shell_exec("rm -rf *.zip");
echo "<pre>1$install3</pre>";

echo "<pre>",shell_exec('ls -lart'),"</pre>";
$htmlStr = ob_get_contents();
ob_end_clean();
$fileName = date("YmdHis"),".txt";
//shell_exec("touch"+$fileName);                             // 20010310;
//$output = `touch {$fileName} -v`;
echo "<pre>filename$fileName</pre>";
$handle = fopen($fileName, 'w') or die('Cannot open file:  '.$fileName); //implicitly creates file
$current = file_get_contents($fileName);
$current .= $htmlStr;
file_put_contents($fileName, $htmlStr);
fclose($handle);
echo "<pre>",shell_exec('ls -lart'),"</pre>";
?>

<a href="output.txt">unzip report</a>
