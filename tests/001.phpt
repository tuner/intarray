--TEST--
Check for intarray presence
--SKIPIF--
<?php if (!extension_loaded("intarray")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php 
echo "intarray extension is available";
ob_start();
phpinfo(INFO_MODULES);
ob_end_clean();
?>
--EXPECT--
intarray extension is available
