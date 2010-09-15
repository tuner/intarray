--TEST--
intarray_symmetric_difference
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

$a = intarray_create_from_array(array(1, 2, 3, 4, 5));
intarray_dump($a);
echo "\n";

intarray_dump(intarray_symmetric_difference($a, $a));
echo "\n";

$b = intarray_create_from_array(array(1, 2, 3));
intarray_dump($b);
echo "\n";

intarray_dump(intarray_symmetric_difference($a, $b));
echo "\n";

$c = intarray_create_from_array(array(4, 5, 6, 7));
intarray_dump($c);
echo "\n";

intarray_dump(intarray_symmetric_difference($a, $c));
echo "\n";

intarray_dump(intarray_symmetric_difference($c, $a));
echo "\n";

intarray_dump(intarray_symmetric_difference($b, $c));
echo "\n";

echo "empty sets\n";
intarray_dump(intarray_symmetric_difference('', $a));
echo "\n";

intarray_dump(intarray_symmetric_difference($a, ''));
echo "\n";

intarray_dump(intarray_symmetric_difference('', ''));
echo "\n";


?>
--EXPECT--
{ 1, 2, 3, 4, 5 }
{ }
{ 1, 2, 3 }
{ 4, 5 }
{ 4, 5, 6, 7 }
{ 1, 2, 3, 6, 7 }
{ 1, 2, 3, 6, 7 }
{ 1, 2, 3, 4, 5, 6, 7 }
empty sets
{ 1, 2, 3, 4, 5 }
{ 1, 2, 3, 4, 5 }
{ }
