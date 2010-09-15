--TEST--
intarray_slice
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

intarray_dump(intarray_slice($intarray, 6, 3));
echo "\n";

intarray_dump(intarray_slice($intarray, 1, 3));
echo "\n";

intarray_dump(intarray_slice($intarray, 1, 6));
echo "\n";

intarray_dump(intarray_slice($intarray, 1, -2));
echo "\n";

intarray_dump(intarray_slice($intarray, -6, 2));
echo "\n";

intarray_dump(intarray_slice($intarray, -2, 2));
echo "\n";

intarray_dump(intarray_slice($intarray, 2, -10));
echo "\n";

intarray_dump(intarray_slice($intarray, 2));
echo "\n";

echo "empty sets\n";
intarray_dump(intarray_slice('', 0));
echo "\n";

intarray_dump(intarray_slice('', 0, 1));
echo "\n";

intarray_dump(intarray_slice('', -1, 1));
echo "\n";

?>
--EXPECT--
{ 1, 2, 3, 4, 5 }
{ }
{ 2, 3, 4 }
{ 2, 3, 4, 5 }
{ 2, 3 }
{ 1, 2 }
{ 4, 5 }
{ }
{ 3, 4, 5 }
empty sets
{ }
{ }
{ }
