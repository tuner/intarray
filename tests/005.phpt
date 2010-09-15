--TEST--
intarray_sort
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

intarray_insert($intarray, 0, 4);
intarray_dump($intarray);
echo "\n";

$intarray = intarray_sort($intarray);
intarray_dump($intarray);
echo "\n"; 

intarray_insert($intarray, 0, 4);
intarray_dump($intarray);
echo "\n";

$intarray = intarray_sort($intarray);
intarray_dump($intarray);
echo "\n"; 

intarray_insert($intarray, 0, 3);
intarray_dump($intarray);
echo "\n";

$intarray = intarray_sort($intarray, true);
intarray_dump($intarray);
echo "\n"; 

$intarray = intarray_sort('');
intarray_dump($intarray);
echo "\n";

?>
--EXPECT--
{ 1, 2, 3 }
{ 4, 1, 2, 3 }
{ 1, 2, 3, 4 }
{ 4, 1, 2, 3, 4 }
{ 1, 2, 3, 4, 4 }
{ 3, 1, 2, 3, 4, 4 }
{ 1, 2, 3, 4 }
{ }
