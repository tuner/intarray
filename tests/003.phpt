--TEST--
intarray_dump intarray_to_json
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

$intarray = intarray_create_from_array(array(1, 2, 3));

intarray_dump($intarray);
echo "\n";

echo intarray_to_json($intarray), "\n";

$empty = intarray_create(0);
intarray_dump($empty);
echo "\n";
echo intarray_to_json($empty), "\n";
?>
--EXPECT--
{ 1, 2, 3 }
[1,2,3]
{ }
[]
