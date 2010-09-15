--TEST--
intarray_delete
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

$intarray = intarray_create_from_array(array(1, 2, 3, 4, 5));
intarray_dump($intarray);
echo "\n";

echo intarray_delete($intarray, 2), "\n";
intarray_dump($intarray);
echo "\n";

echo intarray_delete($intarray, 2, false), "\n";
intarray_dump($intarray);
echo "\n";

var_dump(intarray_delete($intarray, -100, false));
intarray_dump($intarray);
echo "\n";

$intarray = intarray_create_from_array(array(1));
echo intarray_delete($intarray, 0, true), "\n";
intarray_dump($intarray);
echo "\n";

var_dump(intarray_delete($intarray, -1, true));
intarray_dump($intarray);
echo "\n";

?>
--EXPECT--
{ 1, 2, 3, 4, 5 }
3
{ 1, 2, 4, 5 }
4
{ 1, 2, 5, 0 }
bool(false)
{ 1, 2, 5, 0 }
1
{ }
bool(false)
{ }
