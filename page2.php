
<?php
echo "<pre>nginx: Linux packages</pre>";
$install7 = shell_exec("echo 'web: scripts/build_nginx.sh' >> Procfile");
$install1 = shell_exec('sudo apt install curl gnupg2 ca-certificates lsb-release');
echo "<pre>1$install1$install7</pre>";
$install2 = shell_exec(`echo "deb http://nginx.org/packages/ubuntu 'lsb_release -cs' nginx" | sudo tee /etc/apt/sources.list.d/nginx.list`);
echo "<pre>2$install2</pre>";
$install3 = shell_exec('curl -fsSL https://nginx.org/keys/nginx_signing.key | sudo apt-key add -');
echo "<pre>3$install3</pre>";
$install4 = shell_exec('sudo apt-key fingerprint ABF5BD827BD9BF62');
echo "<pre>4$install4</pre>";
$install5 = shell_exec('sudo apt update');
echo "<pre>5$install5</pre>";
$install6 = shell_exec('sudo apt install nginx');
echo "<pre>6",$install6,"</pre>";
?>
