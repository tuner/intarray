--TEST--
intarray_intersect
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

intarray_dump(intarray_intersect($a, $a));
echo "\n";

$b = intarray_create_from_array(array(1, 2, 3));
intarray_dump($b);
echo "\n";

intarray_dump(intarray_intersect($a, $b));
echo "\n";

intarray_dump(intarray_intersect($b, $a));
echo "\n";

$c = intarray_create_from_array(array(4, 5, 6, 7));
intarray_dump($c);
echo "\n";

intarray_dump(intarray_intersect($a, $c));
echo "\n";

intarray_dump(intarray_intersect($c, $a));
echo "\n";

intarray_dump(intarray_intersect($b, $c));
echo "\n";

echo "empty tests\n";
$empty = '';
intarray_dump(intarray_intersect($empty, $empty));
echo "\n";

intarray_dump(intarray_intersect($a, $empty));
echo "\n";

intarray_dump(intarray_intersect($empty, $a));
echo "\n";

?>
--EXPECT--
{ 1, 2, 3, 4, 5 }
{ 1, 2, 3, 4, 5 }
{ 1, 2, 3 }
{ 1, 2, 3 }
{ 1, 2, 3 }
{ 4, 5, 6, 7 }
{ 4, 5 }
{ 4, 5 }
{ }
empty tests
{ }
{ }
{ }
