
<?php
echo "<pre>nginx: Linux packages</pre>";
echo "<pre>",shell_exec('sudo apt install curl gnupg2 ca-certificates lsb-release'),"</pre>";
echo "<pre>",shell_exec('echo "deb http://nginx.org/packages/ubuntu `lsb_release -cs` nginx"'),"</pre>";
echo "<pre>",shell_exec('sudo tee /etc/apt/sources.list.d/nginx.list
'),"</pre>";
echo "<pre>",shell_exec('echo "deb http://nginx.org/packages/mainline/ubuntu `lsb_release -cs` nginx"'),"</pre>";
echo "<pre>",shell_exec('sudo tee /etc/apt/sources.list.d/nginx.list'),"</pre>";
echo "<pre>",shell_exec('curl -fsSL https://nginx.org/keys/nginx_signing.key | sudo apt-key add -'),"</pre>";
echo "<pre>",shell_exec('sudo apt-key fingerprint ABF5BD827BD9BF62'),"</pre>";
echo "<pre>",shell_exec('sudo apt update'),"</pre>";
echo "<pre>",shell_exec('sudo apt install nginx'),"</pre>";


?>
