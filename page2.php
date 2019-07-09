
<?php
echo "<pre>nginx: Linux packages</pre>";
$install1 = shell_exec('sudo apt install curl gnupg2 ca-certificates lsb-release');
echo "<pre>$install1</pre>";
$install2 = shell_exec(`echo "deb http://nginx.org/packages/ubuntu ${lsb_release -cs} nginx" \
    | sudo tee /etc/apt/sources.list.d/nginx.list`);
echo "<pre>$install2</pre>";
$install3 = shell_exec('curl -fsSL https://nginx.org/keys/nginx_signing.key | sudo apt-key add -');
echo "<pre>$install3</pre>";
$install4 = shell_exec('sudo apt-key fingerprint ABF5BD827BD9BF62');
echo "<pre>$install4</pre>";
$install5 = shell_exec('sudo apt update');
echo "<pre>$install5</pre>";
echo "<pre>",exec('sudo apt install nginx'),"</pre>";
?>
