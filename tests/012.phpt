--TEST--
intarray_union
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

intarray_dump(intarray_union($a, $a));
echo "\n";

$b = intarray_create_from_array(array(1, 2, 3));
intarray_dump($b);
echo "\n";

intarray_dump(intarray_union($a, $b));
echo "\n";

$c = intarray_create_from_array(array(4, 5, 6, 7));
intarray_dump($c);
echo "\n";

intarray_dump(intarray_union($a, $c));
echo "\n";

intarray_dump(intarray_union($c, $a));
echo "\n";

intarray_dump(intarray_union($b, $c));
echo "\n";

$e = intarray_create(0);
intarray_dump(intarray_union($a, $e));
echo "\n";
intarray_dump(intarray_union($e, $a));
echo "\n";
intarray_dump(intarray_union($e, $e));
echo "\n";

?>
--EXPECT--
{ 1, 2, 3, 4, 5 }
{ 1, 2, 3, 4, 5 }
{ 1, 2, 3 }
{ 1, 2, 3, 4, 5 }
{ 4, 5, 6, 7 }
{ 1, 2, 3, 4, 5, 6, 7 }
{ 1, 2, 3, 4, 5, 6, 7 }
{ 1, 2, 3, 4, 5, 6, 7 }
{ 1, 2, 3, 4, 5 }
{ 1, 2, 3, 4, 5 }
{ }
