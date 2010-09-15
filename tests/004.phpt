--TEST--
intarray_add, intarray_insert, intarray_set
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

$intarray = intarray_create_from_array(array(1, 2, 4));
intarray_dump($intarray);
echo "\n";

var_dump(intarray_add($intarray, 3));
intarray_dump($intarray);
echo "\n";

var_dump(intarray_add($intarray, 3));
intarray_dump($intarray);
echo "\n";

$ia = '';
var_dump(intarray_add($ia, 1));
intarray_dump($ia);
echo "\n";


intarray_set($intarray, 0, 5);
intarray_dump($intarray);
echo "\n";

intarray_insert($intarray, 1, 6);
intarray_dump($intarray);
echo "\n";

intarray_insert($intarray, 2, 7, false);
intarray_dump($intarray);
echo "\n";

$intarray2 = intarray_create(0);
intarray_dump($intarray2);
echo "\n";

intarray_insert($intarray2, 0, 1);
intarray_dump($intarray2);
echo "\n";

intarray_insert($intarray2, 1, 2);
intarray_dump($intarray2);
echo "\n";

intarray_insert($intarray2, 2, 3, false);
intarray_dump($intarray2);
echo "\n";

intarray_insert($intarray2, 0, 3);
intarray_dump($intarray2);
echo "\n";

intarray_insert($intarray2, 0, 4, false);
intarray_dump($intarray2);
echo "\n";

?>
--EXPECT--
{ 1, 2, 4 }
int(2)
{ 1, 2, 3, 4 }
int(-1)
{ 1, 2, 3, 4 }
int(0)
{ 1 }
{ 5, 2, 3, 4 }
{ 5, 6, 2, 3, 4 }
{ 5, 6, 7, 2, 3 }
{ }
{ 1 }
{ 1, 2 }
{ 1, 2 }
{ 3, 1, 2 }
{ 4, 3, 1 }
