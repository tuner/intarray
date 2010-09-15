--TEST--
intarray_create_from_array 2
--SKIPIF--
<?php if (!extension_loaded("intarray")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php 
if (!extension_loaded('intarray')) {
	dl('intarray.' . PHP_SHLIB_SUFFIX);
}

/* empty */
$a = intarray_create_from_array(array());
$a = intarray_create_from_array(array(0=>1, 887=>1, 838919=>1, 16763718=>1));
$a = intarray_create_from_array(array_keys(array(0=>1, 887=>1, 838919=>1, 16763718=>1)));

?>
--EXPECT--
