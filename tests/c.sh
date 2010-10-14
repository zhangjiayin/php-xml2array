phpize 
export CFLAGS="-lxml2 -I/usr/include/libxml2"
./configure
make 
sudo make install
php test.php
phpize --clean
